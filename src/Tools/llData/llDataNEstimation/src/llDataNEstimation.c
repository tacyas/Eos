/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataNEstimation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataNEstimation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataNEstimation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"

/*
Example:
typedef struct lllDataNEstimationInfo {
	float a;
	int   b;
} lllDataNEstimationInfo;

typedef enum lllDataNEstimationMode {
	a=0,
	b=1
} lllDataNEstimationMode;
*/

int
main(int argc, char* argv[]) 
{
	llDataNEstimationInfo info;
	mrcImageParaTypeReal  RR;
	mrcImageParaTypeReal  N;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	RR = info.R/info.Width/info.xstep;
	N = 2*M_PI*info.r*RR/1.1 - 0.9;
	fprintf(info.fptOut, "N at %15.6g : %15.6g\n", RR, N);	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
