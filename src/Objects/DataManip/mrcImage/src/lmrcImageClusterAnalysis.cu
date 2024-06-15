/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageClusterAnalysis ver %I%
#%Z% Created by Narita  
#%Z% Modified by Tac for AutoRotationMode 
#%Z%
#%Z% Usage : mrcImageClusterAnalysis
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageClusterAnalysis ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageClusterAnalysis.h"


/*
	Historically, we created the mrcImageClusterAnalysis first.
	After this, we created the Cluster class in General.
	So, functions in this file have both of new and old system, especially prevM and prevN.
	In the future, we must modify the sources.
*/

#include "Cluster.h"

void
lmrcImageClusterAnalysisDistanceToLog(FILE* fpt, int n, int m, int prevM, int prevN, float distance)
{
	clusterLogOneRecord cluster;

	cluster.N = n;
	cluster.M = m;
	cluster.prevN = prevM; /* N-M exchange: Historical reason.*/
	cluster.prevM = prevN; /*  In the future, we must modify this inconsintency */
	cluster.distance = distance;
	clusterLogWriteOneRecord(&cluster, fpt, 0);
	fflush(fpt);
}

double
lmrcImageDistanceCalc0(mrcImage* out, mrcImage* cor, mrcImage* clusterN, mrcImage* clusterM, int numN, int numM, lmrcImageClusterAnalysisInfo* linfo) {
	double distance = 0;

	DEBUGPRINT("n lmrcImageDistanceCalc0:");
  	switch(linfo->mode) {
		case lmrcImageClusterAnalysisModeCorrelation:
		case lmrcImageClusterAnalysisModeLinearCorrelation:
		case lmrcImageClusterAnalysisModeEuclidDistance: {
		  if(linfo->flagAutoRotation) {
		  	distance = lmrcImageDistanceCalcWithAutoRotation(out, cor, 
							  clusterN, clusterM, 
			    			  &(linfo->arInitial), linfo->correlationMode, linfo->mode);
		  } else {
		  	DEBUGPRINT("ByCorrelation:");
	  	    distance = lmrcImageDistanceCalc(clusterN, clusterM, linfo->mode);
			*out = *clusterN;
			cor->Image = NULL;
		  }
		  break;
		}
		case lmrcImageClusterAnalysisModeWardMethod: 
		case lmrcImageClusterAnalysisModeWardMethodLinearCorrelation: {
		  if(linfo->flagAutoRotation) {
		  	distance = lmrcImageDistanceCalcByWardMethodWithAutoRotation(out, cor,
			                   clusterN,    clusterM, 
			                   numN, numM,
							   &(linfo->arInitial), linfo->correlationMode, linfo->mode);
		  } else {
		  	DEBUGPRINT("By Ward: ");
            distance = lmrcImageDistanceCalcByWardMethod(
							   clusterN, clusterM, 
		                       numN, numM, 
		                       linfo->mode);
			*out = *clusterN;
			cor->Image = NULL;
		  }
		  break;
		}
		default: {
		  fprintf(stderr, "Not supported mode: %d\n", linfo->mode);
		  exit(EXIT_FAILURE);
		  break;
		}
   	}
	DEBUGPRINT1("Distance: %f\n", distance)
	if(0<distance) {
		return distance;
	} else {
		return (0);
	}
} 

void 
lmrcImageClusterAnalysis(
	int* group,                         /* Output: Group Index */
	mrcImage* in,                       /* Input:  Images  */
	int N,                              /* Input:  Number of Images */ 
	int finalclusternum,                /* Input:  FinalClusterNum */
	lmrcImageClusterAnalysisInfo* linfo /* Input:  Information of ClusterAnalysis */)
{
  float** distance;             /* Distance Array */
  int* index;                   /* the least index of averaged images in each cluster */
  int* averagednum;             /* the number of averaged images in each cluster */
  int i, n,m,minn,minm,clusternum, indexMinN, indexMinM;
  int prevN;
  int prevM;
  float min,F;
  mrcImage* cluster;
  mrcImageParaTypeRealCoord offset;
  mrcImage out;
  mrcImage cor;
  mrcImage minOut;
  mrcImage minCor;
  lmrcImageAutoRotationCorrelationInfo minInfo; 
  int flagSkip   = 0;
  int flagNoValue= 1;
  int flagNoSkip = 0;
  clusterLog* clusterLog=NULL;

  minn       = minm = 0;
  clusternum = N; /* the current number of clusters */
  prevN      = N; /* previous N */
  prevM      = N; /* previous M */

/* Initial Stage */	
  /* Memory Allocation */   
  linfo->Distance = distance = matrix(0, N-1, 0, N-1);
  index       = ivector(0, N);
  averagednum = ivector(0, N-1);
  cluster              = (mrcImage *)memoryAllocate(sizeof(mrcImage)*N, "Enough memory is not available!");
  linfo->averagedImage = (mrcImage*)memoryAllocate(sizeof(mrcImage)*N, "Enough memory is not available!");

  if(linfo->flagLogIn) {
  	DEBUGPRINT("LogIn\n");
  	fseek(linfo->fptLogIn, 0L, SEEK_SET);
   	clusterLog = clusterLogReadAll(clusterLog, linfo->fptLogIn, 0); 
	clusterLogClusterNumberSet2(clusterLog, linfo->previousFileNumber, 0); 
	clusterLog->current=clusterLog->top;
	if(clusterLog->top->prevN==clusterLog->top->prevM) {
		DEBUGPRINT2("Previous FileNumber : %d ClusterNumber %d \n", clusterLog->top->prevN, clusterLog->top->clusterNumber);
		linfo->previousFileNumber = clusterLog->top->prevN;
	} else {
		fprintf(stderr, "Something wrong");
		exit(EXIT_FAILURE);
	}
  }

  offset.x = offset.y = offset.z =0;
  index[N] = N;
  for (i=0; i<N; i++) {
    index[i]       = i;
    averagednum[i] = 1;
    group[i]       = i;

    cluster[i].Header = in[0].Header;
    mrcInit(&cluster[i],0);
    lmrcImageCopy(&cluster[i], &in[i], offset);

    linfo->averagedImage[i].Header = in[0].Header;
    mrcInit(&linfo->averagedImage[i],0);
    lmrcImageCopy(&linfo->averagedImage[i], &cluster[i], offset);
  }
  minOut.Header = cluster[0].Header;
  minCor.Header = cluster[0].Header;
  mrcInit(&minOut, NULL);
  mrcInit(&minCor, NULL);

  /* Cluster Analysis */
  /* 
  	Calculation of distance[n][m] 
	  0 <=     n < clusternum
      0 <= m < n
              n\m 0 1 2 3 ...-2 cluseternum-1
              0   - - - - ... - -
	          1   * - - - ... - - 
	          2   * * - - ... - -
	          3   * * * - ... - -
	          .   * * * * ... - -
	          .   * * * * ... - -
	          .   * * * * ... - - 
   clusternum-1   * * * * ... * -  
         
   *: Calc
   -: No Calc
  */

  while (finalclusternum<clusternum) {
    min=MAXFLOAT;
    for (n=0; n<clusternum; n++) {
      for (m=0; m<n; m++) {

	  	/* Check whether correlation between index[n] and index[m] must be calculated. */	
  		if( clusternum != N       /* At the first step (N==clusternum), we cannot skip */
		 && index[n]   != index[prevM]          
	 	 && index[m]   != index[prevM]
		 && min <= distance[n][m]) {      
		 	flagSkip = 1;
		} else {
			flagSkip = 0;
		}
		if(linfo->flagLogIn && !flagSkip && !flagNoSkip) {
			clusterTypeReal d = -1;
			clusterLog->current = clusterLogGetDistance(clusterLog, n, m, clusternum - (N - linfo->previousFileNumber), &d);
			if(d<=0) {
				DEBUGPRINT3("Zero:: n: %d m: %d d: %g\n", n, m, d);
				flagNoSkip = 1; /* The log file has an error log line */
			}
			if(0<d) {
				distance[n][m] = d;
				flagSkip = 1;
			} else {
				flagSkip = 0;
			}
		} 

		/* Calc distance[n][m] */
		if(flagSkip && 0 < distance[n][m]) { 
			DEBUGPRINT4("skip:   n: %d m: %d prevM: %d prevN: %d\n", n, m, prevM, prevN);
			DEBUGPRINT4("index:  n: %d m: %d prevM: %d prevN: %d\n", index[n], index[m], index[prevM], index[prevN]);
			/* Skip because of no need of calculation */
		} else {
			DEBUGPRINT4("noskip: n: %d m: %d prevM: %d prevN: %d\n", n, m, prevM, prevN);
			DEBUGPRINT4("index:  n: %d m: %d prevM: %d prevN: %d\n", index[n], index[m], index[prevM], index[prevN]);
			distance[n][m] = lmrcImageDistanceCalc0(&out, &cor, 
				&cluster[index[n]], &cluster[index[m]], 
				averagednum[index[n]], averagednum[index[m]], linfo); 
		} 

		/* Evaluate Distance betweeen cluster[index[n]] and cluster[index[m]] */
		if(distance[n][m]<=min) { 
			min  = distance[n][m];
		    minn = n;
		    minm = m;
			if(flagSkip) {
				flagNoValue = 1;
			} else {
				flagNoValue = 0;
				mrcImageFree(&minCor, "in lmrcImageClusterAnalysis");
				mrcImageFree(&minOut, "in lmrcImageClusterAnalysis");
			  	minCor = cor;
			 	minOut = out;
				minInfo = linfo->arInitial;
			}
		} else {
			if(!flagSkip) {
				mrcImageFree(&cor, "in lmrcImageClusterAnalysis");
				mrcImageFree(&out, "in lmrcImageClusterAnalysis");
			}
		}
		lmrcImageClusterAnalysisDistanceToLog(linfo->fptLog, n, m, prevN, prevM, distance[n][m]); 
      }
    } /* End: Calc Distance */

#ifdef DEBUG
	/* Check For Debuging */
	for(n=0; n<clusternum; n++) {
	for(m=0; m<n; m++) {
		DEBUGPRINT1("%6.2f ", distance[n][m]);
	}
		DEBUGPRINT("\n");
	}
    DEBUGPRINT3("index[minm] %d index[minn] %d min %g\n",index[minm], index[minn], min);
    DEBUGPRINT2("minm        %d minn        %d \n",minm, minn);
#endif
    /* 
		cluster[index[minm]] : change
		cluster[index[minn]] : no change
		index[0:clusternum-1]
		index[minm]
		index[minn]
		averagednum
    */
	if(flagNoValue) {
		distance[minn][minm] = lmrcImageDistanceCalc0(&out, &cor,
			&cluster[index[minn]], &cluster[index[minm]], 
			averagednum[index[minn]], averagednum[index[minm]], linfo); 
		mrcImageFree(&minCor, "in lmrcImageClusterAnalysis");
		mrcImageFree(&minOut, "in lmrcImageClusterAnalysis");
		minCor = cor;
		minOut = out;
		minInfo = linfo->arInitial;
	}
	indexMinN = index[minn];
	indexMinM = index[minm];
    lmrcImageClusterMerge(&cluster[index[minm]], &minOut, index, averagednum, minm, minn, &clusternum);
	lmrcImageCopy(&linfo->averagedImage[indexMinN], &cluster[indexMinM], offset);
	lmrcImageCopy(&linfo->averagedImage[indexMinM], &cluster[indexMinM], offset);
	if(linfo->flagLog2) {
		LOGPRINT4(linfo->fptLog2, "CLUST", "MIN", "%5d %5d %15.6g %15.6g", indexMinN, indexMinM, min, minInfo.LinearCorrelation);
	}
	DEBUGPRINT("after\n");
    DEBUGPRINT3("index[minm] %d index[minn] %d min %g\n",index[minm], index[minn], min);

    /*
    distance[n][m]
              n\m 0 1 2 3 ...-1 cluseternum
              0   - - - - ... - -
	          1   * - - - ... - - 
	          2   * * - - ... - -
	          3   * * * - ... - -
	          .   * * * * ... - -
	       minm   * * * * ... - -
	          .   * * * * ... - - 
	       minn   * * * * ... - - 
	          .   * * * * ... - - 
     clusternum   * * * * ... * -  

    group[n]: the number of the group including the nth-image  
      ~                                         ~
	0<= n < N
    */

	/* Grouping : group[minm] <- group[minn] */
    for (n=0; n<N; n++){
      if (group[n] == minn) {
	    group[n] = minm;         /* assignment of the new number of group */
      } else if (group[n] > minn){
	    group[n] = group[n] - 1; /* decrement of the number of group      */
      }
    }

	prevM = minm; /* Always, minm < minn.  So prevM<prevN */ 
	prevN = minn;
    for (n=0; n<clusternum; n++) {
     	for (m=0; m<n; m++) {
			if(m<prevN) {
				if(n<prevN) {
					distance[n][m] = distance[n  ][m  ];
				} else if(prevN<=n){
					distance[n][m] = distance[n+1][m  ];
				}
			} else if(prevN<=m){
				if(n<prevN) {
					fprintf(stderr, "Something wrong: n<m.  Always, m<n\n");
				} else if(prevN<=n) {
					distance[n][m] = distance[n+1][m+1];
				}
			}
		}
	}
    DEBUGPRINT("After distance change\n");
    for(n=0; n<clusternum; n++) {
    for(m=0; m<n; m++) {
		DEBUGPRINT1("%6.2f ", distance[n][m]);
    }
		DEBUGPRINT("\n");
    }
  } /* while end : Cluster Analysis Main Routine */
	
  for (n=0; n<N; n++){
    if (linfo->flagIteration){
      fprintf(stderr, "n %d group %d \n", n, group[n]);
    } else {
      fprintf(stderr, "n %d group %d \n", n, group[n]);
    }
  }
  if (linfo->flagIteration){
  	F = lmrcImageClusterAnalysisByIteration(group, in, finalclusternum, N, linfo->mode);
    for (n=0; n<N; n++){
      fprintf(stderr, "%d %d \n",n,group[n]);
    }
    fprintf(stdout,"F= %g\n",F);
  }
}

/*
lmrcImageClusterMerge
	in1: index[m] -> an averaged image of a new cluster: 
	in2: index[n] -> no change
	index:
	averagednum: the number of averaged images in each cluster
	m: The nearest pair of particles 
	n:                        -> the index to be neglected 
	N: Current cluster number -> N - 1
*/
void lmrcImageClusterMerge(mrcImage* in1, mrcImage* in2, int* index, int* averagednum, int m, int n, int* N)
{
  int io,ii;
  mrcImage in1mul,in2mul;
  float avrm,avrn;
  mrcImageParaTypeRealCoord offset;

  /* Averaging of cluster index[m] and index[n] */
  avrm = (float)averagednum[index[m]] / (averagednum[index[m]] + averagednum[index[n]]);
  avrn = (float)averagednum[index[n]] / (averagednum[index[m]] + averagednum[index[n]]);
  lmrcImageMultiplying(&in1mul, in1, avrm, in1->HeaderMode);
  lmrcImageMultiplying(&in2mul, in2, avrn, in2->HeaderMode);
  llmrcImageAdd(&in1mul, &in2mul);

  /* Set a new averaged image of a new cluster */
  offset.x = offset.y = offset.z =0 ;
  lmrcImageCopy(in1, &in1mul, offset);

  /* Set the number of averaged images */
  averagednum[index[m]] += averagednum[index[n]];

  /* 
    cluster index change : 
		ii<n:  io == ii
		n <ii: io == ii - 1
  */ 
  io=0;
  for (ii=0; ii<*N; ii++) {
    if (ii != n) {
      index[io] = index[ii];
      io++;
    }
  }
  *N = *N - 1;

  /* cleaning */
  mrcImageFree(&in1mul,"");
  mrcImageFree(&in2mul,"");
}

float 
lmrcImageDistanceCalcWithAutoRotation(mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int mode)
{
	double distance;
	switch(mode) {
		case lmrcImageClusterAnalysisModeCorrelation: {
			lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
			distance = -linfo->max;
			break;
		}
		case lmrcImageClusterAnalysisModeEuclidDistance: {
			lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
			distance = linfo->EuclidDistance;
			break;
		}
		case lmrcImageClusterAnalysisModeLinearCorrelation: {
			lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
			distance = linfo->LinearCorrelation;
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageDistanceCalcWithAutoRotation: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	return distance;
}

float 
lmrcImageDistanceCalc(mrcImage* in1, mrcImage* in2, int mode)
{
  double data;
  
  switch (mode) {
  	case lmrcImageClusterAnalysisModeCorrelation: {
    	data = -lmrcImageCorrelationinSpace(in1, in2, 0);
    	break;
	}
  	case lmrcImageClusterAnalysisModeEuclidDistance: {
		data = lmrcImageEuclidDistanceCalc(in1, in2, 1);
		break;
	}
  	case lmrcImageClusterAnalysisModeWardMethod: {
		data = lmrcImageEuclidDistanceCalc(in1, in2, 1);
		data = SQR(data);
		break;
	}
  	case lmrcImageClusterAnalysisModeWardMethodLinearCorrelation: 
	case lmrcImageClusterAnalysisModeLinearCorrelation: {
		data = lmrcImageLinearCorrelation(in1, in2, 1);
		data = exp(SQR(data-1.0)/(1/log(1e4)))-1.0;
		break;
	}	
	default: {
		fprintf(stderr, "Not supported mode in lmrcImageDistanceCalc: %d\n", mode);
		exit(EXIT_FAILURE);
		break;
	}
  }
  return data;
}

float 
lmrcImageDistanceCalcByWardMethodWithAutoRotation(mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, int num1, int num2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int mode)
{
	double distance;
	switch(mode) {
		case lmrcImageClusterAnalysisModeWardMethod: {
			lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
			distance = SQR(linfo->EuclidDistance)*(num1*num2)/(num1+num2);
			break;
		}
		case lmrcImageClusterAnalysisModeWardMethodLinearCorrelation: {
			lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode);
			distance = (exp(SQR(linfo->LinearCorrelation-1.0)/(1/log(1e4)))-1.0)*(num1*num2)/(num1+num2);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageDistanceCalcByWardMethodWithAutoRotation: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	return distance;
}

float 
lmrcImageDistanceCalcByWardMethod(mrcImage* in1, mrcImage* in2, int num1, int num2, int mode)
{
	double data;
	double distance;

	switch(mode) {
		case lmrcImageClusterAnalysisModeWardMethod: {
  			data = lmrcImageEuclidDistanceCalc(in1, in2, 0);
  			distance = (data)*((num1*num2)/(num1+num2));
			break;
		}
		case lmrcImageClusterAnalysisModeWardMethodLinearCorrelation: {
			data = lmrcImageLinearCorrelation(in1, in2, 0); 
			if(0<data) {
				distance = (200.0/(data+1.0)-100)*(num1*num2)/(num1+num2);
			} else {
				distance = (200.0/(data+1.0)-100)*(num1*num2)/(num1+num2);
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageDistanceCalcByWardMethod: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
  	return data;
}

float lmrcImageClusterAnalysisByIteration(int* group, mrcImage* in, int clusternum, int N, int mode)
{
  mrcImage* center;
  int n,m;
  float distancesum,distance,olddistancesum,distancemin,F;
  int* groupnum;
  mrcImageParaTypeRealCoord dum;
  mrcImage tmpimage;
  double clustervar;
  mrcImage centerofclusters;

  center = (mrcImage *)memoryAllocate(sizeof(mrcImage)*clusternum, "Enough memory is not available!");
  groupnum = ivector(0,clusternum-1);
  dum.x = dum.y = dum.z =0;

  distancesum=1;
  olddistancesum=0;
  for (n=0; n<clusternum; n++){
    center[n].Header = in[0].Header;
    mrcInit(&center[n],0);
  }
    
  while (distancesum != olddistancesum){
    olddistancesum=distancesum;
    distancesum=0;
    for (n=0; n<clusternum; n++){
      mrcImageFree(&center[n],"");
      center[n].Header = in[0].Header;
      mrcInit(&center[n],0);
      groupnum[n]=0;
    }
    for (n=0; n<N; n++){
      llmrcImageAdd(&center[group[n]],&in[n]);
      groupnum[group[n]] ++;
    }
    for (n=0; n<clusternum; n++){
      lmrcImageMultiplying(&tmpimage, &center[n], 1.0/groupnum[n], center[n].HeaderMode);
      lmrcImageCopy(&center[n], &tmpimage, dum);
      mrcImageFree(&tmpimage, "");
    }
    for (n=0; n<N; n++){
      distancemin = 1e+16;
      for (m=0; m<clusternum; m++){
	distance = lmrcImageDistanceCalc(&in[n], &center[m], mode);
	if (distance < distancemin){
	  distancemin = distance;	  
	  group[n] = m;
	}
      }
      distancesum += distancemin;
    }
  }

  /* F-value */
  centerofclusters.Header = center[0].Header;
  mrcInit(&centerofclusters,0);
  for (n=0; n<clusternum; n++){
    llmrcImageAdd(&centerofclusters, &center[n]);
  }
  lmrcImageMultiplying(&tmpimage, &centerofclusters, 1.0/clusternum, centerofclusters.HeaderMode);
  lmrcImageCopy(&centerofclusters, &tmpimage, dum);
  mrcImageFree(&tmpimage, "");
  clustervar=0;
  for (n=0; n<clusternum; n++){
    clustervar += lmrcImageDistanceCalc(&centerofclusters, &center[n], 2);
  }
  clustervar /= clusternum;
  if (mode != 2){
    distancesum = 0;
    for (n=0; n<N; n++){
      distancesum += lmrcImageDistanceCalc(&in[n], &center[group[n]], 2);
    }
  }
  distancesum/=N;
  if (distancesum > 0){
    F=clustervar/distancesum;
    F=sqrt(F);
  } else {
    F=0;
  }
  return(F);
}
