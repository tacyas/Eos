/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2Dto3DforVariation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2Dto3DforVariation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc2Dto3DforVariation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "rec3d.h"

/*
Example:
typedef struct lmrc2Dto3DforVariationInfo {
	float a;
	int   b;
} lmrc2Dto3DforVariationInfo;

typedef enum lmrc2Dto3DforVariationMode {
	a=0,
	b=1
} lmrc2Dto3DforVariationMode;
*/

void
main(int argc, char* argv[]) 
{
	mrc2Dto3DforVariationInfo info;

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
