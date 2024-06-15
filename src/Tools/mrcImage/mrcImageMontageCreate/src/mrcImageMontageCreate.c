/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMontageCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMontageCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMontageCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageMontage.h"

int
main(int argc, char* argv[]) 
{
	mrcImageMontageCreateInfo info;
	lmrcImageMontageInfo linfo;
	mrcImage* in;
	mrcImage  out;
	int i;
	int imageNum;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	/* Max */
	linfo.flagMaxValue = info.flagMax;
	linfo.MaxValue     = info.Max;
	linfo.flagValueAssignedToMax = info.flagVMax;
	linfo.ValueAssignedToMax     = info.VMax;

	linfo.flagNoAverage   = info.NoAverage;
	linfo.flagEdgeAverage = info.EdgeAverage;
	linfo.EdgeAverageWindow = info.EdgeAverageWindow;
	/* */
	imageNum = info.flagIn;
	linfo.nx = info.Nx;
	if(imageNum<linfo.nx) {
		fprintf(stderr, "The number of images %d is smaller than Nx %d\n", imageNum, linfo.nx);
	}
	if(info.flagNy) {
		linfo.ny = info.Ny;
		if(linfo.ny*linfo.nx<imageNum) {
			fprintf(stderr, "The number of images %d is larger than Nx*Ny %d. Therefore, first Nx*Ny images only will be used for montage.\n", imageNum, linfo.ny*linfo.nx);
			imageNum = linfo.ny*linfo.nx;
		} else if(imageNum < linfo.ny*linfo.nx) {
			fprintf(stderr, "The number of images %d is smaller than Nx*Ny %d.\n", imageNum, linfo.ny*linfo.nx);
		}
	} else {
		if(imageNum%linfo.nx==0) {
			linfo.ny = imageNum/linfo.nx; 
		} else {
			linfo.ny = imageNum/linfo.nx + 1; 
		}
		if(imageNum < linfo.ny*linfo.nx) {
			fprintf(stderr, "The number of images %d is smaller than Nx*Ny %d.\n", imageNum, linfo.ny*linfo.nx);
		}
	}

	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*imageNum, "from main");
	for(i=0; i<imageNum; i++) {
		mrcFileRead(&(in[i]), info.In[i], "main", 0);
	}

	linfo.PadMode        = info.PadMode;
	linfo.PadInfo.Value  = info.Value;
	linfo.PadInfo.AWSize = info.AvgWnd;
	if(info.flagWidth) { 
		linfo.PadInfo.Width = info.Width;	
	} else {
		linfo.PadInfo.Width = in[0].HeaderN.x;
	}
	if(info.flagHeight) { 
		linfo.PadInfo.Height = info.Height;	
	} else {
		linfo.PadInfo.Height = in[0].HeaderN.y;
	}

	lmrcImageMontageCreate(&out, in, imageNum, linfo, 0);

	mrcFileWrite(&out, info.Out, "main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>> -i inputfile <<<: InputFile Format\n"); 
	fprintf(stderr, "hf0000.roi\n"); 
	fprintf(stderr, "hf0001.roi\n"); 
	fprintf(stderr, "..........\n"); 
	fprintf(stderr, "hf000n.roi\n"); 
	fprintf(stderr, ">>> output file sequence <<<\n"); 
	fprintf(stderr, "from bottom left \n"); 
	fprintf(stderr, ">>> Pad Mode <<<\n"); 
	fprintf(stderr, "see mrcImagePad \n"); 
}

