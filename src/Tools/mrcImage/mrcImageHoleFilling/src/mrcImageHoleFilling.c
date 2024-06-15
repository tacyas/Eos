/*
# mrcImageHoleFilling : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageHoleFilling
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
#include "lmrcImageHoleFilling.h"

/*
Example:
typedef struct lmrcImageHoleFillingInfo {
	float a;
	int   b;
} lmrcImageHoleFillingInfo;

typedef enum lmrcImageHoleFillingMode {
	a=0,
	b=1
} lmrcImageHoleFillingMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageHoleFillingInfo info;
	lmrcImageHoleFillingInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.neighbor = info.Neighbor;

	mrcFileRead(&in, info.In, "in main", 0); 

	lmrcImageHoleFilling(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	if(info.flagBlackArea) {
		mrcFileWrite(&linfo.areaBlack, info.BlackArea, "in main", 0);
	}
	if(info.flagBlackLabel) {
		mrcFileWrite(&linfo.labelBlack, info.BlackLabel, "in main", 0);
	}
	if(info.flagBlack) {
		mrcFileWrite(&linfo.ToneReverse, info.Black, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
