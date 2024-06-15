/*
# lmrcImageMorphology.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageMorphology.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_MORPHOLOGY_H 
#define LMRCIMAGE_MORPHOLOGY_H 

#include <stdio.h>
#include <stdlib.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */
typedef struct lmrcImageMorphologyInfo {
	mrcImage SE; /* Structuring Elements */  

	/* for SE*/
	int n;      /* for Any size */ 
	int nx;
	int ny;
	int nz;
	int radius; /* for Disk/Sphere/Cylinder*/

	/* SE feature */
	int mode;
} lmrcImageMorphologyInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

/* lmrcImageMorphology.c */
void lmrcImageMorphologyStructuringElementSet(lmrcImageMorphologyInfo* linfo, int mode);
void lmrcImageMorphologyStructuringElementSetInfoPrint(FILE* fpt);
void lmrcImageMorphologyStructuringElement2DCross(mrcImage* out, int mode);
void lmrcImageMorphologyStructuringElement2DSquare(mrcImage* out, int mode);
void lmrcImageMorphologyStructuringElement2DDisk(mrcImage* out, int r, int n, int mode);
void lmrcImageMorphologyStructuringElement3DCross(mrcImage* out, int mode);
void lmrcImageMorphologyStructuringElement3DCubic(mrcImage* out, int mode);
void lmrcImageMorphologyStructuringElement3DSphere(mrcImage* out, int r, int n, int mode);
void lmrcImageMorphologyStructuringElementSphere(mrcImage* out, int r, int nx, int ny, int nz, int mode);
void lmrcImageMorphologyStructuringElement2DRectangle(mrcImage* out, int nx, int ny, int mode);
void lmrcImageMorphologyStructuringElement3DCuboid(mrcImage* out, int nx, int ny, int nz, int mode);
void lmrcImageMorphologyStructuringElement3DCylinder(mrcImage* out, int r, int nx, int ny, int nz, int mode);

/* lmrcImageErosion.c */
void lmrcImageErosion(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int mode);

/* lmrcImageDilation.c */
void lmrcImageDilation(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int mode);

/* lmrcImageOpening.c */
void lmrcImageOpening(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode);

/* lmrcImageClosing.c */
void lmrcImageClosing(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode);

/* lmrcImageTopHatTransform.c */
void lmrcImageTopHatTransform(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode);

/* lmrcImageBottomHatTransform.c */
void lmrcImageBottomHatTransform(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
