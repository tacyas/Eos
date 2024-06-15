/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageRadialDistribution.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageRadialDistribution.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_RADIAL_DISTRIBUTION_H 
#define  LMRC_IMAGE_RADIAL_DISTRIBUTION_H

#include "mrcImage.h"
#include "Vector.h"

/* struct begin */
typedef struct lmrcImageRadialDistributionInfo {
	float Cx;
	float Cy;
	float Cz;
	int flagAverage;
	int flagAzimuth;
	int NAzimuth;
	floatVector* azimuth;
} lmrcImageRadialDistributionInfo;
/* struct end */

/* prototype begin */
extern floatVector lmrcImageRadialDistribution(
		floatVector* dst, 
		mrcImage* mrc, 
		lmrcImageRadialDistributionInfo* linfo);
/* prototype end */

#endif
