/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNormalDistributionTest ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNormalDistributionTest
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNormalDistributionTest ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcImageNormalDistributionTestInfo {
	float a;
	int   b;
} lmrcImageNormalDistributionTestInfo;

typedef enum lmrcImageNormalDistributionTestMode {
	a=0,
	b=1
} lmrcImageNormalDistributionTestMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageNormalDistributionTestInfo info;

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
