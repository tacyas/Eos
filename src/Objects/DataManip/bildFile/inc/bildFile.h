/*
# bildFile.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : bildFile.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef BILD_FILE_H 
#define BILD_FILE_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */
typedef enum lmrc2bildMode {
	lmrc2bildModeArrows=0,
	lmrc2bildModeSpheres=1
} lmrc2bildMode;


/* constant end */

/* struct begin */
typedef struct lmrc2bildInfo {
	float zoom;
	float color[3];

	// For Arrow
	float r1; 
	float r2;
	float rho;
  int flagRainbow;
  int RainbowMode;

  int flagRainbowThresLow;
  double RainbowThresLow;
  int flagRainbowThresHigh;
  double RainbowThresHigh;
  int flagRainbowRangeLow;
  double RainbowRangeLow;
  int flagRainbowRangeHigh;
  double RainbowRangeHigh;

	// skip
	int flagSkip;
	int skipX;
	int skipY;
	int skipZ;


    // range
    int flagRangeR;
    double RangeRR;
    double RangeRCX;
    double RangeRCY;
    double RangeRCZ;

    int flagRangeX;
    int RangeXMin;
    int RangeXMax;

    int flagRangeY;
    int RangeYMin;
    int RangeYMax;

    int flagRangeZ;
    int RangeZMin;
    int RangeZMax;
} lmrc2bildInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrc2bildUsage(FILE* fpt);
extern void lmrc2bild(FILE* fpt, mrcImage* in, lmrc2bildInfo linfo, int mode);
extern void lmrc2bildArrows(FILE* fpt, mrcImage* in, lmrc2bildInfo linfo, int mode);
extern void lmrc2bildSpheres(FILE* fpt, mrcImage* in, lmrc2bildInfo linfo, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* BILD_FILE_H */ 
