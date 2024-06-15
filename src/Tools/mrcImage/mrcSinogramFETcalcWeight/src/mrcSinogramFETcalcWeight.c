/*
# mrcSinogramFETcalcWeight : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFETcalcWeight
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
#include "lmrcSinogramFETcalcWeight.h"

/*
Example:
typedef struct lmrcSinogramFETcalcWeightInfo {
	float a;
	int   b;
} lmrcSinogramFETcalcWeightInfo;

typedef enum lmrcSinogramFETcalcWeightMode {
	a=0,
	b=1
} lmrcSinogramFETcalcWeightMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETcalcWeightInfo info;
	lmrcSinogramFETcalcWeightInfo linfo;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	

	DEBUGPRINT("Program Start\n");

	linfo.In = info.fptIn;
	linfo.mode = info.mode;
	linfo.InC = info.fptInC;
	
	lmrcSinogramFETcalcWeight(&out, linfo, 0);
	
	mrcFileWrite(&out, info.Out, "in mrcSinogramFETcalcWeight",0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
