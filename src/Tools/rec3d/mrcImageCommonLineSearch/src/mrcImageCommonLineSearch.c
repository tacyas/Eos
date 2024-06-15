/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCommonLineSearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCommonLineSearch
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCommonLineSearch ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "lmrcImageCommonLine.h"

int
main(int argc, char* argv[]) 
{
	mrcImageCommonLineSearchInfo info;
	lmrcImageCommonLineInfo      linfo;
	mrcImage in;
	mrcImage ref;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	/* File Open */
	mrcFileRead(&in,  info.In,  "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	/* Parameter Set */
	linfo.dtheta = info.dtheta*RADIAN;
	linfo.searchMode = info.searchMode;

	/* Main Routine */
	lmrcImageCommonLineSearch(&out,  &in, &ref, &linfo, info.mode);

	/* Output */
	lmrcImageCommonLineInfoOutput(info.fptOut, &linfo, info.mode);
	if(info.flagOut2) {
		mrcFileWrite(&out, info.Out2, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageCommonLineInfoUsage(stderr);
}

