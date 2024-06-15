/*
# FETOrientationSearchByAnnealing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : FETOrientationSearchByAnnealing
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
//#include "rec3d.h"
#include "lFETOrientationSearchByAnnealing.h"

/*
Example:
typedef struct lFETOrientationSearchByAnnealingInfo {
	float a;
	int   b;
} lFETOrientationSearchByAnnealingInfo;

typedef enum lFETOrientationSearchByAnnealingMode {
	a=0,
	b=1
} lFETOrientationSearchByAnnealingMode;
*/

int
main(int argc, char* argv[]) 
{
	FETOrientationSearchByAnnealingInfo info;
	lFETOrientationSearchByAnnealingInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");



	//linfo.InFL = info.fptInFL;
	//linfo.flagInML = info.flagInML;
	//if(linfo.flagInML == 1)
	//	linfo.InML = info.fptInML;
	mrcFileRead(&in, info.InMS, "in mrcSinogramFETcalcWeight",0);
	linfo.InMS = &in;
	linfo.as1 = info.AS1;
	linfo.as2 = info.AS2;
	linfo.as3 = info.AS3;
	linfo.mode = info.mode;
	linfo.Out = info.fptOut;

	lFETOrientationSearchByRigidSubsetCore(linfo,0);
	//lFETOrientationSearchByAnnealing(linfo,0);
	
		

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");

	fprintf(stderr, "this tool does not work at Oct.31,2007 \n");
	fprintf(stderr, "\n");
	
}
