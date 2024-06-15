/*
# mrcImageDividedByFile : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDividedByFile
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

/*
Example:
typedef struct lmrcImageDividedByFileInfo {
	float a;
	int   b;
} lmrcImageDividedByFileInfo;

typedef enum lmrcImageDividedByFileMode {
	a=0,
	b=1
} lmrcImageDividedByFileMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageDividedByFileInfo info;
	mrcImage in1;
	mrcImage in2;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in1, info.In1, "in main", 0);
	mrcFileRead(&in2, info.In2, "in main", 0);

	lmrcImageDividedByImage(&out, &in1, &in2);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
