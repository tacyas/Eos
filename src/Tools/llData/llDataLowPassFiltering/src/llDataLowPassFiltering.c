/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataLowPassFiltering ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataLowPassFiltering
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataLowPassFiltering ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataLowPassFiltering.h"

int
main(int argc, char* argv[]) 
{
	llData ll;
	llDataLowPassFilteringInfo info;
	llDataParaTypeInteger status;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	llDataFileRead(info.fptIn, &ll, &status);

	ll.truePitch = info.truePitch;
	lllDataLowPassFiltering(&ll, info.RMax, info.mode);

	llDataFileWrite(info.fptOut, &ll, &status);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0: SameMemorySize data\n");
	fprintf(stderr, "-m 1: SavedMemorySize data\n");
}

