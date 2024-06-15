/*
# EvaluateCorrelationMapwithCommonLine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : EvaluateCorrelationMapwithCommonLine
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
#include "lEvaluateCorrelationMapwithCommonLine.h"

/*
Example:
typedef struct lEvaluateCorrelationMapwithCommonLineInfo {
	float a;
	int   b;
} lEvaluateCorrelationMapwithCommonLineInfo;

typedef enum lEvaluateCorrelationMapwithCommonLineMode {
	a=0,
	b=1
} lEvaluateCorrelationMapwithCommonLineMode;
*/

int
main(int argc, char* argv[]) 
{
	EvaluateCorrelationMapwithCommonLineInfo info;
	lEvaluateCorrelationMapwithCommonLineInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.In = info.fptIn;
	linfo.InC = info.fptInC;
	linfo.Out = info.fptOut;
	linfo.mode = info.mode;
	linfo.PA = info.Pm;
	linfo.PN = info.PN;
	linfo.PDT = info.PDT;

	lEvaluateCorrelationMapwithCommonLine(linfo,0);
		
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
