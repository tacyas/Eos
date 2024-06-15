/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDensityChangeEstimation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDensityChangeEstimation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDensityChangeEstimation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageDensity.h"

int
main(int argc, char* argv[]) 
{
	mrcImage in1;
	mrcImage in2;
	mrcImageDensityChangeEstimationInfo info;
	lmrcImageDensityChangeEstimationInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in1, info.In, "main: In", 0);
	mrcFileRead(&in2, info.In2, "main: In2", 0);
	
	lmrcImageDensityChangeEstimation(&linfo, &in1, &in2, info.mode);
	lmrcImageDensityChangeEstimationWrite(info.fptOut, &linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageDensityChangeEstimationModePrint(stderr);
}


