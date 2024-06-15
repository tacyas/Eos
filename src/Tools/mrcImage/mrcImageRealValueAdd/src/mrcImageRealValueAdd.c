/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRealValueAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRealValueAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRealValueAdd ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	mrcImageRealValueAddInfo info;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageAddedByReal(&in, info.Value);

	mrcFileWrite(&in, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
