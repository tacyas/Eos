/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMove.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMove.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_MOVE_H 
#define  LMRC_IMAGE_MOVE_H

#include "mrcImage.h"
#include "Matrix3D.h"

/* struct begin */
typedef enum lmrcImageMoveMode {
	lmrcImageMoveModePixelUnit=0
} lmrcImageMoveMode;
/* struct end */

/* prototype begin */
extern void lmrcImageMoveModePrint(FILE* fpt); 
extern void lmrcImageMove(mrcImage* out, mrcImage* in, double x, double y, double z, lmrcImageMoveMode mode); 

/* lmrcImageTrans.c */
extern void lmrcImageTrans(mrcImage* out, mrcImage* in, Matrix3D mat, int mode);

/* prototype end */

#endif




