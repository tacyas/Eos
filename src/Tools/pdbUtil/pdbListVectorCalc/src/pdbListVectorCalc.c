/*
# pdbListVectorCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdbListVectorCalc
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
#include "pdbFile.h"

/*
Example:
typedef struct lpdbListVectorCalcInfo {
	float a;
	int   b;
} lpdbListVectorCalcInfo;

typedef enum lpdbListVectorCalcMode {
	a=0,
	b=1
} lpdbListVectorCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbListVectorCalcInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	DEBUGPRINT("Not supported yet. Under construction\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
