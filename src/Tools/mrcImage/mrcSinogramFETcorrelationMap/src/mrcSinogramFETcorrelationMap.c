/*
# mrcSinogramFETcorrelationMap : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFETcorrelationMap
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
#include "lmrcSinogramFETcorrelationMap.h"

/*
Example:
typedef struct lmrcSinogramFETcorrelationMapInfo {
	float a;
	int   b;
} lmrcSinogramFETcorrelationMapInfo;

typedef enum lmrcSinogramFETcorrelationMapMode {
	a=0,
	b=1
} lmrcSinogramFETcorrelationMapMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETcorrelationMapInfo info;
	lmrcSinogramFETcorrelationMapInfo linfo;
	mrcImage in1, in2, out, weight, sd;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	mrcFileRead(&in1, info.In1, "in main",0);
	mrcFileRead(&in2, info.In2, "in main",0);
	linfo.flagWeight = info.flagWeight;
	if(info.flagWeight){
		mrcFileRead(&weight, info.Weight, "in main",0);
		linfo.Weight = &weight;
	}
	linfo.flagSD = info.flagSD;
	if(info.flagSD){
		mrcFileRead(&sd, info.SD, "in main",0);
		linfo.SD = &sd;
	}
	linfo.Nmode = info.NM;
	linfo.Cmode = info.CMode;
	lmrcSinogramFETcorrelationMap(&in1, &in2, &out, linfo, 0);

	if(info.mode){
		lmrcSinogramFETcorrelationMapCounterMatching(&out, &sd, 0);
		mrcFileWrite(&sd, info.Out, "in main" ,0);
	}else mrcFileWrite(&out, info.Out, "in main" ,0);
	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0 : default, normal distance correlation\n");
	fprintf(stderr, "mode 1 : average of counter pixel presents same line\n\n");
	fprintf(stderr, "-nm : 0 : normalize free (prenormalized input data)\n");
	fprintf(stderr, "      1 : normalize implementation\n\n");
	fprintf(stderr, "-cmode : 0 : distance calculation\n");
	fprintf(stderr, "         1 : difference product \n\n");
}
