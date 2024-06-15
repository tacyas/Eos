/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageNormalizing ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lmrcImageNormalizing
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_NORMALIZING_H 
#define  LMRC_IMAGE_NORMALIZING_H

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "nr2.h"

/* struct begin */
typedef float lmrcImageNormalizingParaTypeReal;
typedef enum lmrcImageNormalizingMode {
	lmrcImageNormalizingModeDoubleExponential=0,
	lmrcImageNormalizingModeMinMax=1,
	lmrcImageNormalizingModeUsingContour=2,
	lmrcImageNormalizingModeUsingContourWithSolventFlattening=3,
	lmrcImageNormalizingModeNoEstimation=4,
	lmrcImageNormalizingModeAssumeGaussian=5,
	lmrcImageNormalizingModeMin75percent=6,
	lmrcImageNormalizingModeUsingLowValueAreaToHighValueArea=7
} lmrcImageNormalizingMode ;

typedef struct lmrcImageNormalizingInfo {
	lmrcImageNormalizingParaTypeReal A;
	lmrcImageNormalizingParaTypeReal B; /* A x + B */
	lmrcImageNormalizingParaTypeReal ContourMin;
	lmrcImageNormalizingParaTypeReal ContourMax;
	lmrcImageNormalizingParaTypeReal ContourSolvent;
	lmrcImageNormalizingParaTypeReal thresOfLowValueArea;
	lmrcImageNormalizingParaTypeReal thresOfHighValueArea;
	lmrcImageNormalizingMode Mode;
    FILE* paramOut;
} lmrcImageNormalizingInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageNormalizing(mrcImage* out, mrcImage* in, lmrcImageNormalizingInfo* linfo, int mode);
extern void lmrcImageNormalizingModePrint(FILE* fpt, int mode);
/* prototype end */

#endif
