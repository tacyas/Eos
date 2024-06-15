/*
# mrcImageSNEstimate : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSNEstimate
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
#include "Class.h"

/*
Example:
typedef struct lmrcImageSNEstimateInfo {
	float a;
	int   b;
} lmrcImageSNEstimateInfo;

typedef enum lmrcImageSNEstimateMode {
	a=0,
	b=1
} lmrcImageSNEstimateMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageSNEstimateInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
