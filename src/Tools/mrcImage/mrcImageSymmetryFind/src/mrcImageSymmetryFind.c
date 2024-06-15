/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSymmetryFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSymmetryFind
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSymmetryFind ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "lmrcImageSymmetryFind.h"

int
main(int argc, char* argv[])
{
	mrcImage in;
	mrcImageSymmetryFindInfo info;
	lmrcImageSymmetryFindInfo linfo;
	int i;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	if(info.Algorythm) {
		lmrcImageSymmetryFindAlgorythmPrint(stderr);
		exit(EXIT_FAILURE);
	}


	DEBUGPRINT("#### Program Started\n");
	mrcFileRead(&in, info.In, "in main", 0);

	if(info.flagImage && info.flagBack) {
		linfo.Images = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagImage, "in main for Image");
		linfo.Backs  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagBack,  "in main for Back");
		for(i=0; i<info.flagImage; i++) {
			mrcFileRead(&(linfo.Images[i]), info.Image[i], "in main", 0);
		}
		linfo.flagImages = info.flagImage;
		for(i=0; i<info.flagBack; i++) {
			mrcFileRead(&(linfo.Backs[i]), info.Back[i], "in main", 0);
		}
		linfo.flagBacks = info.flagBack;
	}

	linfo.dr = info.dr;
	linfo.dtheta = info.dtheta*RADIAN;
	linfo.threshold1 = info.threshold1;
	linfo.threshold2 = info.threshold2;
	linfo.rmin = info.rmin;
	linfo.rmax = info.rmax;

	if(info.flagnmin) {
		linfo.minNfold = info.nmin;
	} else {
		linfo.minNfold = 2;
	}
	if(info.flagnmax) {
		linfo.maxNfold = info.nmax;
	} else {
		linfo.maxNfold = info.n;
	}
	linfo.centreMode = info.centreMode;
	linfo.fptOut = info.fptOut2;
	linfo.subtractionMode   = info.mode2;
	linfo.flagAvg = info.flagAvg;
	linfo.avgName = info.Avg;
	linfo.centreInfo.minx = info.minx;
	linfo.centreInfo.maxx = info.maxx;
	linfo.centreInfo.delx = info.delx;
	linfo.centreInfo.miny = info.miny;
	linfo.centreInfo.maxy = info.maxy;
	linfo.centreInfo.dely = info.dely;
	linfo.centreInfo.minz = info.minz;
	linfo.centreInfo.maxz = info.maxz;
	linfo.centreInfo.delz = info.delz;
	linfo.centreInfo.delPHI = linfo.dtheta*RADIAN;

	lmrcImageSymmetryFind(&in, &linfo, info.mode1);
	
	if(linfo.flagCorrelation && info.flagOut) {
		mrcFileWrite(&linfo.correlation, info.Out, "in main", 0);
	}
	if(linfo.flagFourier && info.flagOut) {
		mrcFileWrite(&linfo.fourier, info.Out, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
  additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
  lmrcImageSymmetryFindModePrint(stderr);
}

