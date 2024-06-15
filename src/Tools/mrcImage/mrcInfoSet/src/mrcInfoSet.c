/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcInfoSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcInfoSet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcInfoSet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "mrcImage.h"
#include "../inc/config.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcInfoSetInfo info;
    mrcImage mrc;
	int changeCounter = 0;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&mrc, info.In, "in main", 0);

	if(info.flagLengthx || info.flagLengthy || info.flagLengthz) {
		mrc.HeaderLength.x = info.Lengthx; 	
		mrc.HeaderLength.y = info.Lengthy;
		mrc.HeaderLength.z = info.Lengthz; 	
		changeCounter++;	
	}
	if(info.Fixed) {
		mrcDefaultHeaderValueSetOnlyFixedValue(&mrc);
	}

	/* Interactive Mode */
	if(info.Interactive) {
		mrcInfoSet(&mrc, stdin, stderr, 9);
		changeCounter++;	
	}
	if(0<changeCounter) {
		fprintf(stdout, "%s has changed %d times.", info.In, changeCounter);
	} else {
		mrcInfoSet(&mrc, stdin, stderr, 0);
	}

	/* OUt */
	mrcFileWrite(&mrc, info.In, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
