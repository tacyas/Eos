/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMasking ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMasking
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_MASKING_H 
#define  LMRC_IMAGE_MASKING_H

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* struct begin */
typedef enum lmrcImageMaskingInfoShape {
	lmrcImageMaskingInfoShapeSphere=0,
	lmrcImageMaskingInfoSquare=1,
	lmrcImageMaskingInfoCylinder=2,
	lmrcImageMaskingInfoRoundedSquare=3,
	lmrcImageMaskingInfoCone=4,
	lmrcImageMaskingInfoSquareCone=5,
	lmrcImageMaskingInfoRoundedSquareCone=6,
	lmrcImageMaskingInfoSquareConePlatform=7,
	lmrcImageMaskingInfoRoundedSquareConePlatform=8
} lmrcImageMaskingInfoShape;

typedef struct lmrcImageMaskingInfo {
        mrcImageParaTypeRealCoord n;
        mrcImageParaTypeRealCoord c;
        
		// 
		int flagRotation;
		char Euler[4];
		mrcImageParaTypeReal Rot1; 
		mrcImageParaTypeReal Rot2; 
		mrcImageParaTypeReal Rot3;  

		//
       	lmrcImageMaskingInfoShape shape;
        long mode;
} lmrcImageMaskingInfo;

/* struct end */

/* prototype begin */
extern void lmrcImageMasking(mrcImage* out, mrcImage* in, lmrcImageMaskingInfo* linfo, int mode);
/* prototype end */

#endif


