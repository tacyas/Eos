/*
# mrcImageGetPixelsCUDA.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageGetPixelsCUDA.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef MRCIMAGE_GET_PIXELS_CUDA_H 
#define MRCIMAGE_GET_PIXELS_CUDA_H  

#include <stdio.h>

/* constant begin */


/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void mrcPixelsDataGetCUDA(float* out, float* inCoord, int num, float* in, mrcImageMode imageMode,  int nx, int ny, int nz, mrcPixelDataType type,  mrcPixelDataHowToGet howToMode);


extern void mrcPixelDataGetbyMatrix3DCUDA(float* out, float* mat, float* in, mrcImageMode imageMode, int nx, int ny, int nz, mrcPixelDataType type, mrcPixelDataHowToGet howToMode);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /*  MRCIMAGE_GET_PIXELS_CUDA_H */ 
