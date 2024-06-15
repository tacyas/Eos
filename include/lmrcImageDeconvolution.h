/*
# lmrcImageDeconvolution.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageDeconvolution.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_DECONVOLUTON_H 
#define LMRCIMAGE_DECONVOLUTON_H 

#include <stdio.h>
#include "mrcImage.h" 
#include "lmrcImage3DPad.h" 
#include "lmrcImageMultiplying.h" 
#include "lmrcImageSubtractionCalc.h" 
#include "lmrcImageDensityNormalizationByImage.h"
#include "lmrcImageSigmaCalculate.h"
#include "lmrcImageAddValue.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef enum lmrcImageDeconvolutionInfoMode {
	lmrcImageDeconvolutoinInfoModeNoConvolution  = 0,
    lmrcImageDeconvolutoinInfoModePhaseFlipping  = 1,
	lmrcImageDeconvolutoinInfoModeCTFMultiplying = 2,
	lmrcImageDeconvolutoinInfoModeInverseFilter  = 3,
	lmrcImageDeconvolutoinInfoModeWienerFilter   = 4,
	lmrcImageDeconvolutoinInfoModePhaseFlippingCTFWeighted = 5,
	lmrcImageDeconvolutoinInfoModeInverseFilterNoPhaseFlipping = 6,
	lmrcImageDeconvolutoinInfoModeWienerFilterNoPhaseFlipping  = 7,
	lmrcImageDeconvolutoinInfoModeWienerFilterRDependent       = 8,
	lmrcImageDeconvolutoinInfoModeWienerFilterRDependentNoPhaseFlipping = 9
} lmrcImageDeconvolutionInfoMode;

typedef enum lmrcImageDeconvolutionInfoKernelCentre {
	lmrcImageDeconvolutoinInfoKernelCentreBottomLeft = 0,
    lmrcImageDeconvolutoinInfoKernelCentreCentre = 1
} lmrcImageDeconvolutionInfoKernelCentre;

typedef struct lmrcImageDeconvolutionInfo {
	// Input
	double			   thresCTF;
	double			   NSRatio;
	double			   NSCoeff;
	int                Pad3DMode; 	 
 	lmrcImage3DPadInfo Pad3DInfo;	
	int maxIter;
	double minRMSD;
	double lambda;
	lmrcImageDeconvolutionInfoKernelCentre KernelCentreMode;
	int norInfoMode;

	// Output 
	int Iter;
	mrcImageInformation subInfo; 
	lmrcImageDensityNormalizationByImageInfo norInfo;
	mrcImage rmsd;
} lmrcImageDeconvolutionInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageDeconvolutionModePrint(FILE* fpt);
extern void lmrcImageDeconvolutionKernelCentrePrint(FILE* fpt);
extern void lmrcImageDeconvolution(mrcImage* out, mrcImage* convOut, mrcImage* in, mrcImage* kernel, lmrcImageDeconvolutionInfo* linfo, int mode);
extern void lmrcImageIterativeDeconvolution(mrcImage* out, mrcImage* convOut, mrcImage* in, mrcImage* kernel, lmrcImageDeconvolutionInfo* linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_DECONVOLUTON_H */ 
