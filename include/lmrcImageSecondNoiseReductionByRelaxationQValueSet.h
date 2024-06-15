/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationQValueSet.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationQValueSet.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_Q_VALUE_SET_H 
#define  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_Q_VALUE_SET_H

#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#undef DEBUG

/* prototype begin */
extern void lmrcImageSecondNoiseReductionByRelaxationQValueSet(mrcImage* q, double* d, mrcImage* p0, double* r,
							lmrcImageNoiseReductionByRelaxationInfo* info);
/* prototype end */

#endif
