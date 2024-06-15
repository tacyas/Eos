/*
# lmrcImageNoiseCreate.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageNoiseCreate.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_NOISE_CREATE_H 
#define LMRCIMAGE_NOISE_CREATE_H  

#include <stdio.h>
#include "mrcImage.h" 
#include "mrcRefUtil.h" 

/* constant begin */


/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageNoiseCreate(mrcImage* out, mrcImage* in, float Noise, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_NOISE_CREATE_H */ 
