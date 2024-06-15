/*
# lmrcImageBilateral.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageBilateral.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRC_IMAGE_BILATERAL_FILTER_H 
#define LMRC_IMAGE_BILATERAL_FILTER _H

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */


typedef enum lmrcImageBilateralFilterInfoMode {
	lmrcImageBilateralFilterInfoModeGaussian = 0,
	lmrcImageBilateralFilterInfoModeLorentzian = 1 
} lmrcImageBilateralFilterInfoMode;

typedef struct lmrcImageBilateralFilterInfo {
	/* kernelSize */
	int									flagKernelSize;
	mrcImageParaTypeIntegerCoord 		kernelSize;

	/* Space */
	mrcImageParaTypeRealCoord 			sigmaSpace;	
 	lmrcImageBilateralFilterInfoMode 	sigmaSpaceMode;

	/* Density */
	mrcImageParaTypeReal				sigmaDensity;	
 	lmrcImageBilateralFilterInfoMode 	sigmaDensityMode;
} lmrcImageBilateralFilterInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageBilateralFilter(mrcImage* out, mrcImage* in, lmrcImageBilateralFilterInfo linfo, int mode);
extern void lmrcImageBilateralFilterUsage(FILE* fpt);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRC_IMAGE_BILATERAL_FILTER_H */ 
