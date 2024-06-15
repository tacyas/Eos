/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageDensityNormalizationByImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageDensityNormalizationByImage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageDensityNormalizationByImage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageDensityNormalizationByImage.h"

int
main(int argc, char* argv[]) 
{
	mrcImageDensityNormalizationByImageInfo  info;
	lmrcImageDensityNormalizationByImageInfo linfo;
	mrcImage in;
	mrcImage ref;
	mrcImage out;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	/* Input Data */
	mrcFileRead(&in,  info.In,  "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	/* Parameter Set */
	linfo.sigma = 1.0;
	if(info.flagCCenterX&&info.flagCCenterY&&info.flagCMinR&&info.flagCMaxR) {
		linfo.flagCylinder = 1;
		linfo.centerx = info.CCenterX;
		linfo.centery = info.CCenterY;
		linfo.minr = info.CMinR;
		linfo.maxr = info.CMaxR;
	}
	linfo.fitMode = info.fitMode;
	linfo.tstBGMin   = info.tstBGMin;
	linfo.tstBGMax   = info.tstBGMax;
	linfo.tstBGDelta = info.tstBGDelta;

	/* main procedure */ 
	lmrcImageDenstiyNormalizationByImage(&out, &in, &ref, &linfo, info.mode);

	/* Output Data */
	mrcFileWrite(&out, info.Out, "in main", 0);
	lmrcImageDensityNormalizationByImageInfoPrint(info.fptOutParam, linfo);
	if(info.flagUsedData) {
		for(i=0; i<linfo.nData; i++) {
			fprintf(info.fptUsedData, "%15.6g %15.6g\n", linfo.testData[i], linfo.refData[i]);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Mode -----\n");
	lmrcImageDensityNormalizationByImageModePrint(stderr);
}
