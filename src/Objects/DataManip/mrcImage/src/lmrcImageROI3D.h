#ifndef  LMRC_IMAGE_ROI3D_H 
#define  LMRC_IMAGE_ROI3D_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#include "genUtil.h"
#include "mrcImage.h"
 
/* struct begin */
typedef struct lmrcImageROI3DInfo {
	mrcImageParaTypeReal z1;
	mrcImageParaTypeReal z2;
	int flagz; /* This is a dummy parameter the current version for the future */ 
	int flagx;
	mrcImageParaTypeReal x1;
	mrcImageParaTypeReal x2;
	int flagy;
	mrcImageParaTypeReal y1;
	mrcImageParaTypeReal y2;
} lmrcImageROI3DInfo;
/* struct end */

/* prototype begin */
 extern void lmrcImageROI3D(mrcImage* out,
							mrcImage* in,
							lmrcImageROI3DInfo* info);
/* prototype end */
#endif
