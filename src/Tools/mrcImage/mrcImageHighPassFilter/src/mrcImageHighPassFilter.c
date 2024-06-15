/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHighPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHighPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageHighPassFilter ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageHighPassFilterInfo info;
	lmrcImageHighPassFilterInfo linfo;
	mrcImage dst;
	mrcImage src;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.hvp = info.hvp;
	linfo.width = info.width;
	linfo.pathWindowLow  = info.pwLow;
	linfo.pathWindowHigh = info.pwHigh;
	linfo.mode = info.mode;
	mrcFileRead(&src, info.In, "in main", 0);
	lmrcImageHighPassFilter(&dst, &src, &linfo, 0);
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
}
