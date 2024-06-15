/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTProjection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTProjection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTProjection ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Vector.h"
#include "lmrcFFTInfo.h"

int
main(int argc, char* argv[]) 
{
	mrcFFTProjectionInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	lmrcFSInfoYAxisProjection(&out, &in, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "The 2D FFT Image projects to Y-axis\n");
	fprintf(stderr, "This image is not true.\n");
	fprintf(stderr, "Because the real part is buried with mag and the imaginary part is buried with zero.\n");
}
