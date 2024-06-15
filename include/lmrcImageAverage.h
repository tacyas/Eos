/*
# lmrcImageAverage.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageAverage.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"

/* prototype begin */
extern void lmrcImageAverage(mrcImage* out, mrcImage* in, int n, int mode);
extern void lmrcImageAverageOverThreshold(mrcImage* out, mrcImage* in, int n, float* cor, float thres, int mode);
extern void lmrcImageAverageWithWeight(mrcImage* out, mrcImage* outW, mrcImage* in, mrcImage* inW, int n, int mode) ;

/* prototype end */
