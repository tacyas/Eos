/*
# mrcImageEdgeEnhancement : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageEdgeEnhancement
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
#include "lmrcImageEdgeEnhancement.h"

/*
Example:
typedef struct lmrcImageEdgeEnhancementInfo {
	float a;
	int   b;
} lmrcImageEdgeEnhancementInfo;

typedef enum lmrcImageEdgeEnhancementMode {
	a=0,
	b=1
} lmrcImageEdgeEnhancementMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out;
	mrcImageEdgeEnhancementInfo info;
	lmrcImageEdgeEnhancementInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	
	DEBUGPRINT("Program Start\n");
	linfo.flagDirection = info.flagOutDirection;
	linfo.mode = info.NeighborMode;
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageEdgeEnhancement(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	if(info.flagOutDirection) {
		mrcFileWrite(&(linfo.direction[0]), info.OutDirection, "in main", 0);	
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageEdgeEnhancementModePrint(stderr);
}
