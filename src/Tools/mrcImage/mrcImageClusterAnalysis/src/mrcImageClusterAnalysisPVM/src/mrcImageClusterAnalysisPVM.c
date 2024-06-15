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
static char __sccs_id[] = "%Z%mrcImageClusterAnalysisContinue ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <values.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "nr2.h"
#include "mrcRefUtil.h"
#include "lmrcImageMultiplying.h"
#include "lmrcImageCorrelation.h"
#include "pvm3.h"
#include "mrcImagePVM.h"

/* prototypes */
typedef struct lmrcImageClusterAnalysisInfo {
	int mode;          /* */
	int flagIteration; /* */
	int flagAutoRotation; 
        int flagmirrorimage;
	char** filename;   /* filename */
	int correlationMode; /* correlationMode */
	mrcImage* averagedImage;
	lmrcImageAutoRotationCorrelationInfo arInitial;
} lmrcImageClusterAnalysisInfo;

void lmrcImageClusterAnalysisContinuePVM(int* group, int* index, mrcImage* in, int* averagednum, int finalclusternum, int N, lmrcImageClusterAnalysisInfo* linfo, int maxprocess);
void lmrcImageClusterMerge(mrcImage* in1, mrcImage* in2, int* index, int* averagednum, int m, int n, int* N);
float lmrcImageDistanceCalcByWardMethodWithAutoRotationPVM(mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, int num1, int num2,  lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int flagmirror, int* mirrorresult, int mode);
int lmrcImageDistanceCalcByWardMethodWithAutoRotationSend(mrcImage* in1, mrcImage* in2, int num1, int num2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int flagmirror, int mode);
int lmrcImageDistanceCalcByWardMethodWithAutoRotationReceive(float* distance, int* mirrorresult);
void lmrcImagelAutoRotationCorrelationInfoSendByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid);
void lmrcImagelAutoRotationCorrelationInfoReceiveByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid);


int
main(int argc, char* argv[]) 
{
/* variables */
	mrcImageClusterAnalysisPVMInfo  info;
	lmrcImageClusterAnalysisInfo linfo;
	long i;
	mrcImage* in;
	FILE* fpin;
	int* group;
	int* index;
	char dummy[1028];
	int filenum;
	char** filename;
	int* averagednum;
	

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	if((fpin=fopen(info.In,"r"))==NULL){
	  fprintf(stderr ,"File can not be opened.\n");
	  exit(1);
	}
	filenum=0;
	fseek(fpin,0L, SEEK_SET);
	while(fscanf(fpin,"%s %d \n",dummy,&i )!=EOF ){
	  filenum++;
	}
	fseek(fpin,0L, SEEK_SET);
	
	if ( ( in = (mrcImage *)malloc(sizeof(mrcImage)*filenum) ) == NULL){
	  fprintf(stderr, "Enough memory is not available!\n");
	  exit(EXIT_FAILURE);
	}
	if ( ( filename = (char **)malloc(sizeof(int)*filenum) ) == NULL){
	  fprintf(stderr, "Enough memory is not available!\n");
	  exit(EXIT_FAILURE);
	}
	group = ivector(0,filenum-1);
	averagednum = ivector(0,filenum-1);
	index = ivector(0,filenum-1);

	for (i=0; i<filenum; i++){
	  if ( ( filename[i] = (char *)malloc(sizeof(int)*1024) ) == NULL){
	    fprintf(stderr, "Enough memory is not available!\n");
	    exit(EXIT_FAILURE);
	  }
  	  fscanf(fpin,"%s %d \n ",filename[i],&averagednum[i]);
	  fprintf(stderr,"%d %s %d \n ",i,filename[i],averagednum[i]);
	  mrcFileRead(&in[i], filename[i], "in main file", 0);
	  /*
	  lmrcImageNormalization(&in[i],0);
	  */
	}
	
/* Cluster Analysis */
	linfo.mode          = info.mode;
	linfo.flagIteration = info.Iteration;
	linfo.filename      = filename;
	linfo.flagAutoRotation = info.flagAutoRotation;
	linfo.arInitial.nRot   = info.AutoRotation;
	linfo.arInitial.Method = info.AutoRotationMethod;
	linfo.arInitial.iter   = info.AutoRotationIteration;
	linfo.arInitial.flagRestrictionArea = 0;
	linfo.arInitial.flagXshiftOnly = 0;
	linfo.correlationMode  = info.correlationMode;
	linfo.flagmirrorimage = info.Mirrorimage;

	lmrcImageClusterAnalysisContinuePVM(group, index, in, averagednum, info.N, filenum, &linfo, info.Maxprocess);

/* Output Data */
	fprintf(info.fptOut, "Cluster index\n");
	for (i=0; i<filenum; i++){
	  fprintf(info.fptOut, "%s %d\n",filename[i], group[i]);
	}
	fprintf(info.fptOut, "Averaged images\n");
	for (i=0; i<info.N; i++){
	  fprintf(info.fptOut, "%s.avg %d\n",filename[index[i]], averagednum[index[i]]);
	}
	if(info.Output) {
		char s[1024];
		for(i=0; i<filenum; i++) {
			sprintf(s, "%s.avg", filename[i]);
			mrcFileWrite(&(linfo.averagedImage[i]), s, "in main", 0);
		}
	}

	pvm_exit();
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Distance between clusters:\n");
	fprintf(stderr, "\t mode0: By Correlation\n");
	fprintf(stderr, "\t mode1: By Euclid Distance\n");
	fprintf(stderr, "\t mode2 (Default) : By Ward Method\n");
}

void lmrcImageClusterAnalysisContinuePVM(int* group, int* index, mrcImage* in, int* averagednum, int finalclusternum, int N, lmrcImageClusterAnalysisInfo* linfo, int maxprocess)
{
  float** distance;
  int n,m,minn,minm,clusternum;
  int prevN;
  int prevM;
  float min,startmin;
  mrcImage* cluster;
  mrcImageParaTypeRealCoord dum;
  int mode;
  int iterflag;
  mrcImage out;
  mrcImage cor;
  mrcImage minOut;
  int flagSkip;
  lmrcImageAutoRotationCorrelationInfo mindistinfo;
  int mirrorresult;
  int Minmirrorresult;
  int processnum;
  int* nmem;
  int* mmem;
  int* pid;
  int nowid;
  int nowprocess;
  int i;
  float nowdistance;

  startmin=MAXFLOAT;
  minn = minm = 0;
  mode     = linfo->mode; 
  iterflag = linfo->flagIteration; 

  /* N : The Number Of Images */
  clusternum=N; /* the current number of clusters */
  prevN     =N-1; /* previous N */
  prevM     =N-1; /* previous M */

  /* Initial Stage */	
  distance    = matrix(0, N-1, 0, N-1);
  if ( ( cluster = (mrcImage *)malloc(sizeof(mrcImage)*N) ) == NULL){
    fprintf(stderr, "Enough memory is not available!\n");
    exit(EXIT_FAILURE);
  } else {
  	linfo->averagedImage = cluster;
  }
  nmem=ivector(0,maxprocess-1);
  mmem=ivector(0,maxprocess-1);
  pid=ivector(0,maxprocess-1);
  dum.x = dum.y = dum.z =0;

   for (n=0; n<N; n++) {
    index[n]       = n;
    group[n]       = n;
    cluster[n].Header = in[0].Header;
    mrcInit(&cluster[n],0);
    lmrcImageCopy(&cluster[n], &in[n], dum);
  }

  if(linfo->flagAutoRotation) {	
  	minOut.Header = cluster[0].Header;
	mrcInit(&minOut, NULL);
  }

  /* Cluster Analysis */
  /* 
  	Calculation of distance[n][m] 
	  0 <=     n < clusternum
      0 <= m < n
              n\m 0 1 2 3 ...-1 cluseternum
              0   - - - - ... - -
	          1   * - - - ... - - 
	          2   * * - - ... - -
	          3   * * * - ... - -
	          .   * * * * ... - -
	          .   * * * * ... - -
	          .   * * * * ... - - 
     clusternum   * * * * ... * -  
  */
  
  while (finalclusternum<clusternum) {
    min=startmin;
    processnum=0;
    for (n=0; n<clusternum; n++) {
      for (m=0; m<n; m++) {
	DEBUGPRINT2("n:%d m:%d\n",n,m);
	  	if(linfo->flagAutoRotation) {
			/* Saving the calculation steps */
	  		if(
			    clusternum!=N   /* At the first step (N==clusternum), we cannot skip */
			 && index[n]!=index[prevM]        
		 	 && index[m]!=index[prevM]
			) {
			 	flagSkip = 1;
			} else {
				flagSkip = 0;
			}
		} else {
			flagSkip = 0;
		}
		if(flagSkip) {
			DEBUGPRINT4("skip:   n: %d m: %d prevM: %d prevN: %d\n", n, m, prevM, prevN);
			DEBUGPRINT4("index:  n: %d m: %d prevM: %d prevN: %d\n", index[n], index[m], index[prevM], index[prevN]);
			DEBUGPRINT3("index:  n: %d m: %d distance: %f\n", index[n], index[m], distance[n][m]);
			if (distance[n][m] < min){
			  min = distance[n][m];
			  minn = n;
			  minm = m;
			}
			/* Skip because of no need of calculation */
		} else {
			DEBUGPRINT4("noskip: n: %d m: %d prevM: %d prevN: %d\n", n, m, prevM, prevN);
			DEBUGPRINT4("index:  n: %d m: %d prevM: %d prevN: %d\n", index[n], index[m], index[prevM], index[prevN]);
			linfo->arInitial.flagRestrictionArea = 0;
			linfo->arInitial.flagXshiftOnly  = 0;
			DEBUGPRINT2("Maxprocess: %d process: %d\n",maxprocess, processnum);
			if (processnum == maxprocess){

			  DEBUGPRINT2("Waiting data %d %d \n",maxprocess, processnum);
			  nowid=lmrcImageDistanceCalcByWardMethodWithAutoRotationReceive(&nowdistance, &mirrorresult);
			  for (i=0; i<maxprocess; i++){
			    if (pid[i] == nowid){
			      nowprocess = i;
			      break;
			    }
			  }
			  distance[nmem[nowprocess]][mmem[nowprocess]] = nowdistance;
			  DEBUGPRINT4("processnum: %d  index:  n: %d m: %d distance: %f\n", nowprocess, index[nmem[nowprocess]], index[mmem[nowprocess]], distance[nmem[nowprocess]][mmem[nowprocess]]);
			  if (distance[nmem[nowprocess]][mmem[nowprocess]] < min){
			    min = distance[nmem[nowprocess]][mmem[nowprocess]];
			    minn = nmem[nowprocess];
			    minm = mmem[nowprocess];
			  }
			  processnum --;
			  for (i=nowprocess; i<maxprocess; i++){
			    pid[i]=pid[i+1];
			    nmem[i]=nmem[i+1];
			    mmem[i]=mmem[i+1];
			  }
			}

			pid[processnum]=lmrcImageDistanceCalcByWardMethodWithAutoRotationSend(&cluster[index[n]], &cluster[index[m]], 
												 averagednum[index[n]], averagednum[index[m]], &(linfo->arInitial), 
												 linfo->correlationMode, linfo->flagmirrorimage, mode);
			nmem[processnum]=n;
			mmem[processnum]=m;
			DEBUGPRINT4("%d %d %d %d\n",processnum,pid[processnum],nmem[processnum],mmem[processnum]);
			processnum ++;

		} /* Skip */
      } 
    }

    while (processnum){
      nowid=lmrcImageDistanceCalcByWardMethodWithAutoRotationReceive(&nowdistance, &mirrorresult);
      for (i=0; i<maxprocess; i++){
	if (pid[i] == nowid){
	  nowprocess = i;
	  break;
	}
      }
      distance[nmem[nowprocess]][mmem[nowprocess]] = nowdistance;
      DEBUGPRINT4("processnum: %d  index:  n: %d m: %d distance: %f\n", nowprocess, index[nmem[nowprocess]], index[mmem[nowprocess]], distance[nmem[nowprocess]][mmem[nowprocess]]);
      if (distance[nmem[nowprocess]][mmem[nowprocess]] < min){
	min = distance[nmem[nowprocess]][mmem[nowprocess]];
	minn = nmem[nowprocess];
	minm = mmem[nowprocess];
      }
      processnum --;
    }

 
  

    distance[minn][minm]=lmrcImageDistanceCalcByWardMethodWithAutoRotationPVM(&out, &cor,
									      &cluster[index[minn]], &cluster[index[minm]], 
									      averagednum[index[minn]], averagednum[index[minm]], &(linfo->arInitial), 
									      linfo->correlationMode, linfo->flagmirrorimage, &mirrorresult, mode);
    mrcImageFree(&minOut, "in lmrcImageClusterAnalysis");
    mindistinfo = linfo->arInitial;
    Minmirrorresult = mirrorresult;
    minOut = out;
    for(n=0; n<clusternum; n++) {
      for(m=0; m<n; m++) {
	  DEBUGPRINT1("%6.2f ", distance[n][m]);
      }
      DEBUGPRINT("\n");
    }
    DEBUGPRINT3("index[minm] %d index[minn] %d min %g\n",index[minm], index[minn], min);
    DEBUGPRINT2("minm        %d minn        %d \n",minm, minn);
    
/* 
	cluster[index[minm]] : change
	cluster[index[minn]] : no change
	index[0:clusternum-1]
	index[minm]
	index[minn]
	averagednum
*/
    lmrcImageClusterMerge(&cluster[index[minm]], &minOut,               index, averagednum, minm, minn, &clusternum);
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
	if(linfo->flagAutoRotation) {
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
	}
    DEBUGPRINT("After distance change\n");
    for(n=0; n<clusternum; n++) {
    for(m=0; m<n; m++) {
		DEBUGPRINT1("%6.2f ", distance[n][m]);
    }
		DEBUGPRINT("\n");
    }
    for (n=0; n<N; n++){
      fprintf(stdout, "n %d group %d \n", n, group[n]);
    }
    fprintf(stdout, "N: %d Min: %f x: %f y: %f z: %f theta: %f mirror: %d\n", minn, min, mindistinfo.maxP.x, mindistinfo.maxP.y, mindistinfo.maxP.z, mindistinfo.maxTheta/RADIAN, Minmirrorresult);
  }
	
 
}

/*
	in1: index[m] -> an averaged image of a new cluster
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
  mrcImageParaTypeRealCoord dum;

  /* Averaging of cluster index[m] and index[n] */
  avrm = (float)averagednum[index[m]] /  (float)(averagednum[index[m]] + averagednum[index[n]]);
  avrn = (float)averagednum[index[n]] /  (float)(averagednum[index[m]] + averagednum[index[n]]);
  lmrcImageMultiplying(&in1mul, in1, avrm, in1->HeaderMode);
  lmrcImageMultiplying(&in2mul, in2, avrn, in2->HeaderMode);
  llmrcImageAdd(&in1mul, &in2mul);
  /*
  lmrcImageNormalization(&in1mul,0);
  */
  /* Set a new averaged image of a new cluster */
  dum.x = dum.y =dum.z =0 ;
  lmrcImageCopy(in1, &in1mul, dum);
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
lmrcImageDistanceCalcByWardMethodWithAutoRotationPVM(mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, int num1, int num2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int flagmirror, int* mirrorresult, int mode)
{
	double distance,distance2;
	mrcImage tmpout;
	mrcImage tmpcor;
	mrcImage tmpin1;
	lmrcImageAutoRotationCorrelationInfo tmplinfo;

	if (flagmirror){
	  tmplinfo=*linfo;
	  lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
	  distance = SQR(linfo->EuclidDistance)*(num1*num2)/(num1+num2);
	  lmrcMirrorImageCreate(&tmpin1, in1, 0);
	  lmrcImageAutoRotationCorrelation(&tmpout, &tmpcor, &tmpin1, in2, &tmplinfo, lmode); 
	  distance2 = SQR(tmplinfo.EuclidDistance)*(num1*num2)/(num1+num2);
	  if (distance2 < distance){
	    *linfo = tmplinfo;
	    *out = tmpout;
	    *cor = tmpcor;
	    distance = distance2;
	    *mirrorresult=1;
	  } else {
	    *mirrorresult=0;
	  }
	} else {
	  lmrcImageAutoRotationCorrelation(out, cor, in1, in2, linfo, lmode); 
	  distance = SQR(linfo->EuclidDistance)*(num1*num2)/(num1+num2);
	}
	return distance;
}

int
lmrcImageDistanceCalcByWardMethodWithAutoRotationSend(mrcImage* in1, mrcImage* in2, int num1, int num2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int flagmirror, int mode)
{
  int tid;
  int myid;
  int cc;

  myid=pvm_mytid();
  DEBUGPRINT1("myid: %d\n",myid);
  cc=pvm_spawn("/users/Eos/bin/mrcImageClusterAnalysisPVMSlave", (char**)0, 0, "", 1, &tid);
  if (cc !=1){
    pvm_error("I cannot start mrcImageClusterAnalysisPVMSlave");
  }
  pvm_initsend(PvmDataDefault);
  pvm_pkint(&num1, 1, 1);
  pvm_pkint(&num2, 1, 1);
  pvm_pkint(&lmode, 1, 1);
  pvm_pkint(&flagmirror, 1, 1);
  pvm_pkint(&mode, 1, 1);
  cc=pvm_send(tid, 1);
  if (cc<0){
    pvm_error("lmrcImageDistanceCalcByWardMethodWithAutoRotationSend");
  }
  mrcImageSendByPVM(in1, tid, 0);
  mrcImageSendByPVM(in2, tid, 0);
  lmrcImagelAutoRotationCorrelationInfoSendByPVM(linfo, tid);
  return(tid);
}

int
lmrcImageDistanceCalcByWardMethodWithAutoRotationReceive(float* distance, int* mirrorresult)
{
  int bufid;
  int nowid;

  DEBUGPRINT("Waiting"); 
  bufid=pvm_recv(-1, -1);
  DEBUGPRINT1("bufid: %d",bufid); 
  pvm_bufinfo(bufid, (int*)0, (int*)0, &nowid);
  pvm_upkfloat(distance, 1, 1);
  pvm_upkint(mirrorresult , 1, 1);
  return(nowid);
}

void lmrcImagelAutoRotationCorrelationInfoSendByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid)
{
  int info;

  pvm_initsend(PvmDataDefault);
  pvm_pkint(&(linfo->iter), 1, 1);
  pvm_pkint(&(linfo->nRot), 1, 1);
  pvm_pkint(&(linfo->Method), 1, 1);
  pvm_pkfloat(&(linfo->max), 1, 1); 
  pvm_pkfloat(&(linfo->maxTheta), 1, 1);
  pvm_pkfloat(&(linfo->maxP.x), 1, 1);
  pvm_pkfloat(&(linfo->maxP.y), 1, 1);
  pvm_pkfloat(&(linfo->maxP.z), 1, 1);
  pvm_pkfloat(&(linfo->EuclidDistance), 1, 1);
  pvm_pkfloat(&(linfo->LinearCorrelation), 1, 1);
  pvm_pkint(&(linfo->flagRestrictionArea), 1, 1);
  pvm_pkfloat(&(linfo->thetaMin), 1, 1);
  pvm_pkfloat(&(linfo->thetaMax), 1, 1);
  pvm_pkint(&(linfo->flagXshiftOnly), 1, 1);
  info = pvm_send(tid, 1);
  if (info<0){
    pvm_error("lmrcImagelAutoRotationCorrelationInfoSendByPVM");
  }
}

void lmrcImagelAutoRotationCorrelationInfoReceiveByPVM(lmrcImageAutoRotationCorrelationInfo* linfo, int tid)
{
  int bufid;

  bufid = pvm_recv(tid, -1);
  if(bufid<0) {
    pvm_error("lmrcImagelAutoRotationCorrelationInfoReceiveByPVM");
    return;
  }
  pvm_upkint(&(linfo->iter), 1, 1);
  pvm_upkint(&(linfo->nRot), 1, 1);
  pvm_upkint(&(linfo->Method), 1, 1);
  pvm_upkfloat(&(linfo->max), 1, 1);
  pvm_upkfloat(&(linfo->maxTheta), 1, 1);
  pvm_upkfloat(&(linfo->maxP.x), 1, 1);
  pvm_upkfloat(&(linfo->maxP.y), 1, 1);
  pvm_upkfloat(&(linfo->maxP.z), 1, 1);
  pvm_upkfloat(&(linfo->EuclidDistance), 1, 1);
  pvm_upkfloat(&(linfo->LinearCorrelation), 1, 1);
  pvm_upkint(&(linfo->flagRestrictionArea), 1, 1);
  pvm_upkfloat(&(linfo->thetaMin), 1, 1);
  pvm_upkfloat(&(linfo->thetaMax), 1, 1);
  pvm_upkint(&(linfo->flagXshiftOnly), 1, 1);
}
