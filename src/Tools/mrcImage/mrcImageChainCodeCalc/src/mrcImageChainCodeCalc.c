/*
# mrcImageChainCodeCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageChainCodeCalc
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
typedef struct lmrcImageChainCodeCalcInfo {
	float a;
	int   b;
} lmrcImageChainCodeCalcInfo;

typedef enum lmrcImageChainCodeCalcMode {
	a=0,
	b=1
} lmrcImageChainCodeCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageChainCodeCalcInfo info;
	mrcImage in;
	mrcImage out;
	lmrcImagePerimeterCalcInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImagePerimeterCalc(&out, &in, &linfo, info.mode);
	
	mrcFileWrite(linfo.ChainCode, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImagePerimeterCalcUsage(stderr);
}
