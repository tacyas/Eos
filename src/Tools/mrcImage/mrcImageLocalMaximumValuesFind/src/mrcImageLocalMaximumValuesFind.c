/*
# mrcImageLocalMaximumValuesFind : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageLocalMaximumValuesFind
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
#include "lmrcImageLocal.h"

int
main(int argc, char* argv[]) 
{
	mrcImageLocalMaximumValuesFindInfo info;
	lmrcImageLocalMaximumValuesFindInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.size = info.Size;
	linfo.threshold = info.Threshold;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageLocalMaximumValuesFind(&out, &in, &linfo, info.mode); 

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

