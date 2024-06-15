/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSectionGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSectionGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSectionGet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSectionGetInfo info;
	mrcImage in;
	mrcImage out;
	mrcImage section;
	char filename[1024];
	int z;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	mrcFileRead(&in, info.In, "in main", 0);
	if(info.z<0 && info.flagz) {
		for(z=0; z<in.HeaderN.z; z++) {
			sprintf(filename, info.format, info.Out, z);
			mrcImageSectionGet(&section, &in, z, info.mode);
			mrcStatDataSet(&section, 0);
			mrcFileWrite(&section, filename, "in main", 0);
		}
	} else {
		mrcImageSectionGet(&out, &in, info.z, info.mode);
		mrcStatDataSet(&out, 0);
		mrcFileWrite(&out, info.Out, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0: %s\n", mrcImageSectionGetModeDescription(0));
	fprintf(stderr, "mode 1: %s\n", mrcImageSectionGetModeDescription(1));
}
