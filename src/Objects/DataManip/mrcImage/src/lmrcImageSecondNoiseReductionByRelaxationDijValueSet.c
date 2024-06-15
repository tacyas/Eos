/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationDijValueSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationDijValueSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSecondNoiseReductionByRelaxationDijValueSet ver%I%; Date:%D% %Z%";
#include <math.h>
#include "mrcImage.h"

#undef DEBUG
#include "genUtil.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijValueSet.h"
void lmrcImageSecondNoiseReductionByRelaxationDijValueSet(double* d,
							  lmrcImageNoiseReductionByRelaxationInfo* info,
							  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1* mode1,
							  lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2* mode2)
{
  int i;
  double dsum;
  
  /* Calculating */
  
  lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate(d, &dsum, info, mode1, mode2);
  
  DEBUGPRINT1("d0 :  %f\n",d[0]);
  DEBUGPRINT1("dij still unNormalized %d\n",info->ddimx);
  DEBUGPRINT1("sum :  %f\n",dsum);
  /* Normalizing */
  for (i=0; i<info->ddimx*info->ddimy*info->ddimz; i++){
    DEBUGPRINT1("d = :  %f\n",d[i]);
    d[i] = d[i]/dsum;
  }
  
  DEBUGPRINT("dij Normalized!!\n");
}
