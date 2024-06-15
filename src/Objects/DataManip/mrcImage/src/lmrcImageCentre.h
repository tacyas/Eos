#ifndef MRC_CENTRE
#define MRC_CENTRE
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSymmetryFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSymmetryFind 
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* struct begin */

typedef struct lmrcImageCenterOfMass {
  float x;
  float y;
  float z;
} lmrcImageCenterOfMass;

/* struct end */

/* prototype begin */
extern void lmrcImageCenterOfMassCalculate(lmrcImageCenterOfMass *centerOfMass,mrcImage in1);
extern void lmrcImageShiftCenterOfMassIntoImageCenter(mrcImage* out, mrcImage* in, mrcPixelDataHowToGet mode);
/* prototype end */

#endif
