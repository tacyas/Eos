/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdb2bender ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdb2bender
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdb2bender ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"

/*
Example:
typedef struct lpdb2bender {
	float a;
	int   b;
} lpdb2bender;

typedef enum lpdb2benderMode {
	a=0,
	b=1
} lpdb2benderMode;
*/

void
main(int argc, char* argv[]) 
{
	pdb2benderInfo info;

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
