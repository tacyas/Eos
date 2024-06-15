/*
# lmrcImageHoughTransform.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageHoughTransform.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_HOUGH_TRANSFORM 
#define LMRCIMAGE_HOUGH_TRANSFORM 

#include <stdio.h>
#include <stdlib.h>
#include "mrcImage.h"

/* constant begin */

typedef enum lmrcImageHoughTransformMode {
    lmrcImageHoughTransformModeLines=0,
    lmrcImageHoughTransformModeTwoLines,
    lmrcImageHoughTransformModeOpenTwoLines,
    lmrcImageHoughTransformModeRectangles,
    lmrcImageHoughTransformModeFilledRectangles,
    lmrcImageHoughTransformModeCircles,
    lmrcImageHoughTransformModeFilledCircles,
    lmrcImageHoughTransformModeGivenStructure
} lmrcImageHoughTransformMode;

/* constant end */

/* struct begin */


typedef struct lmrcImageHoughTransformInfo {
    double deltaRho;   /* pixel */
    double deltaTheta; /* radian */

	lmrcImageHoughTransformMode HoughSpaceMode;
	// for TwoLines, Rectangle, FilledRectangle
	double widthMin; 
	double widthMax; 
	double widthOut;
	double heightMin;
	double heightMax;
	double heightOut;
	mrcImageMode InterpolationMode; 

	// Inverse
	int Nx;
	int Ny;
	double dx;
	double dy;
} lmrcImageHoughTransformInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageHoughTransformSpaceModePrint(FILE* fpt);

extern void lmrcImageHoughTransform(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformInit(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformTwoLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformFilledRectangles(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);

extern void lmrcImageHoughTransformInverse(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformInverseInit(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformInverseLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);
extern void lmrcImageHoughTransformInverseTwoLines(mrcImage* out, mrcImage* in, lmrcImageHoughTransformInfo* linfo, int mode);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_HOUGH_TRANSFORM */ 
