/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataResolutionCheck ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataResolutionCheck
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataResolutionCheck ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "llData.h"

/*
Example:
typedef struct lllDataResolutionCheckInfo {
	float a;
	int   b;
} lllDataResolutionCheckInfo;

typedef enum lllDataResolutionCheckMode {
	a=0,
	b=1
} lllDataResolutionCheckMode;
*/

int
main(int argc, char* argv[]) 
{
	int i;
	llData* In;
	llDataResolutionCheckInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	In = (llData*)memoryAllocate(sizeof(llData)*info.flagIn, "in main");
	for(i=0; i<info.flagIn; i++) {
		llDataFileRead(info.fptIn[i], &(In[i]), 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


