/*
# mrcImageMultiCTFCompensation.c  1.3
# The latest update : 04/26/96 at 13:45:24
#
#@(#) mrcImageMultiCTFCompensation ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageMultiCTFCompensation
#@(#) Attention
#@(#)
* tacyas: 2008/09/11: Add ctfinfo list from Display2/ctfDisplay 
*/

static char __sccs_id[] = "@(#)mrcImageMultiCTFCompensation ver1.3; Date:96/04/26 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "ctfInfo.h"
#include "lmrcImageCTFCompensation.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMultiCTFCompensationInfo info;
	lmrcImageMultiCTFCompensationInfo linfo;
	mrcImage* src;
	mrcImage  dst;
	mrcImage* fft;
	mrcImage  dstfft;
	ctfInfo*  ctf;
	char      s[1024];
	long i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	src = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	fft = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	ctf = (ctfInfo*)memoryAllocate(sizeof(ctfInfo)*info.flagIn, "in main");

	/* Initial Data Set */
	for(i=0; i<info.flagIn; i++) {
		mrcFileRead(&(src[i]), info.In[i], "in main file", 0);
		if(IsImage(&(src[i]), "in main", 0)) {
			/* lfft2d(&(fft[i]), &(src[i])); */
			lmrcImageFFT(&(fft[i]), &(src[i]), 0);
		} else {
			fft[i] = src[i];
		}
		mrcImageFree(&(src[i]), "in main");

		if(info.flagCTF) {
			ctfInfoRead(info.fptCTF[i], &ctf[i], "", 0); 
		} else {
			if(i==0) {
				fseek(info.fptInList, 0L, SEEK_SET);
			}
			stringGetFromFile(s, "", info.fptInList, stdout, 1);
			ctf[i].defocus = stringGetNthRealData(s, 2, " \t,"); 
			ctf[i].Cs      = stringGetNthRealData(s, 3, " \t,");
			ctf[i].kV      = stringGetNthRealData(s, 4, " \t,");
			ctf[i].ratioOfAmpToPhase = stringGetNthRealData(s, 5, " \t,");
		}
		if(info.flagCTFMode) {
			ctf[i].mode    = info.CTFMode;
		} else {
			ctf[i].mode    = ctfInfoModePhaseAndAmpCTF;
		}
		// WhiteNoise
		if(info.flagWhiteNoise) {
			ctf[i].flagWhiteNoise = 1;
			ctf[i].WhiteNoise = info.WhiteNoise;
		} else {
			ctf[i].flagWhiteNoise = 0;
		}
		// NoiseRaising
		if(info.flagWhiteNoiseRaising) {
			ctf[i].flagWhiteNoiseRaising = 1;
			ctf[i].WhiteNoiseRaising = info.WhiteNoiseRaising;
			DEBUGPRINT2("Raising: %d %f\n", 1, info.WhiteNoiseRaising);
		} else {
			ctf[i].flagWhiteNoiseRaising = 0;
			ctf[i].WhiteNoiseRaising = 0;
		}
		// <axWhiteNoise
		if(info.flagMaxWhiteNoise) {
			ctf[i].flagMaxWhiteNoise = 1;
			ctf[i].MaxWhiteNoise     = info.MaxWhiteNoise;
			DEBUGPRINT2("maxWhiteNoise: %d %f\n", 1, info.MaxWhiteNoise);
		} else {
			ctf[i].flagMaxWhiteNoise = 0;
			ctf[i].MaxWhiteNoise = info.MaxWhiteNoise;
		}
		// N-dependent
		if(info.flagNdependentWhiteNoise) {
			ctf[i].flagNdependentWhiteNoise = 1;
			ctf[i].NdependentWhiteNoise     = info.NdependentWhiteNoise;
		} else {
			ctf[i].flagNdependentWhiteNoise = 0;
			ctf[i].NdependentWhiteNoise = info.NdependentWhiteNoise;
		}
		if(info.flagSinWinRmin && info.flagSinWinRmax) {
			ctf[i].flagWin = 1;
			ctf[i].CutLow  = info.SinWinRmin;
			ctf[i].CutHigh = info.SinWinRmax;
		} else {
			ctf[i].flagWin = 0;
		}
		DEBUGPRINT4("%f %f %f %ld\n", ctf[i].defocus, ctf[i].Cs, ctf[i].kV, ctf[i].mode);
	}
	linfo.maxiteration  = info.MaxIter;
	linfo.okrms         = 1e-6;
	linfo.diversefactor = 10;
	linfo.z             = 0;
	linfo.nhist         = 256;
	linfo.logfile       = info.fptLog;
	linfo.solventMode   = info.solventMode;
	linfo.definedSTD    = info.solventSTD;
	lmrcImageMultiCTFCompensation(&dstfft, fft, ctf, info.flagIn, linfo, info.mode); 
	if(info.flagfftOut) {
		mrcFileWrite(&dstfft, info.fftOut, "in main file", 0);
	}
	/* lfft2d(&dst, &dstfft); */
	lmrcImageFFT(&dst, &dstfft, 0);
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main file", 0); 
	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- InputFileFormat -----\n");
	fprintf(stderr, "filename0 deltaF[A] Cs[mm] kV[kV] ratioOfAmpToPhase\n");
	fprintf(stderr, "filename1 deltaF[A] Cs[mm] kV[kV] ratioOfAmpToPhase\n");
	fprintf(stderr, ".................\n\n");
	fprintf(stderr, "----- Input: ctfinfo, with the same order as the input; from Display2/ctfDisplay -----\n");
	fprintf(stderr, "filename0.ctfinfo \n");
	fprintf(stderr, "filename1.ctfinfo \n");
	fprintf(stderr, ".................\n\n");

	lmrcImageMultiCTFCompensationUsage(stderr); 
}
