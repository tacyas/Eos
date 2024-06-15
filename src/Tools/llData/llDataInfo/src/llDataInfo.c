/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataInfo
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataInfo ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "llData.h"

int
main(int argc, char* argv[]) 
{
    llData   ll;
	llDataInfoInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    llDataFileRead(info.fptIn, &ll, 0);

	if(info.flagNN&&info.flagLL) {
		info.layer = llDataLayerNumberGet(&ll, info.NN, info.LL);
	}
	llDataInfoPrint(info.fptOut, &ll, info.layer, info.mode); 
}

void
additionalUsage()
{
	llDataInfoPrintUsage(stderr);
}
