/*
# mrcImageMeanFreePathCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageMeanFreePathCalc
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

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageMultiplying.h"
#include "lmrcImageTranspose.h"
#include "lmrcImageMeanFreePath.h"

int
main(int argc, char* argv[]) 
{
	mrcImageMeanFreePathCalcInfo info;
	lmrcImageMeanFreePathCalcInfo linfo;
	mrcImage in;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);

	linfo.Length = in.HeaderLength;
	linfo.LineThickness.x = info.LineThicknessX;
	linfo.LineThickness.y = info.LineThicknessY;
	linfo.LineThickness.z = 1;

	linfo.LineMode  = info.LineMode;
	linfo.LineShape = info.LineShape;

	linfo.deltaPhi = info.deltaPhi*RADIAN;
	linfo.deltaTheta = info.deltaTheta*RADIAN;

	DEBUGPRINT1("mode: %ld\n", info.mode);
	lmrcImageMeanFreePathCalc(&in, &linfo, info.mode);

	lmrcImageMeanFreePathCalcPrint(info.fptOut, &linfo, info.mode);

	if(info.flagOutWhite) {
		mrcFileWrite(&linfo.white, info.OutWhite, "in main", 0);
	}
	if(info.flagOutBlack) {
		mrcFileWrite(&linfo.black, info.OutBlack, "in main", 0);
	}
	if(info.flagOutWhiteEdge) {
		mrcFileWrite(&linfo.whiteEdge, info.OutWhiteEdge, "in main", 0);
	}
	if(info.flagOutBlackEdge) {
		mrcFileWrite(&linfo.blackEdge, info.OutBlackEdge, "in main", 0);
	}

	if(info.flagOutWhiteAll) {
		int number = 1;
		lmrcImageAdd(&linfo.white, &linfo.whiteEdge, &number);
		mrcFileWrite(&linfo.white, info.OutWhiteAll, "in main", 0);
	}

	if(info.flagOutBlackAll) {
		int number = 1;
		lmrcImageAdd(&linfo.black, &linfo.blackEdge, &number);
		mrcFileWrite(&linfo.black, info.OutBlackAll, "in main", 0);
	}

	if(info.flagDirection && info.mode == 3) {
		char s[1024];
		for(i=0; i<3; i++) {
			sprintf(s, "%s.%d", info.Direction, i);
			mrcFileWrite(&linfo.direction[i], s, "in main", 0);
		}
	}
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageMeanFreePathCalcModePrint(stderr);
}

