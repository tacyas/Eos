/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSinogramCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSinogramCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSinogramCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageSinogram.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSinogramCorrelationInfo info;
	mrcImage in;
	mrcImage ref;
	mrcImage out;
	lmrcImageSinogramInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	linfo.dphi = in.HeaderLength.y*RADIAN;
	linfo.correlationMode = info.corMode;
	linfo.weightOf0thDerivation = info.w0th;
	linfo.weightOf1stDerivation = info.w1st;
	linfo.weightOf2ndDerivation = info.w2nd;
	linfo.threshold = info.threshold;
	linfo.LengthMode = info.LengthMode;
	linfo.LengthThresholdMode = info.LengthThresholdMode;
	linfo.LengthThresholdRatio = info.LengthThresholdRatio;
	linfo.LengthCorrelationMode = info.LCMode;
	linfo.LengthCorrelationThreshold = info.LengthCorrelationThreshold;
	linfo.weightOfLength = info.weightLength;
	lmrcImageSinogramCorrelation(&out, &in, &ref, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);

}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- LengthMode -----\n");
	fprintf(stderr, "-LM = 0 : without Length Correlation\n");
	fprintf(stderr, "-LM = 1 : addition to Length Correlation (-LT)\n");
	fprintf(stderr, "----- LengthCorrelationMode -----\n");
	fprintf(stderr, "-LCM = 0 : weight (-wL , -LTM , -LTR)\n");
	fprintf(stderr, "-LCM = 1 : threshold (-LTM , -LTR , -LCT)\n");
	fprintf(stderr, "-LCM = 2 : power weight (-LTM , -LTR , -wL)\n");
	fprintf(stderr, "----- LengthThresholdMode -----\n");
	fprintf(stderr, "-LTM = 0 : Multiply derivationMax and ratio(-LTR)\n");
	fprintf(stderr, "-LTM = 1 : Average of all derivation \n");
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "-m = 0 :    simple Correlation\n");
	fprintf(stderr, "-m = 1 :    weight Correlation (addition to derivation)\n");
	fprintf(stderr, "-m = 2 : threshold Correlation (addition to derivation)\n");
	fprintf(stderr, "-m = 3 : power weight Correlation (addition to derivation : -LM=1 -LCM=2)\n");
}

