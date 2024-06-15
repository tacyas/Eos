/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataFitServer ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataFitServer
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataFitServer ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataFit.h"

int
main(int argc, char* argv[]) 
{
	llDataFitServerInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start: llDataFitPVMServer\n");
	
	lllDataFitPVMServer();	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
