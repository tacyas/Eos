/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataNormalization ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataNormalization
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataNormalization ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "lllDataDifferenceCalc.h"

/*
Example:
typedef struct lllDataNormalizationInfo {
	float a;
	int   b;
} lllDataNormalizationInfo;

typedef enum lllDataNormalizationMode {
	a=0,
	b=1
} lllDataNormalizationMode;
*/

int
main(int argc, char* argv[]) 
{
	llData in;
	llData ref;
	llData out;
	llData dif;
	llDataNormalizationInfo info;
	lllDataDifferenceCalcInfo linfo;
	double rms;
	int i;
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	llDataFileRead(info.fptIn,  &in, 0);
	llDataFileRead(info.fptRef, &ref, 0);

	for(i=0; i<10; i++) {
		fprintf(info.fptOutParam, "in: %f ref: %f\n", in.LL[0].data[0].F, ref.LL[0].data[0].F);
		rms = lllDataDifferenceCalcWithNormalizing(&dif, &out, 
				&in, &ref, &linfo, 0);
		fprintf(info.fptOutParam, "A[%d]: %f\n", i, linfo.A);
		fprintf(info.fptOutParam, "Dif: %f out: %f in: %f ref: %f\n", 
			dif.LL[0].data[0].F, out.LL[0].data[0].F,
			in.LL[0].data[0].F, ref.LL[0].data[0].F
			);
		in = out;
	}
	llDataFileWrite(info.fptOut, &out, 0);
	llDataFileWrite(info.fptDif, &dif, 0);
	fprintf(info.fptOutParam, "A: %f\n", linfo.A);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
