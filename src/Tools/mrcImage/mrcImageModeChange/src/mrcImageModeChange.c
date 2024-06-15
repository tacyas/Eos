/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageModeChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageModeChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageModeChange ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageModeChange.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageModeChangeInfo info;
	mrcImage in;
	mrcImage out;
	double datain;
	double dataout;
	double min, max;
	mrcImageParaTypeReal x, y, z;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&in, info.In, "in main", 0);

	if(info.flagStat) {
		mrcStatDataSet(&in, 0);
	}

	if(info.flagMin) {
		in.HeaderAMin = info.Min;
	}
	if(info.flagMax) {
		in.HeaderAMax = info.Max;
	} 

    if(info.flagSigned) {
        in.flagSigned = 1;
    } else {
        in.flagSigned = 0;
    }
	lmrcImageModeChange(&out, &in, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0); 	
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
}
