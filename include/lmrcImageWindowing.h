/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageWindowing.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageWindowing.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_WINDOWING_H 
#define  LMRC_IMAGE_WINDOWING_H

#include <math.h>

/* struct begin */

typedef enum lmrcImageWindowingInfoMode {
	lmrcImageWindowingInfoModeCosWindowFixed=0,
	lmrcImageWindowingInfoModeCosWindowYVariable=1,
	lmrcImageWindowingInfoModeCosWindowXYVariable=2,
	lmrcImageWindowingInfoModeRectangleWindow=3,
	lmrcImageWindowingInfoModeHanningWindow=4,
	lmrcImageWindowingInfoModeHammingWindow=5,
	lmrcImageWindowingInfoModeBlackmanWindow=6,
	lmrcImageWindowingInfoModeDolphChebyshevWindow=7,
	lmrcImageWindowingInfoModeKaiserWindow=8,
	lmrcImageWindowingInfoModeGaussWindow=9,
	lmrcImageWindowingInfoModeExponentialWindow=10,
	lmrcImageWindowingInfoModeDownToAverage=0x10,
} lmrcImageWindowingInfoMode;


typedef struct lmrcImageWindowingInfo {
	long flagWy;
	float Wy;

	long flagWx;
	float Wx;

	long flagWyMax;
	float WyMax;

	long flagWxMax;
	float WxMax;

	double Offset;

} lmrcImageWindowingInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageWindowing(mrcImage* dst, mrcImage* src, 
	lmrcImageWindowingInfo* info, long mode);

extern void lmrcImageWindowingModePrint(FILE* fpt);
/* prototype end */

#endif
