/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDensityInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDensityInfo
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDensityInfo ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageModeChange.h"
#include "lmrcImageDensity.h"
#include "Vector.h"

int
main(int argc, char* argv[]) 
{
	mrcImageDensityInfoInfo  info;
	lmrcImageDensityInfoInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "main", 0);

	linfo.deltaVolume = info.Contour;
	lmrcImageDensityInfo(&linfo, &in, info.mode);

	linfo.in = in;
	lmrcImageDensityInfoWrite(info.fptOut, &linfo, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	lmrcImageDensityInfoModePrint(stderr);
}
