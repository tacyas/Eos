#ifndef LMRC_IMAGE_SECOMD_NOISE_REDUCTION_BY_RELAXATION_H
#define LMRC_IMAGE_SECOMD_NOISE_REDUCTION_BY_RELAXATION_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxation.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxation.h 
#%Z% Attention
#%Z%
*/
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"

/* struct begin */
typedef enum lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1 {
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1SavitzyGolay = 1
} lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1;
  
typedef enum lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2 {
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2Rectangle = 1,
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2Circle = 2
} lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2;

typedef enum lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3 {
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3FiveTimesFive = 1,
  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3SevenTimesSeven = 2
} lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3;
/* struct end */

/* prototype begin */
#define XYZCOORD(x,y,z,nx,ny,nz) ((x)+(y)*(nx)+(z)*(nx)*(ny))

extern void  lmrcImageSecondNoiseReductionByRelaxation(mrcImage* out, mrcImage* pPrev, mrcImage* q, double* densityLevel,
					       lmrcImageNoiseReductionByRelaxationInfo* info);
/* prototype end */

#endif

