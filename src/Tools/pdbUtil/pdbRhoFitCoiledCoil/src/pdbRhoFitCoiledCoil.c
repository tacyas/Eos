/*
# pdbRhoFitCoiledCoil : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdbRhoFitCoiledCoil
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
typedef struct lpdbRhoFitCoiledCoilInfo {
	float a;
	int   b;
} lpdbRhoFitCoiledCoilInfo;

typedef enum lpdbRhoFitCoiledCoilMode {
	a=0,
	b=1
} lpdbRhoFitCoiledCoilMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbRhoFitCoiledCoilInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	DEBUGPRINT("Not supported yet. under construction\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
