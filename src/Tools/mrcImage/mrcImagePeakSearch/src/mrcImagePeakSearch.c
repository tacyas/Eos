/*
# mrcImagePeakSearch : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagePeakSearch
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageBinarization.h"
#include "lmrcImageCalcArea.h"

typedef struct lmrcImagePeakSearchInfo {
	double area;      /* pixel size */
	double threshold; /* pixel values */
	mrcImage outB;
	mrcImage outL;
	mrcImage outA;
	mrcImageInformation imageInfo;
} lmrcImagePeakSearchInfo;

/*
typedef enum lmrcImagePeakSearchMode {
	a=0,
	b=1
} lmrcImagePeakSearchMode;
*/

void lmrcImagePeakSearch(mrcImage* out, mrcImage* in, lmrcImagePeakSearchInfo* linfo, int mode);
void lmrcImagePeakInformation(mrcImage* out, mrcImage* in, lmrcImagePeakSearchInfo* linfo, int mode);
void lmrcImagePeakInformationPrint(FILE* fpt, lmrcImagePeakSearchInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImagePeakSearchInfo info;
	lmrcImagePeakSearchInfo linfo;
	mrcImage in;
	mrcImage out;
	mrcImageInformation imageInfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	/* Threshold */
	if(info.flagThreshold && info.flagSigma) {
		fprintf(stderr, "Cannot use both Threshold(-T) and Sigma(-t).\n");		
		fprintf(stderr, "Put Sigma(-t) above Threshold(-T).\n");		
	}
	if(!info.flagThreshold && !info.flagSigma) {
		fprintf(stderr, "Use Sigma (-t).\n");		
	}
	imageInfo.mode = meanOfAll;
	lmrcImageInformation(&imageInfo, &in);
	linfo.imageInfo = imageInfo;
	if(info.flagSigma || !info.flagThreshold) {
		info.Threshold = imageInfo.mean + info.Sigma*imageInfo.sd;
	}
	linfo.threshold = info.Threshold;

	/* Area */
	if(info.flagAreaPixel && info.flagArea) {
		fprintf(stderr, "Cannot use both AreaPixel[pixel^1 or ^2 or ^3] (-A) and Area[A ^1 or ^2 or ^3] (-a).\n");		
		fprintf(stderr, "Put Area(-a) above AreaPixel(-A).\n");		
	}
	if(!info.flagAreaPixel && !info.flagArea) {
		fprintf(stderr, "Use Area(-a).\n");		
	}
	if(info.flagArea || !info.flagAreaPixel) {
		if(       1< in.HeaderN.x && 1< in.HeaderN.y && 1==in.HeaderN.z) {  /* 2D */
			info.AreaPixel = info.Area/(in.HeaderLength.x*in.HeaderLength.y);
		} else if(1< in.HeaderN.x && 1==in.HeaderN.y && 1< in.HeaderN.z) { 
			info.AreaPixel = info.Area/(in.HeaderLength.x*in.HeaderLength.z);
		} else if(1==in.HeaderN.x && 1< in.HeaderN.y && 1< in.HeaderN.z) { 
			info.AreaPixel = info.Area/(in.HeaderLength.y*in.HeaderLength.z);
		} else if(1< in.HeaderN.x && 1< in.HeaderN.y && 1< in.HeaderN.z) {  /* 3D */
			info.AreaPixel = info.Area/(in.HeaderLength.x*in.HeaderLength.y*in.HeaderLength.z);
		} else if(1< in.HeaderN.x && 1==in.HeaderN.y && 1==in.HeaderN.z) {  /* 1D */
			info.AreaPixel = info.Area/(in.HeaderLength.x);
		} else if(1==in.HeaderN.x && 1< in.HeaderN.y && 1==in.HeaderN.z) { 
			info.AreaPixel = info.Area/(in.HeaderLength.y);
		} else if(1==in.HeaderN.x && 1==in.HeaderN.y && 1< in.HeaderN.z) { 
			info.AreaPixel = info.Area/(in.HeaderLength.z);
		} else {                                                            /* 0D */ 
			info.AreaPixel = info.Area/(in.HeaderLength.x);
		}
	}
	linfo.area = info.AreaPixel;
	DEBUGPRINT2("Thres: %f Area: %f\n", linfo.threshold, linfo.area);
	/* */
	lmrcImagePeakSearch(&out, &in, &linfo, info.mode);	
	lmrcImagePeakInformation(&out, &in, &linfo, info.mode);

	/* */
	lmrcImagePeakInformationPrint(info.fptOutStatics, &linfo, info.mode);
	if(info.flagOut) {
		mrcFileWrite(&out, info.Out, "in main", 0);
	}
	if(info.flagOutB) {
		mrcFileWrite(&linfo.outB, info.OutB, "in main", 0);
	}
	if(info.flagOutL) {
		mrcFileWrite(&linfo.outL, info.OutL, "in main", 0);
	}
	if(info.flagOutA) {
		mrcFileWrite(&linfo.outA, info.OutA, "in main", 0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImagePeakSearch(mrcImage* out, mrcImage* in, lmrcImagePeakSearchInfo* linfo, int mode)
{
	lmrcImageBinarizationInfo llinfo;
	mrcImageParaTypeReal x, y, z;
	double data;
	llinfo.thresHold = linfo->threshold;
	llinfo.value     = 0;
	llinfo.flagNear  = 0;
	llinfo.near      = 0;
	llinfo.nLevel    = 1;
	llinfo.p         = 0;
	lmrcImageBinarization(&linfo->outB, in, llinfo, 0);
	lmrcImageCalcArea(&linfo->outA, &linfo->outL, &linfo->outB, 0);
	out->Header = linfo->outA.Header;
	mrcInit(out, NULL);
	for(z=0; z<linfo->outA.HeaderN.z; z++) {
	for(y=0; y<linfo->outA.HeaderN.y; y++) {
	for(x=0; x<linfo->outA.HeaderN.x; x++) {
		mrcPixelDataGet(&linfo->outA, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(linfo->area<=data) {
			mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);
		} else {
			mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);
		}
	}
	}
	}
}

void 
lmrcImagePeakInformation(mrcImage* out, mrcImage* in, lmrcImagePeakSearchInfo* linfo, int mode)
{


}
void 
lmrcImagePeakInformationPrint(FILE* fpt, lmrcImagePeakSearchInfo* linfo, int mode)
{


}

