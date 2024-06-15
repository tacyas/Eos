/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfEnvelopFunction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfEnvelopFunction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfEnvelopFunction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "ctfInfo.h"

/*
Example:
typedef struct lctfEnvelopFunctionInfo {
	float a;
	int   b;
} lctfEnvelopFunctionInfo;

typedef enum lctfEnvelopFunctionMode {
	a=0,
	b=1
} lctfEnvelopFunctionMode;
*/

void
main(int argc, char* argv[]) 
{
	ctfEnvelopFunctionInfo info;
	float R;
	ctfInfo CTFInfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	CTFInfo.Cs = info.Cs;
	CTFInfo.defocus = info.Defocus;
	CTFInfo.kV = info.kV;
	CTFInfo.mode = info.ctfMode;
	CTFInfo.ratioOfAmpToPhase = info.AoverP;
	CTFInfo.Ain = info.Ain;

	for(R=0; R<info.Rmax; R+=info.dR) {
		fprintf(info.fptOut, "%e %e\n", R, ctfEnvelopFunction(&CTFInfo, R, 0)); 
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	 fprintf(stderr, ">>>> ctfMode <<<< \n");
	 fprintf(stderr, "ctfInfoModeWithIlluminationAngle   32 \n");
	 fprintf(stderr, "ctfInfoModeWithEnergySpread        64 \n");
}

