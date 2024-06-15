/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSimilarImageSearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSimilarImageSearch
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSimilarImageSearch ver%I%; Date:%D% %Z%";
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
typedef struct lmrcImageSimilarImageSearchInfo {
	float a;
	int   b;
} lmrcImageSimilarImageSearchInfo;

typedef enum lmrcImageSimilarImageSearchMode {
	a=0,
	b=1
} lmrcImageSimilarImageSearchMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageSimilarImageSearchInfo info;

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
