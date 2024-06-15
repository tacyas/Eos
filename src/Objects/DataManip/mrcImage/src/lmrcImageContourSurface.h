/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageContourSurface.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageContourSurface.h 
#%Z% Attention
#%Z%
*/
#ifndef MRC_CONTOUR_SURFACE_H
#define MRC_CONTOUR_SURFACE_H


#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageContourSurfaceInfo {
	mrcImageParaTypeReal Contour;
} lmrcImageContourSurfaceInfo;

typedef enum lmrcImageContourSurfaceMode {
	lmrcImageContourSurfaceModeSimple=0
} lmrcImageContourSurfaceMode;
/* struct end */

/* prototype begin */
extern void lmrcImageContourSurfaceCreate(mrcImage* out, mrcImage* in, lmrcImageContourSurfaceInfo info, lmrcImageContourSurfaceMode mode);

/* prototype end */

#endif
