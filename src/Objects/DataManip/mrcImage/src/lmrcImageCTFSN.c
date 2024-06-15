/*
# lmrcImageCTFSN.c  1.3
# The latest update : 07/02/96 at 14:13:15
#
#@(#) lmrcImageCTFSN ver 1.3
#@(#) Created by Sakane Isao
#@(#)
#@(#) Usage : mrcImageCTFSN
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrcImageCTFSN ver1.3; Date:96/07/02 @(#)";
#include <stdio.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "ctfInfo.h"
#include "Memory.h"

#define PI M_PI

/* y = a + bx */
typedef struct { float a, b;} Line;
typedef struct { double r, i;} Complex;
typedef struct
{
	long n;
	double d, *h;
} Histogram;

extern void lmrcImageCTFSN(mrcImage *outMrc, const mrcImage *inMrc, lmrcImageCTFSNInfo *info, long mode);
static void getSN(const mrcImage *inFFT, mrcImage *outFFT, lmrcImageCTFSNInfo *info);
static Histogram makeHistogram(const mrcImage *inFFT);
static Line fitExp(Histogram inHist, lmrcImageCTFSNInfo *info);
static void setSN(const mrcImage *inFFT, mrcImage *outFFT, Histogram inHist, Line inLine);
static void deleteHistogram(Histogram theHist);
static long ctfZeroPointNumberAtR(ctfInfo *info, float R, long mode);
static float ctfZeroPoint(ctfInfo *info, long n, long mode);

void lmrcImageCTFSN(mrcImage *outMrc, const mrcImage *inMrc, lmrcImageCTFSNInfo *info, long mode)
{
	long doFT = 0; /* A flag if the image have FFTd. */
	mrcImage inFFT, outFFT;

	/* Determin if data need to be FFTd. */
	if(IsImage(inMrc, "in lmrcImageBandPassFilter", 0))
	{
		DEBUGPRINT("Image is in the real space.\n");
		doFT = 1;
		// lfft2d(&inFFT, inMrc);
		lmrcImageFFT(&inFFT, inMrc, 0);
	}
	else
	{
		DEBUGPRINT("Image is in the Fourier space.\n");
		doFT = 0;
		inFFT = *inMrc;
	}

	DEBUGPRINT("Copy the header.\n");
	outFFT.Header = inFFT.Header;
	DEBUGPRINT("MRC Init.\n");
	mrcInit(&outFFT, NULL);

	getSN(&inFFT, &outFFT, info);

	if(doFT) {
		//lfft2d(outMrc, &outFFT);
		lmrcImageFFT(outMrc, &outFFT, 0);
	}
	else *outMrc = outFFT;
}

void getSN(const mrcImage *inFFT, mrcImage *outFFT, lmrcImageCTFSNInfo *info)
{
	Histogram theHist;
	Line theLine;

	DEBUGPRINT("Make Histogram.\n");
	theHist = makeHistogram(inFFT);
	if(theHist.h == NULL) exit(EXIT_FAILURE);
	DEBUGPRINT("Fit line by least square method.\n");
	theLine = fitExp(theHist, info);
	DEBUGPRINT("Write out the solution.\n");
	setSN(inFFT, outFFT, theHist, theLine);
	DEBUGPRINT("Delete Histogram.\n");
	deleteHistogram(theHist);
}

Histogram makeHistogram(const mrcImage *inFFT)
{
	mrcImageParaTypeInteger nx, ny, nz, maxNx, maxNy, maxNz;
	double R, maxR;
	double Lx, Ly, Lz, dRx, dRy, dRz;
	Complex data;
	long i, theSection, *numberOfPointsAtR;
	Histogram theHist;

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
	theHist.n = (int)floor(maxR / dRx) + 1;
	theHist.d = dRx;
	theHist.h = (double *)memoryAllocate(sizeof(double) * theHist.n, "in makeHistogram, theHist.h");
	numberOfPointsAtR = (long *)memoryAllocate(sizeof(long) * theHist.n, "in makeHistogram numberOfPointsAtR");
	if(theHist.h == NULL || numberOfPointsAtR == NULL)
	{
		free(theHist.h);
		free(numberOfPointsAtR);
		theHist.h = NULL;
	}
	else
	{
		for(i = 0; i < theHist.n; i++) theHist.h[i] = numberOfPointsAtR[i] = 0;

		DEBUGPRINT3("# of sections %ld\t Max radius %g\t Delta x %g\n", theHist.n, maxR, theHist.d);
		for(nz = -inFFT->HeaderN.z / 2.0; nz < inFFT->HeaderN.z / 2.0; nz += 1.0)
		{
			for(ny = -inFFT->HeaderN.y / 2.0; ny < inFFT->HeaderN.y / 2.0; ny += 1.0)
			{
				for(nx = 0; nx <= inFFT->HeaderN.x / 2.0; nx += 1.0)
				{
					mrcPixelDataGet(inFFT, nx, ny, nz, &data.r, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(inFFT, nx, ny, nz, &data.i, mrcPixelImPart, mrcPixelHowNearest);
					R = sqrt((nx * dRx * nx * dRx) + (ny * dRy * ny * dRy) + (nz * dRz * nz * dRz));
					theSection = (int)floor(R / theHist.d);
					numberOfPointsAtR[theSection]++;
					theHist.h[theSection] += sqrt(data.r * data.r + data.i * data.i);
				}
			}
		}	
		for(i = 0; i < theHist.n; i++)
			theHist.h[i] /= (double)numberOfPointsAtR[i] * dRx * dRy * dRz;

		free(numberOfPointsAtR);
	}

#ifdef DEBUG
	{
		FILE *fp;
		fp = fopen("lmrcImageCTFSNHistogram.dat", "w");
		if(fp != NULL)
			for(i = 0; i < theHist.n; i++) fprintf(fp, "%ld\t%g\t%g\n", i, i * dRx, theHist.h[i]);
		fclose(fp);
	}
#endif

	return theHist;
}

Line fitExp(Histogram inHist, lmrcImageCTFSNInfo *info)
{
	Line theLine;
	double N = 0, Xi = 0, Yi = 0, Xi2 = 0, XiYi = 0, det;
	long i, minDeg, maxDeg;
#ifdef DEBUG
	FILE *fp;
#endif

	/* Test for all points where CTF function is zero. */
	minDeg = MAX(0, info->deg1);
	maxDeg = MIN(ctfZeroPointNumberAtR(&(info->ctf), inHist.n * inHist.d, info->mode), info->deg2);
	DEBUGPRINT2("ZeroPointDegree : %ld to %ld\n", minDeg, maxDeg);
	for(i = minDeg; i <= maxDeg; i++)
	{
		double R, X, Y;
		R = ctfZeroPoint(&(info->ctf), i, info->mode);
		X = R / inHist.d;
		Y = log(inHist.h[(int)floor(X)]);
		N += 1.0;
		Xi += X;
		Yi += Y;
		Xi2 += X * X;
		XiYi += X * Y;
	}

	/* Fit the line with the least square method. */
	if(N >= 2.0)
	{
		det = N * Xi2 - Xi * Xi;
		theLine.a = (Xi2 * Yi - Xi * XiYi) / det;
		theLine.b = (-Xi * Yi +  N * XiYi) / det / inHist.d;
	}
	else
		theLine.a = theLine.b = 0.0;
#ifdef DEBUG
	fp = fopen("lmrcImageCTFSNZeroPoint.dat", "w");
	if(fp != NULL)
		for(i = minDeg; i <= maxDeg; i++) fprintf(fp, "%g\t%g\n", ctfZeroPoint(&(info->ctf), i, info->mode), exp(theLine.a + theLine.b * ctfZeroPoint(&(info->ctf), i, info->mode)));
	fclose(fp);
#endif

	/* Assert that value at the point where CTF function is zero is over the line. */
	for(i = minDeg; i <= maxDeg; i++)
	{
		double R, X, Y, dY;

		R = ctfZeroPoint(&(info->ctf), i, info->mode);
		X = R / inHist.d;
		Y = log(inHist.h[(int)floor(X)]);
		dY = theLine.a + theLine.b * R - Y;
		if(dY > 0.0) theLine.a -= dY;
	}

	DEBUGPRINT2("The line fitted to y = %g + %g x\n", theLine.a, theLine.b);
	return theLine;
}

void setSN(const mrcImage *inFFT, mrcImage *outFFT, Histogram inHist, Line inLine)
{
	mrcImageParaTypeInteger nx, ny, nz;
	double Lx, Ly, Lz, dRx, dRy, dRz, A, B;

	Lx = inFFT->HeaderLength.x * inFFT->HeaderN.x;
	Ly = inFFT->HeaderLength.y * inFFT->HeaderN.y;
	Lz = inFFT->HeaderLength.z * inFFT->HeaderN.z;
	if(Lx == 0) Lx = 1;
	if(Ly == 0) Ly = 1;
	if(Lz == 0) Lz = 1;
	dRx = 1 / Lx;
	dRy = 1 / Ly;
	dRz = 1 / Lz;
	A = exp(inLine.a);
	B = exp(inLine.b * inHist.d);

	for(nz = -outFFT->HeaderN.z / 2.0; nz < outFFT->HeaderN.z / 2.0; nz += 1.0)
	{
		for(ny = -outFFT->HeaderN.y / 2.0; ny < outFFT->HeaderN.y / 2.0; ny += 1.0)
		{
			DEBUGPRINT1("Ny = %ld\t", ny);
			for(nx = 0; nx <= outFFT->HeaderN.x / 2.0; nx += 1.0)
			{
				double R, theSN;
				long n;

				R = sqrt((nx * dRx * nx * dRx) + (ny * dRy * ny * dRy) + (nz * dRz * nz * dRz));
				n = floor(R / inHist.d);
				theSN = inHist.h[n] / (A * pow(B, (double)n)) - 1.0;
				mrcPixelDataSet(outFFT, nx, ny, nz, theSN, mrcPixelRePart);
				mrcPixelDataSet(outFFT, nx, ny, nz, 0.0, mrcPixelImPart);
			}
		}
	}
}

void deleteHistogram(Histogram theHist)
{
	memoryFree(theHist.h);
}

float ctfZeroPoint(ctfInfo *info, long n, long mode)
{
	/* All length should mesured in angstrome */
	float R = 0, df, l, cs;
	float a, s;

	l = wavelengthOfElectron(info->kV * 1000.0) * 1e10;
	cs =  info->Cs * 1e7;
	df = info->defocus;

	switch(mode)
	{
	case ctfInfoModePhaseCTFOnly:
		if(df > 0)
			R = sqrt((df - sqrt(df * df - 2.0 * cs * l * n)) / (cs * l * l));
		else
			R = sqrt((df + sqrt(df * df + 2.0 * cs * l * n)) / (cs * l * l));
		break;
	case ctfInfoModePhaseAndAmpCTF:
		a = info->ratioOfAmpToPhase;
		s = atan(a);
		if(df >0)
			R = sqrt((df - sqrt(df * df - 2.0 * cs * l * (n - s / PI + 1.0))) / (cs * l * l));
		else
			R = sqrt((df + sqrt(df * df + 2.0 * cs * l * (n - s / PI + 1.0))) / (cs * l * l));
		break;
	}
	DEBUGPRINT2("Zero point of Degree %ld is %g\n", n, R);
	return R;
}

long ctfZeroPointNumberAtR(ctfInfo *info, float R, long mode)
{
	/* All length should mesured in angstrome */
	float n = 0;
	float df, l, cs;
	float a, s;

	l = wavelengthOfElectron(info->kV * 1000.0) * 1e10;
	cs =  info->Cs * 1e7;
	df = info->defocus;

	switch(mode)
	{
	case ctfInfoModePhaseCTFOnly:
		n = (df - cs * l * l * R * R * 0.5) * l * R * R;
		break;
	case ctfInfoModePhaseAndAmpCTF:
		a = info->ratioOfAmpToPhase;
		s = atan(a);
		n = (df - cs * l * l * R * R * 0.5) * l * R * R + s / PI - 1.0;
		break;
	}
	DEBUGPRINT2("ctfZeroPointNumberAtR %g is %g\n", R, n);
	return floor(n);
}
