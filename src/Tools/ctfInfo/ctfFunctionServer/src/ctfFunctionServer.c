/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfFunctionServer ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfFunctionServer
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfFunctionServer ver%I%; Date:%D% %Z%";
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
typedef struct lctfFunctionServerInfo {
	float a;
	int   b;
} lctfFunctionServerInfo;

typedef enum lctfFunctionServerMode {
	a=0,
	b=1
} lctfFunctionServerMode;
*/

#ifdef PVM
#include "pvm3.h"
#endif
void
main(int argc, char* argv[]) 
{
	ctfFunctionServerInfo info;
	int mytid;
	
#ifdef PVM
	mytid = pvm_mytid();
#endif
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	while(1) {
		ctfFunctionPVMServer();
	}
	
#ifdef PVM
	mytid = pvm_exit();
#endif
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

