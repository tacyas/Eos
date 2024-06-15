/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTBandPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTBandPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTBandPassFilter ver%I%; Date:%D% %Z%";
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
typedef struct lmrcFFTBandPassFilter {
	float a;
	int   b;
} lmrcFFTBandPassFilter;

typedef enum lmrcFFTBandPassFilterMode {
	a=0,
	b=1
} lmrcFFTBandPassFilterMode;
*/

void
main(int argc, char* argv[]) 
{
	mrcFFTBandPassFilterInfo info;

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
