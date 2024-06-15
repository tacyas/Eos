#ifndef LMRCIMAGE3DWINDOWING_H
#define LMRCIMAGE3DWINDOWING_H

/*
# LmrcImage3DWindowing.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DWindowing
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImage3DWindowingInfo {
	mrcImageParaTypeRealCoord center;
	mrcImageParaTypeRealCoord width;
	mrcImageParaTypeRealCoord widthCos;
	mrcImageParaTypeReal radius;
	mrcImageParaTypeReal widthofR;
	mrcImageParaTypeReal wz;
} lmrcImage3DWindowingInfo;

typedef enum lmrcImage3DWindowingMode {
	lmrcImage3DWindowingModeGaussianRectangularSolid=0,
	lmrcImage3DWindowingModeCosCylinder=1,
	lmrcImage3DWindowingModeCosSphere=2,
	lmrcImage3DWindowingModeCosSphereOffset=3
} lmrcImage3DWindowingMode;

/* struct end */

/* prototype begin */ 

extern void lmrcImage3DWindowingUsage(FILE* fpt);
extern void lmrcImage3DWindowing(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode);
extern void lmrcImage3DWindowingGaussianRectanglularSolid(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode);
extern void lmrcImage3DWindowingCosCylinder(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode);
extern void lmrcImage3DWindowingCosSphere(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode);
extern void lmrcImage3DWindowingCosSphereOffset(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode);

/* prototype end */ 

#endif 
