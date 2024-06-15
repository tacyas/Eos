/*
# mrcImageFourierNeighborCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFourierNeighborCorrelation
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

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageFourierNeighborCorrelation.h"

/*
Example:
typedef struct lmrcImageFourierNeighborCorrelationInfo {
	float a;
	int   b;
} lmrcImageFourierNeighborCorrelationInfo;

typedef enum lmrcImageFourierNeighborCorrelationMode {
	a=0,
	b=1
} lmrcImageFourierNeighborCorrelationMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageFourierNeighborCorrelationInfo info;
	lmrcImageFourierNeighborCorrelationInfo linfo;
	lmrcImageFourierNeighborCorrelationResult res;
	mrcImage in;	
		
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.flagCentre = info.Centre;
	linfo.shiftMode  = info.GetMode;
	mrcFileRead(&in, info.In, "in main", 0);
	if(info.flagdelta) { 
		linfo.delta = info.delta;
	} else {
		linfo.delta = 0.0;
		if(1<in.HeaderN.x) {
			linfo.delta = MAX(linfo.delta, 1.0/(in.HeaderN.x*in.HeaderLength.x));
		}
		if(1<in.HeaderN.y) {
			linfo.delta = MAX(linfo.delta, 1.0/(in.HeaderN.y*in.HeaderLength.y));
		}
		if(1<in.HeaderN.z) {
			linfo.delta = MAX(linfo.delta, 1.0/(in.HeaderN.y*in.HeaderLength.z));
		}
	}
	DEBUGPRINT1("delta: %f\n", linfo.delta);
	linfo.flagPredictedFSC = info.FSC;
	if(linfo.flagPredictedFSC && ( ! info.flagInMask || ! info.flagInBackMask)) {
		fprintf(stderr, "-FSC need -mask and -maskBack\n");
		usage(argv[1]);
	}
	if(info.flagInMask) {
		mrcFileRead(&(linfo.objMask), info.InMask, "in main", 0);
	}
	if(info.flagInBackMask) {
		DEBUGPRINT("Back Mask Read\n");
		mrcFileRead(&(linfo.backMask), info.InBackMask, "in main", 0);
	}

	res.flagFSCfull = info.FSCfull;
	res.flagCref    = info.Cref;
	res.flagNoiseWeighted = info.flagBrestore;
	res.Brestore = info.Brestore;

	lmrcImageFourierNeighborCorrelation(&res, &in, linfo, info.mode); 
	lmrcImageFourierNeighborCorrelationPrint(info.fptOut, &res, linfo, info.mode); 

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageFourierNeighborCorrelationPrintCentreMode(stderr);
}
