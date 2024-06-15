/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFirstNoiseReductionByRelaxation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFirstNoiseReductionByRelaxation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageFirstNoiseReductionByRelaxation ver%I%; Date:%D% %Z%";
#include <math.h>
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "genUtil.h"
#include "lmrcImagePixelSummationOfProbabilityGetByImage.h"
#undef DEBUG

void lmrcImageFirstNoiseReductionByRelaxation( mrcImage* out, mrcImage* p0, 
					      mrcImage* in, mrcImage* summationOfProbability,
					      double *densityLevel,
					      lmrcImageNoiseReductionByRelaxationInfo* info)
{
  double data, sum;
  double p, pmax;
  int x,y,z;
  int i,maxi;
    
  lmrcImagePixelSummationOfProbabilityGetByImage(summationOfProbability, in, densityLevel, info);
  
  for (z=0; z<out->HeaderN.z; z++){
    for (y=0; y<out->HeaderN.y; y++){
      for (x=0; x<out->HeaderN.x; x++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(summationOfProbability, x, y, z, &sum, mrcPixelRePart, mrcPixelHowNearest);
	maxi = 0;
	pmax = 0;
	for (i=0; i<(info->classNumber); i++){
	  p = exp(-SQR(densityLevel[i]-data)/(2.0*SQR(info->SD)))/sum;
	  mrcPixelDataSet(&(p0[i]), x, y, z, p, mrcPixelRePart);
	  if( pmax < p ){
	    pmax  = p;
	    maxi  = i;
	  }
	}
	data = densityLevel[maxi];
	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
	
      }
    }
  } 
}

