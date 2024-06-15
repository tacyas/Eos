/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSolventFlattening ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSolventFlattening
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSolventFlattening ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "lmrcImageSolventFlattening.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSolventFlatteningInfo info;
	mrcImageInformation linfo;
	lmrcImageSolventFlatteningInfo llinfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.mode     = info.mode;
	linfo.rmax     = info.rmax;
	linfo.flagrmax = info.flagrmax;

	llinfo.range    = info.Range;
	llinfo.flagrange = info.flagRange;

	llinfo.density = info.density;
	llinfo.flagdensity = info.flagdensity;

	llinfo.flagFloating = info.Floating;

	mrcFileRead(&in, info.In, "from Main Routine", 0);
	lmrcImageInformation(&linfo, &in);	
	lmrcImageSolventFlattening(&out, &in, &llinfo, &linfo);

	mrcFileWrite(&out, info.Out, "in Main", 0);

	fprintf(info.fptOutParam, "Mean: %g\n", llinfo.Mean);	
	fprintf(info.fptOutParam, "SD: %g\n", llinfo.SD);	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m 0: mean of all density\n");
	fprintf(stderr, "   1: mean of sphere surface density at rmax\n");
	fprintf(stderr, "   2: mean of cylinder surface density at rmax\n");
	fprintf(stderr, "   6: mean of 2D Edge X=0 or N.x-1\n");
	fprintf(stderr, "-SD range : assign the voxels whose density is less than maen + range*SD as solvent range \n");
	fprintf(stderr, "-density is stronger than -m\n");
}	
