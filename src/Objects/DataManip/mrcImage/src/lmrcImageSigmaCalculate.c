/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSigmaCalculate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSigmaCalculate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSigmaCalculate ver%I%; Date:%D% %Z%";

#include <math.h>
#include "lmrcImageSummationCalculate.h"
#include "lmrcImageSigmaCalculate.h"

double
lmrcImageSigmaCalculate(mrcImage* in)
{
  int x,y,z;
  double s=0.0;
  double data;
  double sum;
  double avg;
  
  sum = lmrcImageSummationCalculate(in, 1.0);
  avg = sum/((in->HeaderN.x*in->HeaderN.y*in->HeaderN.z));
  /*fprintf (stdout, "%f \n", avg);*/
  for (z=0; z<in->HeaderN.z; z++){
    for (y=0; y<in->HeaderN.y; y++){
      for (x=0; x<in->HeaderN.x; x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	s += (data-avg)*(data-avg);
      }
    }
  }
  /*fprintf (stdout, "%f \n", s);*/
  s = sqrt(s/((in->HeaderN.x*in->HeaderN.y*in->HeaderN.z - 1)));
  return s;
}
