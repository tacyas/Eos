/*
# mrcImageBottomHatTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageBottomHatTransform
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
#include "lmrcImageMorphology.h"

/*
Example:
typedef struct lmrcImageBottomHatTransformInfo {
	float a;
	int   b;
} lmrcImageBottomHatTransformInfo;

typedef enum lmrcImageBottomHatTransformMode {
	a=0,
	b=1
} lmrcImageBottomHatTransformMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageBottomHatTransformInfo info;
	lmrcImageMorphologyInfo linfo;
	mrcImage in;
	mrcImage out;

    init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	 
	DEBUGPRINT("Program Start\n");
	linfo.mode = info.SEmode;
	linfo.n = info.n;
	linfo.radius = info.radius;
	lmrcImageMorphologyStructuringElementSet(&linfo, 0);
	
	mrcFileRead(&in, info.In, "in main", 0);
	
	lmrcImageBottomHatTransform(&out, &in, linfo, info.times, info.mode);
	
	if(info.flagOutSE) {
		mrcFileWrite(&linfo.SE, info.OutSE, "in main", 0);
	}
	
	mrcFileWrite(&out, info.Out, "in main", 0);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
