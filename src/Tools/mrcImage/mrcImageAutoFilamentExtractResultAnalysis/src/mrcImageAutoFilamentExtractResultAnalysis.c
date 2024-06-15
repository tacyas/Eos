/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAutoFilamentExtractResultAnalysis ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAutoFilamentExtractResultAnalysis
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageAutoFilamentExtractResultAnalysis ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lllExtractdYEstimate.h"

typedef struct lmrcImageAutoFilamentFinalExtractInfo{
	char* In;
	FILE* fptIn;
	char* Out;
	FILE* fptOut;
	int ROIy;
}lmrcImageAutoFilamentFinalExtractInfo;

extern void __lmrcImageAutoFilamentFinalExtract(lmrcImageAutoFilamentFinalExtractInfo* linfo,
										        lllExtractdYEstimateInfo* dYinfo);

int
main(int argc, char* argv[]) 
{
	mrcImageAutoFilamentExtractResultAnalysisInfo info;
	lllExtractdYEstimateInfo dYinfo;
	lmrcImageAutoFilamentFinalExtractInfo linfo;

	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcHeaderRead(&in, info.In, "in main", 0);

	dYinfo.truePitch = info.truePitch;	
	dYinfo.deltadY   = info.deltadY;	
	dYinfo.mag       = info.mag;	
	dYinfo.PixelSize = info.PixelSize;	

	linfo.ROIy       = info.y;
	linfo.In         = info.In;
	linfo.Out        = info.Out;

	__lmrcImageAutoFilamentFinalExtract(&linfo, &dYinfo);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
__lmrcImageAutoFilamentFinalExtract( lmrcImageAutoFilamentFinalExtractInfo* linfo,
                                     lllExtractdYEstimateInfo* dYinfo)
{
	char commandFinalROI[200];
	char commandMagnificationChange[200];
	char commandHeaderChange[200];
	char commandRM1[200];
	char commandRM2[200];
	char FilenameInROI[100];
	char FilenameOutROI[100];
	char FilenameInMag[100];
	char FilenameOutMag[100];
	char FilenameInHead[100];
	char FilenameOutHead[100];
	int ROIy;
	int dY;
	mrcImage inExtracted;

	DEBUGPRINT("############ Final Extract ############\n");
	ROIy = ((int)(linfo->ROIy/2))*2 -1 ;

	sprintf (FilenameInROI , "%s", linfo->In);
	sprintf (FilenameOutROI, "%s.final", FilenameInROI);
	sprintf (commandFinalROI, "%s %s %s %s %s  %s %d %s",
								"mrcImageROI", "-i", FilenameInROI, "-o", FilenameOutROI,
								"-y", ROIy, "-m 2\n");
	fprintf(stderr, commandFinalROI);
	system (commandFinalROI);

	mrcHeaderRead(&inExtracted, FilenameOutROI, "in __lmrcImageAutoFilamentFinalExtract", 0);
	dY = lllExtractdYEstimate(&inExtracted, dYinfo);
	DEBUGPRINT1("dY=%d\n",dY);


	sprintf (FilenameInMag , "%s", FilenameOutROI);
	sprintf (FilenameOutMag, "%s.mag", linfo->In);
	sprintf (commandMagnificationChange, "%s %s %s %s %s  %s %d %s %f %s %d %s",
									"mrcImageROI", "-i", FilenameInMag, "-o", FilenameOutMag,
									"-truePitch", (int)dYinfo->truePitch, "-Ly", dYinfo->PixelSize,
									"-dY", dY, "-m 2\n");
	fprintf(stderr, commandMagnificationChange);
	system (commandMagnificationChange);

	sprintf (FilenameInHead , "%s", FilenameOutMag);
	sprintf (FilenameOutHead, "%s", linfo->Out);
	sprintf (commandHeaderChange, "%s %s %s %s %s  %s %f %s %f \n",
								"mrcImageHeaderChange", "-i", FilenameInHead, "-o", FilenameOutHead,
								"-x", dYinfo->PixelSize, "-y", dYinfo->PixelSize);
	fprintf(stderr, commandHeaderChange);
	system (commandHeaderChange);
		
	sprintf (commandRM1, "rm -f %s\n", FilenameOutROI);
	fprintf(stderr, commandRM1);
	system (commandRM1);

	sprintf (commandRM2, "rm -f %s\n", FilenameOutMag);
	fprintf(stderr, commandRM2);
	system (commandRM2);
}

