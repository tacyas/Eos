/*
# mrcImageAutoRotationAverage : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageAutoRotationAverage
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"
#include "lmrcImageAverage.h"
#include "lmrcImageCorrelation.h"

/*
Example:
typedef struct lmrcImageAutoRotationAverageInfo {
	float a;
	int   b;
} lmrcImageAutoRotationAverageInfo;

typedef enum lmrcImageAutoRotationAverageMode {
	a=0,
	b=1
} lmrcImageAutoRotationAverageMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage* in;
	mrcImage  ref;
	mrcImage* fit;
	mrcImage* cor;
	float* corC;
	mrcImage  out;
	mrcImageAutoRotationAverageInfo info;
	lmrcImageAutoRotationCorrelationInfo* linfo;
	int i, k;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	in  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	fit = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	cor = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	corC = (float*)memoryAllocate(sizeof(float)*info.flagIn, "in main");
	linfo = (lmrcImageAutoRotationCorrelationInfo*)memoryAllocate(sizeof(lmrcImageAutoRotationCorrelationInfo)*info.flagIn, "in main");
	for(i=0; i<info.flagIn; i++) {
		mrcFileRead(&(in[i]), info.In[i], "in main", 0);
	}
	if(info.flagRef) {
		mrcFileRead(&ref, info.Ref, "in main", 0);
	} else {
		fprintf(stderr, "FileImage(%s) is used as a reference.\n", info.In[0]);
		mrcFileRead(&ref, info.In[0], "in main", 0);
	}

	// linfo
	for(i=0; i<info.flagIn; i++) {
		linfo[i].iter = info.iter;
		linfo[i].nRot = (int)((info.Max - info.Min)/info.Delta)+1;
		linfo[i].Method = info.Method;
		linfo[i].flagRestrictionArea = 1;
		linfo[i].thetaMin = info.Min*RADIAN;
		linfo[i].thetaMax = info.Max*RADIAN;
	}

	for(k=0; k<info.maxIter; k++) {
		for(i=0; i<info.flagIn; i++) {
			DEBUGPRINT2("%d: %d\n", k, i);
			lmrcImageAutoRotationCorrelation(&(fit[i]), &(cor[i]), &(in[i]), &ref, &(linfo[i]), info.CorMode);
			corC[i] = linfo[i].LinearCorrelation;
		}
		lmrcImageAverageOverThreshold(&out, fit, info.flagIn, corC, info.Thres, info.mode);
		mrcImageFree(&ref, "in main");
		ref = out;
	}

	lmrcImageAverageOverThreshold(&out, fit, info.flagIn, corC, info.Thres, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	
	for(i=0; i<info.flagIn; i++) {
		float w;
		if(corC[i]<info.Thres) {
			w = 0;
		} else {
			w = 1;
		}
		fprintf(info.fptLog, "%d weight %f correlation %f linesr %f theta %f at %f %f\n", 
					i, 
					w,
					linfo[i].max, 
					linfo[i].LinearCorrelation, 
					linfo[i].maxTheta*DEGREE, linfo[i].maxP.x, linfo[i].maxP.y
					);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- -Mode -----\n");
	lmrcImageCorrelationModePrint(stderr);

}
