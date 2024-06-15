/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFitParamInverse ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFitParamInverse 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFitParamInverse ver%I%; Date:%D% %Z%";

#include "../inc/llData.h"
#include "lllDataFit.h"

void
lllDataFitParamInverse(llDataFittedParam* dst, llDataFittedParam* src)
{
	*dst = *src;	
	/* IntraMolecule */
	dst->Para.Omega.Value = 0.0 - src->Para.Omega.Value;
	dst->Para.x.Value     = 0.0 - src->Para.x.Value;
		
	/* InterMolecule */
	dst->Para.z.Value     = 0.0 - src->Para.z.Value;
	dst->Para.r.Value     = 1.0 / src->Para.r.Value;
	dst->Para.phi.Value   = 0.0 - src->Para.phi.Value;
}
