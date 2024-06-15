/*
# FETmapOrientationSearchBySimultaneousFitting : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : FETmapOrientationSearchBySimultaneousFitting
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
#include "lFETmapOrientationSearchBySimultaneousFitting.h"
//#include "rec3d.h"

/*
Example:
typedef struct lFETmapOrientationSearchBySimultaneousFittingInfo {
	float a;
	int   b;
} lFETmapOrientationSearchBySimultaneousFittingInfo;

typedef enum lFETmapOrientationSearchBySimultaneousFittingMode {
	a=0,
	b=1
} lFETmapOrientationSearchBySimultaneousFittingMode;
*/

int
main(int argc, char* argv[]) 
{
	FETmapOrientationSearchBySimultaneousFittingInfo info;
	lFETmapOrientationSearchBySimultaneousFittingInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	linfo.PM = info.PM;
	if(linfo.PM>10||linfo.PM<0){
		fprintf(stderr,"error: PeakAreaMode %d is out of range.\n",linfo.PM);
		linfo.PM = 4;
	}
	linfo.PDT = info.PDT;
	if(linfo.PDT>1.0||linfo.PDT<0){
		fprintf(stderr,"error: PeakDetectThreshold %4.2f is out of range.\n",linfo.PDT); 
		linfo.PDT = 0.2;
	}
	linfo.PN = info.PN;
	if(linfo.PN>50||linfo.PN<1){
		fprintf(stderr,"error: PeakNumber %d is out of range.\n",linfo.PN);
		linfo.PN = 50;
	}
	linfo.InNL = info.fptInNL;
	linfo.InML = info.fptInML;
	linfo.InCL = info.fptInCL;
	
	lFETmapOrientationSearchBySimultaneousFitting(linfo,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "InputMapList: FETcorrelationMapList\n");
	fprintf(stderr, "InputNameList: FETfileNameList \n");
	fprintf(stderr, "PaekAreaMode: 0-10\n");
	fprintf(stderr, "PaekNumber: 1-50\n");
	fprintf(stderr, "PaekDetectThreshold: 0.02-1.00\n");
	fprintf(stderr, "SearchArea: 1-20\n");
	
}
