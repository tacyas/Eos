/*
# lmrcImageUnsharpening.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageUnsharpening.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGEUNSHARPENING_H 
#define LMRCIMAGEUNSHARPENING_H 

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

extern void lmrcImageUnsharpeningUsage(FILE* fpt);
extern void lmrcImageUnsharpening(mrcImage* out, mrcImage* in, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGEUNSHARPENING_H */ 
