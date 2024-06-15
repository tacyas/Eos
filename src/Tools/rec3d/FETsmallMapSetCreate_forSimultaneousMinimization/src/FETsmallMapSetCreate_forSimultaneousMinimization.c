/*
# FETsmallMapSetCreate_forSimultaneousMinimization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : FETsmallMapSetCreate_forSimultaneousMinimization
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
#include "lFETsmallMapSetCreate_forSimultaneousMinimization.h"

/*
Example:
typedef struct lFETsmallMapSetCreate_forSimultaneousMinimizationInfo {
	float a;
	int   b;
} lFETsmallMapSetCreate_forSimultaneousMinimizationInfo;

typedef enum lFETsmallMapSetCreate_forSimultaneousMinimizationMode {
	a=0,
	b=1
} lFETsmallMapSetCreate_forSimultaneousMinimizationMode;
*/

int
main(int argc, char* argv[]) 
{
	FETsmallMapSetCreate_forSimultaneousMinimizationInfo info;
	lFETsmallMapSetCreate_forSimultaneousMinimizationInfo linfo;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	linfo.InML = info.fptInML;
	linfo.Out = &out;
	linfo.ss = info.InSS;
	linfo.sr = info.InSR;

	lFETsmallMapSetCreate_forSimultaneousMinimization(linfo,0);
	mrcFileWrite(&out, info.OutMS ,"in main" ,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "\tinput MapList must not have empty line.\n");
	fprintf(stderr, "\t360 %% (ss*2) = 0 \n");
	fprintf(stderr, "\tss <= sr, sr %% ss = 0 \n");
}
