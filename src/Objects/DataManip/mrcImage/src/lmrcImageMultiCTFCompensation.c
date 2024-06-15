/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMultiCTFCompensation ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : void lmrcImageMultiCTFCompensation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, long mode)
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageMultiCTFCompensation ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "ctfInfo.h"
#include "./lmrcImageCTFCompensation.h"

extern void __lmrcImageMultiCTFCompensationMode0(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode);
extern void __lmrcImageMultiCTFCompensationMode1(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode);

void
lmrcImageMultiCTFCompensation(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode)
{
	DEBUGPRINT("lmrcImageMultiCTFCompensation Start\n"); 
	fprintf(stderr, "lmrcImageMultiCTFCompensation Start: %ld\n", mode);fflush(stderr);
	switch(mode&0xf) {
		case 0: {
			__lmrcImageMultiCTFCompensationMode0(dst, src, ctf, nfile, info, mode);
			break;
		}
		case 1: {
			__lmrcImageMultiCTFCompensationMode1(dst, src, ctf, nfile, info, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageMultiCTFCompensation: %ld\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void
lmrcImageMultiCTFCompensationUsage(FILE* fpt)
{
	fprintf(fpt, "mode: 0  : CTF-weighted compensation, CTF/(SQR(CTF) + (NS)^2)\n");
	fprintf(fpt, "mode: +1 : Adding solvent-flattening process\n");
	fprintf(fpt, "mode: +16: Without phase flipping, in case of images after phase only correction.\n ");
}

void
__lmrcImageMultiCTFCompensationMode1(mrcImage* dstfft, /* Fourier transform of CTF-corrected image */ 
									 mrcImage* srcfft, /* Fourier transforms of observed images */
									 ctfInfo* ctf,     /* CTFs of observed images */
									 long nfile,       /* Number of observed images */
									 lmrcImageMultiCTFCompensationInfo info,
									 long mode)
{
	long i;
	mrcImage* predict;                         /* Predicted observed images */
	mrcImage* predictfft;                      /* Fourier transforms of predicted observed images */
	mrcImage* deltasrc;                        
	mrcImage* deltasrcfft;                     
	mrcImage  deltadstfft;
	mrcImage  deltadst;
	mrcImage* src;                             /* Observed images */
	mrcImage  dst;                             /* CTF-coorected image */ 
	mrcImage  mindst;                          /* CTF-coorected image (minimum)*/ 
	mrcImageParaTypeReal x, y, z;
	double rms, minrms;
	double okrms, diversefactor = 10;
	double data, delta, tmppredict, tmpsrc;
	long   iteration, maxiteration;	
	double* hist;
	double maxhist, maxhistdens;
	long    nhist;

	DEBUGPRINT("lmrcImageMultiCTFCompensationMode1 Start\n");

	maxiteration = info.maxiteration;
	okrms         = info.okrms;
	diversefactor = info.diversefactor;
	z = info.z;
	nhist = info.nhist;

	predictfft = (mrcImage*)memoryAllocate(sizeof(mrcImage)*nfile, "in __lmrcImageMultiCTFCompensation");
	predict    = (mrcImage*)memoryAllocate(sizeof(mrcImage)*nfile, "in __lmrcImageMultiCTFCompensation");
	src        = (mrcImage*)memoryAllocate(sizeof(mrcImage)*nfile, "in __lmrcImageMultiCTFCompensation");

	deltasrcfft = predictfft;
	deltasrc    = predict;

	/* Create the observed images */ 
	for(i=0; i<nfile; i++) {
		DEBUGPRINT1("Create the observed image[%ld]\n", i);
		/* lfft2d(&(src[i]), &(srcfft[i])); */
		lmrcImageFFT(&(src[i]), &(srcfft[i]), 0);
	}

	/* Create the fisrt CTF-corrected image and its Fourier transform */
	DEBUGPRINT("Create the first CTF-corrected image on Fourier space\n");
	__lmrcImageMultiCTFCompensationMode0(dstfft, srcfft, ctf, nfile, info, mode);
	for(i=0; i<nfile; i++) {
		mrcImageFree(&(srcfft[i]), "in __mrcImageMultiCTFCompensation");
	}

	DEBUGPRINT("Create the first CTF-corrected image on real space\n");
	/* lfft2d(&dst, dstfft); */
	lmrcImageFFT(&dst, dstfft, 0);
	mrcImageFree(dstfft, "in __lmrcImageMultiModeCTFCompensation");

	rms = minrms = 1e6;
	iteration = 0;
	mindst.Image = NULL;
	do {
		DEBUGPRINT1("#Iter: %10ld Start\n", iteration);
		switch(info.solventMode) {
			case lmrcImageMultiCTFCompensationSolventFlatteningModeDensityPeakIsSolvent: {

			/* non-linear filtering : solvent flattening : mode of density is density of solvent*/
			/*                                             density in the defined solvent area is density of solvent*/
				mrcStatDataSet(&dst, 0);
				lmrcImageHistgram(&hist, nhist, &dst); 
				maxhist     = 0.0;
				maxhistdens = 0;
				for(i=0; i<nhist; i++) {
					if(maxhist<hist[i]) {
						maxhist     = hist[i];
						maxhistdens = i;
					}
				}
				free(hist);
				maxhistdens = maxhistdens/(nhist-1)*(dst.HeaderAMax - dst.HeaderAMin) + dst.HeaderAMin;
				for(x=0; x<dst.HeaderN.x; x++) {
					for(y=0; y<dst.HeaderN.y; y++) {
						mrcPixelDataGet(&dst, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest); 
						if(data<maxhistdens) {
							mrcPixelDataSet(&dst, x, y, z, (double)maxhistdens, mrcPixelMag);
						}
					}
				}
				break;
			}
			case lmrcImageMultiCTFCompensationSolventFlatteningModeDefinedSTDIsSolvent: {
				mrcImageInformation imageInfo;
				double threshold; 

				imageInfo.mode = meanOfAll;
				lmrcImageInformation(&imageInfo, &dst);	
				threshold = imageInfo.mean + imageInfo.sd*info.definedSTD; 
				for(x=0; x<dst.HeaderN.x; x++) {
					for(y=0; y<dst.HeaderN.y; y++) {
						mrcPixelDataGet(&dst, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest); 
						if(data<threshold) {
							mrcPixelDataSet(&dst, x, y, z, (double)threshold, mrcPixelMag);
						}
					}
				}
				break;
			}
			default: {
				fprintf(stderr, "Not supported Mode for lmrcImageMultiCTFCompensationSolventFlatteningMode %d", info.solventMode);
				exit(EXIT_FAILURE);
			}
		}
		DEBUGPRINT("Create Fourier transforms of CTF-corrected image\n");
		/* lfft2d(dstfft, &dst); */
		lmrcImageFFT(dstfft, &dst, 0);

		DEBUGPRINT("Create the predicted observed images\n");
		for(i=0; i<nfile; i++) {
			/* Determine CTF : on real space*/
			/*                 If r is max, then OK !! */

			/* Create Fourier transforms of the predicted observed images */
			DEBUGPRINT1("%ld: CTF Observation dstfft -> predictfft \n", i);
			lmrcImageCTFObservation(&(predictfft[i]), dstfft, &(ctf[i]), 0);

			/* Create the predicted images to observe */
			DEBUGPRINT1("%ld: fft predictfft to predict\n", i);
			/* lfft2d(&(predict[i]), &(predictfft[i])); */
			lmrcImageFFT(&(predict[i]), &(predictfft[i]), 0);

			/* predictfft Image Area Free */
			mrcImageFree(&(predictfft[i]), "in __lmrcImageMultiModeCTFCompensation");
		}
		mrcImageFree(dstfft, "in __lmrcImageMultiModeCTFCompensation");

		/* Normarize the observed image against the predicted observed image */ 
		/*     Now not supported for normalization */ 
		/*

		*/	

		/* Compare the predicted defocused image with real images and change dst*/ 
		for(x=0; x<dst.HeaderN.x; x++) {
			for(y=0; y<dst.HeaderN.y; y++) {
				/* check the difference between predicted images (predict) and obseved images (src) */
				for(i=0; i<nfile; i++) {
					/* predict -> deltasrc : Attention !!! Now common memories are used */
					mrcPixelDataGet(&(predict[i]),  x, y, z, &tmppredict, mrcPixelMag, mrcPixelHowNearest); 
					mrcPixelDataGet(&(src[i]),      x, y, z, &tmpsrc,     mrcPixelMag, mrcPixelHowNearest); 
					/* src - predict */
					delta = tmpsrc - tmppredict;
					mrcPixelDataSet(&(deltasrc[i]), x, y, z, delta	, mrcPixelMag);
				}
			}
		}
		/* deltasrc -> deltasrcfft */
		for(i=0; i<nfile; i++) {
			DEBUGPRINT1("%ld: fft deltasrc to deltasrcfft \n", i);
			/* lfft2d(&(deltasrcfft[i]), &(deltasrc[i])); */
			lmrcImageFFT(&(deltasrcfft[i]), &(deltasrc[i]), 0);
			mrcImageFree(&(deltasrc[i]), "in __lmrcImageMultiModeCTFCompensation");
		}

		/* deltasrcfft -> deltadst */
		DEBUGPRINT1("Create the %ld th delta image \n", iteration);
		__lmrcImageMultiCTFCompensationMode0(&deltadstfft, deltasrcfft, ctf, nfile, info, mode);
		for(i=0; i<nfile; i++) {
			mrcImageFree(&(deltasrcfft[i]), "in __lmrcImageMultiModeCTFCompensation");
		}
		/* lfft2d(&deltadst, &deltadstfft); */
		lmrcImageFFT(&deltadst, &deltadstfft, 0);
		mrcImageFree(&deltadstfft, "in __lmrcImageMultiModeCTFCompensation");

		/* change the CTF-corrected image (dst = dst - deltadst ) */
		for(x=0; x<dst.HeaderN.x; x++) {
			for(y=0; y<dst.HeaderN.y; y++) {
				mrcPixelDataGet(&deltadst, x, y, z, &delta, mrcPixelMag, mrcPixelHowNearest); 
				rms += SQR(delta);
				mrcPixelDataGet(&dst, x, y, z, &data, mrcPixelMag, mrcPixelHowNearest); 
				data += delta;	
				mrcPixelDataSet(&dst, x, y, z, data, mrcPixelMag); 
			}
		}
		mrcStatDataSet(&dst, 0);
		rms = sqrt(rms/dst.HeaderN.x/dst.HeaderN.y)/dst.HeaderAMean;
		mrcImageFree(&deltadst, "in __lmrcImageMultiModeCTFCompensation");

		fprintf(info.logfile, "iter %10ld : rms %15.6e : min %15.6e\n", iteration, rms, minrms);
		DEBUGPRINT3("iter %10ld : rms %15.6e : min %15.6e\n", iteration, rms, minrms);
		if(rms<minrms) {
			if(fabs(rms-minrms)<1e-6) {
				break;
			}
			minrms = rms;
			if(NULL!=mindst.Image) {
				DEBUGPRINT("old mindst free\n");
				mrcImageFree(&mindst, "in __lmrcImageMultiMOdeCTFCompensation");
			}
			mindst = dst;
			dst.Image = NULL;
			mrcInit(&dst, NULL);
			for(x=0; x<dst.HeaderN.x; x++) {
				for(y=0; y<dst.HeaderN.y; y++) {
					mrcPixelDataGet(&mindst, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataSet(&dst, x, y, z, data, mrcPixelRePart);
				}
			}
		}
		iteration++;
	} while(okrms     < rms 
	 	 && iteration < maxiteration 
		 && rms       < diversefactor*minrms); /* Condition for ending iteration */
	/* lfft2d(dstfft, &dst); */
	lmrcImageFFT(dstfft, &mindst, 0);
	mrcImageFree(&mindst, "in __mrcImageMultiCTFCompensationMode1");
	mrcImageFree(&dst, "in __mrcImageMultiCTFCompensationMode1");
}

void
__lmrcImageMultiCTFCompensationMode0(mrcImage* dst, mrcImage* src, ctfInfo* ctf, long nfile, lmrcImageMultiCTFCompensationInfo info, long mode)
{
	double W, NW;
	double Win;
	double re, im, dstre, dstim;	
	double* Weight;
	float X, Y, R;
	float dX, dY;
	long i;

	DEBUGPRINT(" __lmrcImageMultiCTFCompensationMode0\n");
	Weight = (double*)memoryAllocate(sizeof(double)*nfile, "in __lmrcImageMultiCTFCompensation");
	dst->Header = src[0].Header;
	mrcInit(dst, NULL);	
	for(X=0; X <= dst->HeaderN.x/2; X++) {
		for(Y=-dst->HeaderN.y/2; Y < dst->HeaderN.y/2; Y++) {
			W = 0.0;
			mrcPixelDataSet(dst, X, Y, 0.0, 0.0, mrcPixelRePart);
			mrcPixelDataSet(dst, X, Y, 0.0, 0.0, mrcPixelImPart);
			for(i=0; i<nfile; i++) {
				dX = 1.0/(src[i].HeaderN.x*src[i].HeaderLength.x);
				dY = 1.0/(src[i].HeaderN.y*src[i].HeaderLength.y);
				R = sqrt(SQR(X*dX) + SQR(Y*dY));

				if(ctf[i].flagAstigmatism) {
					Weight[i] = ctfFunction2D(&(ctf[i]), X*dX, Y*dY, 0);
				} else {
					Weight[i] = ctfFunction(&(ctf[i]), R, 0);
				}	
				if(mode&0x10) {
					Weight[i] = fabs(Weight[i]);
				}
				W += SQR(Weight[i]);
				

				if(ctf[i].flagWhiteNoiseRaising) {
					NW = SQR(ctf[i].WhiteNoise*exp(ctf[i].WhiteNoiseRaising*R));
				} else if(ctf[i].flagWhiteNoise) {
					NW = SQR(ctf[i].WhiteNoise);
				} 
				if(ctf[i].flagNdependentWhiteNoise) {
					NW = NW/sqrt(ctf[i].NdependentWhiteNoise);
				}
				if(ctf[i].flagMaxWhiteNoise) {
					NW = MIN(NW, ctf[i].MaxWhiteNoise);
				}
				W += NW;

				DEBUGPRINT3("R: %f Weight %f NW %f\n", R, Weight[i], NW);
				if(ctf[i].flagWin) {
					if(R<ctf[i].CutLow) {
						Win = 1.0;
					} else if(ctf[i].CutLow<R && R<ctf[i].CutHigh) {
						Win = (cos((R - ctf[i].CutLow)/(ctf[i].CutHigh - ctf[i].CutLow)*M_PI)+1.0)/2.0;
						DEBUGPRINT2("%f %f\n", R, Win);
					} else {
						Win = 0.0;
					}
				} else {
					Win = 1.0;
				}

				mrcPixelDataGet(dst, X, Y, 0.0, &dstre, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(dst, X, Y, 0.0, &dstim, mrcPixelImPart, mrcPixelHowNearest);
				mrcPixelDataGet(&(src[i]), X, Y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&(src[i]), X, Y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
				dstre += (re*Weight[i]*Win);
				dstim += (im*Weight[i]*Win);
				mrcPixelDataSet(dst, X, Y, 0.0, dstre, mrcPixelRePart);
				mrcPixelDataSet(dst, X, Y, 0.0, dstim, mrcPixelImPart);
			}

			mrcPixelDataGet(dst, X, Y, 0.0, &dstre, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(dst, X, Y, 0.0, &dstim, mrcPixelImPart, mrcPixelHowNearest);
			if(0.0!=W) {
				mrcPixelDataSet(dst, X, Y, 0.0, dstre/W, mrcPixelRePart);
				mrcPixelDataSet(dst, X, Y, 0.0, dstim/W, mrcPixelImPart);
			} else {
				mrcPixelDataSet(dst, X, Y, 0.0, 0.0, mrcPixelRePart);
				mrcPixelDataSet(dst, X, Y, 0.0, 0.0, mrcPixelImPart);
			}
		}
	}
}


