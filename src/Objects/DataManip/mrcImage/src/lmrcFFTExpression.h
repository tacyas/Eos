/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTExpression.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTExpression
#%Z% Attention
#%Z%
*/

#ifndef MRC_FFT_EXPRESSION_H
#define MRC_FFT_EXPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype begin */
void lmrcFFTExpressionModePrint(FILE* fpt);

void lmrcFFTExpression(mrcImage* img, mrcImage* fft, double th ,int mode);
long lmrcFFTExpressionOffset(mrcImage* fft);
void
lmrcFFTAmplitude(mrcImage* img, mrcImage* fft);
void 
lmrcFFTLogAmplitude(mrcImage* img, mrcImage* fft ,double data);
void 
lmrcFFTPower(mrcImage* img, mrcImage* fft);
void 
lmrcFFTLogPower(mrcImage* img, mrcImage* fft ,double data);
void 
lmrcFFTPhase(mrcImage* img, mrcImage* fft);
void
lmrcFFTReal(mrcImage* img, mrcImage* fft);
/* prototype end */

#endif
