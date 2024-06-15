/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataEquatorAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataEquatorAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataEquatorAdd ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataEquatorAdd.h"

int
main(int argc, char* argv[]) 
{
	llData in, out;
	llDataEquatorAddInfo info;
	llDataParaTypeInteger status;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	llDataFileRead(info.fptIn, &in, &status);

	lllDataEquatorAdd(&out, &in, info.mode);

	llDataFileWrite(info.fptOut, &out, &status);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
