/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationRValueSet.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationRValueSet.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_R_VALUE_SET_H 
#define  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_R_VALUE_SET_H

#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"


/* prototype begin */
void lmrcImageSecondNoiseReductionByRelaxationRValueSet( double *r, double *densityLevel,
							lmrcImageNoiseReductionByRelaxationInfo* info);
/* prototype end */

#endif
