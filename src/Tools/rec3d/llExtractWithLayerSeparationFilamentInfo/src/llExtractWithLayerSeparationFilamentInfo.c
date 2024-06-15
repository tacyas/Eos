/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractWithLayerSeparationFilamentInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractWithLayerSeparationFilamentInfo
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractWithLayerSeparationFilamentInfo ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lllExtractdYEstimate.h"

int
main(int argc, char* argv[]) 
{
	llExtractWithLayerSeparationFilamentInfoInfo info;
	lllExtractdYEstimateInfo dYinfo;
	int dY;

	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	dYinfo.truePitch = info.truePitch;
	dYinfo.deltadY   = info.deltadY;
	dYinfo.mag       = 1.0;
	dYinfo.PixelSize = info.PixelSize;
	
	mrcHeaderRead(&in, info.In, "in main", 0);
	dY = lllExtractdYEstimate(&in, &dYinfo);

	fprintf(info.fptOut, "%s %d %f %f %f %f 1.0\n",
						info.OutF, dY, info.Defocus, info.Cs, info.kV, info.AoverP);

	fprintf(info.fptOutI, "%f %f %f %f\n",
						info.Defocus, info.Cs, info.kV, info.AoverP);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
