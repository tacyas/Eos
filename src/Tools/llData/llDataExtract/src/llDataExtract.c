/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataExtract ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataExtract
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataExtract ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataExtract.h"

int
main(int argc, char* argv[]) 
{
	llData in, out;
	llDataExtractInfo info;
	lllDataExtractInfo linfo;
	llDataParaTypeInteger status;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.n = info.n;
	linfo.l = info.l;

	llDataFileRead(info.fptIn, &in, &status);

	lllDataExtract(&out, &in, &linfo, info.mode);

	llDataFileWrite(info.fptOut, &out, &status);


	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "input n and l \n");
}
