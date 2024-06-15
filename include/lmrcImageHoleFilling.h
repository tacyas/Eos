/*
# lmrcImageHoleFilling.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageHoleFilling.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_HOLE_FILLING 
#define LMRCIMAGE_HOLE_FILLING 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct lmrcImageHoleFillingInfo {
	int neighbor;	

	mrcImage areaWhite;
	mrcImage areaBlack;
	mrcImage labelWhite;
	mrcImage labelBlack;
	mrcImage ToneReverse;

} lmrcImageHoleFillingInfo;


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void lmrcImageHoleFilling(mrcImage* out, mrcImage* in, lmrcImageHoleFillingInfo* linfo, int mode);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
