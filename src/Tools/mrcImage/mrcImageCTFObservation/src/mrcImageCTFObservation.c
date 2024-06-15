/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCTFObservation ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrcImageCTFObservation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCTFObservation ver%I%; Date:%D% %Z%";
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
#include "ctfInfo.h"

int
main(int argc, char* argv[]) 
{
	mrcImageCTFObservationInfo info;
	mrcImage src;
	mrcImage dstfft;
	mrcImage dst;
	ctfInfo CTFInfo;
	float X, Y, R, CTF, Weight, dX, dY;
	double re, im;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	memoryClear(&CTFInfo, sizeof(CTFInfo), (char)0);
	if(info.flagCTF) {
		ctfInfoRead(info.fptCTF, &CTFInfo, "", 0);
		if(info.flagCs     ) CTFInfo.Cs = info.Cs;
		if(info.flagDefocus) CTFInfo.defocus = info.Defocus;
		if(info.flagkV     ) CTFInfo.kV = info.kV;
		if(info.flagctfMode) CTFInfo.mode = info.ctfMode;
		if(info.flagAoverP ) CTFInfo.ratioOfAmpToPhase = info.AoverP;
		if(info.flagAoverP ) CTFInfo.Ain = info.Ain;
	} else {
		CTFInfo.Cs = info.Cs;
		CTFInfo.defocus = info.Defocus;
		CTFInfo.kV = info.kV;
		CTFInfo.mode = info.ctfMode;
		CTFInfo.ratioOfAmpToPhase = info.AoverP;
		CTFInfo.Ain = info.Ain;
	}
	if(info.flagSinWinRmin && info.flagSinWinRmax) {
		CTFInfo.flagWin = 1;
		CTFInfo.CutLow  = info.SinWinRmin;
		CTFInfo.CutHigh = info.SinWinRmax;
	}
	if(info.flagdfMin) {
		CTFInfo.flagAstigmatism = 1;
		CTFInfo.defocus2D[0] = info.dfMax;
		CTFInfo.defocus2D[1] = info.dfMin;
		CTFInfo.defocus0axis = info.asAxis*RADIAN;
		DEBUGPRINT("Astig\n")
	}
	mrcFileRead(&src, info.In, "in main", 0);

	if(1<src.HeaderN.z) {
		lmrcImagesCTFObservation(&dst, &src, &CTFInfo, 0x10|info.mode);
	} else {
		lmrcImageCTFObservation(&dst, &src, &CTFInfo, 0x10|info.mode);
	}

	mrcFileWrite(&dst, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- ctfMode -----\n");
	fprintf(stderr, "-ctfMode %d  : Phase Only\n",           ctfInfoModePhaseCTFOnly);
	fprintf(stderr, "-ctfMode %d  : Phase and Amplitude \n", ctfInfoModePhaseAndAmpCTF);
	fprintf(stderr, "-ctfMode %d  : With Illumination Angle\n", ctfInfoModeWithIlluminationAngle);
	fprintf(stderr, "-ctfMode %d  : As Absolute Value\n", ctfInfoModeAbsoluteValue);
}


