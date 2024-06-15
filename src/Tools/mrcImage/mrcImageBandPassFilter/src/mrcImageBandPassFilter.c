/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageBandPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageBandPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageBandPassFilter ver%I%; Date:%D% %Z%";
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
	mrcImageBandPassFilterInfo info;
	lmrcImageBandPassFilterInfo linfo;
	mrcImage dst;
	mrcImage src;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.hvl = info.hvl;
	linfo.hvh = info.hvh;
	linfo.wl = info.wl;
	linfo.wh = info.wh;
	linfo.flagLowWeight = info.flaglowWeight;
	linfo.lowWeight = info.lowWeight;
	linfo.mode = info.mode;
	mrcFileRead(&src, info.In, "in main", 0);
	lmrcImageBandPassFilter(&dst, &src, &linfo, 0);
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode <<<< \n");
	fprintf(stderr, "    1: Step filter : required argumnent: -hvl -hvh\n");
	fprintf(stderr, "    2: Cos filter  : required argumnent: -hvl -hvh -wl -wh\n");
	fprintf(stderr, "    3: Exp filter  : required argumnent: -hvl -hvh -wl -wh\n");
	fprintf(stderr, ">>> -lowweight <<<< \n");
	fprintf(stderr, "Weight of Low Freq.  \n");
}
