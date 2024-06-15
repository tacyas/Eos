/*
# eosPointCurvatureInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointCurvatureInfo
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
#include "eosPoint.h"

/*
Example:
typedef struct leosPointCurvatureInfoInfo {
	float a;
	int   b;
} leosPointCurvatureInfoInfo;

typedef enum leosPointCurvatureInfoMode {
	a=0,
	b=1
} leosPointCurvatureInfoMode;
*/

int
main(int argc, char* argv[]) 
{
	eosPointCurvatureInfoInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    /*
extern void eosPointFileFormatUsage(FILE* fpt);
 43 extern void eosPointRead(FILE* fpt, eosPoint* p, int mode);
 44 
 45 extern void eosPointWrite(FILE* fpt, eosPoint* p, int mode);
 */
	DEBUGPRINT("Not Completed\n");

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
    fprintf(Stderr, "eosPointFormat\n");
    eosPointFileFormatUsage(stderr);
}
