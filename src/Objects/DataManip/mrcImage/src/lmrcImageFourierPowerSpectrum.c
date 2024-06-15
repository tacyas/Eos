/*
# lmrcImageFourierPowerSpectrum.c  1.2
# The latest update : 07/02/96 at 14:47:12
#
#@(#) lmrcImageFourierPowerSpectrum ver 1.2
#@(#) Created by Sakane Isao
#@(#)
#@(#) Usage : mrcImageFourierPowerSpectrum
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrcImageFourierPowerSpectrum ver1.2; Date:96/07/02 @(#)";
#include <stdio.h>
#include <math.h>
#include "genUtil.h"
#include "mrcImage.h"
#include "ctfInfo.h"
#include "Memory.h"

#define PI M_PI

typedef struct { double r, i;} Complex;

extern mrcImageFourierPowerSpectrum lmrcImageFourierPowerSpectrumMakeSpectrum(const mrcImage *inFFT, lmrcImageFourierPowerSpectrumInfo *info);
extern void lmrcImageFourierPowerSpectrumDeleteSpectrum(mrcImageFourierPowerSpectrum theSpectrum);
extern mrcImageFourierPowerSpectrum lmrcImageFourierPowerSpectrum(const mrcImage *inMrc, lmrcImageFourierPowerSpectrumInfo *info, long mode);

mrcImageFourierPowerSpectrum lmrcImageFourierPowerSpectrum(const mrcImage *inMrc, lmrcImageFourierPowerSpectrumInfo *info, long mode)
{
	mrcImage inFFT;

	/* Determin if data need to be FFTd. */
	if(IsImage(inMrc, "in lmrcImageBandPassFilter", 0))
	{
		DEBUGPRINT("Image is in the real space.\n");
		lmrcImageFFT(&inFFT, inMrc ,0);
	}
	else
	{
		DEBUGPRINT("Image is in the Fourier space.\n");
		inFFT = *inMrc;
	}

	return lmrcImageFourierPowerSpectrumMakeSpectrum(&inFFT, info);
}

mrcImageFourierPowerSpectrum lmrcImageFourierPowerSpectrumMakeSpectrum(const mrcImage *inFFT, lmrcImageFourierPowerSpectrumInfo *info)
{
	mrcImageParaTypeInteger Nx, Ny, Nz, maxNx, maxNy, maxNz;
	double R, maxR;
	double Lx, Ly, Lz, dRx, dRy, dRz;
	Complex data;
	long i, theSection, *numberOfPointsAtR;
	mrcImageFourierPowerSpectrum theSpectrum;

	Lx = inFFT->HeaderLength.x * inFFT->HeaderN.x;
	Ly = inFFT->HeaderLength.y * inFFT->HeaderN.y;
	Lz = inFFT->HeaderLength.z * inFFT->HeaderN.z;
	if(Lx == 0) Lx = 1;
	if(Ly == 0) Ly = 1;
	if(Lz == 0) Lz = 1;
	dRx = 1 / Lx;
	dRy = 1 / Ly;
	dRz = 1 / Lz;
	maxNx = inFFT->HeaderN.x / 2.0;
	maxNy = inFFT->HeaderN.y / 2.0;
	maxNz = inFFT->HeaderN.z / 2.0;
	maxR = sqrt(dRx * dRx * maxNx * maxNx + dRy * dRy * maxNy * maxNy + dRz * dRz * maxNz * maxNz);
	theSpectrum.d = sqrt(info->dX * info->dX * dRx * dRx + info->dY * info->dY * dRy * dRy + info->dZ * info->dZ * dRz * dRz);
	theSpectrum.n = (int)floor(maxR / theSpectrum.d) + 1;
	DEBUGPRINT2("Number of sections: %ld, Section width: %g\n", theSpectrum.n, theSpectrum.d);
	theSpectrum.h = (double *)memoryAllocate(sizeof(double) * theSpectrum.n, "when theSpectrum.h");
	numberOfPointsAtR = (long *)memoryAllocate(sizeof(long) * theSpectrum.n, "when numberOfPointsAtR");
	if(theSpectrum.h == NULL || numberOfPointsAtR == NULL)
	{
		memoryFree(theSpectrum.h);
		memoryFree(numberOfPointsAtR);
		theSpectrum.h = NULL;
	}
	else
	{
		for(i = 0; i < theSpectrum.n; i++) theSpectrum.h[i] = numberOfPointsAtR[i] = 0;
		DEBUGPRINT3("# of sections %ld\t Max radius %g\t Delta x %g\n", theSpectrum.n, maxR, theSpectrum.d);
		for(Nz = -inFFT->HeaderN.z / 2.0; Nz < inFFT->HeaderN.z / 2.0; Nz += 1.0)
		{
			for(Ny = -inFFT->HeaderN.y / 2.0; Ny < inFFT->HeaderN.y / 2.0; Ny += 1.0)
			{
				for(Nx = 0; Nx <= inFFT->HeaderN.x / 2.0; Nx += 1.0)
				{
					mrcPixelDataGet(inFFT, Nx, Ny, Nz, &data.r, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(inFFT, Nx, Ny, Nz, &data.i, mrcPixelImPart, mrcPixelHowNearest);
					R = sqrt((Nx * dRx * Nx * dRx) + (Ny * dRy * Ny * dRy) + (Nz * dRz * Nz * dRz));
					theSection = (int)floor(R / theSpectrum.d);
					numberOfPointsAtR[theSection]++;
					theSpectrum.h[theSection] += sqrt(data.r * data.r + data.i * data.i);
				}
			}
		}	
		for(i = 0; i < theSpectrum.n; i++)
			if(numberOfPointsAtR[i])
				theSpectrum.h[i] /= (double)numberOfPointsAtR[i] * dRx * dRy * dRz;
		free(numberOfPointsAtR);
	}
	return theSpectrum;
}

void lmrcImageFourierPowerSpectrumDeleteSpectrum(mrcImageFourierPowerSpectrum theSpectrum)
{
	memoryFree(theSpectrum.h);
}
