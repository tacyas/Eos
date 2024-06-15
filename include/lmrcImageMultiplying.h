#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef  LMRC_IMAGE_MULTIPLYING_H 
#define  LMRC_IMAGE_MULTIPLYING_H

#include "mrcImage.h"

/* prototype begin */
extern void lmrcImageMultiplyingByFile(mrcImage* inout, mrcImage* in);
extern void lmrcImageMultiplying(mrcImage* out, mrcImage* in, float value, long mode);
extern void lmrcImageMultiplying2(mrcImage* in, float value, long mode);
/* prototype end */

#endif
