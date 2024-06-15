/*
# mrcImageToneReversal : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageToneReversal
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
#include "lmrcImageTone.h"

/*
Example:
typedef struct lmrcImageToneReversalInfo {
	float a;
	int   b;
} lmrcImageToneReversalInfo;

typedef enum lmrcImageToneReversalMode {
	a=0,
	b=1
} lmrcImageToneReversalMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageToneReversalInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageToneReversal(&out, &in, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
