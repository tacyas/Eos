/*
# mrcImageFourierPowerSpectrum.c  1.1
# The latest update : 07/02/96 at 15:01:17
#
#@(#) mrcImageFourierPowerSpectrum ver 1.1
#@(#) Created by Sakane Isao
#@(#)
#@(#) Usage : mrcImageFourierPowerSpectrum
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageFourierPowerSpectrum ver1.1; Date:96/07/02 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImage src;
	mrcImageFourierPowerSpectrumInfo info;
	lmrcImageFourierPowerSpectrumInfo linfo;
	mrcImageFourierPowerSpectrum theSpectrum;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	linfo.dX = info.dX;
	linfo.dY = info.dY;
	linfo.dZ = info.dZ;

	int i;
	mrcFileRead(&src, info.In, "in main", 0);
	theSpectrum = lmrcImageFourierPowerSpectrum(&src, &linfo, 0);
	for(i = 0; i < theSpectrum.n; i++) {
		fprintf(info.fptOut, "%g\t%g\n", theSpectrum.d * i, theSpectrum.h[i]);
	}
	lmrcImageFourierPowerSpectrumDeleteSpectrum(theSpectrum);

	return -1;
}

void
additionalUsage()
{
}
