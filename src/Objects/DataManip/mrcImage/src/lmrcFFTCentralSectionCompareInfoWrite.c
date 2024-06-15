/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcFFTCentralSectionCompareInfoWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcFFTCentralSectionCompareInfoWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcFFTCentralSectionCompareInfoWrite ver%I%; Date:%D% %Z%";

#include "genUtil.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include "./lmrcFFTCentralSection.h"

void lmrcFFTCentralSectionCompareInfoWrite(FILE* fpt, float Likelihood, int mode){
	
	fprintf(fpt, "%f\n",Likelihood);
}

