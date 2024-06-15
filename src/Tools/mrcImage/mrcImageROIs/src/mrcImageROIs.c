/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageROIs ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageROIs
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageROIs ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "File.h"
#include "eosString.h"
#include "mrcImage.h"
#include "lmrcImageROI2D.h"
#include "lmrcImageMontage.h"

int
main(int argc, char* argv[]) 
{
	mrcImageROIsInfo   info;
	lmrcImageROIsInfo linfo;
	mrcImage in;
	mrcImage* out;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	if(info.flagInfo) {
		lmrcImageROIsInformationGet(info.fptInfo, &linfo);
	} else {
		fprintf(stderr, "No information to extract ROIs\n");
		exit(EXIT_FAILURE);
	}
	if(info.flagShrink) {
		for(i=0; i<linfo.numROI; i++) {
			linfo.ROI[i].brx *= info.Shrink;
			linfo.ROI[i].bry *= info.Shrink;
			linfo.ROI[i].blx *= info.Shrink;
			linfo.ROI[i].bly *= info.Shrink;
			linfo.ROI[i].trx *= info.Shrink;
			linfo.ROI[i].try *= info.Shrink;
			linfo.ROI[i].tlx *= info.Shrink;
			linfo.ROI[i].tly *= info.Shrink;
			linfo.ROI[i].centerx *= info.Shrink;
			linfo.ROI[i].centery *= info.Shrink;
			linfo.ROI[i].width  *= info.Shrink;
			linfo.ROI[i].height *= info.Shrink;
			linfo.ROI[i].radius *= info.Shrink;
			linfo.ROI[i].startx *= info.Shrink;
			linfo.ROI[i].starty *= info.Shrink;
			linfo.ROI[i].endx *= info.Shrink;
			linfo.ROI[i].endy *= info.Shrink;
		}
	}
	for(i=0; i<linfo.numROI; i++) {
		if(info.NonPeriodic) {
			linfo.ROI[i].flagNonPeriodic =1;
		} else {
			linfo.ROI[i].flagNonPeriodic =0;
		}
	}
	mrcFileRead(&in, info.In, "main", 0); 

	out = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.numROI, "in main (out)");
	for(i=0; i<linfo.numROI; i++) {
		linfo.ROI[i].mode = info.Mode;
		linfo.ROI[i].flagWidth = info.flagWidth;
		if(info.flagWidth) {
			linfo.ROI[i].width = info.Width;
		}
		linfo.ROI[i].flagHeight = info.flagHeight;
		if(info.flagHeight) {
			linfo.ROI[i].height = info.Height;
		}
		lmrcImageSingleROI(&(out[i]), &in, &(linfo.ROI[i]), info.mode);
	}

	for(i=0; i<linfo.numROI; i++) {
		mrcFileWrite(&(out[i]), linfo.ROI[i].FileName, "main", 0);
	}

	if(info.flagOut) {
		lmrcImageMontageInfo lmonInfo;
		mrcImage mon;

		lmonInfo.PadMode = 0;
		lmonInfo.PadInfo.Width  = out[0].HeaderN.x;
		lmonInfo.PadInfo.Height = out[0].HeaderN.y;
		lmonInfo.PadInfo.Value  = 0;
		lmonInfo.nx      = MIN(linfo.numROI,10);
		lmonInfo.ny      = linfo.numROI/10+MIN(1,linfo.numROI%10);
		lmrcImageMontageCreate(&mon, out, linfo.numROI, lmonInfo, 0);
		mrcFileWrite(&mon, info.Out, "main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "0: Nearest \n");
	fprintf(stderr, "1: Bilinear\n");
	fprintf(stderr, "2: CubicConvolution\n");
	fprintf(stderr, "----- Information File Format -----\n");
	fprintf(stderr, "Shape ShapeInfo1 ... [Additional AdditionalInfo1 ...]\n");
	fprintf(stderr, "...............\n");

	lmrcImageROIsUsage(stderr);
/*
	fprintf(stderr, "Shape: OutFileName Rect       blx bly brx bry trx try tlx tly\n");
	fprintf(stderr, "Shape: OutFileName TiltRect   blx bly brx bry trx try tlx tly\n");
	fprintf(stderr, "Shape: OutFileName Rect2      centerx centery width height \n");
	fprintf(stderr, "Shape: OutFileName Circle     centerx centery radius \n");
*/
}

