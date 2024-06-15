/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDataStraightCopy ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDataStraightCopy 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageStraightCopy ver%I%; Date:%D% %Z%";

#include "mrcImage.h"
#include "lmrcImageDataStraightCopy.h"

void lmrcImageDataStraightCopy(mrcImage* out, mrcImage* in)
{
  int x,y,z;
  double data;
  
  for (z=0; z<in->HeaderN.z; z++){
    for (y=0; y<in->HeaderN.y; y++){
      for (x=0; x<in->HeaderN.x; x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
      }
    }
  }
}
