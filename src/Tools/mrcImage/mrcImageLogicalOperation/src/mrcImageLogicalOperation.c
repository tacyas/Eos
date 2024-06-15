/*
# mrcImageLogicalOperation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageLogicalOperation
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
#include "lmrcImageLogic.h"

/*
Example:
typedef struct lmrcImageLogicalOperationInfo {
	float a;
	int   b;
} lmrcImageLogicalOperationInfo;

typedef enum lmrcImageLogicalOperationMode {
	a=0,
	b=1
} lmrcImageLogicalOperationMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageLogicalOperationInfo info;
	mrcImage P;
	mrcImage Q;
	mrcImage R;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&P, info.In1, "in main", 0);

	if(info.flagIn2) {
		mrcFileRead(&Q, info.In2, "in main", 0);
	}

	if(info.flagIn2) {
		lmrcImageLogicalOperation(&R, &P, &Q, info.mode);
	} else {
		lmrcImageLogicalOperation(&R, &P, NULL, info.mode);
	}

	mrcFileWrite(&R, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageLogicalOpModePrint(stderr);
}
