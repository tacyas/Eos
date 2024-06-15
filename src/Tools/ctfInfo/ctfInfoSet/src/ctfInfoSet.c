/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfInfoSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfInfoSet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfInfoSet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"

/*
Example:
typedef struct lctfInfoSetInfo {
	float a;
	int   b;
} lctfInfoSetInfo;

typedef enum lctfInfoSetMode {
	a=0,
	b=1
} lctfInfoSetMode;
*/

int
main(int argc, char* argv[]) 
{
	ctfInfoSetInfo info;
	static ctfInfo ctfInfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	ctfInfoRead(info.fptIn, &ctfInfo, "", 0);  
	ctfInfoWrite(info.fptOut, ctfInfo, "", 0);  
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

