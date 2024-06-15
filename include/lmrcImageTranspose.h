/*
# lmrcImageTranspose.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageTranspose.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_TANSPOSE_H 
#define LMRCIMAGE_TANSPOSE_H 

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

void lmrcImageTransposeUsage(FILE* fpt);
void lmrcImageTranspose(mrcImage* out , mrcImage* in ,int mode ,int mode2);
  


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
