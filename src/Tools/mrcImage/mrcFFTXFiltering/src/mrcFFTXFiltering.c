/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTXFiltering ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTXFiltering
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTXFiltering ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcFFTInfo.h"

int
main(int argc, char* argv[]) 
{
	mrcFFTXFilteringInfo info;
	mrcImage in;
	mrcImage out;
	float RMaxX;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	RMaxX = info.RMaxX;
	mrcFileRead(&in, info.In, "in main", 0);
	lmrcFSInfoXFiltering(&out, &in, RMaxX, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "This filter cuts high resolution information only X direction.\n");
	fprintf(stderr, "RMaxX [1/A] is maximum resolution\n");
}
