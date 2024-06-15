/*
# mrcImageFFTSetsExtract : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFFTSetsExtract
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
typedef struct lmrcImageFFTSetsExtractInfo {
	float a;
	int   b;
} lmrcImageFFTSetsExtractInfo;

typedef enum lmrcImageFFTSetsExtractMode {
	a=0,
	b=1
} lmrcImageFFTSetsExtractMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageFFTSetsExtractInfo info;

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
