/*
# mrcImageEdgeCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageEdgeCalc
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
#include "lmrcImageEdge.h"

/*
Example:
typedef struct lmrcImageEdgeCalcInfo {
	float a;
	int   b;
} lmrcImageEdgeCalcInfo;

typedef enum lmrcImageEdgeCalcMode {
	a=0,
	b=1
} lmrcImageEdgeCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageEdgeCalcInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);
	lmrcImageEdgeCalc(&out, &in, info.Neighbor, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
