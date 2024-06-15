/*
# lmrcImageFourierNeighborCorrelation.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFourierNeighborCorrelation.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_FOURIER_NEIGHBOR_CORRELATION_H 
#define LMRCIMAGE_FOURIER_NEIGHBOR_CORRELATION_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */

typedef enum lmrcImageFourierNeighborCorrelationCentreMode {
	lmrcImageFourierNeighborCorrelationCentreModeCentre = 0,
	lmrcImageFourierNeighborCorrelationCentreModeBottomLeft = 1, 
	lmrcImageFourierNeighborCorrelationCentreModeUseStartN = 2 
} lmrcImageFourierNeighborCorrelationCentreMode; 

/* constant end */

/* struct begin */

typedef struct lmrcImageFourierNeighborCorrelationInfo {
	lmrcImageFourierNeighborCorrelationCentreMode flagCentre;
	mrcPixelDataHowToGet shiftMode;
	double delta;

	int flagPredictedFSC;
	mrcImage objMask;  // 1: Object
	mrcImage backMask; // 1: Background 
} lmrcImageFourierNeighborCorrelationInfo;

typedef struct lmrcImageFourierNeighborCorrelationResult {
	int     nR;
	double* R;
	double* data;
	int* N;
	double  FNCF;
	double  FNCN;
	double* FNCFs;
	double* FNCNs;
	double* SNR; 
	double* FSC; 

    int flagFSCfull;
	double* FSCfull;

	int flagCref;
	double* Cref;

	int flagNoiseWeighted;
	double  Brestore;
	double* NoiseWeighted;

} lmrcImageFourierNeighborCorrelationResult;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void
lmrcImageFourierNeighborCorrelation(lmrcImageFourierNeighborCorrelationResult* res, 
	mrcImage* in,
	lmrcImageFourierNeighborCorrelationInfo linfo, int mode);

extern void
lmrcImageFourierNeighborCorrelationPrint(FILE* fpt,
	lmrcImageFourierNeighborCorrelationResult* res, 
	lmrcImageFourierNeighborCorrelationInfo linfo, int mode);

extern void
lmrcImageFourierNeighborCorrelationPrintCentreMode(FILE* fpt);
/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_FOURIER_NEIGHBOR_CORRELATION_H */ 
