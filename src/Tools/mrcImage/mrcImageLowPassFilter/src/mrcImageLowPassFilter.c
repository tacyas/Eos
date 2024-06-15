/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageLowPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageLowPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageLowPassFilter ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GLOBAL_DECLARATION
#undef DEBUG
#include "../inc/config.h"
#include "mrcImage.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageLowPassFilterInfo info;
	lmrcImageLowPassFilterInfo linfo;
	mrcImage dst;
	mrcImage src;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.hvp = info.hvp;
	linfo.width = info.width;
	linfo.mode = info.mode;
	mrcFileRead(&src, info.In, "in main", 0);
	DEBUGPRINT("Call lmrcImageLowPassFilter\n");
	lmrcImageLowPassFilter(&dst, &src, &linfo, 0);
	DEBUGPRINT("RFS lmrcImageLowPassFilter\n");
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode <<<< \n");
	fprintf(stderr, "    1: Step filter : required argumnent: -hvp\n");
	fprintf(stderr, "    2: Cos filter  : required argumnent: -hvp -w\n");
	fprintf(stderr, "    3: Exp filter  : required argumnent: -hvp\n");
	fprintf(stderr, "    4: Gauss filter  : required argumnent: -hvp \n");
	fprintf(stderr, "    5: Lorenz filter  : required argumnent: -hvp\n");
}
