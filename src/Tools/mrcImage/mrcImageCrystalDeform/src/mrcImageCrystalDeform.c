/*
# mrcImageCrystalDeform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageCrystalDeform
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
#include "Class.h"

/*
Example:
typedef struct lmrcImageCrystalDeformInfo {
	float a;
	int   b;
} lmrcImageCrystalDeformInfo;

typedef enum lmrcImageCrystalDeformMode {
	a=0,
	b=1
} lmrcImageCrystalDeformMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageCrystalDeformInfo info;

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
