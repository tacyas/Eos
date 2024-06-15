/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDensityNormalizationByImage.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDensityNormalizationByImage.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_DENSITY_NORMALIZATION_BY_IMAGE_H 
#define  LMRC_IMAGE_DENSITY_NORMALIZATION_BY_IMAGE_H

#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageDenstiyNormalizationByImageInfo {
  /* Input */
  double sigma;

  /* Region Information */
  int flagCylinder;	
  float centerx, centery;
  float minr, maxr;
  /* Fitting Mode */
  int fitMode;
  float tstBGMin;
  float tstBGMax;
  float tstBGDelta;

  /* Output */
  float a;
  float b;
  float sigma_a;
  float sigma_b;
  float chi2;
  float q;
  float r;

  float refBG;
  float tstBG;
  float	chi2Signal;
  float chi2BG;
  int nData;
  float* testData;
  float* refData; 
} lmrcImageDensityNormalizationByImageInfo;


/*
   minimization of (in1 - (a+b*in2))^2
   out = a + b*in2
*/

typedef enum lmrcImageDensityNormalizationByImageMode {
  lmrcImageDensityNormalizationByImageModeSigma   = 1,
  lmrcImageDensityNormalizationByImageModeStdout  = 2,
  lmrcImageDensityNormalizationByImageModeReverse = 4,
  lmrcImageDensityNormalizationByImageModeRobust  = 8
} lmrcImageDensityNormalizationByImageMode; 

typedef enum lmrcImageDensityNormalizationByImageFitMode {
  lmrcImageDensityNormalizationByImageFitModeSingleLine = 0,
  lmrcImageDensityNormalizationByImageFitModeSingleLineWithBackground = 1 
} lmrcImageDensityNormalizationByImageFitMode;

/* struct end */

/* prototype begin */
extern void
  lmrcImageDensityNormalizationByImageModePrint(FILE* fpt);

extern void
  lmrcImageDensityNormalizationByImageInfoPrint(FILE* fpt, lmrcImageDensityNormalizationByImageInfo info);

extern void
  lmrcImageDenstiyNormalizationByImage(mrcImage* out, mrcImage* in2, mrcImage* in1, 
				       lmrcImageDensityNormalizationByImageInfo* info,
				       lmrcImageDensityNormalizationByImageMode  mode);
extern void
  lmrcImageDensityFittingForNormalization(mrcImage* out, mrcImage* in2, mrcImage* in1, 
				       lmrcImageDensityNormalizationByImageInfo* info,
				       lmrcImageDensityNormalizationByImageMode  mode);
/* prototype end */

#endif




