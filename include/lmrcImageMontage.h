/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMontage.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMontage.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_MONTAGE_H 
#define  LMRC_IMAGE_MONTAGE_H

#include "mrcImage.h"
#include "lmrcImagePad.h"

/* struct begin */
typedef struct lmrcImageMontageInfo {
	lmrcImagePadMode PadMode;
	lmrcImagePadInfo PadInfo;
	int nx;
	int ny;
	int                  flagMaxValue;
	mrcImageParaTypeReal MaxValue;	
	int                  flagValueAssignedToMax;
	mrcImageParaTypeReal ValueAssignedToMax;	

	int flagEdgeAverage;
	int EdgeAverageWindow;
	int flagNoAverage;
} lmrcImageMontageInfo;
/* struct end */

/* prototype begin */
extern int lmrcImageMontageCreate(mrcImage* out, mrcImage* in, int imageNum, lmrcImageMontageInfo linfo, int mode);
/* prototype end */


#endif /* LMRC_IMAGE_MONTAGE_H  */

