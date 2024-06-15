/*
# mrcImageHoughTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageHoughTransform
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
	mrcImageHoughTransformInfo info;
	lmrcImageHoughTransformInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.deltaRho   = info.DeltaRho;
	linfo.deltaTheta = info.DeltaTheta*RADIAN;
	linfo.HoughSpaceMode = info.HoughMode;
	linfo.widthMin = info.widthMin;
	linfo.widthMax = info.widthMax;
	linfo.widthOut = info.widthOut;
	linfo.InterpolationMode = info.InterpolationMode;

	mrcFileRead(&in, info.In, "in main", 0);
	
	lmrcImageHoughTransform(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageHoughTransformSpaceModePrint(stderr);
}

