/*
# mrcImageUnsharpening : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageUnsharpening
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

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
#include "lmrcImageUnsharpening.h"
*/

/*
Example:
typedef struct lmrcImageUnsharpeningInfo {
	float a;
	int   b;
} lmrcImageUnsharpeningInfo;

typedef enum lmrcImageUnsharpeningMode {
	a=0,
	b=1
} lmrcImageUnsharpeningMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageUnsharpeningInfo info;
	mrcImage in;
	mrcImage out;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageUnsharpening(&out, &in, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageUnsharpeningUsage(stderr);
}
