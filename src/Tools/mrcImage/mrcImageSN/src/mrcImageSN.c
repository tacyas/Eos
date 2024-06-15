/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSN ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSN
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSN ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "Memory.h"
#include "lmrcImagesStatDataGet.h"

int
main(int argc, char* argv[]) 
{
	int i;
	lmrcImagesStatDataGetInfo linfo;
	mrcImageSNInfo info;
	mrcImage* in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	/* File Read */
	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	for(i=0; i<info.flagIn; i++) {
		mrcFileRead(&(in[i]), info.In[i], "in main", 0);
	}
	linfo.numImage = info.flagIn;
	linfo.flagAvg  = info.flagAvg;
	linfo.flagTrimmedAvg  = info.flagTrimmedAvg;
    linfo.TrimmedRange = info.TrimmedRange;
	linfo.flagMedian = info.flagMedian;
	linfo.flagSN   = info.flagSN;
	linfo.flagt    = info.flagt;
	linfo.flagSE   = info.flagSE;
	linfo.flagSD   = info.flagSD;
	linfo.flagVar  = info.flagVar;

	lmrcImagesStatDataGet(&linfo, in, info.flagIn, 0);

	if(info.flagAvg) {
		mrcFileWrite(&(linfo.Avg), info.Avg, "in main", 0);
	}
	if(info.flagTrimmedAvg) {
		mrcFileWrite(&(linfo.TrimmedAvg), info.TrimmedAvg, "in main", 0);
	}
	if(info.flagMedian) {
		mrcFileWrite(&(linfo.Median), info.Median, "in main", 0);
	}
	if(info.flagSN) {
		mrcFileWrite(&(linfo.SN), info.SN, "in main", 0);
	}
	if(info.flagt) {
		mrcFileWrite(&(linfo.t), info.t, "in main", 0);
	}
	if(info.flagSE) {
		mrcFileWrite(&(linfo.SE), info.SE, "in main", 0);
	}
	if(info.flagSD) {
		mrcFileWrite(&(linfo.SD), info.SD, "in main", 0);
	}
	if(info.flagVar) {
		mrcFileWrite(&(linfo.Var), info.Var, "in main", 0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{

}
