#ifndef MRC_CRYSTAL_CREATE_H
#define MRC_CRYSTAL_CREATE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageCrystalCreateInfo {
	long nx;
	long ny;
	long nz;
	float ax;
	float ay;
	float az;
	float bx;
	float by;
	float bz;
	float cx;
	float cy;
	float cz;
	float sx;
	float sy;
	float sz;
  long pixelMode;
} lmrcImageCrystalCreateInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageCrystalCreate(mrcImage* out, mrcImage* in, lmrcImageCrystalCreateInfo* info);
/* prototype end */

#endif
