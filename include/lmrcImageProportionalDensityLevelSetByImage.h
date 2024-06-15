/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageProportionalDensityLevelSetByImage.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageProportionalDensityLevelSetByImage.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_PROPORTIONAL_DENSITY_LEVELSET_BY_IMAGE_H 
#define  LMRC_IMAGE_PROPORTIONAL_DENSITY_LEVELSET_BY_IMAGE_H

#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"

/* prototype begin */
extern void lmrcImageProportionalDensityLevelSetByImage(double *densityLevel, 
						 lmrcImageNoiseReductionByRelaxationInfo* info);
/* prototype end */
#endif
