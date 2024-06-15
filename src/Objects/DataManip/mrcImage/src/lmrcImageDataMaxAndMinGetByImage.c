/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDataMaxAndMinGetByImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDataMaxAndMinGetByImage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageDataMaxAndMinGetByImage ver%I%; Date:%D% %Z%";
#include "mrcImage.h"
#undef DEBUG
#include "lmrcImageDataMaxAndMinGetByImage.h"

void lmrcImageDataMaxAndMinGetByImage(mrcImage* in, double* datamax, double* datamin)
{
  int x, y, z;
  double data;
  
  mrcPixelDataGet(in, 0, 0, 0, datamax, mrcPixelRePart, mrcPixelHowNearest);
  *datamin=(*datamax);
  for (z=0; z<in->HeaderN.z; z++){
    for (y=0; y<in->HeaderN.y; y++){
      for (x=0; x<in->HeaderN.x; x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	if (*datamax < data){
	  *datamax=data;
	}
	if (*datamin > data){
	  *datamin=data;
	}
	
      }
    }
  }
}
