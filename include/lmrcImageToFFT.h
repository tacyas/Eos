/*
# lmrcImageToFFT.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageToFFT.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGETOFFT_H 
#define LMRCIMAGETOFFT_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageToFFT(mrcImage* out, mrcImage* in, mrcImageParaTypeRealCoord center, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGETOFFT_H */ 
