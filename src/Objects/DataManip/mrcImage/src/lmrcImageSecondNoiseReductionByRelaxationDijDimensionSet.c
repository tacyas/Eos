/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet ver%I%; Date:%D% %Z%";

#include <math.h>
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet.h"
#undef DEBUG
#include "genUtil.h"
#include <stdlib.h>

void lmrcImageSecondNoiseReductionByRelaxationDijDimensionSet(lmrcImageNoiseReductionByRelaxationInfo* info,
							      lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3* mode3)
{
  /* Set dimension of Dij */
  switch (*mode3){
  case lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3FiveTimesFive:
    info->ddimx = 5;
    info->ddimy = 5;
    info->ddimz = 1;
    break;
  case lmrcImageSecondNoiseReductionByRelaxationDijStyleMode3SevenTimesSeven:
    info->ddimx = 7;
    info->ddimy = 7;
    info->ddimz = 1;
    break;
  default:
    fprintf(stderr,"dij-dimension not supported !! (ToT)/ ");
    exit(EXIT_FAILURE);
  }
  DEBUGPRINT("dij -dimension checked !\n");
}
