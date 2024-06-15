/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNormalizing ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrcImageNormalizing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNormalizing ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageNormalizing.h"
#include "nr2.h"

int
main(int argc, char* argv[]) 
{
	mrcImageNormalizingInfo info;
	mrcImage in;
	mrcImage out;
	lmrcImageNormalizingInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&in, info.In, "from main", 0);

	linfo.A    = info.A;
	linfo.B    = info.B;
	linfo.ContourMin = info.ContourMin;
	linfo.ContourMax = info.ContourMax;
	linfo.ContourSolvent = info.ContourSolvent;
    linfo.thresOfLowValueArea  = info.thresOfLowValueArea;
    linfo.thresOfHighValueArea = info.thresOfHighValueArea;
	linfo.Mode = info.mode;
    linfo.paramOut = info.fptParamOut;	

	lmrcImageNormalizing(&out, &in, &linfo, 0);

    mrcStatDataSet(&out, 0);
    fprintf(linfo.paramOut, "Nor(min,mean,max): %f %f %f\n", out.HeaderAMin, out.HeaderAMean, out.HeaderAMax);
	mrcFileWrite(&out, info.Out, "from main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- mode -----\n");
	lmrcImageNormalizingModePrint(stderr, 0);
	fprintf(stderr, "----- HighValueArea and LowValueArea for %03d -----\n", lmrcImageNormalizingModeUsingLowValueAreaToHighValueArea);
}

