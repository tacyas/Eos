/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageHighPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHighPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageHighPassFilter ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"

typedef enum mrcImageHighPassFilterMode
{
	Step = 1,
	Cos,
	Exp
} mrcImageHighPassFilterMode;

typedef struct { double r, i;} Complex;

#define PI M_PI
#define Log2 0.69314718055994529

extern void lmrcImageHighPassFilter(mrcImage *outMrc, mrcImage *inMrc, lmrcImageHighPassFilterInfo *info, long mode);

static void (*SetHighPassMethod(mrcImageHighPassFilterMode inMethod))(void);
static void doHighPass(mrcImage *inFFT, mrcImage *outFFT, lmrcImageHighPassFilterInfo *info);
static Complex HighPassByStep(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex HighPassByCos(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex HighPassByExp(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static void lmrcImageHighPassFilterAxisFix(mrcImage *ioFFT);

static Complex (*lmrcImageHighPassFilterImageTransformFunction)(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);

void lmrcImageHighPassFilter(mrcImage *outMrc, mrcImage *inMrc, lmrcImageHighPassFilterInfo *info, long mode)
{
	long doFT = 0; /* A flag if the image have FFTd. */
	mrcImage inFFT, outFFT;

	/* Set the method how data will be processed. */
	if(SetHighPassMethod((mrcImageHighPassFilterMode)info->mode) == NULL)
		exit(EXIT_FAILURE); /* Error! No method have selected. */
	
	/* Determin if data need to be FFTd. */
	if(IsImage(inMrc, "in lmrcImageHighPassFilter", 0))
	{
		doFT = 1;
		lmrcImageFFT(&inFFT, inMrc ,0);
	}
	else
	{
		doFT = 0;
		inFFT = *inMrc;
	}

	doHighPass(&inFFT, &outFFT, info);

	if(doFT) lmrcImageFFT(outMrc, &outFFT ,0);
	else *outMrc = outFFT;
}

/*
	This function sets the method for the low pass filter.
*/
void (*SetHighPassMethod(mrcImageHighPassFilterMode inMethod))()
{
	switch(inMethod)
	{
	case Step:
		lmrcImageHighPassFilterImageTransformFunction = &HighPassByStep;
		break;
	case Cos:
		lmrcImageHighPassFilterImageTransformFunction = &HighPassByCos;
		break;
	case Exp:
		lmrcImageHighPassFilterImageTransformFunction = &HighPassByExp;
		break;
	default:
		fprintf(stderr, "Not supported mode in lmrcImageHighPassFilter: %ld\n", (long)inMethod);
		lmrcImageHighPassFilterImageTransformFunction = NULL;
		break;
	}
	
	return (void (*)())lmrcImageHighPassFilterImageTransformFunction;
}

void doHighPass(mrcImage *inFFT, mrcImage *outFFT, lmrcImageHighPassFilterInfo *info)
{
	mrcImageParaTypeInteger nx, ny, nz;
	double Lx, Ly, Lz, Fx, Fy, Fz;
	Complex data;
	
	outFFT->Header = inFFT->Header;
	mrcInit(outFFT, NULL);
	Lx = inFFT->HeaderLength.x * inFFT->HeaderN.x;
	Ly = inFFT->HeaderLength.y * inFFT->HeaderN.y;
	Lz = inFFT->HeaderLength.z * inFFT->HeaderN.z;
	Fx = 1 / Lx;
	Fy = 1 / Ly;
	Fz = 1 / Lz;

	for(nz = -inFFT->HeaderN.z / 2.0; nz < inFFT->HeaderN.z / 2.0; nz += 1.0) {
		for(ny = -inFFT->HeaderN.y / 2.0; ny < inFFT->HeaderN.y / 2.0; ny += 1.0) {
			for(nx = 0; nx <= inFFT->HeaderN.x / 2.0; nx += 1.0) {
			      DEBUGPRINT3("%d %d %d  ",nx,ny,nz);
				mrcPixelDataGet(inFFT, nx, ny, nz, &data.r, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(inFFT, nx, ny, nz, &data.i, mrcPixelImPart, mrcPixelHowNearest);

				data = lmrcImageHighPassFilterImageTransformFunction(info, data, Fx * nx, Fy * ny, Fz * nz);

				mrcPixelDataSet(outFFT, nx, ny, nz, data.r, mrcPixelRePart);
				mrcPixelDataSet(outFFT, nx, ny, nz, data.i, mrcPixelImPart);
			}
		}
	}
	lmrcImageHighPassFilterAxisFix(outFFT);
}

Complex HighPassByStep(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r2; 
	Complex ret;
	
	r2 = kx * kx + ky * ky + kz * kz;
	
	if(r2 >= info->hvp * info->hvp) {
		ret.r = info->pathWindowHigh*data.r;
		ret.i = info->pathWindowHigh*data.i;
	} else {
		ret.r = info->pathWindowLow*data.r;
		ret.i = info->pathWindowLow*data.i;
	} 
	return ret;
}

Complex HighPassByCos(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);
	c = (0.5 + sin((r - info->hvp) * PI / info->width) * 0.5)*(info->pathWindowHigh - info->pathWindowLow) + info->pathWindowLow;
	
	if(r < info->hvp - info->width / 2.0)
	{
		ret.r = info->pathWindowLow;
		ret.i = info->pathWindowLow;
	}
	else
	{
		if(r < info->hvp + info->width / 2.0)
		{
			ret.r = data.r * c;
			ret.i = data.i * c;
		}
		else
		{
			ret.r = data.r*info->pathWindowHigh;
			ret.i = data.i*info->pathWindowHigh;
		}
	}
	return ret;
}

Complex HighPassByExp(lmrcImageHighPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);
	c = (1.0 - exp(- r * Log2 / info->hvp))*(info->pathWindowHigh - info->pathWindowLow) + info->pathWindowLow;
	
	ret.r = data.r * c;
	ret.i = data.i * c;
	
	return ret;	
}

void lmrcImageHighPassFilterAxisFix(mrcImage *ioFFT)
{
	mrcImageParaTypeInteger ny, nz;
	Complex z, z1, z2;
	
	for(nz = -ioFFT->HeaderN.z / 2.0; nz < ioFFT->HeaderN.z / 2.0; nz += 1.0) {
		for(ny = 0.0; ny < ioFFT->HeaderN.y / 2.0; ny += 1.0) {
			mrcPixelDataGet(ioFFT, 0.0,  ny,  nz, &z1.r, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0,  ny,  nz, &z1.i, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, -ny, -nz, &z2.r, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, -ny, -nz, &z2.i, mrcPixelImPart, mrcPixelHowNearest);

			if(z1.r != z2.r || z1.i != -z2.i) {
				z.r = (z1.r + z2.r) / 2.0;
				z.i = (z1.i - z2.i) / 2.0;
				mrcPixelDataSet(ioFFT, 0.0,  ny,  nz,  z.r, mrcPixelRePart);
				mrcPixelDataSet(ioFFT, 0.0,  ny,  nz,  z.i, mrcPixelImPart);
				mrcPixelDataSet(ioFFT, 0.0, -ny, -nz,  z.r, mrcPixelRePart);
				mrcPixelDataSet(ioFFT, 0.0, -ny, -nz, -z.i, mrcPixelImPart);
			}
		}
	}
}
