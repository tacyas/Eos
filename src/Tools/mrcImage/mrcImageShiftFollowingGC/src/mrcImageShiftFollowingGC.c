/*
# mrcImageShiftFollowingGC : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShiftFollowingGC
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageDensity.h"
#include "lmrcImageDensityInverse.h"

int
main(int argc, char* argv[]) 
{
	mrcImageShiftFollowingGCInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	if(info.Inverse) {
		lmrcImageDensityInverse(&in, 0);
	}

	lmrcImageShiftFollowingGC(&out, &in, info.mode);

	if(info.Inverse) {
		lmrcImageDensityInverse(&out, 0);
	}

	mrcFileWrite(&out, info.Out, "in main", 0);
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

