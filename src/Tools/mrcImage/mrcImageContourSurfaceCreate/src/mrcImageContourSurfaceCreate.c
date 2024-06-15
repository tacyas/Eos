/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageContourSurfaceCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageContourSurfaceCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageContourSurfaceCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageContourSurface.h"

int
main(int argc, char* argv[]) 
{
	mrcImageContourSurfaceCreateInfo info;
	lmrcImageContourSurfaceInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	linfo.Contour = info.Contour;
	lmrcImageContourSurfaceCreate(&out, &in, linfo, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "    -m %d : SimpleMethod\n", lmrcImageContourSurfaceModeSimple);
	fprintf(stderr, "              When a point has contour surfaces between six voxels (Upper-Downward Right-Left For-Back) and the point,\n");
	fprintf(stderr, "              the point is defined as ContourSurface\n");
	fprintf(stderr, "              -C option are required \n");
}
