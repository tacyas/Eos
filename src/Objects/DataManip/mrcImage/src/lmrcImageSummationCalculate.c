/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSummationcalculate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSummationcalculate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSummationcalculate ver%I%; Date:%D% %Z%";
#include "lmrcImageSummationCalculate.h"

double
lmrcImageSummationCalculate(mrcImage* in, double sigma)
{
  int x,y,z;
  double data;
  double sum=0.0;
  
  for (z=0; z<in->HeaderN.z; z++){
    for (y=0; y<in->HeaderN.y; y++){
      for (x=0; x<in->HeaderN.x; x++){
        mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        sum += (data/(sigma*sigma));
      }
    }
  }
  return sum;
}

