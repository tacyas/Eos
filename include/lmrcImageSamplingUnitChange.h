#ifndef LMRC_IMAGE_SAMPLING_UNIT_CHANGE_INFO_H
#define LMRC_IMAGE_SAMPLING_UNIT_CHANGE_INFO_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSamplingUnitChange.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSamplingUnitChange.h 
#%Z% Attention
#%Z%
*/

#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageSamplingUnitChangeInfo {
	mrcImageParaTypeRealCoord    L;
	mrcImageParaTypeIntegerCoord N;
	mrcImageParaTypeInteger      SamplingMethodMode;
} lmrcImageSamplingUnitChangeInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageSamplingUnitChange(mrcImage* out, mrcImage* in, lmrcImageSamplingUnitChangeInfo info, long mode);
/* prototype end */

#endif 

