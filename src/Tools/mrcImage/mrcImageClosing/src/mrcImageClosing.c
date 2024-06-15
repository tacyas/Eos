/*
# mrcImageClosing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageClosing
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
#include "lmrcImageMorphology.h"

/*
Example:
typedef struct lmrcImageClosingInfo {
	float a;
	int   b;
} lmrcImageClosingInfo;

typedef enum lmrcImageClosingMode {
	a=0,
	b=1
} lmrcImageClosingMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageClosingInfo info;
	lmrcImageMorphologyInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);


	linfo.mode = info.SEmode;
	linfo.n = info.n;
	linfo.radius = info.radius;
	lmrcImageMorphologyStructuringElementSet(&linfo, 0);

	lmrcImageClosing(&out, &in, linfo, info.times, info.mode);

	if(info.flagOutSE) {
		mrcFileWrite(&linfo.SE, info.OutSE, "in main", 0);
	}
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Structuring Element : Mode \n");
	lmrcImageMorphologyStructuringElementSetInfoPrint(stderr);
}
