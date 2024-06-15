/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSamplingUnitChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSamplingUnitChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSamplingUnitChange ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "lmrcImageSamplingUnitChange.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageSamplingUnitChangeInfo info;
	mrcImage in;
	mrcImage out;
	lmrcImageSamplingUnitChangeInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&in, info.In, "in main", 0);
    
	linfo.L.x = info.Sx;
	linfo.L.y = info.Sy;
	linfo.L.z = info.Sz;
    if(info.flagRatio) {
	    linfo.L.x = info.Sx*info.Ratio;
	    linfo.L.y = info.Sy*info.Ratio;
	    linfo.L.z = info.Sz*info.Ratio;
    }
	linfo.SamplingMethodMode = info.mode;
	lmrcImageSamplingUnitChange(&out, &in, linfo, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "---- Ratio ---- \n");
    fprintf(stderr, "-R and -S\n");
    fprintf(stderr, "   Ratio*Sx Ratio*Sy Ratio*Sy\n");
	fprintf(stderr, "---- Mode ---- \n");
	fprintf(stderr, "%d: Nearest\n", mrcPixelHowNearest);
	fprintf(stderr, "%d: Linear \n", mrcPixelHowLinear);
	fprintf(stderr, "%d: Cubic \n", mrcPixelHowCubicConv);
}
