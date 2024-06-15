/*
# tgaInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : tgaInfo
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
#include "tgaFile.h"

/*
Example:
typedef struct ltgaInfoInfo {
	float a;
	int   b;
} ltgaInfoInfo;

typedef enum ltgaInfoMode {
	a=0,
	b=1
} ltgaInfoMode;
*/

int
main(int argc, char* argv[]) 
{
	tgaInfoInfo info;
	tgaFile tga;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	tgaFileHeaderRead(&tga, info.fptIn, info.mode);
	tgaFileHeaderPrint(&tga, info.fptOut, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
