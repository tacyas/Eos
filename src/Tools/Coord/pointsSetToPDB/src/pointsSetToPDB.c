/*
# pointsSetToPDB : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pointsSetToPDB
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
typedef struct lpointsSetToPDBInfo {
	float a;
	int   b;
} lpointsSetToPDBInfo;

typedef enum lpointsSetToPDBMode {
	a=0,
	b=1
} lpointsSetToPDBMode;
*/

int
main(int argc, char* argv[]) 
{
	pointsSetToPDBInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	fprintf(stderr, "Not suported yet ! Under Contraction");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
