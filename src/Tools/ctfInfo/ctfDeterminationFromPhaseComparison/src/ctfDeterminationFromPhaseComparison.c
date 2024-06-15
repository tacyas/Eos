/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfDeterminationFromPhaseComparison ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfDeterminationFromPhaseComparison
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfDeterminationFromPhaseComparison ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"
#include "mrcImage.h"
#include "ctfDeterminationFromPhaseComparison.h"

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage ref;
	mrcImage inFFT;
	mrcImage refFFT;
	ctfDeterminationFromPhaseComparisonInfo info;
	ctfInfoDeterminationFromPhaseComparison DetInfo;
	double result;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in , info.In , "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	/* FILE CHECK */			
	if (in.HeaderN.x != ref.HeaderN.x || in.HeaderN.y != ref.HeaderN.y || in.HeaderN.z != ref.HeaderN.z){
		fprintf(stderr, "Different Size (%d %d %d) != (%d %d %d)\n",
								(int)in.HeaderN.x, (int)in.HeaderN.y, (int)in.HeaderN.z,
								(int)ref.HeaderN.x, (int)ref.HeaderN.y, (int)ref.HeaderN.z);
		exit(EXIT_FAILURE);
	}

	if(1!=in.HeaderN.z) {
		fprintf(stderr, "2D Only Supported\n");
		exit(EXIT_FAILURE);
	}

	if(IsImage(&in, "in main", 0)) {
		lmrcImageFFT(&inFFT, &in, 0);
	} else if(IsFT(&in, "in main", 0)) {
		inFFT = in;
	} else {
		fprintf(stderr, "Not supported mode : %ld\n", in.HeaderMode);
		exit(EXIT_FAILURE);
	}

	if(IsImage(&ref, "ref main", 0)) {
		lmrcImageFFT(&refFFT, &ref, 0);
	} else if(IsFT(&ref, "ref maref", 0)) {
		refFFT = ref;
	} else {
		fprintf(stderr, "Not supported mode : %ld\n", ref.HeaderMode);
		exit(EXIT_FAILURE);
	}

	/* Initial Parameter */
	DetInfo.val.Cs                  = info.Cs;
	DetInfo.val.kV                  = info.kV;
	DetInfo.val.mode                = ctfInfoModePhaseAndAmpCTF;
	DetInfo.Rmax                    = info.Rmax;
	DetInfo.min.defocus             = info.mindf;
	DetInfo.max.defocus             = info.maxdf;
	DetInfo.del.defocus             = info.deldf;
	DetInfo.min.ratioOfAmpToPhase   = info.minAoverP;
	DetInfo.max.ratioOfAmpToPhase   = info.maxAoverP;
	DetInfo.del.ratioOfAmpToPhase   = info.delAoverP;
	/* Main */
	result = ctfDeterminationFromPhaseComparison(&inFFT, &refFFT, &DetInfo, 0); 
	fprintf(stderr, "RESULT= %15.6f\n", result);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
