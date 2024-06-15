/*
# clusterLogAnalysis : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : clusterLogAnalysis 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h" 
#include "Vector.h" 
#include "../inc/Cluster.h" 

extern clusterLogOneRecord* specifiedClusterNumberPointerGet(clusterLog* cluster, clusterTypeInteger clusterNumber, int mode);

extern intVector* clusterSizeListForSpecifiedClusterNumberGet(intVector* out, clusterLog* cluster, clusterTypeInteger clusterNumber, int mode);

/*
	Get the list of the original file number of each cluster within the same layer 
	specified by the argumetns(clusterNumber)
*/
intVector**
originalFileNumberListsOfEachClusterForSpecifiedClusterNumberGet(clusterLog* cluster, clusterTypeInteger clusterNumber, int mode)
{
	intVector*  clusterSize= NULL;
	intVector** out= NULL;
	clusterLogOneRecord* tmp;
	clusterLogOneRecord* tmp2;
	int Nskip;
	int i;

	tmp = specifiedClusterNumberPointerGet(cluster, clusterNumber, mode);
	Nskip = clusterNumber*(clusterNumber-1)/2;
	for(i=0; i<Nskip; i++, tmp=tmp->next) {
		DEBUGPRINT("Skip\n");
	}

	clusterSize = clusterSizeListForSpecifiedClusterNumberGet(clusterSize, cluster, clusterNumber, mode);
	out =  (intVector**)memoryAllocate(sizeof(intVector*)*(clusterNumber+i), "originalFileNumberListsOfEachClusterForSpecifiedClusterNumberGet");
	out[clusterNumber] = NULL;

	for(i=0; i<clusterNumber; i++) {
		intVectorInit(out[i], clusterSize->data[i]);
	}

	tmp2 = tmp->belowLayerForM;
	out[0]->data[0] = tmp->originalM;
	i=1;

	return out;
}

void
clusterMemberListBelowClusterGet(intVector* out, clusterTypeInteger* i, clusterLogOneRecord* cluster, int mode)
{
	if(NULL==cluster->belowLayerForN) {
		out->data[*i] = cluster->originalN;
	}
}

/*
	Get the list of the representative original file number specified by the argumetns(clusterNumber)
		representative file: the eariler file of each cluster 
*/
intVector*
representativeOriginalFileNumberListForSpecifiedClusterNumberGet(intVector* out, clusterLog* cluster, clusterTypeInteger clusterNumber, int mode)
{
	clusterLogOneRecord* tmp;
	int Nskip;
	int i;

	tmp = specifiedClusterNumberPointerGet(cluster, clusterNumber, mode);

	Nskip = clusterNumber*(clusterNumber-1)/2;
	out = intVectorInit(out, clusterNumber);

	for(i=0; i<Nskip; i++, tmp=tmp->next) {
		DEBUGPRINT("Skip\n");
	}

	out->data[0] = tmp->originalM;	
	for(i=1; i<clusterNumber-1; i++, tmp=tmp->next) { 
		if(clusterNumber!=tmp->clusterNumber) {
			fprintf(stderr, "Somthing wrong for LogFile : unexpected lines\n");  
			exit(EXIT_FAILURE);
		}
		out->data[i] = tmp->originalN;
	}
#ifdef DEBUG
	for(i=0; i<out->size; i++) { 
		DEBUGPRINT2("out[%5d]=%d\n", i, out->data[i]);
	}
#endif
	return out;
}

/*
	Get the size of each cluster of the same layer specified by the argumetns(clusterNumber)
*/
intVector*
clusterSizeListForSpecifiedClusterNumberGet(intVector* out, clusterLog* cluster, clusterTypeInteger clusterNumber, int mode)
{
	clusterLogOneRecord* tmp;
	int Nskip;
	int i;

	tmp = specifiedClusterNumberPointerGet(cluster, clusterNumber, mode);

	Nskip = clusterNumber*(clusterNumber-1)/2;
	out = intVectorInit(out, clusterNumber);

	for(i=0; i<Nskip; i++, tmp=tmp->next) {
		DEBUGPRINT("Skip\n");
	}

	out->data[0] = tmp->belowLayerForN->clusterSize;	
	for(i=1; i<clusterNumber-1; i++, tmp=tmp->next) { 
		if(clusterNumber!=tmp->clusterNumber) {
			fprintf(stderr, "Somthing wrong for LogFile : unexpected lines\n");  
			exit(EXIT_FAILURE);
		}
		out->data[i] = tmp->belowLayerForM->clusterSize;;
	}
#ifdef DEBUG
	for(i=0; i<out->size; i++) { 
		DEBUGPRINT2("out[%5d]=%d\n", i, out->data[i]);
	}
#endif
	return out;
}

/*
	Get the first record pointer for the cluster number specified by arguments(clusterNumber). 
*/
clusterLogOneRecord*
specifiedClusterNumberPointerGet(clusterLog* cluster, clusterTypeInteger clusterNumber, int mode)
{
	clusterLogOneRecord* tmp;

	for(tmp = cluster->bottom; tmp!=NULL; tmp = tmp->belowLayerStart) {
		if(tmp->clusterNumber == clusterNumber) {
			break;
		}
	}
	if(NULL==tmp) {
		fprintf(stderr, "Error in SpecifiedClusterNumberPointGet: Not found %d\n", clusterNumber);
		exit(EXIT_FAILURE);
	}
	return tmp;
}

