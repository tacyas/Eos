/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSubtractionCalc.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSubtractionCalc.h 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGE_SUBTRACTION_CALC_H 
#define  LMRC_IMAGE_SUBTRACTION_CALC_H

#include "mrcImage.h"

/* prototype */
extern void
lmrcImageSubtractionCalc(mrcImage* out, mrcImage* in1, mrcImage* in2);

extern void
lmrcImageMinSubtraction(mrcImage* out, mrcImage* in);

extern void
lmrcImageMeanSubtraction(mrcImage* out, mrcImage* in);

extern void
lmrcImageSubtraction(mrcImage* out, mrcImage* in , double value);
/* prototype */

#endif
