/*
# clusterLogUtil: $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLogUtil
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#undef DEBUG
#undef DEBUG2
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "../inc/Cluster.h"

/* Transform */
//
static int 
__clusterLog2ShrinkedNumberGet(clusterLog2OneRecord* tmp, int n)
{
	int shrinkedN;

	shrinkedN = n;
	tmp = tmp->prev;
	while(NULL!=tmp) {
		if(tmp->N<n) {
			shrinkedN--;
		}
		tmp = tmp->prev; 
	}
	return shrinkedN;
}

clusterLog*
clusterLogTransformLog2ToLog(clusterLog2* cluster2, clusterTypeInteger lastNum, int mode)
{
	clusterLog* cluster = NULL;
	int clusterNum;
	int connectionNum;
	clusterLog2OneRecord* tmpRecord;
	int n, m;
	int minn, minm;
	int prevN, prevM;
	double unknownMax = 1e30;

	clusterNum = lastNum;
	cluster2->current = cluster2->bottom;
	while(NULL!=cluster2->current) {
		clusterNum++;
		cluster2->current->clusterNumber = clusterNum;
		cluster2->current = cluster2->current->prev;
	}
	DEBUGPRINT1("clusterNum: %d\n", clusterNum);

	cluster = (clusterLog*)memoryAllocate(sizeof(clusterLog), "clusterLog");  
	cluster->current = cluster->top = cluster->bottom = NULL;
	cluster2->current = cluster2->top;
	prevN = prevM = cluster2->current->clusterNumber; 
	while(NULL!=cluster2->current) {
		minn = __clusterLog2ShrinkedNumberGet(cluster2->current, cluster2->current->N);
		minm = __clusterLog2ShrinkedNumberGet(cluster2->current, cluster2->current->M);
#ifdef DEBUG2
		DEBUGPRINT4("%d %d %d %d\n", minn, minm, cluster2->current->N, cluster2->current->M);
#endif
		for(n=0; n<cluster2->current->clusterNumber; n++) {
			for(m=0; m<n; m++) {
				if(mode!=0 && (minn!=n || minm!=m)) {
				} else {
					if(NULL==cluster->current) {           /* Top */
				   		cluster->current = clusterLogInitOneRecord(cluster->current, 0);
					   	cluster->current->prev = NULL;
					   	cluster->current->next = NULL;
					    cluster->top           = cluster->current;
					    cluster->bottom        = cluster->current;
				    } else {
			          	cluster->current->next = clusterLogInitOneRecord(cluster->current->next, 0);
		            	cluster->current->next->prev   = cluster->current;
            			cluster->current->next->next   = NULL;
            			cluster->current = cluster->current->next;
            			cluster->bottom  = cluster->current;
        			}

					cluster->current->N = n;  
					cluster->current->M = m; 
					cluster->current->prevN = prevN; 
					cluster->current->prevM = prevM; 
				
					if(minn==n && minm==m) {
						cluster->current->distance = cluster2->current->distance; 
					} else {
						cluster->current->distance = unknownMax;	
					}
#ifdef DEBUG2
					DEBUGPRINT5("%d %d %d %d %g\n", n, m, minn, minm, cluster->current->distance);
#endif
				}	
			}
		}
		prevN = minn; 
		prevM = minm; 
		cluster2->current = cluster2->current->next;
	}
	return cluster;
}


/* Set */
void
clusterLogClusterInformationSet(clusterLog* cluster, clusterTypeInteger lastNum, int mode)
{
	DEBUGPRINT1("lastNum; %d \n", lastNum);
    if(0<lastNum && cluster->bottom != NULL) {
		if(NULL!=cluster->bottom->next) {
			fprintf(stderr, "Something wrong. The bottom pointer is not at the bottom line\n");
		}
		switch(mode) {
			case 0: 
        		clusterLogClusterNumberSet(cluster->bottom, lastNum, 0);
				break;
			case 1:
        		clusterLogClusterNumberSetForLog2(cluster, lastNum, 0);
				break;
		}
    } else {
		DEBUGPRINT1("in  clusterLogClusterInformationSet: lastNum %d\n", lastNum);
		switch(mode) {
			case 0: 
        		clusterLogClusterNumberSet2(cluster, 0, 0);
				break;
			case 1:
        		clusterLogClusterNumberSetForLog2(cluster, lastNum, 0);
				break;
		}
    }
    clusterLogBelowLayerPointerSet(cluster, 0);
    clusterLogClusterSizeSet(cluster, 0);
}

/*
	Set the number of clusters: n
		Therefore, the log lines are nC2 in size.

	bottom: Last Number
	Attention!!: Recursive Call
*/

/* From Bottom */
void 
clusterLogClusterNumberSet(clusterLogOneRecord* bottom, clusterTypeInteger lastClusterNumber, int mode)
{
	clusterLogOneRecord* tmp;
	int num;
	int n;
	int n2;
	int i;

	DEBUGPRINT1("Start NumberSet %d\n", lastClusterNumber);
	n   = lastClusterNumber; /* Given number of this cluster */
	num = (n+1)*n/2;         /* Expected max of log line number among this cluster */
	
	tmp = bottom;
	for(i=0; i<num; i++) {
		if(tmp!=NULL) {	
			tmp->clusterNumber = n;

			if(tmp->prev!=NULL) { /* If the previous line exists, */ 
				if(tmp->prev->prevN != tmp->prevN
				 ||tmp->prev->prevM != tmp->prevM) {
				 	/* The previous line is the upper layer of this cluster */
					tmp = tmp->prev;
					break;
				}
			} else {
				if(i!=num-1) {
					fprintf(stderr, "No Log previous data line for this layer (%d), while %d < %d \n", n, i, num);
				}
				return;
			}
			tmp = tmp->prev;
		} else {
			fprintf(stderr, "No log previous data line, while %d < %d \n", i, num);
			return;
		}
	}
	if(tmp!=NULL) {
		if(tmp->next->prevN == tmp->prevN && tmp->next->prevM == tmp->prevM) {
			fprintf(stderr, "A given lastClusterNumber(%d) is inconsistent with LogFile: N %d M %d\n", n, tmp->N, tmp->M);
		}
	}

	DEBUGPRINT1("End NumberSet: %d\n", tmp->clusterNumber);
	/* to the next larger cluster */
	n2 = n + 1;
	clusterLogClusterNumberSet(tmp, n2, mode);
}

/* From Top */
void
clusterLogClusterNumberSet2(clusterLog* in, clusterTypeInteger clusterNumber, int mode)
{
	clusterLogOneRecord* cluster;	

	cluster = in->top;
	while(1) {
		if(cluster==NULL) {
			return;
		}
		if(clusterNumber<=0) {
			if(cluster->prevN==cluster->prevM) { /* First turn */ 
				clusterNumber = cluster->prevN;
			} else {
				fprintf(stderr, "Unknown cluster Number because previousClusterNumber ==  %d: prevN : %d prevM %d\n", clusterNumber, cluster->prevN, cluster->prevM);
				return;	
			}
		} 
		cluster->clusterNumber = clusterNumber;
		DEBUGPRINT1("ClusterNumber in Set2 %d\n", clusterNumber);
		if(cluster->next==NULL) {
			return;
		} else {
			if(cluster->next->prevN == cluster->prevN && cluster->next->prevM == cluster->prevM) {
				cluster = cluster->next;
			} else {
				DEBUGPRINT1("clusterNumber down: %d\n",clusterNumber)	
				cluster = cluster->next;
				clusterNumber =  clusterNumber - 1;
			}
		}
	}
}

void
clusterLogClusterNumberSetForLog2(clusterLog* in, clusterTypeInteger clusterNumber, int mode)
{
	clusterLogOneRecord* cluster;	

	DEBUGPRINT1("Start: %x\n", in->top);
	cluster = in->top;
	while(1) {
		if(cluster==NULL) {
			return;
		}
		if(clusterNumber<=0) {
			if(cluster->prevN==cluster->prevM) { /* First turn */ 
				clusterNumber = cluster->prevN;
			} else {
				fprintf(stderr, "Unknown cluster Number because previousClusterNumber ==  %d: prevN : %d prevM %d\n", clusterNumber, cluster->prevN, cluster->prevM);
				return;	
			}
		} 
		cluster->clusterNumber = clusterNumber;
		DEBUGPRINT1("ClusterNumber in Set2 %d\n", clusterNumber);
		if(cluster->next==NULL) {
			return;
		} else {
			DEBUGPRINT1("clusterNumber down: %d\n",clusterNumber)	
			cluster = cluster->next;
			clusterNumber =  clusterNumber - 1;
		}
	}
}

/*
	clusterLogGetDistance	

*/
clusterLogOneRecord*
clusterLogGetDistance(clusterLog* in, clusterTypeInteger N, clusterTypeInteger M, clusterTypeInteger clusterNum, clusterTypeReal* data)
{
	clusterLogOneRecord* first;
	clusterLogOneRecord* cluster;
	clusterLogOneRecord* old=NULL;
	clusterLogOneRecord* old2=NULL;

	first = in->current;
	cluster = in->current;
	while(1) {
		if(clusterNum<=0) {
			*data = -1;
			return first;
		}
		if(cluster==NULL) {
			*data = -1;
			return first;
		} 
		if(clusterNum==cluster->clusterNumber
		 && N==cluster->N
		 && M==cluster->M) {
			*data = cluster->distance;
			return cluster;
		}

		/* List Order Check : whether the expected line exists in the previous line or the next line  */
		if(clusterNum<=cluster->clusterNumber) {
			if(old ==cluster->next 
			 &&old2==cluster) {
			 	*data = -1;
				return first;
			}	
			old2 = old;
			old  = cluster;
			cluster = cluster->next;
		} else {
			if(old ==cluster->prev
			 &&old2==cluster) {
			 	*data = -1;
				return first;
			}	
			old2 = old;
			old  = cluster;
			cluster = cluster->prev;
		}
	}
	*data = -1;
	return cluster;
}

/*
	Set the pointers related to a below cluster layer
*/
void
clusterLogBelowLayerPointerSet0(clusterLogOneRecord* tmp, int mode)
{
	static clusterLogOneRecord*    start = NULL;
	static clusterLogOneRecord*    end   = NULL;
	static clusterLogOneRecord*    root  = NULL;
	clusterLogOneRecord* tmp2;

	int num;

	if(tmp->next!=NULL) { /* If a current line is last */
		num = tmp->next->clusterNumber; 
	} else {
		num = 0; 
	}
	if(num!=tmp->clusterNumber) { 
		/* Entering a below cluster layer */
		start = tmp;
		end   = NULL; 
		root  = NULL; 
		for(tmp2 = tmp; tmp2 != NULL; tmp2 = tmp2->prev) { 
			if(tmp2->clusterNumber==tmp->clusterNumber+1) { /* in below layer */
				if(tmp2->N==tmp->prevN && tmp2->M==tmp->prevM) { 
					root = tmp2;
				} 
			}
			if(tmp2->clusterNumber==tmp->clusterNumber+2) {
				end = tmp2->next;
				break;
			}
		}
	} 
	tmp->belowLayer      = root; 
	tmp->belowLayerStart = start; 
	tmp->belowLayerEnd   = end; 
}

void
clusterLogUpperLayerPointerSet0(clusterLogOneRecord* tmp, int mode)
{
	if(NULL==tmp->belowLayer) {
		return;
	}
	tmp->belowLayer->upperLayer = tmp;
	clusterLogUpperLayerPointerSet0(tmp->belowLayer, mode);	
}

/*	
	clusterLogBelowLayerNandMOriginalSet
		Set originalN and originalM in the below layer 
*/
void
clusterLogBelowLayerNandMOriginalSet(clusterLogOneRecord* tmp, int mode)
{
	if(tmp->N < MAX(tmp->prevN,tmp->prevM)) { 
		tmp->originalN = tmp->N;
	} else {
		tmp->originalN = tmp->N + 1; 
	}
	if(tmp->M < MAX(tmp->prevN,tmp->prevM)) { 
		tmp->originalM = tmp->M;
	} else {
		tmp->originalM = tmp->M + 1; 
	}
}

clusterLogOneRecord*
clusterLogBelowLayerNPointerGet(clusterLogOneRecord* tmp, int N, int mode)
{
	if(NULL==tmp->belowLayer) {
		return NULL;
	}
#ifdef DEBUG2
	DEBUGPRINT5("N: %d M: %d belowLayer N: %d M: %d : input N %d\n",tmp->N, tmp->M, tmp->belowLayer->N, tmp->belowLayer->M, N);
#endif
	if(MAX(tmp->belowLayer->N,tmp->belowLayer->M) <= N) {
#ifdef DEBUG2
		DEBUGPRINT4("Next below Layer %d -> %d because below->N %d below->M %d\n", N, N+1, tmp->belowLayer->N, tmp->belowLayer->M);
#endif
		N = N + 1;
	} else {
#ifdef DEBUG2
		DEBUGPRINT2("Next below Layer %d -> %d\n", N, N)
#endif
	}

	if(N == MIN(tmp->belowLayer->N,tmp->belowLayer->M)) {
		return tmp->belowLayer;
	} else {
		return clusterLogBelowLayerNPointerGet(tmp->belowLayer, N, mode);
	}
}

clusterLogOneRecord*
clusterLogBelowLayerMPointerGet(clusterLogOneRecord* tmp, int M, int mode)
{
	if(NULL==tmp->belowLayer) {
		return NULL;
	}
	if(MAX(tmp->belowLayer->N,tmp->belowLayer->M) <= M) {
		M = M + 1;
	}
	if(M == MIN(tmp->belowLayer->N,tmp->belowLayer->M)) {
		return tmp->belowLayer;	
	} else {
		return clusterLogBelowLayerMPointerGet(tmp->belowLayer, M, mode);
	}
}

void
clusterLogBelowLayerNandMPointerSet0(clusterLogOneRecord* tmp, int mode)
{
	DEBUGPRINT2("N: %d M: %d\n", tmp->N, tmp->M);
	tmp->belowLayerForN = clusterLogBelowLayerNPointerGet(tmp, tmp->N, mode);
	if(NULL!=tmp->belowLayerForN) {
		tmp->belowLayerForN->upperLayer = tmp;
	}
	DEBUGPRINT3("N: %d M: %d ForN %x\n", tmp->N, tmp->M, tmp->belowLayerForN);
	tmp->belowLayerForM = clusterLogBelowLayerMPointerGet(tmp, tmp->M, mode);
	if(NULL!=tmp->belowLayerForM) {
		tmp->belowLayerForM->upperLayer = tmp;
	}
}


int
clusterLogFirstNGet(clusterLogOneRecord* cluster, int N) 
{
	if(cluster->belowLayer==NULL) {
		return N;
	} 
	if(MAX(cluster->belowLayer->N,cluster->belowLayer->M)<=N) {
		N = N + 1;
	}
	return clusterLogFirstNGet(cluster->belowLayer, N);
}

int
clusterLogFirstMGet(clusterLogOneRecord* cluster, int M) 
{
	if(cluster->belowLayer==NULL) {
		return M;
	} 
	if(MAX(cluster->belowLayer->N,cluster->belowLayer->M)<=M) {
		M = M + 1;
	}
	return clusterLogFirstMGet(cluster->belowLayer, M);
}

void
clusterLogBelowLayerPointerSet(clusterLog * cluster, int mode)
{
	clusterLogOneRecord* tmp = NULL;
	int previousN;
	int previousM;

	previousN=0;
	previousM=0;
  	for(tmp = cluster->bottom; tmp != NULL; tmp = tmp->prev) {
		clusterLogBelowLayerPointerSet0(tmp, 0); 
	}
	
	clusterLogUpperLayerPointerSet0(cluster->bottom, 0); 
	
  	for(tmp = cluster->bottom; tmp != NULL; tmp = tmp->prev) {
		tmp->firstN = clusterLogFirstNGet(tmp, tmp->N);
		tmp->firstM = clusterLogFirstMGet(tmp, tmp->M);
	}

	/* Set original N and M in the below layer */
  	for(tmp = cluster->bottom; tmp != NULL; tmp = tmp->prev) {
		clusterLogBelowLayerNandMOriginalSet(tmp, mode); 
	}

  	for(tmp = cluster->bottom; tmp != NULL; tmp = tmp->prev) {
		clusterLogBelowLayerNandMPointerSet0(tmp, mode); 
	}
}

/**************************************
*	Related to the cluster size
***************************************/
/*
	clusterLogClusterSizeGet
		Get the cluster size, which is the number to be averaged.

	Attention:: You must set belowLayer Pointers before this call.


   N-node

*/
int
clusterLogClusterSizeGet(clusterLogOneRecord* cluster, int mode)
{
	int counter;

	if(cluster->belowLayerForN!=NULL && cluster->belowLayerForM!=NULL) {
		counter = cluster->belowLayerForN->clusterSize + cluster->belowLayerForM->clusterSize;
	} else if(cluster->belowLayerForN!=NULL &&  cluster->belowLayerForM==NULL) {
		counter = cluster->belowLayerForN->clusterSize + 1;
	} else if(cluster->belowLayerForN==NULL &&  cluster->belowLayerForM!=NULL) {
		counter = cluster->belowLayerForM->clusterSize + 1;
	} else {
	 	counter = 1 + 1;
	}

	return counter;
}

/*
	clusterLogClusterSizeSet(clusterLog* cluster, int mode)
		Set the cluster size

*/
void
clusterLogClusterSizeSet(clusterLog* cluster, int mode)
{
	clusterLogOneRecord* tmp;

	for(tmp=cluster->top; tmp!=NULL; tmp=tmp->next) {
		//DEBUGPRINT4("%d %d-> %d %d \n", tmp->N, tmp->M, tmp->prevN, tmp->prevM);
		tmp->clusterSize = clusterLogClusterSizeGet(tmp, mode); 
#undef DEBUG
#ifdef DEBUG
		if(2<tmp->clusterSize) {
			DEBUGPRINT5("%d %d-> %d %d Size %d\n", tmp->N, tmp->M, tmp->prevN, tmp->prevM, tmp->clusterSize);
		}
#endif
	}
}

/********************************************
*	Related To the Bottom of clusterLog Lines
*********************************************/

/*
	clusterLogBottomGet
		return the bottom pointer of clusterLog 
*/

clusterLogOneRecord*
clusterLogBottomGet(clusterLog* cluster, int mode)
{
	clusterLogOneRecord* bottom=NULL;
	clusterLogOneRecord* tmp;

	for(tmp=cluster->current; tmp!=NULL; tmp=tmp->next) {
		if(NULL==tmp->next) {
			bottom = tmp; 
			fprintf(stderr, "bottom %x \n", (unsigned int)bottom);
			break;
		}
	}
	return bottom;
}


/*
	clusterLogBottomSet
		Set the bottom pointer to all Log Lines
*/

void
clusterLogBottomSet(clusterLog* cluster, int mode)
{
	cluster->bottom = clusterLogBottomGet(cluster, mode);
}

