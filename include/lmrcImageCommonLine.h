#ifndef LMRC_IMAGE_COMMON_LINE_H
#define LMRC_IMAGE_COMMON_LINE_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCommonLine.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCommonLine.h 
#%Z% Attention
#%Z%
*/

#include "mrcImage.h"

/* struct begin */

typedef enum lmrcImageCommonLineMode {
	lmrcImageCommonLineModeImageCenterIsGC = 1
} lmrcImageCommonLineMode;


typedef enum lmrcImageCommonLineSearchMode {
	lmrcImageCommonLineSearchModeFourierSpace = 0,
	lmrcImageCommonLineSearchModeRealSpace = 1 
} lmrcImageCommonLineSearchMode;

typedef struct lmrcImageCommonLineInfo {
	/* Input */
	double dtheta;
	lmrcImageCommonLineSearchMode searchMode; 
	/* Output */
	double optimumThetaIn;
	double optimumThetaRef;
	double optimumCor; 
} lmrcImageCommonLineInfo;

/* struct end */

/* prototype begin */
extern void lmrcImageCommonLineSearch(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageCommonLineInfo* linfo, int mode);
extern void lmrcImageCommonLineInfoOutput(FILE* fpt, lmrcImageCommonLineInfo* linfo, int mode);

extern void lmrcImageCommonLineInfoUsage(FILE* fpt);
/* prototype end */

#endif

