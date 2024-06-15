/*
# lmrcImageFourierShellCorrelation.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFourierShellCorrelation.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"

typedef struct lmrcImageFourierShellCorrelationInfo  {
	double Low;
	double High;
	double Delta;
} lmrcImageFourierShellCorrelationInfo;

typedef struct lmrcImageFourierShellCorrelationResult {
	double* data;
	int*    N;
    double* R;
	int     nR;

	int flagSNR;
	double* SNR;

	int flagFSCfull;
	double* FSCfull;

	int flagCref;
	double* Cref;

	int flagNoiseWeighted;
	double  Brestore;
	double* NoiseWeighted;
} lmrcImageFourierShellCorrelationResult; 

extern void lmrcImageFourierShellCorrelation(lmrcImageFourierShellCorrelationResult* res, mrcImage* in1 ,mrcImage* in2, lmrcImageFourierShellCorrelationInfo linfo ,int mode, int mode2);

extern void lmrcImageFourierShellCorrelationPrint(FILE* fpt, lmrcImageFourierShellCorrelationResult* res, lmrcImageFourierShellCorrelationInfo linfo ,int mode, int mode2);
