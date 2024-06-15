/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageBinarization.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageBinalization
#%Z% Attention
#%Z%
*/

#ifndef MRC_BINARIZATION_H
#define MRC_BINARIZATION_H

#include <stdio.h>
#include "mrcImage.h"

/* struct begin */

typedef struct lmrcImageBinarizationInfo {
	double thresHold;	
	double value;	
	int flagNear;
	double near; /* pixel unit */	
	int  nLevel; /* Histgram */
	int  width;  /* Histgram Smoothing */
	double p;
	
	int flagDeltaThreshold;
	double deltaThreshold;
	double sigmaThreshold;
}lmrcImageBinarizationInfo;

/* struct end */

/* prototype begin */

/* Binalization Methods */
extern float lmrcImageBinarization(mrcImage* out, mrcImage* in, lmrcImageBinarizationInfo linfo, int mode);
extern void    lmrcImageBinarization0(mrcImage* out, mrcImage* in, lmrcImageBinarizationInfo linfo, int mode);
extern void    lmrcImageBinarizationUsage(FILE* fpt);
extern double  lmrcImageDeterminationOfThresholdForBinarizationByKittlerMethod(mrcImage* mrc, int L, int mode);
extern double  lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(mrcImage* mrc, int L, int mode);
extern double  lmrcImageDeterminationOfThresholdForBinarizationByptileMethod(mrcImage* mrc, int L, double p, int mode);
extern double  lmrcImageDeterminationOfThresholdForBinarizationByDifferentialHistogramMethod(mrcImage* mrc, int L, int mode);
extern double  lmrcImageDeterminationOfThresholdForBinarizationByLaplacianHistogramMethod(mrcImage* mrc, int L, int mode);
extern double  determinationThresholdFromGraylevelHistogramByOhtsuMethod(int* tile, int L);


/* prototype end */

#endif
