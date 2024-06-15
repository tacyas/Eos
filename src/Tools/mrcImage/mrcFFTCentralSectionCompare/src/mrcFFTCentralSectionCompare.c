/*
# mrcFFTCentralSectionCompare : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTCentralSectionCompare
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
#include "eosString.h"
#include "lmrcFFTCentralSection.h"

/*
Example:
typedef struct lmrcFFTCentralSectionCompareInfo {
	float a;
	int   b;
} lmrcFFTCentralSectionCompareInfo;

typedef enum lmrcFFTCentralSectionCompareMode {
	a=0,
	b=1
} lmrcFFTCentralSectionCompareMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcFFTCentralSectionCompareInfo info;
	lmrcFFTCentralSectionCompareInfo linfo;
	mrcImage in;
	mrcImage volume;

	int i=0;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In2D, "in main", 0);
	mrcFileRead(&volume, info.In3D, "in main", 0);
	mrcFileRead(&linfo.vol2d, info.In2D, "in main", 0);
	
	strncpy(linfo.llinfo.EulerMode, info.EAMode, 4);
	linfo.llinfo.Rot1 = info.Rot1*RADIAN;
	linfo.llinfo.Rot2 = info.Rot2*RADIAN;
	linfo.llinfo.Rot3 = info.Rot3*RADIAN;
	linfo.llinfo.TransX = info.TransX;
	linfo.llinfo.TransY = info.TransY;
	linfo.llinfo.InterpMode = info.InterpMode;
	
	lmrcFFTCentralSectionCompare(&in, &volume, &linfo, info.mode);

	lmrcFFTCentralSectionCompareInfoWrite(info.fptOut, *linfo.Likelihood, info.mode);

	DEBUGPRINT("END\n");
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
