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
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosPThread.h"
#include "mrcImage.h"
#include "nr2.h"
#include "mrcRefUtil.h"
#include "lmrcImageMultiplying.h"
#include "lmrcImageCorrelation.h"
#include "lmrcImageClusterAnalysis.h"

/* prototypes */

void lmrcImageClusterAnalysisInfoSet(
	lmrcImageClusterAnalysisInfo* linfo, 
	 mrcImageClusterAnalysisInfo   info);


int
main(int argc, char* argv[]) 
{
/* variables */
	mrcImageClusterAnalysisInfo  info;
	lmrcImageClusterAnalysisInfo linfo;
	long i;
	mrcImage* in;
	int* group; /* Group Index */

	memset(&info,  0, sizeof(info ));
	memset(&linfo, 0, sizeof(linfo));
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	if (NULL==(in=(mrcImage *)malloc(sizeof(mrcImage)*info.flagIn) )){
	  fprintf(stderr, "Enough memory is not available!\n");
	  exit(EXIT_FAILURE);
	}
	group = ivector(0,info.flagIn-1);
	for (i=0; i<info.flagIn; i++){
	  mrcFileRead(&in[i], info.In[i], "in main file", 0);
	}

/* Cluster Analysis */
	lmrcImageClusterAnalysisInfoSet(&linfo, info);
	lmrcImageClusterAnalysis(group, in, info.flagIn, info.N, &linfo);

/* Output Data */
	for (i=0; i<info.flagIn; i++){
	  fprintf(info.fptOut, "%s %d\n",info.In[i], group[i]);
	}
	if(info.Output) {
		char s[1024];
		for(i=0; i<info.flagIn; i++) {
			sprintf(s, "%s.avg", info.In[i]);
			mrcFileWrite(&(linfo.averagedImage[i]), s, "in main", 0);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	int i;
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Distance between clusters: mode\n");
	i=0;
	while(1) {
		if(NULL!=lmrcImageClusterAnalysisModeMessage[i]) {
			fprintf(stderr, "\tmode %d: %s\n", i, lmrcImageClusterAnalysisModeMessage[i]);
		} else {
			break;
		}
		i++;
	}
}

void lmrcImageClusterAnalysisInfoSet(
	lmrcImageClusterAnalysisInfo* linfo, 
	mrcImageClusterAnalysisInfo info)
{
	linfo->mode          = info.mode;
	linfo->flagIteration = info.Iteration;
	linfo->filename      = info.In;
	linfo->flagAutoRotation = info.flagAutoRotation;
	linfo->arInitial.nRot   = info.AutoRotation;
	linfo->arInitial.Method = info.AutoRotationMethod;
	if(linfo->flagIteration) {
		linfo->arInitial.iter   = info.AutoRotationIteration;
	} else {
		linfo->arInitial.iter   = 1;
	}
	if(info.flagARMin && info.flagARMax) {
		linfo->arInitial.flagRestrictionArea = 1; 
		linfo->arInitial.thetaMin= info.ARMin*RADIAN;
		linfo->arInitial.thetaMax= info.ARMax*RADIAN;
	}
	linfo->correlationMode  = info.correlationMode;
	linfo->flagPVM          = info.pvm;
	linfo->flagLogIn        = info.flagLogIn;
	linfo->fptLogIn         = info.fptLogIn;
	linfo->previousFileNumber = info.prevFileNum;
	linfo->flagLog          = info.flagLog;
	linfo->fptLog           = info.fptLog;
	linfo->flagLog2         = info.flagLog2;
	linfo->fptLog2          = info.fptLog2;

	if(info.pthread>0) {
		__eosPThread__ = 1;	
		__eosPThreadNum__ = info.pthread;
		DEBUGPRINT2("pthread: %d %d\n", __eosPThread__, __eosPThreadNum__);
	}

	linfo->NoRecalculation = info.NoRecalc;

	DEBUGPRINT3("AutoRotatio Initial Param: %d %d %d\n", linfo->arInitial.nRot, linfo->arInitial.Method, linfo->arInitial.iter);	
}

