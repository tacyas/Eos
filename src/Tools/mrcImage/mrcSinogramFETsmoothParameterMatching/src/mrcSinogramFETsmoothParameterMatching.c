/*
# mrcSinogramFETsmoothParameterMatching : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFETsmoothParameterMatching
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
#include "lmrcSinogramFETsmoothParameterMatching.h"

/*
typedef enum lmrcSinogramFETsmoothParameterMatchingMode {
	a=0,
	b=1
} lmrcSinogramFETsmoothParameterMatchingMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETsmoothParameterMatchingInfo info;
	lmrcSinogramFETsmoothParameterMatchingInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.InSTD, "in main", 0);
	linfo.InList = info.fptIn;
	linfo.InSTD = &in;
	fprintf(stdout,"still in main\n");
	lmrcSinogramFETsmoothParameterMatching(linfo,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
