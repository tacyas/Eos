/*
# mrcImageHoughTransformInverse : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageHoughTransformInverse
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
#include "lmrcImageHoughTransform.h"

int
main(int argc, char* argv[]) 
{
	mrcImageHoughTransformInverseInfo info;
	lmrcImageHoughTransformInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;
	linfo.dx = info.delta;
	linfo.dy = info.delta;
	linfo.HoughSpaceMode = info.HoughSpaceMode;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageHoughTransformInverse(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
