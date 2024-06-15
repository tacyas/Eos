#ifndef  LMRC_IMAGE_PROJECTION_H 
#define  LMRC_IMAGE_PROJECTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageProjectionInfo{
	long mode;
	} lmrcImageProjectionInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageProjection(mrcImage* out, mrcImage* in,
								lmrcImageProjectionInfo* linfo);
extern void lmrcImageProjectionMIP(mrcImage* out, mrcImage* in,
								lmrcImageProjectionInfo* linfo);
/* prototype end */
#endif
