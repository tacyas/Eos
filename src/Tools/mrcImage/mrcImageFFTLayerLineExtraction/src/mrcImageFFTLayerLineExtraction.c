/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFFTLayerLineExtraction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFFTLayerLineExtraction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFFTLayerLineExtraction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#define UNDEBUG2
#include "eosString.h"
#include "genUtil.h"
#define SECTION_MARK " \t,"
#include "mrcImage.h"
#include "llData.h"

typedef struct lmrcImageFFTLayerLineExtractionInfo {
	float x;
	float z;
	int dY;
	int maxdY;
	float truePitch;
} lmrcImageFFTLayerLineExtractionInfo;

extern void lmrcImageFFTLayerLineExtraction(mrcImage* out,
											mrcImage* in,
											lmrcImageFFTLayerLineExtractionInfo linfo,
											long mode);

int
main(int argc, char* argv[]) 
{
	mrcImageFFTLayerLineExtractionInfo info;
	lmrcImageFFTLayerLineExtractionInfo linfo;
	mrcImage out;
	mrcImage in;
	char s[GEN_UTIL_MAX_STRING_LENGTH];
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);

	/* Information File Read */ 
	if(info.flagInI) {
		fpt = info.fptInI;
		fseek(fpt,0L, SEEK_SET);
		stringGetFromFile(s, "", fpt, NULL, 1);
		linfo.x  = stringGetNthRealData(s, 2, SECTION_MARK);
		linfo.z  = stringGetNthRealData(s, 3, SECTION_MARK);
		linfo.dY = stringGetNthRealData(s, 4, SECTION_MARK);
		DEBUGPRINT3("x %15.6f:  z %15.6f:  dY %d\n", linfo.x, linfo.z, linfo.dY);
	}else{
		DEBUGPRINT("in dY \n");
		linfo.x  = 0; 
		linfo.z  = 0;
		linfo.dY = floor(in.HeaderN.y*in.HeaderLength.y/info.truePitch);
		DEBUGPRINT3("x %15.6f:  z %15.6f:  dY %d\n", linfo.x, linfo.z, linfo.dY);
	}
	
	lmrcImageFFTLayerLineExtraction(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Input File Format\n");
	fprintf(stderr, "FileName  x  z  dY \n");
	fprintf(stderr, "---------------------- \n");
	fprintf(stderr, "-I option is stronger than -dY option.\n");
}

void
lmrcImageFFTLayerLineExtraction(mrcImage* out,
								mrcImage* in,
								lmrcImageFFTLayerLineExtractionInfo linfo,
								long mode)
{
	mrcImageParaTypeReal iX, iY;
	double re=0.0, im=0.0;
	double phase, mag;
	double phaseShiftX=0.0, phaseShiftZ=0.0;
	int maxdY;
	float maxdYcheck;

	/* check routine is under construction */
	maxdY = floor(in->HeaderN.y/linfo.dY + 0.5);
	maxdYcheck = in->HeaderN.y/linfo.dY;
	fprintf(stderr, "maxdY : %d    maxdYcheck : %15.6f \n", maxdY, maxdYcheck);

	out->Header = in->Header;
	out->HeaderN.y = maxdY;

	DEBUGPRINT1(" dY:%d\n",linfo.dY);
	DEBUGPRINT2(" inHeaderN.y:%ld,   inHeaderLength.y:%15.6f\n",  in->HeaderN.y,  in->HeaderLength.y);
	DEBUGPRINT2("outHeaderN.y:%ld,  outHeaderLength.y:%15.6f\n", out->HeaderN.y, out->HeaderLength.y);

	mrcInit(out, NULL);

	for(iY=-out->HeaderN.y/2.0; iY<=out->HeaderN.y/2.0 -1; iY++) {
		for(iX=0.0; iX<=out->HeaderN.x/2.0; iX++) {
			mrcPixelDataGet(in , iX, iY*linfo.dY, 0.0, &mag,   mrcPixelMag,   mrcPixelHowNearest);
			mrcPixelDataGet(in , iX, iY*linfo.dY, 0.0, &phase, mrcPixelPhase, mrcPixelHowNearest);

			DEBUG2PRINT2(" mag:%15.6f,   phase:%15.6f\n", mag, phase);
			phaseShiftX = (-2*PI)*(linfo.x*(iX           /(out->HeaderN.x*out->HeaderLength.x)));
			phaseShiftZ = (-2*PI)*(linfo.z*((iY*linfo.dY)/(out->HeaderN.y*out->HeaderLength.y)));
			DEBUG2PRINT2(" phaseShiftX:%15.6f,   phaseShiftZ:%15.6f\n", phaseShiftX, phaseShiftZ);

			re = mag*cos(phaseShiftX + phaseShiftZ + phase);
			im = mag*sin(phaseShiftX + phaseShiftZ + phase);

			mrcPixelDataSet(out, iX, iY, 0.0,  re, mrcPixelRePart);
			mrcPixelDataSet(out, iX, iY, 0.0,  im, mrcPixelImPart);
		}
	}

/*
			phaseShiftX = (2*PI)*(linfo.x*(iX/(out->HeaderN.x*out->HeaderLength.x)));
			phaseShiftZ = (2*PI)*(linfo.z*(iY/(out->HeaderN.y*out->HeaderLength.y)));
			mrcPixelDataGet(in , iX, iY*linfo.dY, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in , iX, iY*linfo.dY, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);

			mrcPixelDataGet(in , iX, iY*linfo.dY, 0.0, &mag,   mrcPixelMag,   mrcPixelHowNearest);
			mrcPixelDataGet(in , iX, iY*linfo.dY, 0.0, &phase, mrcPixelPhase, mrcPixelHowNearest);
			mrcPixelDataSet(out, iX, iY, 0.0,  mag,   mrcPixelMag);
			mrcPixelDataSet(out, iX, iY, 0.0,  phase, mrcPixelPhase);
*/

}

