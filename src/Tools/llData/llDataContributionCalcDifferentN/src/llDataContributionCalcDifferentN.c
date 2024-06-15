/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataContributionCalcDifferentN ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataContributionCalcDifferentN
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataContributionCalcDifferentN ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"

#include "lllDataContributionCalcDifferentN.h"

void
main(int argc, char* argv[]) 
{
	llDataContributionCalcDifferentNInfo info;
	llData llIn;
	llData llOut;
	llDataParaTypeInteger status;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	llDataFileRead(info.fptIn, &llIn, &status);

	lllDataContributionCalcDifferentN(&llOut, &llIn, 0);

	llDataFileWrite(info.fptOut, &llOut, &status);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
