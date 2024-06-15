/*
# lmrcImageAddValue.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageAddValue.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef __LMRCIMAGEADDVALUE_H
#define __LMRCIMAGEADDVALUE_H

#include "mrcImage.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void lmrcImageAddValue(mrcImage* out, mrcImage* in, float value, long mode);
extern void lmrcImageAddValueCuda(float* out, float* in, float value, int nPixel, int imageMode, int mode);
#ifdef __cplusplus
};
#endif

#endif /* __LMRCIMAGEADDVALUE_H */
