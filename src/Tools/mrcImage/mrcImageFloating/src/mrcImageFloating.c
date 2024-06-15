/*
# mrcImageFloating : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFloating
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
#include "mrcImage.h"
#include "lmrcImageFloating.h"

/*
Example:
typedef struct lmrcImageFloatingInfo {
	float a;
	int   b;
} lmrcImageFloatingInfo;

typedef enum lmrcImageFloatingMode {
	a=0,
	b=1
} lmrcImageFloatingMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageFloatingInfo   info;
	lmrcImageFloatingInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.value = info.Value;
	linfo.info.flagrmax = info.flagrmax;
	linfo.info.rmax = info.rmax;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageFloating(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageFloatingModePrint(stderr);
}
