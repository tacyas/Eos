/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataFit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataFit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataFit ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

void
main(int argc, char* argv[]) 
{
	long status;
	llDataFitInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
