/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageProportionalDensityLevelSetByImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageProportionalDensityLevelSetByImage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageProportionalDensityLevelSetByImage ver%I%; Date:%D% %Z%";
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageProportionalDensityLevelSetByImage.h"

void lmrcImageProportionalDensityLevelSetByImage(double *densityLevel, 
						 lmrcImageNoiseReductionByRelaxationInfo* info)
{
  int i;
  for (i=0; i<(info->classNumber); i++){
    densityLevel[i] = (i+1)*((info->datamax)-(info->datamin))/(info->classNumber) + (info->datamin);
  }
}
