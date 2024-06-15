/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractWithLayerSeparationServer ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractWithLayerSeparationServer
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractWithLayerSeparationServer ver%I%; Date:%D% %Z%";
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
typedef struct lllExtractWithLayerSeparationServerInfo {
	float a;
	int   b;
} lllExtractWithLayerSeparationServerInfo;

typedef enum lllExtractWithLayerSeparationServerMode {
	a=0,
	b=1
} lllExtractWithLayerSeparationServerMode;
*/

int
main(int argc, char* argv[]) 
{
	llExtractWithLayerSeparationServerInfo info;

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
