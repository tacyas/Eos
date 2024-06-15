/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageLowPassFilter ver %I%
#%Z% Created by Sakane Isao
#%Z%
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageLowPassFilter ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"

typedef enum mrcImageLowPassFilterMode
{
	Step = 1,
	Cos,
	Exp,
	Gauss,
	Lorenz
} mrcImageLowPassFilterMode;

typedef struct { double r, i;} Complex;

#define PI M_PI
#define E M_E

extern void lmrcImageLowPassFilter(mrcImage *outMrc, mrcImage *inMrc, lmrcImageLowPassFilterInfo *info, long mode);

static void (*SetLowPassMethod(mrcImageLowPassFilterMode inMethod))(void);
static void doLowPass(mrcImage *inFFT, mrcImage *outFFT, lmrcImageLowPassFilterInfo *info);
static Complex LowPassByStep(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex LowPassByCos(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex LowPassByExp(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex LowPassByGauss(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static Complex LowPassByLorenz(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);
static void lmrcImageLowPassFilterAxisFix(mrcImage *ioFFT);

static Complex (*lmrcImageLowPassFilterImageTransformFunction)(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz);

void 
lmrcImageLowPassFilter(mrcImage *outMrc, mrcImage *inMrc, lmrcImageLowPassFilterInfo *info, long mode)
{
	long doFT = 0; /* A flag if the image have FFTd. */
	mrcImage inFFT, outFFT;

	if(0==inMrc->HeaderLength.z) {
		fprintf(stderr, "Length.z==0, then let Length.z=Length.x\n");
		inMrc->HeaderLength.z=inMrc->HeaderLength.x;
	}

	if(0==inMrc->HeaderLength.y) {
		fprintf(stderr, "Length.y==0, then let Length.z=Length.x\n");
		inMrc->HeaderLength.y=inMrc->HeaderLength.x;
	}

	DEBUGPRINT("lmrcImageLowPassFilter\n");
	/* Set the method how data will be processed. */
	
	if(SetLowPassMethod((mrcImageLowPassFilterMode)info->mode) == NULL) {
		fprintf(stderr, "\nNot Set LowPassFilter\n");
		exit(EXIT_FAILURE); /* Error! No method have selected. */
	}

	/* Determin if data need to be FFTd. */
	if(IsImage(inMrc, "in lmrcImageLowPassFilter", 0))	{
		doFT = 1;
		lmrcImageFFT(&inFFT, inMrc ,0);
		DEBUGPRINT("FFT");
	}else{
		doFT = 0;
		inFFT = *inMrc;
		DEBUGPRINT("NoFFT");
	}

	doLowPass(&inFFT, &outFFT, info);

	if(doFT){ 
		lmrcImageFFT(outMrc, &outFFT ,0);
	}
	
	else {
	*outMrc = outFFT;
	}
}

/*
	This function sets the method for the low pass filter.
*/
void (*SetLowPassMethod(mrcImageLowPassFilterMode inMethod))()
{
	switch(inMethod){
		case Step:
			lmrcImageLowPassFilterImageTransformFunction = &LowPassByStep;
			break;
		case Cos:
			lmrcImageLowPassFilterImageTransformFunction = &LowPassByCos;
			break;
		case Exp:
			lmrcImageLowPassFilterImageTransformFunction = &LowPassByExp;
			break;
		case Gauss:
			lmrcImageLowPassFilterImageTransformFunction = &LowPassByGauss;
			break;
		case Lorenz:
			lmrcImageLowPassFilterImageTransformFunction = &LowPassByLorenz;
			break;
		default:
			fprintf(stderr, "Not supported mode in lmrcImageLowPassFilter: %ld\n", (long)inMethod);
			lmrcImageLowPassFilterImageTransformFunction = NULL;
			break;
	}
	
	return (void (*)())lmrcImageLowPassFilterImageTransformFunction;
}

void 
doLowPass(mrcImage *inFFT, mrcImage *outFFT, lmrcImageLowPassFilterInfo *info)
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

	for(nz = -inFFT->HeaderN.z / 2.0; nz < inFFT->HeaderN.z / 2.0; nz += 1.0){
		for(ny = -inFFT->HeaderN.y / 2.0; ny < inFFT->HeaderN.y / 2.0; ny += 1.0){
			for(nx = 0; nx <= inFFT->HeaderN.x / 2.0; nx += 1.0){
				mrcPixelDataGet(inFFT, nx, ny, nz, &data.r, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(inFFT, nx, ny, nz, &data.i, mrcPixelImPart, mrcPixelHowNearest);
				//fprintf(stderr, "%d %d %d %f\n",nx,ny,nz, data.r);
				DEBUGPRINT3("%d %d %d \n",nx,ny,nz);
				data = lmrcImageLowPassFilterImageTransformFunction(info, data, Fx * nx, Fy * ny, Fz * nz);
				//fprintf(stderr, "%d %d %d %f\n",nx,ny,nz, data.r);
				mrcPixelDataSet(outFFT, nx, ny, nz, data.r, mrcPixelRePart);
				mrcPixelDataSet(outFFT, nx, ny, nz, data.i, mrcPixelImPart);
			}
		}
	}
	DEBUGPRINT("Axis");
/*	lmrcImageLowPassFilterAxisFix(outFFT); */
}

Complex 
LowPassByStep(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r2; 
	Complex zero;

	
	zero.r = zero.i = 0;
	
	r2 = kx * kx + ky * ky + kz * kz;
	
	return (r2 <= info->hvp * info->hvp ? data : zero);
}

Complex 
LowPassByCos(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);
	c = (1 - sin((r - info->hvp) * PI / info->width))/2.0;
	
	if(r < info->hvp - info->width / 2.0) {
		ret = data;
	} else {
		if(r < info->hvp + info->width / 2.0) {
			ret.r = data.r * c;
			ret.i = data.i * c;
		} else {
			ret.r = 0.0;
			ret.i = 0.0;
		}
	}
	return ret;
}

Complex 
LowPassByExp(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);
	/*c = exp(- r / info->hvp) * E / 2.0 ;*/
	c=pow(2 , -r / info->hvp);
	
	ret.r = data.r * c;
	ret.i = data.i * c;
	
	return ret;	
}

Complex 
LowPassByGauss(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);
	c=pow(2 , -(r * r) / (info->hvp * info->hvp));

	//fprintf(stderr, "r:%f (%f %f %f) w:%f hvp %f\n", r, kx, ky, kz, c, info->hvp);
	ret.r = data.r * c;
	ret.i = data.i * c;
	
	return ret;	
}

Complex 
LowPassByLorenz(lmrcImageLowPassFilterInfo *info, Complex data, mrcImageParaTypeReal kx, mrcImageParaTypeReal ky, mrcImageParaTypeReal kz)
{
	double r, c;
	Complex ret;
	
	r = sqrt(kx * kx + ky * ky + kz * kz);
	c=1 / (1 + ((r / info->hvp) * (r / info->hvp)));
	
	ret.r = data.r * c;
	ret.i = data.i * c;
	
	return ret;	
}

void 
lmrcImageLowPassFilterAxisFix(mrcImage *ioFFT)
{
	mrcImageParaTypeInteger ny, nz;
	Complex z, z1, z2;
	
	for(nz = -ioFFT->HeaderN.z / 2.0; nz <= ioFFT->HeaderN.z / 2.0; nz += 1.0){
		for(ny = 0.0; ny <= ioFFT->HeaderN.y / 2.0; ny += 1.0)	{
			mrcPixelDataGet(ioFFT, 0.0, ny, nz, &z1.r, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, -ny, -nz, &z1.i, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, ny, nz, &z2.r, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(ioFFT, 0.0, -ny, -nz, &z2.i, mrcPixelImPart, mrcPixelHowNearest);

			if(z1.r != z2.r || z1.i != -z2.i){
				z.r = (z1.r + z2.r) / 2.0;
				z.i = (z1.i - z2.i) / 2.0;
				mrcPixelDataSet(ioFFT, 0.0, ny, nz, z.r, mrcPixelRePart);
				mrcPixelDataSet(ioFFT, 0.0, ny, nz, z.i, mrcPixelImPart);
				mrcPixelDataSet(ioFFT, 0.0, -ny, -nz, z.r, mrcPixelRePart);
				mrcPixelDataSet(ioFFT, 0.0, -ny, -nz, -z.i, mrcPixelImPart);
			}
		}
	}
}
