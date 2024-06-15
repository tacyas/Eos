/*
# mrcImageSurfaceAreaCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSurfaceAreaCalc
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
#include "lmrcImageFeatureCalc.h"

/*
Example:
typedef struct lmrcImageSurfaceAreaCalcInfo {
	float a;
	int   b;
} lmrcImageSurfaceAreaCalcInfo;

typedef enum lmrcImageSurfaceAreaCalcMode {
	a=0,
	b=1
} lmrcImageSurfaceAreaCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageSurfaceAreaCalcInfo info;
	lmrcImageSurfaceAreaCalcInfo linfo;
	mrcImage in;
	mrcImage area;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", info.mode);
	linfo.Neighbor = info.Neighbor;

	lmrcImageSurfaceAreaCalc(&area, &in, &linfo, info.mode);  

	if(info.flagOutSurface) {
		mrcFileWrite(linfo.Surface, info.OutSurface, "in main", info.mode);
	}
	if(info.flagOutSurfaceArea) {
		lmrcImageSurfaceAreaCalcPrint(info.fptOutSurfaceArea, linfo, info.mode); 
	}
	mrcFileWrite(&area, info.Out, "in main", info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
