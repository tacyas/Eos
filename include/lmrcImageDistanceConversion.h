/*
# lmrcImageDistanceConversion.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageDistanceConversion.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#ifndef MRC_DISTANCE_CONVERSION_H
#define MRC_DISTANCE_CONVERSION_H

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */
typedef enum lmrcImageDistanceConversionMode {
	lmrcImageDistanceConversionMode4Neibour	= 0,
	lmrcImageDistanceConversionMode8Neibour	= 1,
	lmrcImageDistanceConversionMode6Neibour	= 2,
	lmrcImageDistanceConversionMode18Neibour= 3,
	lmrcImageDistanceConversionMode26Neibour= 5
} lmrcImageDistanceConversionMode;

/* constant end */

/* struct begin */


/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageDistanceConversion(mrcImage* in,mrcImage* out,int mode,int form);
extern void lmrcImageDistanceConversion_4Neighborhood(mrcImage* in,mrcImage* out);
extern void lmrcImageDistanceConversion_8Neighborhood(mrcImage* in,mrcImage* out);
extern void lmrcImageDistanceConversion_6Neighborhood(mrcImage* in,mrcImage* out);
extern void lmrcImageDistanceConversion_18Neighborhood(mrcImage* in,mrcImage* out);
extern void lmrcImageDistanceConversion_26Neighborhood(mrcImage* in,mrcImage* out);
extern void lmrcImageMakingFrame(mrcImage* in,mrcImage* out,int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
