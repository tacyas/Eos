/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTExpression.c ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTExpression
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTExpression ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "lmrcFFTExpression.h"

void
lmrcFFTExpressionModePrint(FILE* fpt)
{
	fprintf(fpt, "----- FFT Expression MOde -----\n");
	fprintf(fpt, "0:Amplitude\n");
	fprintf(fpt, "1:LogAmplitude\n");
	fprintf(fpt, "2:Power\n");
	fprintf(fpt, "3:LogPower\n");
	fprintf(fpt, "4:Phase\n");
	fprintf(fpt, "5:Real\n");
}

void
lmrcFFTExpression(mrcImage* img, mrcImage* fft ,double th ,int mode) 
{
    img->Header = fft->Header;
    img->HeaderMode = mrcFloatImage;
    mrcInit(img, NULL);
    switch(mode) {
        case 0: {
            lmrcFFTAmplitude(img, fft);
            break;
        }
        case 1: {
            lmrcFFTLogAmplitude(img, fft ,th);
            break;
        }
        case 2: {
            lmrcFFTPower(img, fft);
            break;
        }
        case 3: {
            lmrcFFTLogPower(img, fft ,th);
            break;
        }
        case 4: {
            lmrcFFTPhase(img, fft);
            break;
        }
        case 5: {
	    lmrcFFTReal(img, fft);
	    break;
	}
        default: {
            fprintf(stderr, "Not Supported Mode: %d\n", mode);
            exit(EXIT_FAILURE);
        }
    }
	mrcStatDataSet(img, 0);
}

long
lmrcFFTExpressionOffset(mrcImage* fft)
{
	long offset;

	switch(fft->HeaderMode) {
		case mrcComplexFloatOneDimFT: {
			offset = fft->HeaderN.y/2;	
			break;
		}
		default: {
			offset = 0;
		}
	}
	return offset;
}

void
lmrcFFTAmplitude(mrcImage* img, mrcImage* fft)
{
    long ix, iy, iz, offset;
    double data, re, im;

	offset = lmrcFFTExpressionOffset(fft);
    for(iz=0; iz<img->HeaderN.z; iz++){
        for(iy=0; iy<img->HeaderN.y; iy++) {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &re, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &im, mrcPixelImPart, mrcPixelHowNearest);
                data = sqrt(re*re + im*im);
                mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, data, mrcPixelRePart);
            }
        }
    }
}

void 
lmrcFFTLogAmplitude(mrcImage* img, mrcImage* fft ,double th)
{
    long ix, iy, iz;
    double data, re, im;
	long offset;

	offset = lmrcFFTExpressionOffset(fft);
    for(iz=0; iz<img->HeaderN.z; iz++){
        for(iy=0; iy<img->HeaderN.y; iy++) {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &re, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &im, mrcPixelImPart, mrcPixelHowNearest);
                data = sqrt(re*re + im*im);
                if (data < th){
                    data = log10(th)/2.0;
                } else {
                    data = log10(data)/2.0;
                }
                mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, data, mrcPixelRePart);
            }
        }
    }
}

void 
lmrcFFTPower(mrcImage* img, mrcImage* fft)
{
    long ix, iy, iz;
    double data, re, im;
	long offset;

	offset = lmrcFFTExpressionOffset(fft);
    for(iz=0; iz<img->HeaderN.z; iz++){
        for(iy=0; iy<img->HeaderN.y; iy++) {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &re, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &im, mrcPixelImPart, mrcPixelHowNearest);
                data = re*re + im*im;
                mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, data, mrcPixelRePart);
            }
        }
    }
}

void 
lmrcFFTLogPower(mrcImage* img, mrcImage* fft ,double th)
{
    long ix, iy, iz;
    double data, re, im;
	long offset;

	offset = lmrcFFTExpressionOffset(fft);
    for(iz=0; iz<img->HeaderN.z; iz++){
        for(iy=0; iy<img->HeaderN.y; iy++) {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &re, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &im, mrcPixelImPart, mrcPixelHowNearest);
                data = re*re + im*im;
                if (data < th){
                    data = log10(th);
                } else {
                    data = log10(re*re + im*im);
                }
                mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, data, mrcPixelRePart);
            }
        }
    }
}
void 
lmrcFFTPhase(mrcImage* img, mrcImage* fft)
{
    long ix, iy, iz;
    double data, re, im;
	long offset;

	offset = lmrcFFTExpressionOffset(fft);
    for(iz=0; iz<img->HeaderN.z; iz++){
        for(iy=0; iy<img->HeaderN.y; iy++) {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &data, mrcPixelRePart, mrcPixelHowNearest);
                mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, data, mrcPixelRePart);
            }
        }
    }
}

void
lmrcFFTReal(mrcImage* img, mrcImage* fft)
{
    long ix, iy, iz;
    double data, re, im;
	long offset;

	offset = lmrcFFTExpressionOffset(fft);
    for(iz=0; iz<img->HeaderN.z; iz++){
        for(iy=0; iy<img->HeaderN.y; iy++) {
            for(ix=0; ix<img->HeaderN.x; ix++) {
                mrcPixelDataGet(fft, (mrcImageParaTypeReal)ix-img->HeaderN.x/2, (mrcImageParaTypeReal)iy-img->HeaderN.y/2+offset, (mrcImageParaTypeReal)iz-img->HeaderN.z/2, &re, mrcPixelRePart, mrcPixelHowNearest);
                data = re;
                mrcPixelDataSet(img, (mrcImageParaTypeReal)ix, (mrcImageParaTypeReal)iy, (mrcImageParaTypeReal)iz, data, mrcPixelRePart);
            }
        }
    }
}

