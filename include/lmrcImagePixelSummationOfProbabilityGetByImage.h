/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImagePixelSummationOfProbabilityGetByImage.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImagePixelSummationOfProbabilityGetByImage.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_PIXEL_SUMMATION_OF_PROBABILITY_GET_BY_IMAGE_H 
#define  LMRC_IMAGE_PIXEL_SUMMATION_OF_PROBABILITY_GET_BY_IMAGE_H

#include <math.h>
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "genUtil.h"

/* prototype begin */
extern void lmrcImagePixelSummationOfProbabilityGetByImage(mrcImage* out, mrcImage* in, 
						    double *densityLevel,
						    lmrcImageNoiseReductionByRelaxationInfo* info);
/* prototype end */

#endif 
