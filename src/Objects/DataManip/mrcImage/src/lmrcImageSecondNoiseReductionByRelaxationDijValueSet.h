/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationDijValueSet.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationDijValueSet.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_DIJ_VALUE_SET_H 
#define  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_DIJ_VALUE_SET_H

#include <math.h>
#include "mrcImage.h"

#undef DEBUG
#include "genUtil.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate.h"

/* prototype begin */
extern void lmrcImageSecondNoiseReductionByRelaxationDijValueSet(double* d,
							  lmrcImageNoiseReductionByRelaxationInfo* info,
							  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1* mode1,
							  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2* mode2);
/* prototype end */
#endif
