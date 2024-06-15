/*
# mrcFFTShellInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTShellInfo
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
#include "lmrcFFTInfo.h"

typedef struct lmrcFFTShellInfoInfo {
	double minR;
	double maxR;
} lmrcFFTShellInfoInfo;

typedef enum lmrcFFTShellInfoMode {
	lmrcFFTShellInfoAverageMagnitude=1,
	lmrcFFTShellInfoAveragePower=2
} lmrcFFTShellInfoMode;

extern void lmrcFFTShellInfo(FILE* fpt, mrcImage* in, lmrcFFTShellInfoInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcFFTShellInfoInfo info;
	lmrcFFTShellInfoInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.minR = info.minR;
	linfo.maxR = info.maxR;

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcFFTShellInfo(info.fptOut, &in, linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-mode %d : AveragedMagnitute\n", lmrcFFTShellInfoAverageMagnitude);
	fprintf(stderr, "-mode %d : AveragedPower\n",     lmrcFFTShellInfoAveragePower);
}

void 
lmrcFFTShellInfo(FILE* fpt, mrcImage* in, lmrcFFTShellInfoInfo linfo, int mode)
{
	double data;
	mrcImage fft;
	int flagFFT=0;

	if(IsImage(in, "in lmrcFFTShellInfo", 0)) {
		lmrcImageFFT(&fft, in, 0);
		flagFFT=1;	
	}else if(IsFT(in, "in lmrcFFTShellInfo", 0)) {
		fft = *in;
	} else {
		fprintf(stderr, "Not supported in file\n");
		usage("");	
	}

	if(mode&&lmrcFFTShellInfoAverageMagnitude) {
			data  = lmrcImageFSInfoScatteringAugularDistribution3DShell(&fft, linfo.minR, linfo.maxR, mrcPixelMag);
			fprintf(fpt, "3DShell.MagnituiteAverage: %g\n", data);
	}
	if(mode&&lmrcFFTShellInfoAveragePower) {
			data  = lmrcImageFSInfoScatteringAugularDistribution3DShell(&fft, linfo.minR, linfo.maxR, mrcPixelPow);
			fprintf(fpt, "3DShell.PowerAverage: %g\n", data);
	}
	if(flagFFT) {
		mrcImageFree(&fft, "in lmrcFFTShellInfo");
	}
}
