/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMove ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMove
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMove ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageMove.h"

int
main(int argc, char* argv[]) 
{
	mrcImageMoveInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	lmrcImageMove(&out, &in, info.x, info.y, info.z, info.mode); 
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageMoveModePrint(stderr);
}
