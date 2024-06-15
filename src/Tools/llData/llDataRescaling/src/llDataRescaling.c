/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataRescaling ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataRescaling
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataRescaling ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataRescaling.h"

void
main(int argc, char* argv[]) 
{
	llData llIn;
	llData llOut;
	llDataRescalingInfo info;
	lllDataRescalingInfo linfo;

	llDataParaTypeInteger status;
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	llDataFileRead(info.fptIn, &llIn, &status);

	linfo.delBR = info.delBR;
	linfo.rScale = info.rScale;

	lllDataRescaling(&llOut, &llIn, linfo, info.mode);

	llDataFileWrite(info.fptOut, &llOut, &status);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
