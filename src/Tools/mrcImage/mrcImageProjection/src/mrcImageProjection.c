/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageProjection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageProjection
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImageProjection ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "lmrcImageProjection.h"

int
main(int argc, char* argv[]) 
{
	mrcImageProjectionInfo info;
	lmrcImageProjectionInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	mrcFileRead(&in, info.In, "in main", 0);

	linfo.mode = info.mode;

	lmrcImageProjection(&out, &in, &linfo);

	mrcStatDataSet(&out, 0);
	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}
void
additionalUsage()
{
  fprintf(stderr, "----- Mode -----\n");
  fprintf(stderr, "0: x-y sufacae along z-axis [3D to 2D]\n");
  fprintf(stderr, "1: y-z sufacae along x-axis [3D to 2D]\n");
  fprintf(stderr, "2: z-x sufacae along y-axis [3D to 2D]\n");
  fprintf(stderr, "3: z-x sufacae to y-axis [2D/3D to 1D]\n");
  fprintf(stderr, "4: y-z sufacae to x-axis [2D/3D to 1D]\n");
  fprintf(stderr, "5: x-y sufacae to z-axis [2D/3D to 1D]\n");
}

