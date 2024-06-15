/*
# mrcImagePerimeterCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagePerimeterCalc
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
typedef struct lmrcImagePerimeterCalcInfo {
	float a;
	int   b;
} lmrcImagePerimeterCalcInfo;

typedef enum lmrcImagePerimeterCalcMode {
	a=0,
	b=1
} lmrcImagePerimeterCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImagePerimeterCalcInfo info;
	lmrcImagePerimeterCalcInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.flagArea = 0;
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImagePerimeterCalc(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	if(info.flagOutArea) {
		mrcFileWrite(linfo.Area, info.OutArea, "in main", 0);
	}
	if(info.flagOutLabel) {
		mrcFileWrite(linfo.Label, info.OutLabel, "in main", 0);
	}
	if(info.flagOutChainCode) {
		mrcFileWrite(linfo.ChainCode, info.OutChainCode, "in main", 0);
	}
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImagePerimeterCalcUsage(stderr);
}
