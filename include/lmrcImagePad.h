#ifndef  LMRC_IMAGE_PAD_H 
#define  LMRC_IMAGE_PAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"

/* struct begin */
typedef struct lmrcImagePadInfo {
	mrcImageParaTypeInteger Width;
	mrcImageParaTypeInteger Height;
	mrcImageParaTypeReal Value;
	mrcImageParaTypeReal AWSize;
	mrcImageParaTypeReal AWMin;
	mrcImageParaTypeReal AWMax;
	mrcImageParaTypeReal ExpectedValue;
	int flagExpectedValue;	
	mrcImageParaTypeReal TiltAxisAngle;
	mrcImageParaTypeReal TiltAngle;
} lmrcImagePadInfo;

typedef enum lmrcImagePadMode {
	lmrcImagePadModeAverage                   = 0,
	lmrcImagePadModeAveragedYAxis             = 1,
	lmrcImagePadModeDynamicAveragedYAxis      = 2,
	lmrcImagePadModeAveragedEdge              = 3,
	lmrcImagePadModeBottomLeft                = 4,
	lmrcImagePadModeCenterWithoutAveraging    = 5,
	lmrcImagePadModeBottomLeftWithoutAveraging= 6,
	lmrcImagePadModeAveragedOutsideCircle     = 7,
	lmrcImagePadModeAveragedOutsideRing       = 8, 
	lmrcImagePadModeByValue                   = 9,
	lmrcImagePadModePeripheryMaskingByValue   = 10,
	lmrcImagePadModeNormalizedByBgAvgAndBgAvgOffset    = 11,
	lmrcImagePadModeNormalizedByImgVarAndImgAvgOffset  = 12,
	lmrcImagePadModeNormalizedByBgVarAndBgAvgOffset    = 13,
	lmrcImagePadModeNormalizedByDifferenceBeteweenImgAvgAndBgAvg    = 14,
	lmrcImagePadModeTiltedImageCircleAverage		        = 15,
	lmrcImagePadModeDynamicAveragedXYAxis      = 16
} lmrcImagePadMode;
/* struct end */

/* prototype begin */
extern void lmrcImagePad(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, lmrcImagePadMode mode);
extern void lmrcImagePadModePrint(FILE* fpt);
extern void __lmrcImagePadTiltImage(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad0(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad1(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad2(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad3(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad4(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad5(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad6(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad7(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad8(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad9(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad10(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad11(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad12(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad13(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad14(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad15(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
extern void __lmrcImagePad16(mrcImage* out, mrcImage* in, lmrcImagePadInfo* info, long mode);
/* prototype end */

#endif

