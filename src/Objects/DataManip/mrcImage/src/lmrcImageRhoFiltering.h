/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageRhoFiltering.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageRhoFiltering.h 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_RHO_FILTERING_H 
#define  LMRC_IMAGE_RHO_FILTERING_H

#include "mrcImage.h"
#include "Matrix3D.h"

typedef struct lmrcImageRhoFilteringInfo {
	int 	counterThresholdMode;	  
	double 	counterThreshold;
	int	   	weightMode;
	int    	flagThicknessWeight;
	int	   	SubSampling;
} lmrcImageRhoFilteringInfo;

typedef enum lmrcImageRhoFiltering1Mode {
	lmrcImageRhoFilter1ModeRhoFilter  = 0,
	lmrcImageRhoFilter1ModeRamLak     = 1,
	lmrcImageRhoFilter1ModeSheppLogan = 2,
	lmrcImageRhoFilter1ModeCosine     = 3
} lmrcImageRhoFiltering1Mode;

typedef struct lmrcImageRhoFiltering1Info {
	double Rmax;
	lmrcImageRhoFiltering1Mode filterMode;
} lmrcImageRhoFiltering1Info;

/* For double tilt mode */
/*
	mode 0: Preparing mode for final Rho Filtering 
	mode 1: Final treatment : RhoFiltering 
*/

/* prototype begin */
extern void lmrcImageRhoFiltering2(mrcImage* out3D, mrcImage* counter, int index, Matrix3D m, lmrcImageRhoFilteringInfo* linfo, long mode);

/* For single tilt mode */
extern void lmrcImageRhoFiltering(mrcImage* out, mrcImage* in, Matrix3D m, lmrcImageRhoFiltering1Info linfo, long mode);
/* prototype end */

#endif
