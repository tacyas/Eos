/*
# lmrcImageFloating.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFloating.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_FLOATHING_H 
#define LMRCIMAGE_FLOATHING_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */
typedef enum lmrcImageFloatingMode {
	lmrcImageFloatingModeAllMean             = 0,
	lmrcImageFloatingModeSphereSurfaceMean   = 1,
	lmrcImageFloatingModeCylinderSurfaceMean = 2,
	lmrcImageFloatingModeEdgePixel           = 3
} lmrcImageLFloatingMode;

/* constant end */

/* struct begin */
typedef struct lmrcImageFloatingInfo {
	// Input
	double value; /* to Floating Value */

	// Output
	mrcImageInformation info;
} lmrcImageFloatingInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

void lmrcImageFloatingModePrint(FILE* fpt);
void lmrcImageFloating(mrcImage* out, mrcImage* in, lmrcImageFloatingInfo* linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
