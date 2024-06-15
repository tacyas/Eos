/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageConnection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageConnection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageConnection ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "lmrcImageConnection.h"

#define DEBUG

int
main(int argc, char* argv[]) 
{
	mrcImageConnectionInfo info;
	lmrcImageConnectionInfo linfo; 
	mrcImage in1;
	mrcImage in2;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.mode     = info.mode;

	mrcFileRead(&in1, info.In1, "from Main Routine", 0);
	mrcFileRead(&in2, info.In2, "from Main Routine", 0);

	lmrcImageConnection(&out, &in1, &in2, &linfo);

	mrcFileWrite(&out, info.Out, "in Main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0: z connection\n");
}
