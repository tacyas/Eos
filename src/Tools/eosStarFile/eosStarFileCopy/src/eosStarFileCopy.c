/*
# eosStarFileCopy : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosStarFileCopy
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
#include "eosStarFile.h"

/*
Example:
typedef struct leosStarFileCopyInfo {
	float a;
	int   b;
} leosStarFileCopyInfo;

typedef enum leosStarFileCopyMode {
	a=0,
	b=1
} leosStarFileCopyMode;
*/

int
main(int argc, char* argv[]) 
{
	eosStarFileCopyInfo info;
    eosStarFile star;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    eosStarFileRead(info.fptIn, &star, info.mode);
    eosStarFileWrite(info.fptOut, &star, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
