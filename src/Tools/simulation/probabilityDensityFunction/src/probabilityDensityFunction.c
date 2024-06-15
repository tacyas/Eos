/*
# probabilityDensityFunction : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : probabilityDensityFunction
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

/*
typedef struct lprobabilityDensityFunctionInfo {
	float a;
	int   b;
} lprobabilityDensityFunctionInfo;
*/

typedef enum lprobabilityDensityFunctionMode {
	probabilityFunctionExponentialDistribution=0,
	probabilityFunctionPoissonDistribution=1,
	probabllityFunctionErlangDistribution=2
} lprobabilityDensityFunctionMode;

int
main(int argc, char* argv[]) 
{
	probabilityDensityFunctionInfo info;

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
