/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFilamentSearchResultShow ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFilamentSearchResultShow
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFilamentSearchResultShow ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Crystal.h"


int
main(int argc, char* argv[]) 
{
	mrcImageFilamentSearchResultShowInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
