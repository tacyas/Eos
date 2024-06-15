/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImagePixelSummationOfProbabilityGetByImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImagePixelSummationOfProbabilityGetByImage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImagePixelSummationOfProbabilityGetByImage ver%I%; Date:%D% %Z%";
#include "mrcImage.h"
#include <math.h>
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "genUtil.h"
#include "lmrcImagePixelSummationOfProbabilityGetByImage.h"

void lmrcImagePixelSummationOfProbabilityGetByImage(mrcImage* out, mrcImage* in, 
						    double *densityLevel,
						    lmrcImageNoiseReductionByRelaxationInfo* info)
{
  int x, y, z;
  double data,sum;
  int i;
  
  for (z=0; z<in->HeaderN.z; z++){
    for (y=0; y<in->HeaderN.y; y++){
      for (x=0; x<in->HeaderN.x; x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	sum=0;
	for (i=0; i<(info->classNumber); i++){
	  sum += exp(-SQR(densityLevel[i]-data)/(2.0*SQR(info->SD)));
	} 
	mrcPixelDataSet(out, x, y, z, sum, mrcPixelRePart);
      }
    }
  }
}
