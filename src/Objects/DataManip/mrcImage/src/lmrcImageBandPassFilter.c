/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageBandPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageBandPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageBandPassFilter ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"

typedef enum mrcImageBandPassFilterMode
{
	Step = 1,
	Cos,
	Exp
} mrcImageBandPassFilterMode;

typedef struct { double r, i;} Complex;

#define PI M_PI
#define Log2 0.69314718055994529

extern void lmrcImageBandPassFilter(mrcImage *outMrc, mrcImage *inMrc, lmrcImageBandPassFilterInfo *info, long mode);

static void (*SetBandPassMethod(mrcImageBandPassFilterMode inMethod))(void);
static void doBandPass(mrcImage *inFFT, mrcImage *outFFT, lmrcImageBandPassFilterInfo *info);
static Complex BandPassByStep(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex BandPassByCos(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex BandPassByExp(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static void lmrcImageBandPassFilterAxisFix(mrcImage *ioFFT);

static Complex (*lmrcImageBandPassFilterImageTransformFunction)(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);

void lmrcImageBandPassFilter(mrcImage *outMrc, mrcImage *inMrc, lmrcImageBandPassFilterInfo *info, long mode)
{
	long doFT = 0; /* A flag if the image have FFTd. */
	mrcImage inFFT, outFFT;

	/* Set the method how data will be processed. */
	if(SetBandPassMethod((mrcImageBandPassFilterMode)info->mode) == NULL)
		exit(EXIT_FAILURE); /* Error! No method have selected. */
	
	/* Determin if data need to be FFTd. */
	if(IsImage(inMrc, "in lmrcImageBandPassFilter", 0))
	{
		doFT = 1;
		lmrcImageFFT(&inFFT, inMrc ,0);
	}
	else
	{
		doFT = 0;
		inFFT = *inMrc;
	}

	doBandPass(&inFFT, &outFFT, info);

	if(doFT) lmrcImageFFT(outMrc, &outFFT ,0);
	else *outMrc = outFFT;
}

/*
	This function sets the method for the low pass filter.
*/
void (*SetBandPassMethod(mrcImageBandPassFilterMode inMethod))()
{
	switch(inMethod)
	{
	case Step:
		lmrcImageBandPassFilterImageTransformFunction = &BandPassByStep;
		break;
	case Cos:
		lmrcImageBandPassFilterImageTransformFunction = &BandPassByCos;
		break;
	case Exp:
		lmrcImageBandPassFilterImageTransformFunction = &BandPassByExp;
		break;
	default:
		fprintf(stderr, "Not supported mode in lmrcImageBandPassFilter: %ld\n", (long)inMethod);
		lmrcImageBandPassFilterImageTransformFunction = NULL;
		break;
	}
	
	return (void (*)())lmrcImageBandPassFilterImageTransformFunction;
}

void doBandPass(mrcImage *inFFT, mrcImage *outFFT, lmrcImageBandPassFilterInfo *info)
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
				mrcPixelDataGet(inFFT, nx, ny, nz, &data.r, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(inFFT, nx, ny, nz, &data.i, mrcPixelImPart, mrcPixelHowNearest);

				data = lmrcImageBandPassFilterImageTransformFunction(info, data, Fx * nx, Fy * ny, Fz * nz);

				mrcPixelDataSet(outFFT, nx, ny, nz, data.r, mrcPixelRePart);
				mrcPixelDataSet(outFFT, nx, ny, nz, data.i, mrcPixelImPart);
			}
		}
	}
	lmrcImageBandPassFilterAxisFix(outFFT);
}

Complex BandPassByStep(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r2; 
	Complex zero;


	zero.r = zero.i = 0.0;
	
	r2 = kx * kx + ky * ky + kz * kz;

	if(info->flagLowWeight) {
		if(r2< info->hvl*info->hvl) { 
			data.r *= info->lowWeight;
			data.i *= info->lowWeight;
		} else if(info->hvh*info->hvh < r2) {
			data = zero;
		}
		return data;
	} else {
		return (info->hvl * info->hvl <= r2 && r2 <= info->hvh * info->hvh ? data : zero);
	}
}

Complex BandPassByCos(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, cl, ch;
	Complex ret, zero;
	
	zero.r = zero.i = 0.0;
	r = sqrt(kx * kx + ky * ky + kz * kz);
	if(info->flagLowWeight) {
		cl = (1 + sin((r - info->hvl)*PI/info->wl))*0.5*(1-info->lowWeight) + info->lowWeight;
	} else {
		cl = (1 + sin((r - info->hvl)*PI/info->wl))*0.5;
	}
	ch = 0.5 - sin((r - info->hvh) * PI / info->wh) * 0.5;
	
	if(r < info->hvl + info->wl / 2.0) {
		if(r < info->hvl - info->wl / 2.0) {
			if(info->flagLowWeight) {
				ret.r = data.r*info->lowWeight;
				ret.i = data.i*info->lowWeight;
			} else {
				ret = zero;
			}
		} else {
			ret.r = data.r * cl;
			ret.i = data.i * cl;
		}
	} else {
		if(info->hvh - info->wh / 2.0 < r) {
			if(info->hvh + info->wh / 2.0 < r) {
				ret = zero;
			} else {
				ret.r = data.r * ch;
				ret.i = data.i * cl;
			}
		} else {
			ret = data;
		}
	}
	return ret;
}

Complex BandPassByExp(lmrcImageBandPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);

	if(r < info->hvl + info->wl) {
		if(info->flagLowWeight) {
			c = exp((r - info->hvl - info->wl) * Log2 / info->wl)*(1-info->lowWeight) + info->lowWeight;
		} else {
			c = exp((r - info->hvl - info->wl) * Log2 / info->wl);
		}
	} else if(info->hvh - info->wh < r) {
			/* Bug fixed:           - replaced to + by tacyas */
			c = exp(-(r - info->hvh + info->wh) * Log2 / info->wh);
	} else {
		c = 1;
	}
	
	ret.r = data.r * c;
	ret.i = data.i * c;
	
	return ret;	
}

void lmrcImageBandPassFilterAxisFix(mrcImage *ioFFT)
{
	mrcImageParaTypeInteger ny, nz;
	Complex z, z1, z2;
	
	for(nz = -ioFFT->HeaderN.z / 2.0; nz < ioFFT->HeaderN.z / 2.0; nz += 1.0) {
		for(ny = 0.0; ny <= ioFFT->HeaderN.y / 2.0; ny += 1.0) {
			mrcPixelDataGet(ioFFT, 0.0,  ny,  nz, &z1. r, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, -ny, -nz, &z1. i, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0,  ny,  nz, &z2. r, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, -ny, -nz, &z2. i, mrcPixelImPart, mrcPixelHowNearest);

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
