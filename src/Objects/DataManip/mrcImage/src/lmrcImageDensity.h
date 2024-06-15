/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDensity ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDensity
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_DENSITY_H 
#define  LMRC_IMAGE_DENSITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageModeChange.h"
#include "Vector.h"

/* struct begin */
typedef struct lmrcImageDensityInfoInfo {
	floatVector percentageVolume;
	mrcImageParaTypeRealCoord centreOfGravity;
	mrcImageParaTypeRealCoord centreOfGravitySD;
	mrcImageParaTypeRealCoord max;
	mrcImageParaTypeRealCoord maxSD;
	double                    deltaVolume; 
	mrcImage in;
} lmrcImageDensityInfoInfo;

typedef enum lmrcImageDensityInfoMode {
	mrcImageDensityInfoPercentageVolume  =1,
	mrcImageDensityInfoCentreOfGravity   =2,
	mrcImageDensityInfoMax               =4,
	mrcImageDensityInfoCentreOfGravitySD =8,
	mrcImageDensityInfoMaxSD             =16
} lmrcImageDensityInfoMode;

typedef struct lmrcImageDensityChangeEsitmationInfo0 {
	mrcImageParaTypeRealCoord change;
	mrcImageParaTypeRealCoord changeSD;
	double                    delta;
	double                    deltaSD;
	double                    deltaXY;
	double                    deltaXYSD;
} lmrcImageDensityChangeEstimationInfo0;

typedef struct lmrcImageDensityChangeEsitmationInfo {
	lmrcImageDensityChangeEstimationInfo0 CG;
	lmrcImageDensityChangeEstimationInfo0 Max;
	mrcImage in1;
	mrcImage in2;
} lmrcImageDensityChangeEstimationInfo;

typedef enum lmrcImageDensityChangeEstimationMode {
	mrcImageDensityChangeEstimationCentreOfGravity   =2,
	mrcImageDensityChangeEstimationMax               =4,
	mrcImageDensityChangeEstimationCentreOfGravitySD =8,
	mrcImageDensityChangeEstimationMaxSD             =16
} lmrcImageDensityChageEstimationMode;

/* struct end */


/* prototype begin */

extern void lmrcImageDensityInfoModePrint(FILE* fpt);

extern void lmrcImageDensityInfo(lmrcImageDensityInfoInfo* linfo, mrcImage* in, long mode);
extern void lmrcImageDensityInfoWrite(FILE* fpt, lmrcImageDensityInfoInfo* linfo, long mode);

extern floatVector lmrcImageDensityInfoPercentageVolume(mrcImage* in, double delta, long mode);
extern mrcImageParaTypeRealCoord lmrcImageDensityInfoCentreOfGravity(mrcImage* in, long mode);
extern mrcImageParaTypeRealCoord lmrcImageDensityInfoMax(mrcImage* in, long mode);
extern mrcImageParaTypeRealCoord lmrcImageDensityInfoSD(mrcImage* in, mrcImageParaTypeRealCoord centre, long mode);

extern void lmrcImageDensityChangeEstimationModePrint(FILE* fpt);
extern void lmrcImageDensityChangeEstimation(lmrcImageDensityChangeEstimationInfo* linfo, mrcImage* in1, mrcImage* in2, long mode); 
extern void lmrcImageDensityChangeEstimationWrite(FILE*fpt, lmrcImageDensityChangeEstimationInfo* linfo, long mode); 
extern void lmrcImageDensityChangeEstimationCentreOfGravity(lmrcImageDensityChangeEstimationInfo0* linfo, mrcImage* in, mrcImage* in2, long mode);
extern void lmrcImageDensityChangeEstimationMax(lmrcImageDensityChangeEstimationInfo0* linfo, mrcImage* in, mrcImage* in2, long mode);

extern void lmrcImageDensityChangeEstimationSD(lmrcImageDensityChangeEstimationInfo0* linfo,
																	mrcImage* in1, mrcImage* in2, long mode);

/* prototype end */

#endif

