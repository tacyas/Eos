/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFilterCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFilterCreate 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_FILTER_CREATE_H 
#define  LMRC_IMAGE_FILTER_CREATE_H


#include "mrcImage.h"

/* struct begin */
typedef enum lmrcImageFilterCreateMode {
	lmrcImageFilterModeSquare=0,
	lmrcImageFilterModeCircle=1
} lmrcImageFilterCreateMode;

typedef struct lmrcImageFilterCreateInfo {
	mrcImageParaTypeInteger    np;
	mrcImageParaTypeRealCoord* p;
	mrcImageParaTypeReal*      weight;

	mrcImageParaTypeIntegerCoord N;

	mrcImageParaTypeIntegerCoord Size;

	lmrcImageFilterCreateMode shape;
	long                      outputMode;
} lmrcImageFilterCreateInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageFilterInfoFileRead(FILE* fpt, lmrcImageFilterCreateInfo* linfo, int mode);
extern void lmrcImageFilterInfoPrint(FILE* fpt, lmrcImageFilterCreateInfo linfo, int mode);
extern void lmrcImageFilterInfoFileFormat(FILE* fpt, int mode);
extern void lmrcImageFilterCreate(mrcImage* fpt, lmrcImageFilterCreateInfo linfo, int mode);
/* prototype end */

#endif

