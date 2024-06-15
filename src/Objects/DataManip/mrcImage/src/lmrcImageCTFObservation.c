/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCTFObservation ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : void lmrcImageCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode)
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageCTFObservation ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "ctfInfo.h"

extern void __lmrcImageCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode);

void
lmrcImageCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode)
{
	mrcImage fft;
	mrcImage dstfft;

	if(mode&0x10) {
		if(IsImage(src, "in main", 0)) {
			lmrcImageFFT(&fft, src, 0);
		} else if(IsFT(src, "in main", 0)) {
			fft = *src;
		} else {
			fprintf(stderr, "Not supported mode : %ld\n", src->HeaderMode);
			exit(EXIT_FAILURE);
		}
	} else {
		fft = *src;
	}	

	switch(mode&0xf) {
		case 0: {
			__lmrcImageCTFObservation(&dstfft, &fft, ctf, mode&0xf);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageCTFObservation: %ld\n", mode&0xf);
			exit(EXIT_FAILURE);
		}
	}

	if(mode&0x10) {
		if(IsFT(&dstfft, "in main", 0)) {
			lmrcImageFFT(dst, &dstfft, 0);
		} else {
			fprintf(stderr, "Something wrong !! Programing Miss !!\n");
			exit(EXIT_FAILURE);
		}
	} else {
		*dst = dstfft;
	}
}

void
lmrcImagesCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode)
{
	int i;
	mrcImage section;
	mrcImage ctfImage;
	
	*dst = *src;
	mrcInit(dst, NULL);	
	if(0<src->numTailer) {
		mrcTailerCopy(dst, src, 1);  
	}
	for(i=0; i<src->HeaderN.z; i++) {
		mrcImageSectionGet(&section, src, i, 0);	
		lmrcImageCTFObservation(&ctfImage, &section, ctf, 0x10|mode);
		mrcImageSectionSet(dst, &ctfImage, i, 0); 
		mrcImageFree(&section, "");
		mrcImageFree(&ctfImage, "");
	}
}

void
__lmrcImageCTFObservation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long mode)
{
	double re, im, dstre, dstim;	
	double Weight, Win;
	float X, Y, R;
	float dX, dY;

	dst->Header = src->Header;
	mrcInit(dst, NULL);	
	dX = 1.0/(src->HeaderN.x*src->HeaderLength.x);
	dY = 1.0/(src->HeaderN.y*src->HeaderLength.y);

	for(Y=-dst->HeaderN.y/2; Y < dst->HeaderN.y/2; Y++) {
		for(X=0; X <= dst->HeaderN.x/2; X++) {
			R = sqrt(SQR(X*dX) + SQR(Y*dY));
			if(ctf->flagAstigmatism) {
				Weight = ctfFunction2D(ctf, X*dX, Y*dY, 0);
				DEBUGPRINT3("%f %f %f\n", X, Y, Weight);
			} else {
				Weight = ctfFunction(ctf, R, 0);
				DEBUGPRINT1("W: %f", Weight);
			}
			mrcPixelDataGet(src, X, Y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(src, X, Y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
			if(ctf->flagWin) {
				if(R<ctf->CutLow) {
					Win = 1.0;
				} else if(ctf->CutLow<R && R<ctf->CutHigh) {
					Win = (cos((R - ctf->CutLow)/(ctf->CutHigh - ctf->CutLow)*M_PI) + 1.0)/2.0;
				} else {
					Win = 0.0;
				}
			} else {
				Win = 1.0;
			}
			dstre = (re*Weight*Win);
			dstim = (im*Weight*Win);
			mrcPixelDataSet(dst, X, Y, 0.0, dstre, mrcPixelRePart);
			mrcPixelDataSet(dst, X, Y, 0.0, dstim, mrcPixelImPart);
#ifdef DEBUG
			if(R==0) {
				DEBUGPRINT3("W at R=0: %g dst: (%g, %g)\n", Weight, dstre, dstim);	
			}
#endif
		}
	}
}

