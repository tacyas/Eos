#ifndef LMRC_IMAGE_FIRST_NOISE_REDUCTION_BY_RELAXATION_H
#define LMRC_IMAGE_FIRST_NOISE_REDUCTION_BY_RELAXATION_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFirstNoiseReductionByRelaxation.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFirstNoiseReductionByRelaxation.h 
#%Z% Attention
#%Z%
*/
#include "mrcImage.h"

/* struct begin */   
typedef struct lmrcImageNoiseReductionByRelaxationInfo {
  /* input */
  /* OR Output */
  double SD;
  double datamax;
  double datamin;
  long classNumber;
  int ddimx; 
  int ddimy;
  int ddimz;
} lmrcImageNoiseReductionByRelaxationInfo;

typedef enum lmrcImageNoiseReductionByRelaxationMode {
  lmrcImageNoiseReductionByRelaxationModeSigma = 1,
} lmrcImageNoiseReductionByRelaxationMode; 
/* struct end */

/* prototype begin */
extern void lmrcImageFirstNoiseReductionByRelaxation( mrcImage* out, mrcImage* p0, 
						     mrcImage* in, mrcImage* summationOfProbability,
						     double *densityLevel,
						     lmrcImageNoiseReductionByRelaxationInfo* info);
/* prototype end */

#endif

