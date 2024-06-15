/*
# pdbCoordAdd : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pdbCoordAdd
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
#include "lpdbCoord.h"
/*
Example:
typedef struct lpdbCoordAddInfo {
	float a;
	int   b;
} lpdbCoordAddInfo;

typedef enum lpdbCoordAddMode {
	a=0,
	b=1
} lpdbCoordAddMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbCoordAddInfo info;
	pdbFile in1;
	pdbFile in2;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	pdbFileRead(info.fptIn1, &in1); 
	pdbFileRead(info.fptIn2, &in2); 

	lpdbCoordAdd(&in1, &in2);

	pdbFileWrite(info.fptOut, &in1); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "In2 is a subgroup of In1. \n");
}

