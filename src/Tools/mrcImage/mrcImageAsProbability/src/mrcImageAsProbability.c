/*
# mrcImageAsProbability : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageAsProbability
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
#include "lmrcImageAsProbability.h"

/*
Example:
typedef struct lmrcImageAsProbabilityInfo {
	float a;
	int   b;
} lmrcImageAsProbabilityInfo;

typedef enum lmrcImageAsProbabilityMode {
	a=0,
	b=1
} lmrcImageAsProbabilityMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageAsProbabilityInfo info;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageNormalizationAsProbability(&in, info.mode);

	mrcFileWrite(&in, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
