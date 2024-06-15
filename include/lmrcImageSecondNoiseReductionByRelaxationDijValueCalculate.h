/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_DIJ_VALUE_CALCULATE_H 
#define  LMRC_IMAGE_SECOND_NOISE_REDUCTION_BY_RELAXATION_DIJ_VALUE_CALCULATE_H

#include <math.h>
#undef DEBUG
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"

/* prototype begin */
void lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate(double* d, double* dsum,
								lmrcImageNoiseReductionByRelaxationInfo* info,
								lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1* mode1,
								lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2* mode2);
/* prototype end */
#endif






