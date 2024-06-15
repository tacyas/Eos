/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageActinSingleParticleAnalysis ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageActinSingleParticleAnalysis
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageActinSingleParticleAnalysis ver%I%; Date:%D% %Z%";
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
typedef struct lmrcImageActinSingleParticleAnalysisInfo {
	float a;
	int   b;
} lmrcImageActinSingleParticleAnalysisInfo;

typedef enum lmrcImageActinSingleParticleAnalysisMode {
	a=0,
	b=1
} lmrcImageActinSingleParticleAnalysisMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageActinSingleParticleAnalysisInfo info;

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
