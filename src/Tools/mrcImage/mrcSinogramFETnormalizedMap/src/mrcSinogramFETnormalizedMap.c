/*
# mrcSinogramFETnormalizedMap : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFETnormalizedMap
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
#include "lmrcSinogramFETnormalizedMap.h"

/*
Example:
typedef struct lmrcSinogramFETnormalizedMapInfo {
	float a;
	int   b;
} lmrcSinogramFETnormalizedMapInfo;

typedef enum lmrcSinogramFETnormalizedMapMode {
	a=0,
	b=1
} lmrcSinogramFETnormalizedMapMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETnormalizedMapInfo info;
	lmrcSinogramFETnormalizedMapInfo linfo;
	mrcImage outfet, outmap, weight;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.In = info.fptIn;
	linfo.outFET = &outfet;
	linfo.fptOut = info.fptOutMAP;
	linfo.flagOutMAP = info.flagOutMAP;
	linfo.flagcomList = info.flagcomList;
	linfo.comList = info.fptcomList;
	if(info.flagOutMAP){
		linfo.outMAP = &outmap;
	}
	linfo.flagWeight = info.flagWeight;
	if(info.flagWeight){
		mrcFileRead(&weight, info.Weight, "in main",0);
		linfo.weight = &weight;
	}
	linfo.aatestmode = info.AAtm;
	linfo.mode = info.mode;
	
	lmrcSinogramFETnormalizedMap(linfo,0);
	
	mrcFileWrite(&outfet, info.OutFET, "in main" ,0);
	/*if(info.flagOutMAP){
		mrcFileWrite(&outmap, info.OutMAP, "in main" ,0);
	}*/
	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, " \"-O\" option do not work at Oct.24,2007\n");
	fprintf(stderr, " aatestmode 0: default, check whole distance\n");
	fprintf(stderr, "            1: check about all features\n");
	
	fprintf(stderr, "mode 0: normal 1: PCA (Nov.1,2007)\n");
	
}
