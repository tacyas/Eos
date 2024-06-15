/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataWeightSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataWeightSet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataWeightSet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "llData.h"

void
main(int argc, char* argv[]) 
{
	long status;
	llDataWeightSetInfo info;
	llData llIn;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	llDataFileRead(info.fptIn, &llIn, 0);

	lllDataWeightSet(info.fptllInfo, &llIn, info.weight, 0);

	llDataFileWrite(info.fptOut, &llIn, &status);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
