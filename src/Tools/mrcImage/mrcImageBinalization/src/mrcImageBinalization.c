/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageBinalization ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageBinalization
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageBinalization ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageBinarization.h"


int
main(int argc, char* argv[]) 
{
	mrcImageBinalizationInfo info;
	lmrcImageBinarizationInfo linfo;
	float threshold;

/* variables */
	mrcImage in;
	mrcImage out;
	
/* input parameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in,  info.In , "in main" ,0);

	linfo.thresHold = info.t;
	linfo.value     = info.v;
	linfo.flagNear  = info.flagnear;
	linfo.near      = info.near;
	linfo.nLevel    = info.nLevel;
	linfo.p         = info.p;

	linfo.flagDeltaThreshold = info.flagdeltaThreshold;
	linfo.deltaThreshold = info.deltaThreshold;
	linfo.sigmaThreshold = info.sigmaThreshold;

	DEBUGPRINT1("mode: %ld\n", info.mode);
	threshold = lmrcImageBinarization(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out ,"in main" ,0);

	fprintf(info.fptOutParam, "Threshold: %f\n", threshold);
/* end */
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageBinarizationUsage(stderr);
}

   
