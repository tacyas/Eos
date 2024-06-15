/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCorrelationServer ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCorrelationServer
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCorrelationServer ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "lmrcImageCorrelation.h"

int
main(int argc, char* argv[]) 
{
	mrcImageCorrelationServerInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start: mrcImageCorrelationServer\n");

	lmrcImageCorrelationServer();
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
