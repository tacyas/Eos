/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDeconvolution ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDeconvolution 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageDeconvoluton ver%I%; Date:%D% %Z%";


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>       
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "./lmrcImageDeconvolution.h"

void
lmrcImageDeconvolutionModePrint(FILE* fpt)
{
	fprintf(fpt, "%d: No deconvolution\n",           lmrcImageDeconvolutoinInfoModeNoConvolution);
	fprintf(fpt, "%d: CTF/|CTF| (phase flipping)\n", lmrcImageDeconvolutoinInfoModePhaseFlipping);
	fprintf(fpt, "%d: CTF       (CTF-Multi)\n",      lmrcImageDeconvolutoinInfoModeCTFMultiplying);
	fprintf(fpt, "%d: 1/CTF     (Inverse Filter)\n", lmrcImageDeconvolutoinInfoModeInverseFilter);
	fprintf(fpt, "%d: CTF/(SQR(CTF)+SQR(NS))  (Wiener Filter)\n", lmrcImageDeconvolutoinInfoModeWienerFilter);
	fprintf(fpt, "%d: SQR(CTF) x CTF/|CTF|    (phase flipping + ctfWeighted)\n", lmrcImageDeconvolutoinInfoModePhaseFlippingCTFWeighted);
	fprintf(fpt, "%d: 1/|CTF|                   (No phase-flipping: Inverse Filter)\n", lmrcImageDeconvolutoinInfoModeInverseFilterNoPhaseFlipping);
	fprintf(fpt, "%d: |CTF|/(SQR(CTF)+SQR(NS))  (No phase-flipping: Wiener Filter)\n", lmrcImageDeconvolutoinInfoModeWienerFilterNoPhaseFlipping);
	fprintf(fpt, "%d:  CTF /(SQR(CTF)+SQR(NS*exp(a*R)))  (phase-flipping:    Wiener Filter + Noise)\n", lmrcImageDeconvolutoinInfoModeWienerFilterRDependent);
	fprintf(fpt, "%d: |CTF|/(SQR(CTF)+SQR(NS*exp(a*R)))  (No phase-flipping: Wiener Filter + Noise)\n", lmrcImageDeconvolutoinInfoModeWienerFilterRDependentNoPhaseFlipping);
}


void
lmrcImageDeconvolutionKernelCentrePrint(FILE* fpt)
{
	fprintf(fpt, "%d: BottomLeft\n",  lmrcImageDeconvolutoinInfoKernelCentreBottomLeft);
	fprintf(fpt, "%d: Centre\n",      lmrcImageDeconvolutoinInfoKernelCentreCentre);
}

void
lmrcImageIterativeDeconvolution(mrcImage* out, mrcImage* convOut, mrcImage* in, mrcImage* kernel, lmrcImageDeconvolutionInfo* linfo, int mode)
{
	int i;
	mrcImage deconvTmp;
	mrcImage deconvTmpNext;
	mrcImage convTmp;
	mrcImage subTmp;
	mrcImage subTmpDeconv;
	mrcImage deltaTmp;
	mrcImageInformation tmpInfo;

	linfo->subInfo.mode = meanOfAll;
	tmpInfo.mode = meanOfAll;
	/*
		deconv(i+1) = deconv(i) + lambda*Deconv(in-Conv(deconv(i)))
					  deconvTmp                         deconvTmp
					                              subTmp
                                         subTmpDeconv
	                              -subTmpDeconv2 
		deconvTmpNext
	*/
	lmrcImageDeconvolution(&deconvTmp, &convTmp, in, kernel, linfo, mode); 	
	lmrcImageInformation(&tmpInfo, &deconvTmp); DEBUGPRINT1("deconvTmp.sd: %f\n", tmpInfo.sd);
	lmrcImageInformation(&tmpInfo, &convTmp); DEBUGPRINT1("convTmp.sd: %f\n", tmpInfo.sd);

	lmrcImageSubtractionCalc(&subTmp, in, &convTmp);
	lmrcImageInformation(&(linfo->subInfo), &subTmp); DEBUGPRINT1("subTmp.sd: %f\n", linfo->subInfo.sd);
	
	for(i=0; i<linfo->maxIter; i++) {
		linfo->Iter = i+1;		
		if(linfo->minRMSD < linfo->subInfo.sd) {
			lmrcImageDeconvolution(&subTmpDeconv, NULL, &subTmp, kernel, linfo, mode);
			lmrcImageMultiplying2(&subTmpDeconv, -linfo->lambda, subTmpDeconv.HeaderMode);
			lmrcImageSubtractionCalc(&deconvTmpNext, &deconvTmp, &subTmpDeconv);
			//
			mrcImageFree(&deconvTmp, 0);
			mrcImageFree(&convTmp, 0);
			mrcImageFree(&subTmp, 0);
			mrcImageFree(&subTmpDeconv, 0);
			//
			deconvTmp = deconvTmpNext;
			//
			lmrcImageConvolution(&convTmp, &deconvTmp, kernel, 0);	 
			lmrcImageInformation(&tmpInfo, &convTmp); DEBUGPRINT1("convTmp.sd: %f\n", tmpInfo.sd);

			lmrcImageSubtractionCalc(&subTmp, in, &convTmp);
			lmrcImageInformation(&(linfo->subInfo), &subTmp); DEBUGPRINT1("subTmp.sd: %f\n", linfo->subInfo.sd);
		} else {
			mrcImageFree(&subTmpDeconv, 0);
			break;
		}
	}
	linfo->rmsd = subTmp;
	*out     = deconvTmp;
	*convOut = convTmp;
}

void
lmrcImageDeconvolution(mrcImage* out, mrcImage* convOut, mrcImage* in, mrcImage* kernel, lmrcImageDeconvolutionInfo* linfo, int mode)
{
	int srcX, srcY, srcZ;
	int minX, minY, minZ;
	int maxX, maxY, maxZ;
	int minxx, minyy, minzz;
	int maxxx, maxyy, maxzz;
	mrcImage K;
	mrcImage KShift;
	mrcImage fftK;
	mrcImage fftIn;
	mrcImage fftOut;
	mrcImage preOut;
	mrcImage convOutTmp;
	mrcImage convTmp;

	int kx, ky, kz;
	int x, y, z;
	double srcR, srcI;
	double dstR, dstI;
	double weightR, weightI, weight, weight2;
	double ns, ns2;
	double R;
	mrcImageInformation tmpInfo;

	tmpInfo.mode = meanOfAll;
	lmrcImageInformation(&tmpInfo, kernel); DEBUGPRINT1("kernel.sd: %f\n", tmpInfo.sd);

	if(kernel->HeaderN.x!=in->HeaderN.x
	 ||kernel->HeaderN.y!=in->HeaderN.y
	 ||kernel->HeaderN.z!=in->HeaderN.z) {
	 	linfo->Pad3DInfo.Nx = in->HeaderN.x;
	 	linfo->Pad3DInfo.Ny = in->HeaderN.y;
	 	linfo->Pad3DInfo.Nz = in->HeaderN.z;
		lmrcImage3DPad(&K, kernel, linfo->Pad3DInfo, linfo->Pad3DMode);	
		lmrcImageInformation(&tmpInfo, &K); DEBUGPRINT1("K.sd: %f\n", tmpInfo.sd);
	} else {
		K = *kernel;
	}
	switch(linfo->KernelCentreMode) {
		case lmrcImageDeconvolutoinInfoKernelCentreBottomLeft: {
			KShift = K;	
			break;
		}
		case lmrcImageDeconvolutoinInfoKernelCentreCentre: {
			mrcImageParaTypeRealCoord shift;
			shift.x = -(K.HeaderN.x-1)*0.5;
			shift.y = -(K.HeaderN.y-1)*0.5;
			shift.z = -(K.HeaderN.z-1)*0.5;
			lmrcImageShift(&KShift, &K, shift, mrcPixelHowCubicConv);
			break;
		}
	}
	//		mrcFileWrite(&KShift, "/tmp/test.3d", "in lmrcImageDeconvolution", 0);
	lmrcImageFFT(&fftK,  &KShift, 0);
	lmrcImageFFT(&fftIn, in, 0);

	fftOut.Header = fftIn.Header;	
	mrcInit(&fftOut, NULL);

	minX=0;                  maxX=fftIn.HeaderN.x/2;
	minY=MIN(0,-fftIn.HeaderN.y/2); maxY=MAX(0,fftIn.HeaderN.y/2-1);
	minZ=MIN(0,-fftIn.HeaderN.z/2); maxZ=MAX(0,fftIn.HeaderN.z/2-1);
	DEBUGPRINT6("%d %d %d %d %d %d\n", minX, minY, minZ, maxX, maxY, maxZ);	

	for(srcZ=minZ; srcZ<=maxZ; srcZ++) {
	for(srcY=minY; srcY<=maxY; srcY++) {
	for(srcX=minX; srcX<=maxX; srcX++) {
		mrcPixelDataGet(&fftIn, srcX, srcY, srcZ, &srcR, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&fftIn, srcX, srcY, srcZ, &srcI, mrcPixelImPart, mrcPixelHowNearest);
		//DEBUGPRINT5("%d %d %d <= %f %f\n", srcX, srcY, srcZ, srcR, srcI);

		mrcPixelDataGet(&fftK,  srcX, srcY, srcZ, &weightR, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&fftK,  srcX, srcY, srcZ, &weightI, mrcPixelImPart, mrcPixelHowNearest);
		//DEBUGPRINT5("%d %d %d <= %f %f\n", srcX, srcY, srcZ, weightR, weightI);

		switch(mode) {
			case lmrcImageDeconvolutoinInfoModeNoConvolution: {
				dstR = srcR;
				dstI = srcI;
				//DEBUGPRINT5("%d %d %d <= %f %f\n", srcX, srcY, srcZ, dstR, dstI);
				break;
			} 
			case lmrcImageDeconvolutoinInfoModePhaseFlipping: {
				weight2 = SQR(weightR) + SQR(weightI);
				//DEBUGPRINT5("%d %d %d <= %f %f\n", srcX, srcY, srcZ, weightR, weightI);
				if(0<weight) {
					weight = sqrt(weight2);
					dstR = (srcR*weightR - srcI*weightI)/weight;
					dstI = (srcR*weightI + srcI*weightR)/weight;
				} else {
					dstR = dstI = 0;
				}
				break;
			}
			case lmrcImageDeconvolutoinInfoModeCTFMultiplying: {
				dstR = (srcR*weightR - srcI*weightI);
				dstI = (srcR*weightI + srcI*weightR);
				break;
			}
			case lmrcImageDeconvolutoinInfoModeInverseFilter: {
				weight2 = SQR(weightR) + SQR(weightI);
				if(0<weight2) {
					weight = sqrt(weight2);
					if(weight<linfo->thresCTF) {
						weight2 = 0;
					}
				} 
				if(0<weight2) {
					dstR = (srcR*weightR - srcI*weightI)/weight2;
					dstI = (srcR*weightI + srcI*weightR)/weight2;
				} else {
					dstR = dstI = 0;
				}	
				break;
			}
			case lmrcImageDeconvolutoinInfoModeWienerFilter: {
				weight2 = SQR(weightR) + SQR(weightI);
				ns2     = SQR(linfo->NSRatio);
				if(0<weight2) {
					dstR = (srcR*weightR - srcI*weightI)/(weight2 + ns2);
					dstI = (srcR*weightI + srcI*weightR)/(weight2 + ns2);
				} else {
					dstR = dstI = 0;
				}
				break;
			}
			case lmrcImageDeconvolutoinInfoModePhaseFlippingCTFWeighted: {
				weight2 = SQR(weightR) + SQR(weightI);
				weight = sqrt(weight2);
				dstR = (srcR*weightR - srcI*weightI)*weight;
				dstI = (srcR*weightI + srcI*weightR)*weight;
				break;
			}
	  		case lmrcImageDeconvolutoinInfoModeInverseFilterNoPhaseFlipping: {
				weight2 = SQR(weightR) + SQR(weightI);
				if(0<weight2) {
					weight = sqrt(weight2);
					if(weight<linfo->thresCTF) {
						weight = 0;
					}
				} 
				if(0<weight) {
					dstR = srcR/weight;
					dstI = srcI/weight;
				} else {
					dstR = dstI = 0;
				}	
				break;
			}
			case lmrcImageDeconvolutoinInfoModeWienerFilterNoPhaseFlipping: {
				weight2 = SQR(weightR) + SQR(weightI);
				ns2     = SQR(linfo->NSRatio);
				if(0<weight2) {
					weight = sqrt(weight2);
					dstR = srcR*weight/(weight2 + ns2);
					dstI = srcI*weight/(weight2 + ns2);
				} else {
					dstR = dstI = 0;
				}
				break;
			}
	    	case lmrcImageDeconvolutoinInfoModeWienerFilterRDependent: {
				R = srcX/(in->HeaderLength.x*in->HeaderN.x) 
				   +srcY/(in->HeaderLength.y*in->HeaderN.y)
				   +srcZ/(in->HeaderLength.z*in->HeaderN.z);
				weight2 = SQR(weightR) + SQR(weightI);
				ns2     = SQR(linfo->NSRatio*exp(linfo->NSCoeff*R));
				if(0<weight2) {
					dstR = (srcR*weightR - srcI*weightI)/(weight2 + ns2);
					dstI = (srcR*weightI + srcI*weightR)/(weight2 + ns2);
				} else {
					dstR = dstI = 0;
				}
				break;
			}
			case lmrcImageDeconvolutoinInfoModeWienerFilterRDependentNoPhaseFlipping: {
				R = srcX/(in->HeaderLength.x*in->HeaderN.x) 
				   +srcY/(in->HeaderLength.y*in->HeaderN.y)
				   +srcZ/(in->HeaderLength.z*in->HeaderN.z);
				weight2 = SQR(weightR) + SQR(weightI);
				ns2     = SQR(linfo->NSRatio*exp(linfo->NSCoeff*R));
				if(0<weight2) {
					weight = sqrt(weight2);
					dstR = srcR*weight/(weight2 + ns2);
					dstI = srcI*weight/(weight2 + ns2);
				} else {
					dstR = dstI = 0;
				}
				break;
			}
			default: {
				fprintf(stderr, "Not supported mode in lmrcImageDeconvolution: %d\n", mode);
				exit(EXIT_FAILURE);
				break;
			}
		}

		mrcPixelDataSet(&fftOut, srcX, srcY, srcZ, dstR, mrcPixelRePart);
		mrcPixelDataSet(&fftOut, srcX, srcY, srcZ, dstI, mrcPixelImPart);
	}
	}
	}
	lmrcImageFFT(&preOut, &fftOut, 0);
	lmrcImageConvolution(&convTmp, &preOut, kernel, 0);	 

	/* Calculate NormalizedImage and a, b*/
	if(linfo->norInfoMode&lmrcImageDensityNormalizationByImageModeSigma) {
		linfo->norInfo.sigma =  lmrcImageSigmaCalculate(in);
	} else {
		linfo->norInfo.sigma = 1.0;
	}
	DEBUGPRINT1("sigma: %f \n ", linfo->norInfo.sigma);
	lmrcImageDenstiyNormalizationByImage(&convOutTmp, &convTmp, in, &(linfo->norInfo), linfo->norInfoMode);

	DEBUGPRINT2("a: %f + b:  %f x in\n ", linfo->norInfo.a, linfo->norInfo.b);
	lmrcImageInformation(&tmpInfo, &preOut); DEBUGPRINT1("preOut.sd: %f\n", tmpInfo.sd);
	lmrcImageMultiplying2(&preOut,  linfo->norInfo.b, preOut.HeaderMode);
	lmrcImageInformation(&tmpInfo, &preOut); DEBUGPRINT1("preOut.sd: %f\n", tmpInfo.sd);
	lmrcImageAddValue(out, &preOut, linfo->norInfo.b, 0);
	lmrcImageInformation(&tmpInfo, out); DEBUGPRINT1("out.sd: %f\n", tmpInfo.sd);

	if(NULL!=convOut) {
		*convOut = convOutTmp;
	}
	mrcImageFree(&preOut, 0);
	mrcImageFree(&fftOut, 0);
	mrcImageFree(&fftK, 0);
}
