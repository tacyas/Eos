/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImagePattersonFunctionCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImagePattersonFunctionCalc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImagePattersonFunctionCalc ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "Memory.h"

void
lmrcImagePattersonFunctionCalc(mrcImage* out, mrcImage* outfft, mrcImage* in)
{
	mrcImage fft;
	mrcImage powfft;
	mrcImageParaTypeReal X, Y, Z;
	double pow;

    DEBUGPRINT("lmrcImagePattersonFunctionCalc");
	lmrcImageFFT(&fft, in, 0);
    powfft.Header = fft.Header;
    mrcInit(&powfft, NULL);

	for(Z=-fft.HeaderN.z/2.0; Z<  fft.HeaderN.z/2.0; Z++) {	
	for(Y=-fft.HeaderN.y/2.0; Y<  fft.HeaderN.y/2.0; Y++) {	
	for(X=0;                  X<= fft.HeaderN.x/2.0; X++) {	
		mrcPixelDataGet(&fft, X, Y, Z, &pow, mrcPixelPow,    mrcPixelHowNearest);
		mrcPixelDataSet(&powfft, X, Y, Z, pow,  mrcPixelRePart);
		mrcPixelDataSet(&powfft, X, Y, Z, 0,    mrcPixelImPart);
	}
	}
	}
	lmrcImageFFT(out, &powfft, 0);	
	mrcImageFree(&fft, "in lmrcImagePattersonFunction\n");
    *outfft = powfft;
}

void
lmrcImagePattersonFunctionPrint(FILE* fpt, mrcImage* pat, int mode)
{
	int x, y, z, ir;
	double data;
    double r;
    double* patData;
    int* patDataCount;

    patData = memoryAllocate(sizeof(double)*(pat->HeaderN.x/2+1), "in ");
    patDataCount = memoryAllocate(sizeof(int)*(pat->HeaderN.x/2+1), "in ");

    for(ir=0; ir<pat->HeaderN.x/2; ir++) {
		patData[ir] = 0;
        patDataCount[ir] = 0;
    }

	for(z=0; z<pat->HeaderN.z; z++) {
	for(y=0; y<pat->HeaderN.y; y++) {
	for(x=0; x<pat->HeaderN.x; x++) {
        mrcPixelDataGet(pat, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        r = sqrt(SQR(MIN(x,pat->HeaderN.x-x-1))+SQR(MIN(y,pat->HeaderN.y-y-1))+SQR(MIN(z,pat->HeaderN.z-z-1)));
        ir = MIN((int)(r+0.5), pat->HeaderN.x/2);
        patData[ir] += data; 
        patDataCount[ir]++; 
    }
    }
    }

    for(ir=0; ir<pat->HeaderN.x/2; ir++) {
        if(0<patDataCount[ir]) {
    		fprintf(fpt, "%d %f %f %d\n", ir, ir*pat->HeaderLength.x, patData[ir]/patDataCount[ir], patDataCount[ir]);
        } else {
    		fprintf(fpt, "%d %f %f %d\n", ir, ir*pat->HeaderLength.x, patData[ir], patDataCount[ir]);
        }
    }
}

void
lmrcImageGuinierFunctionPrint(FILE* fpt, mrcImage* guinier, int mode)
{
	int x, y, z, ir;
	double data;
    double r;
    double* guinierData;
    int* guinierDataCount;

    guinierData = memoryAllocate(sizeof(double)*(guinier->HeaderN.x/2+1), "in ");
    guinierDataCount = memoryAllocate(sizeof(int)*(guinier->HeaderN.x/2+1), "in ");

    for(ir=0; ir<guinier->HeaderN.x/2; ir++) {
		guinierData[ir] = 0;
        guinierDataCount[ir] = 0;
    }

	for(z=-guinier->HeaderN.z/2.0; z<guinier->HeaderN.z/2.0; z++) {
	for(y=-guinier->HeaderN.y/2.0; y<guinier->HeaderN.y/2.0; y++) {
	for(x=-guinier->HeaderN.x/2.0; x<guinier->HeaderN.x/2.0; x++) {
        mrcPixelDataGet(guinier, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        r = sqrt(SQR(x/(double)guinier->HeaderN.x)+SQR(y/(double)guinier->HeaderN.y)+SQR(z/(double)guinier->HeaderN.z))*guinier->HeaderN.x;
        ir = MIN((int)(r+0.5), guinier->HeaderN.x/2);
        guinierData[ir] += data; 
        guinierDataCount[ir]++; 
    }
    }
    }

    for(ir=0; ir<guinier->HeaderN.x/2; ir++) {
        if(0<guinierDataCount[ir]) {
    		fprintf(fpt, "%d %f %f %f %d\n", ir, ir/(guinier->HeaderN.x*guinier->HeaderLength.x), SQR(ir/(guinier->HeaderN.x*guinier->HeaderLength.x)), guinierData[ir]/guinierDataCount[ir], guinierDataCount[ir]);
        } else {
    		fprintf(fpt, "%d %f %f %f %d\n", ir, ir/(guinier->HeaderN.x*guinier->HeaderLength.x), SQR(ir/(guinier->HeaderN.x*guinier->HeaderLength.x)), guinierData[ir], guinierDataCount[ir]);
        }
    }
}

