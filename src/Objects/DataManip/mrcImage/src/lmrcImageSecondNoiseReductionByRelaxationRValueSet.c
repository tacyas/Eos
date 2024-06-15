/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationRValueSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationRValueSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSecondNoiseReductionByRelaxationRValueSet ver%I%; Date:%D% %Z%";

#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#include <math.h>
#include "lmrcImageSecondNoiseReductionByRelaxationRValueSet.h"

void lmrcImageSecondNoiseReductionByRelaxationRValueSet( double *r, double *densityLevel,
							lmrcImageNoiseReductionByRelaxationInfo* info)
{
  /* Set r value , calculating (IGRAY(l)-IGRAY(l')) */
  int i,j;
  double x, xmax;
  xmax = (densityLevel[info->classNumber-1]-densityLevel[0]);
  for (i=0; i<info->classNumber; i++){
    for (j=0; j<info->classNumber; j++){
      x = fabs(densityLevel[i]-densityLevel[j]) / xmax;      
      if ( x <= 1 ){
	r[i+j*info->classNumber] = 1 - 2*x ;
      }
      else {
	r[i+j*info->classNumber] = -1 ;
      }
    
    }
  }

}
