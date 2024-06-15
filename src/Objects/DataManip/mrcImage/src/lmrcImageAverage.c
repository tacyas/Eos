/*
# lmrcImageAverage : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageAverage 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageAverage.h"

void
lmrcImageAverage(mrcImage* out, mrcImage* in, int n, int mode)
{
	int i;
	long num=0;

	for(i=0; i<n; i++) {
		lmrcImageAdd(out, &(in[i]), &num);
  	}
	if(num==n) {
   		lmrcImageDividedByReal(out, (double)num);
	} else {
		fprintf(stderr, "Something wrong: n %d != num %d\n", n, num);	
	}	
}

void
lmrcImageAverageOverThreshold(mrcImage* out, mrcImage* in, int n, float* cor, float thres, int mode)
{
	int i;
	long num=0;

	for(i=0; i<n; i++) {
		if(thres<cor[i]) {
			lmrcImageAdd(out, &(in[i]), &num);
		}
  	}
	if(num==n) {
   		lmrcImageDividedByReal(out, (double)num);
	} else {
		fprintf(stderr, "Something wrong: n %d != num %d\n", n, num);	
	}	
}

/*
	For Subtomogram averaging, with considering missing-wedge
*/
void
lmrcImageAverageWithWeight(mrcImage* out, mrcImage* outW, mrcImage* in, mrcImage* inW, int n, int mode)
{
	int i;
	mrcImage* tmpIn;
	mrcImage* tmpOut;
	mrcImageParaTypeReal x, y, z, X, Y, Z;
	double re, im, reOut, imOut, w, data;

	DEBUGPRINT("Start lmrcImageAverageWithWeight\n");
	/* Allocation */
	outW->Header = inW[0].Header;
	mrcInit(outW, NULL); /* All pixel data are zero */

	/* preTreatment: Fit Mode of Image to that of Weight */
	if(IsFT(&in[0], "in AverageWithWeight", 0)) {
		if(IsFT(&inW[0], "in AverageWithWeight", 0)) {
			/* 	in:  FT
				inW: FT */
			DEBUGPRINT("FTvsFT\n");
			tmpIn  = in;
			out->Header = in[0].Header;
			mrcInit(out, NULL);
			tmpOut = out; 
		} else {
			/* 	in:  FT
				inW: Image */
			DEBUGPRINT("FTvsImg\n");
			tmpIn = (mrcImage*)memoryAllocate(sizeof(mrcImage)*n, "in lmrcImageAverageWithWeight");
			for(i=0; i<n; i++) {
				lmrcImageFFT(&tmpIn[i], &in[i], 0);
			}
			tmpOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageAverageWithWeight"); 
			tmpOut->Header = in[0].Header;
			mrcInit(tmpOut, NULL);
			out->Header = in[0].Header;
		}
	} else {
		if(IsFT(&inW[0], "in AverageWithWeight", 0)) {
			/* 	in:  Image 
				inW: FT */
			DEBUGPRINT("ImgvsFT\n");
			tmpIn = (mrcImage*)memoryAllocate(sizeof(mrcImage)*n, "in lmrcImageAverageWithWeight");
			for(i=0; i<n; i++) {
				lmrcImageFFT(&tmpIn[i], &in[i], 0);
			}
			tmpOut = (mrcImage*)memoryAllocate(sizeof(mrcImage)*1, "in lmrcImageAverageWithWeight"); 
			tmpOut->Header = inW[0].Header;
			tmpOut->HeaderMode = mrcComplexFloatFT;	
			mrcInit(tmpOut, NULL);
		} else {
			/* 	in:  Image 
				inW: Image */
			DEBUGPRINT("Imgvs\n");
			tmpIn  = in;
			out->Header = in[0].Header;
			mrcInit(out, NULL); 
			tmpOut = out;
		}
	}

	/* Averaging */	
	if(IsFT(&tmpIn[0], "in AverageWithWeight", 0)) {
		DEBUGPRINT("Weight: FT\n");
		/* Sum */
		for(i=0; i<n; i++) {
			DEBUGPRINT4("%d %d %d %d\n", i, tmpIn[i].HeaderN.x, tmpIn[i].HeaderN.y, tmpIn[i].HeaderN.z);
			for(Z=-tmpIn[i].HeaderN.z/2.0; Z< tmpIn[i].HeaderN.z/2.0; Z++) {
			for(Y=-tmpIn[i].HeaderN.y/2.0; Y< tmpIn[i].HeaderN.y/2.0; Y++) {
			for(X=0;                       X<=tmpIn[i].HeaderN.x/2.0; X++) {
				mrcPixelDataGet(&tmpIn[i], X, Y, Z, &re,    mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&tmpIn[i], X, Y, Z, &im,    mrcPixelImPart, mrcPixelHowNearest);
				mrcPixelDataGet(&inW[i],   X, Y, Z, &w,     mrcPixelRePart, mrcPixelHowNearest);

				mrcPixelDataGet(tmpOut,    X, Y, Z, &reOut, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(tmpOut,    X, Y, Z, &imOut, mrcPixelImPart, mrcPixelHowNearest);
				mrcPixelDataGet(outW,      X, Y, Z, &data,  mrcPixelRePart, mrcPixelHowNearest);

			//	DEBUGPRINT6("%f %f %f %f %f %f\n", re, im, w, reOut, imOut, data);

				mrcPixelDataSet(tmpOut,    X, Y, Z, reOut+re*w, mrcPixelRePart);
				mrcPixelDataSet(tmpOut,    X, Y, Z, imOut+im*w, mrcPixelImPart);
				mrcPixelDataSet(outW,      X, Y, Z, data +w,    mrcPixelRePart);
			}
			}
			}
		}

		/* Average */ 
		DEBUGPRINT("Start Average");
		for(Z=-tmpOut->HeaderN.z/2.0; Z< tmpOut->HeaderN.z/2.0; Z++) {
		for(Y=-tmpOut->HeaderN.y/2.0; Y< tmpOut->HeaderN.y/2.0; Y++) {
		for(X=0;                      X<=tmpOut->HeaderN.x/2.0; X++) {
			mrcPixelDataGet(tmpOut,    X, Y, Z, &reOut, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpOut,    X, Y, Z, &imOut, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataGet(outW,      X, Y, Z, &w,     mrcPixelRePart, mrcPixelHowNearest);
			//DEBUGPRINT6("(%f,%f) w %f at (%f %f %f)\n", reOut, imOut, w, X, Y, Z);
			if(0<w) {
				mrcPixelDataSet(tmpOut,    X, Y, Z, reOut/w, mrcPixelRePart);
				mrcPixelDataSet(tmpOut,    X, Y, Z, imOut/w, mrcPixelImPart);
			} else {
				mrcPixelDataSet(tmpOut,    X, Y, Z, 0.0, mrcPixelRePart);
				mrcPixelDataSet(tmpOut,    X, Y, Z, 0.0, mrcPixelImPart);
			}
		}
		}
		}
		DEBUGPRINT("End Average");
	} else {
		DEBUGPRINT("Weight: Img\n");
		for(i=0; i<n; i++) {
			for(z=0; z< tmpIn[i].HeaderN.z; z++) {
			for(y=0; y< tmpIn[i].HeaderN.y; y++) {
			for(x=0; x< tmpIn[i].HeaderN.x; x++) {
				mrcPixelDataGet(&tmpIn[i], x, y, z, &re,    mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&inW[i],   x, y, z, &w,     mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(tmpOut,    x, y, z, &reOut, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(outW,      x, y, z, &data,  mrcPixelRePart, mrcPixelHowNearest);

				mrcPixelDataSet(tmpOut,    x, y, z, reOut+re*w, mrcPixelRePart);
				mrcPixelDataSet(outW,      x, y, z, data +w,    mrcPixelRePart);
			}
			}
			}
		}

		for(z=0; z< tmpOut->HeaderN.z; z++) {
		for(y=0; y< tmpOut->HeaderN.y; y++) {
		for(x=0; x< tmpOut->HeaderN.x; x++) {
			mrcPixelDataGet(outW,      x, y, z, &w,     mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpOut,    x, y, z, &reOut, mrcPixelRePart, mrcPixelHowNearest);
			if(0<w) {	
				mrcPixelDataSet(tmpOut, x, y, z, reOut/w, mrcPixelRePart);
			} else {
				mrcPixelDataSet(tmpOut, x, y, z, 0.0,     mrcPixelRePart);
			}
		}
		}
		}
	}

	/* Post Treatment */
	if(IsFT(&in[0], "in AverageWithWeight", 0)) {
		if(IsFT(&inW[0], "in AverageWithWeight", 0)) {
			/* 	in:  FT
				inW: FT */
		} else {
			/* 	in:  FT
				inW: Image */
			for(i=0; i<n; i++) {
				mrcImageFree(&tmpIn[i], 0);
			}
			memoryFree(tmpIn);	
			lmrcImageFFT(out, tmpOut, 0);
			mrcImageFree(tmpOut, 0);
			memoryFree(tmpOut);
		}
	} else {
		if(IsFT(&inW[0], "in AverageWithWeight", 0)) {
			/* 	in:  Image 
				inW: FT */
			DEBUGPRINT("Start FREE")
			for(i=0; i<n; i++) {
				mrcImageFree(&tmpIn[i], 0);
			}
			memoryFree(tmpIn);	
			DEBUGPRINT("Start FFT")
			DEBUGPRINT1("out->HeaderMode: %d\n", out->HeaderMode);
			DEBUGPRINT1("tmpOut->HeaderMode: %d\n", tmpOut->HeaderMode);
			lmrcImageFFT(out, tmpOut, 0);

			DEBUGPRINT("End FFT")
			mrcImageFree(tmpOut, 0);
			memoryFree(tmpOut);
		} else {
			/* 	in:  Image 
				inW: Image */
		}
	}
}
