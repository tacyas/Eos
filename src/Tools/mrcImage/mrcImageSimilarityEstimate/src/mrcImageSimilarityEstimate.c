/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSimilarityEstimate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSimilarityEstimate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSimilarityEstimate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "eosString.h"
#include "genUtil.h"
#define SECTION_MARK " \t,"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageCorrelation.h"
#include "ctfInfo.h"

typedef struct lmrcImageSimilarityEstimateInfo {
	ctfInfo CTFInfo;
	int imageNum;
	long cormode;
	float max;
	float maxx;
	float maxy;
	float maxz;
	float maxNumber;
} lmrcImageSimilarityEstimateInfo;

extern void lmrcImageSimilarityEstimate(mrcImage* in, mrcImage* ref, mrcImage* cor, mrcImage* outCor,
										lmrcImageSimilarityEstimateInfo* info);

int
main(int argc, char* argv[]) 
{
	mrcImageSimilarityEstimateInfo info;
	lmrcImageSimilarityEstimateInfo linfo; 
	mrcImage  in;
	mrcImage  outCor;
	mrcImage* ref;
	mrcImage* cor;
	char s[GEN_UTIL_MAX_STRING_LENGTH];
	FILE* fpt;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.imageNum = info.flagref;
	linfo.cormode  = info.cormode;

	memoryClear(&linfo.CTFInfo, sizeof(linfo.CTFInfo), (char)0);

	fpt = info.fptctfinfo;
	fseek(fpt,0L, SEEK_SET);
	stringGetFromFile(s, "", fpt, NULL, 1);
	linfo.CTFInfo.defocus = stringGetNthRealData(s, 1, SECTION_MARK);
	linfo.CTFInfo.Cs = stringGetNthRealData(s, 2, SECTION_MARK);
	linfo.CTFInfo.kV = stringGetNthRealData(s, 3, SECTION_MARK);
	linfo.CTFInfo.ratioOfAmpToPhase = stringGetNthRealData(s, 4, SECTION_MARK);
	linfo.CTFInfo.mode = 1; /* Phase and Amplitude */
	linfo.CTFInfo.Ain = 0.0;

	DEBUGPRINT6("Cs %15.6f, defocus %15.6f, kV %15.6f, mode %ld, AoverP %15.6f, Ain %15.6f in main \n",
														linfo.CTFInfo.Cs, 
														linfo.CTFInfo.defocus,
														linfo.CTFInfo.kV,
														linfo.CTFInfo.mode,
														linfo.CTFInfo.ratioOfAmpToPhase,
														linfo.CTFInfo.Ain);

	DEBUGPRINT1("Image Number %d in main\n", linfo.imageNum);
	
	ref = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.imageNum, "from main");
	cor = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.imageNum, "from main");

	mrcFileRead(&in ,info.In ,"in main" ,0);

	for(i=0; i<linfo.imageNum; i++) {
		mrcFileRead(&(ref[i]), info.ref[i], "main", 0);
	}
	
	lmrcImageSimilarityEstimate(&in, ref, cor, &outCor, &linfo);

	if(info.flagcorfilename){
		for(i=0; i<linfo.imageNum; i++) {
			mrcFileWrite(&(cor[i]), info.corfilename[i], "main", 0);
		}
	}

	if(info.flagOutCor){
		mrcFileWrite(&outCor, info.OutCor, "main", 0);
	}

	DEBUGPRINT6("maxNumber:%15.6f max:%15.6f (%15.6f, %15.6f, %15.6f) correlation mode %ld in main\n",
					linfo.maxNumber, 
					linfo.max, 
					linfo.maxx,
					linfo.maxy,
					linfo.maxz,
					linfo.cormode); 

	fprintf(info.fptOut, "%s maxNumber: %15.6f max: %15.6f (%15.6f, %15.6f, %15.6f) correlation mode %ld\n",
									info.In,
									linfo.maxNumber,
									linfo.max,
									linfo.maxx,
									linfo.maxy,
									linfo.maxz,
									linfo.cormode);
	
	exit(EXIT_SUCCESS);
}

void
lmrcImageSimilarityEstimate(mrcImage* in, mrcImage* ref, mrcImage* cor, mrcImage* outCor,
							lmrcImageSimilarityEstimateInfo* info)
{
	int i;
	mrcImageInformation imgInfo;
	mrcImage reffft;
	mrcImage ctfreffft;
	float tmpmax;

	memoryClear(&imgInfo, sizeof(imgInfo), 0);

	DEBUGPRINT1("correlation mode: %ld in lmrcImageSimilarityEstimate\n", info->cormode);

	lmrcImageFFT(&reffft, &(ref[0]), 0);
	lmrcImageCTFObservation(&ctfreffft, &reffft, &info->CTFInfo, 0);
	lmrcImageCorrelation(&(cor[0]), &ctfreffft, in, info->cormode);
	lmrcImageInformation(&imgInfo, &(cor[0]));
	info->max  = imgInfo.max;
	info->maxx = imgInfo.maxCoord.x;
	info->maxy = imgInfo.maxCoord.y;
	info->maxz = imgInfo.maxCoord.z;
	info->maxNumber = 0;
	lmrcImageCorrelation(outCor, &ctfreffft, in, info->cormode);

	DEBUGPRINT5("maxNumber %15.6f, max %15.6f (%15.6f %15.6f %15.6f) in lmrcImageSimilarityEstimate\n",
													info->maxNumber,
													info->max,
													info->maxx,
													info->maxy,
													info->maxz); 

	for(i=0; i<info->imageNum; i++) {
		lmrcImageFFT(&reffft, &(ref[i]), 0);
		lmrcImageCTFObservation(&ctfreffft, &reffft, &info->CTFInfo, 0);
		lmrcImageCorrelation(&(cor[i]), &ctfreffft, in, info->cormode);
		lmrcImageInformation(&imgInfo, &(cor[i]));
		DEBUGPRINT5("i: %d, max: %15.6f (%15.6f, %15.6f, %15.6f) in lmrcImageSimilarityEstimate\n",
					 i, imgInfo.max, imgInfo.maxCoord.x, imgInfo.maxCoord.y, imgInfo.maxCoord.z);

		tmpmax = imgInfo.max;
		if (tmpmax>info->max){
			info->max  = tmpmax;
			info->maxx = imgInfo.maxCoord.x;
			info->maxy = imgInfo.maxCoord.y;
			info->maxz = imgInfo.maxCoord.z;
			info->maxNumber = i;
			lmrcImageCorrelation(outCor, &ctfreffft, in, info->cormode);
		}
	}
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "cormode:(lmrcImageCorrelation)\n");
	fprintf(stderr, "0: Normal Correlation FxG*\n");
	fprintf(stderr, "1: Phase  Correlation FxG*/     |FxG*|\n");
	fprintf(stderr, "2: Phase  Correlation FxG*/sqrt(|FxG*|)\n");
	fprintf(stderr, "3: Normalized Normal Correlation FxG*/|F||G|)\n");
	fprintf(stderr, "16: (0,0) = 0\n");
	fprintf(stderr, "ctfmode:1 (Phase and Amplitude)\n");
	fprintf(stderr, "ctfinf format:defocus Cs kV AoverP\n");
}
