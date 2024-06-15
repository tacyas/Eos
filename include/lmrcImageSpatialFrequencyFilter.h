/*
# lmrcImageSpatialFrequencyFilter.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSpatialFrequencyFilter.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_SPATIAL_FREQUENCY_FILTER_H 
#define LMRCIMAGE_SPATIAL_FREQUENCY_FILTER_H

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */


/* constant end */

/* struct begin */

typedef struct lmrcImageSpatialFrequencyFilterInfo {
	// Weight
	int nR;
	double* R;
	double* W;

	// Low Cut
	int flagL;
	double L;

	// High Cut
	int flagH;
	double  H;
} lmrcImageSpatialFrequencyFilterInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageSpatialFrequencyFilter(mrcImage* out, mrcImage* in, lmrcImageSpatialFrequencyFilterInfo linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_SPATIAL_FREQUENCY_FILTER_H */ 
