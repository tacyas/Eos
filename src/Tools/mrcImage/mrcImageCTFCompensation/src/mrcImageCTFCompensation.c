/*
# mrcImageCTFCompensation.c  1.1
# The latest update : 05/28/96 at 09:33:29
#
#@(#) mrcImageCTFCompensation ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageCTFCompensation
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageCTFCompensation ver1.1; Date:96/05/28 @(#)";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG 
#include "eosString.h"
#include "Memory.h"
#include "genUtil.h"
#define SECTION_MARK " \t"
#include "mrcImage.h"
#include "ctfInfo.h"
#include "lmrcImageCTFCompensation.h"

int
main(int argc, char* argv[]) 
{
	mrcImageCTFCompensationInfo info;
	mrcImage src;
	mrcImage dst;
	mrcImage fft;
	ctfInfo CTFInfo;
	char s[GEN_UTIL_MAX_STRING_LENGTH];
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	memoryClear(&CTFInfo, sizeof(CTFInfo), 0);
	DEBUGPRINT1("Astigmatism %d\n", CTFInfo.flagAstigmatism);
	if(info.flagInfo){
		fpt = info.fptInfo;
		fseek(fpt,0L, SEEK_SET);
		stringGetFromFile(s, "", fpt, NULL, 1);
		/*
		info.In                   = stringGetNthWord(s, 1, " ,\t\n");
		*/
		CTFInfo.defocus           = stringGetNthRealData(s, 1, SECTION_MARK);
		CTFInfo.Cs                = stringGetNthRealData(s, 2, SECTION_MARK);
		CTFInfo.kV                = stringGetNthRealData(s, 3, SECTION_MARK);
		CTFInfo.ratioOfAmpToPhase = stringGetNthRealData(s, 4, SECTION_MARK);
		DEBUGPRINT4("defocus [%15.6f] Cs [%15.6f] kV[%15.6f] AmplitudeContrast[%15.6f]\n",
							CTFInfo.defocus,
							CTFInfo.Cs,
							CTFInfo.kV,
							CTFInfo.ratioOfAmpToPhase);
		CTFInfo.WhiteNoise = info.WhiteNoise; 
    }

	if(info.flagInfo2){
		fpt = info.fptInfo2;
		fseek(fpt,0L, SEEK_SET);
		ctfInfoRead(fpt, &CTFInfo, "", 0);
		DEBUGPRINT4("defocus [%15.6f] Cs [%15.6f] kV[%15.6f] AmplitudeContrast[%15.6f]\n",
							CTFInfo.defocus,
							CTFInfo.Cs,
							CTFInfo.kV,
							CTFInfo.ratioOfAmpToPhase);
		DEBUGPRINT3("Astigmatism %15.6f %15.6f %15.6f \n", CTFInfo.defocus2D[0], CTFInfo.defocus2D[1], CTFInfo.defocus0axis*DEGREE);
		CTFInfo.WhiteNoise = info.WhiteNoise; 
    }

	DEBUGPRINT1("Astigmatism %d\n", CTFInfo.flagAstigmatism);
	if(info.flagCs) {
		CTFInfo.Cs = info.Cs;
	}
	if(info.flagDefocus) {
		CTFInfo.defocus = info.Defocus;
	}
	if(info.flagkV) {
		CTFInfo.kV = info.kV;
	}
	if(info.flagWhiteNoise) {
		CTFInfo.WhiteNoise = info.WhiteNoise; 
	}
	if(info.flagAmp) {
		CTFInfo.ratioOfAmpToPhase = info.Amp;
	}

	if(info.flagdfMin) {
		CTFInfo.flagAstigmatism = 1;
		CTFInfo.defocus2D[0] = info.dfMax;
		CTFInfo.defocus2D[1] = info.dfMin;
		CTFInfo.defocus0axis = info.asAxis*RADIAN;
		DEBUGPRINT3("Astigmatism %15.6f %15.6f %15.6f \n", CTFInfo.defocus2D[0], CTFInfo.defocus2D[1], CTFInfo.defocus0axis*DEGREE);
	} 

    if(info.flagWhiteNoiseRaising) {
        CTFInfo.WhiteNoiseRaising = info.WhiteNoiseRaising;
    }
	mrcFileRead(&src, info.In, "in main", 0);
	if(IsImage(&src, "in main", 0)) {
		lmrcImageFFT(&fft, &src, 0);
	} else if(IsFT(&src, "in main", 0)) {
		fft = src;
	} else {
		fprintf(stderr, "Not supported mode : %d\n", src.HeaderMode);
		exit(EXIT_FAILURE);
	}
	if(info.flagSinWinRmin&&info.flagSinWinRmax) {
		CTFInfo.flagWin = 1;
		CTFInfo.CutLow  = info.SinWinRmin; 
		CTFInfo.CutHigh = info.SinWinRmax;
	}

	if(info.NoAstigmatism) {	
		 CTFInfo.flagAstigmatism = 0;
	}	
	DEBUGPRINT3("%ld %f %f ",CTFInfo.flagWin,CTFInfo.CutLow,CTFInfo.CutHigh);
	lmrcImageCTFCompensation(&fft, &CTFInfo, info.mode);
	lmrcImageFFT(&dst, &fft, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- mode -----\n");
#ifdef TEST
	fprintf(stderr, "\t\t0: No CTF compensation\n");
	fprintf(stderr, "\t\t1: Phase only: W = CTF/|CTF|\n");
	fprintf(stderr, "\t\t2: Multiply  : W = CTF\n");
	fprintf(stderr, "\t\t3: Multiply  : W = 1/CTF\n");
	fprintf(stderr, "\t\t4: Wiener filter (constant noise): W = CTF/(|CTF|^2+N^2)\n");
#endif
	ctfWeightForCorrectionUsage(stderr);

	fprintf(stderr, "----- Note -----\n");
	fprintf(stderr, "You can enter information from -info\n");
	fprintf(stderr, "Info file was made by llExtractWithLayerSeparationFilamentInfo -oI \n");
	fprintf(stderr, "defocus Cs kV AmplitudeContrast\n");
	fprintf(stderr, "----- Note1 -----\n");
	fprintf(stderr, "-NoStig is the highest priority and so -Astig and parameters in -info2 are ignored.\n");
}
