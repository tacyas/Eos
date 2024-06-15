/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFitAndAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFitAndAverage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFitAndAverage ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lllDataFitAndAverage.h"
#include "lllDataCTFCompensation.h"

void 
lllDataAverage(llData* llAve, llData* llOut, 
               llData* llIn,  llData llRef, 
			   llDataFittedParam* paraFit, 
			   lllDataFitAndAverageInfo info, 
			   int mode)
{
	lllDataMultiCTFCompensation(llAve, llOut, llIn, llRef, paraFit, info, 
		lllDataMultiCTFCompensationModeOnlyAverage);
}
