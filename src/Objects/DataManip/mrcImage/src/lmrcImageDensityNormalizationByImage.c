/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDensityNormalizationByImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDensityNormalizationByImage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageDensityNormalizationByImage ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "nr2.h"
#include "./lmrcImageDensityNormalizationByImage.h"
#include "./lmrcImageSummationCalculate.h"
#include "./lmrcImageStudentCalculate.h"
#include <math.h>

extern void __lmrcImageDensityNormalizationByImage0(
						mrcImage* out, mrcImage* in2, mrcImage* in1, 
						lmrcImageDensityNormalizationByImageInfo* info,
						lmrcImageDensityNormalizationByImageMode  mode);

extern void __lmrcImageDensityNormalizationByImage8(
						mrcImage* out, mrcImage* in2, mrcImage* in1, 
						lmrcImageDensityNormalizationByImageInfo* info,
						lmrcImageDensityNormalizationByImageMode  mode);

void
lmrcImageDensityNormalizationByImageInfoPrint(FILE* fpt, lmrcImageDensityNormalizationByImageInfo info)
{
	switch(info.fitMode) {
		case lmrcImageDensityNormalizationByImageFitModeSingleLine: {
			fprintf(fpt, "#A+Bx\n");
			fprintf(fpt, "A: %15.6g %15.6g\n", info.a, info.sigma_a);
			fprintf(fpt, "B: %15.6g %15.6g\n", info.b, info.sigma_b);
			fprintf(fpt, "chi: %15.6g %15.6g \n", info.chi2, info.q);
			break;
		}
		case lmrcImageDensityNormalizationByImageFitModeSingleLineWithBackground: {
			fprintf(fpt, "#A+Bx  (tstBG<tst)\n");
			fprintf(fpt, "#refBG (tstBG>tst)\n");
			fprintf(fpt, "A:  %15.6g %15.6g\n", info.a, info.sigma_a);
			fprintf(fpt, "B:  %15.6g %15.6g\n", info.b, info.sigma_b);
			fprintf(fpt, "BG: %15.6g %15.6g\n", info.tstBG, info.refBG);
			fprintf(fpt, "chiBG:      %15.6g \n", info.chi2BG);
			fprintf(fpt, "chiSignal:  %15.6g \n", info.chi2Signal);
			fprintf(fpt, "chi: %15.6g %15.6g \n", info.chi2, info.q);
			break;
		}
	}
}

void
lmrcImageDensityNormalizationByImageModePrint(FILE* fpt)
{
  fprintf(fpt, "%3d: Sigma!=1.0 \n", lmrcImageDensityNormalizationByImageModeSigma);
  fprintf(fpt, "%3d: Stdout     \n", lmrcImageDensityNormalizationByImageModeStdout);
  fprintf(fpt, "%3d: Reversed   \n", lmrcImageDensityNormalizationByImageModeReverse);
  fprintf(fpt, "%3d: Robust Test\n", lmrcImageDensityNormalizationByImageModeRobust);
  fprintf(fpt, "Fitting Mode\n");
  fprintf(fpt, "%3d: Single Line\n", lmrcImageDensityNormalizationByImageFitModeSingleLine);
  fprintf(fpt, "        ref    /                      \n");
  fprintf(fpt, "          ^   /   ref = A + B*tst     \n");
  fprintf(fpt, "          |  /                        \n");
  fprintf(fpt, "          |------> tst                \n");
  fprintf(fpt, "%3d: Single Line with Background\n", lmrcImageDensityNormalizationByImageFitModeSingleLineWithBackground);
  fprintf(fpt, "        ref      /                              \n");
  fprintf(fpt, "          ^     /   ref = A + B*tst (tst>tstBG) \n");
  fprintf(fpt, " refBG-   | ___/          refBG     (tst<tstBG) \n");
  fprintf(fpt, "          | ------> tst                         \n");
  fprintf(fpt, "               |                                \n");
  fprintf(fpt, "              tstBG                             \n");
}


void
lmrcImageDenstiyNormalizationByImage(
						mrcImage* out, mrcImage* in2, mrcImage* in1, 
						lmrcImageDensityNormalizationByImageInfo* info,
						lmrcImageDensityNormalizationByImageMode  mode)
{
	if(0==(lmrcImageDensityNormalizationByImageModeRobust&mode)) {
		__lmrcImageDensityNormalizationByImage0(out, in2, in1, info, mode);
	} else {
		__lmrcImageDensityNormalizationByImage8(out, in2, in1, info, mode);
	}
}


void
__lmrcImageDensityNormalizationByImage8(
						mrcImage* out, mrcImage* y, mrcImage* x, 
						lmrcImageDensityNormalizationByImageInfo* info,
						lmrcImageDensityNormalizationByImageMode  mode)
{
	fprintf(stderr, "Not supproted yet\n");
}

void
__lmrcImageDensityNormalizationByImage0(
						mrcImage* out, mrcImage* test, mrcImage* ref, 
						lmrcImageDensityNormalizationByImageInfo* info,
						lmrcImageDensityNormalizationByImageMode  mode)
{
	int x,y,z;
	double tstData;

	/* Density Distribution Fitting */
	lmrcImageDensityFittingForNormalization(out, test, ref, info, mode);

	out->Header = ref->Header;
	mrcInit(out, NULL);

	/* Normalization Follwoing FitParameters */
	for (z=0; z<out->HeaderN.z; z++){
	for (y=0; y<out->HeaderN.y; y++){
	for (x=0; x<out->HeaderN.x; x++){
		mrcPixelDataGet(test, x, y, z, &tstData, mrcPixelRePart, mrcPixelHowNearest);
		tstData = info->a+info->b*tstData;
		mrcPixelDataSet(out, x, y, z,  tstData, mrcPixelRePart);
	}
	}
	}
}


void
lmrcImageDensityFittingForNormalization(
						mrcImage* out, mrcImage* test, mrcImage* ref, 
						lmrcImageDensityNormalizationByImageInfo* info,
						lmrcImageDensityNormalizationByImageMode  mode)
{
	int i;
	int x,y,z;
	double tstData;
	double refData;
	int n;
	int flag;
	float* inx;
	float* iny;
	float* insig;

  /* 
	 x: test y: ref 

	 Chi-square fitting to a line from Numerical Recipies in chapter of 15.2
	 Chi-square = Sum {(yi - a - b xi)/SDi}^2
  */
  	n     = (test->HeaderN.x*test->HeaderN.y*test->HeaderN.z);
	inx   = (float*)memoryAllocate(sizeof(float)*(n+1), "");
	iny   = (float*)memoryAllocate(sizeof(float)*(n+1), "");
	insig = (float*)memoryAllocate(sizeof(float)*(n+1), "");
	i = 1; 
	n = 0; 
    for(z=0; z<ref->HeaderN.z; z++) {
    for(y=0; y<ref->HeaderN.y; y++) {
    for(x=0; x<ref->HeaderN.x; x++) {
		if(1==info->flagCylinder) { 
			if(SQR(x-info->centerx) + SQR(y-info->centery) >= SQR(info->minr) 
			&& SQR(x-info->centerx) + SQR(y-info->centery) <= SQR(info->maxr)) {
				flag = 1;
			} else {
				flag = 0;
			}
		} else {
			flag = 1;
		}
		if(1==flag) {
            mrcPixelDataGet(ref,  x, y, z, &refData, mrcPixelRePart, mrcPixelHowNearest);
	        mrcPixelDataGet(test, x, y, z, &tstData, mrcPixelRePart, mrcPixelHowNearest);
			inx[i]   = tstData; 	
			iny[i]   = refData;	
			insig[i] = info->sigma; 	
			i++;
			n++;
		}	
	}
	}
	}
	info->nData     = n;
	info->testData  = inx + 1;
	info->refData   = iny + 1;
	switch(info->fitMode) {
		case lmrcImageDensityNormalizationByImageFitModeSingleLine: {
			fit(inx, iny, n, insig, 0, 		
				&info->a, &info->b, &info->sigma_a, &info->sigma_b, 
				&info->chi2, &info->q);
			break;
		}
		case lmrcImageDensityNormalizationByImageFitModeSingleLineWithBackground: {
			float* xBG;
			float* xSignal;
			float* yBG;
			float* ySignal;
			float* sigBG;
			float* sigSignal;
			float  tstBG, tstBGMin, tstBGMax, tstBGDelta;
			float  refBG;
		    int    nBG, nSignal;
			float  chi2BG, chi2Signal, chi2;
			float  a, b, sa, sb, q;
			float  minChi2, minChi2Signal, minChi2BG, minTstBG, minRefBG;
			float  amin, bmin, samin, sbmin, qmin;
			
			xBG       = (float*)memoryAllocate(sizeof(float)*(n+1), "in lmrcImageDensityFittingForNormalization");
			xSignal   = (float*)memoryAllocate(sizeof(float)*(n+1), "in lmrcImageDensityFittingForNormalization");
			yBG       = (float*)memoryAllocate(sizeof(float)*(n+1), "in lmrcImageDensityFittingForNormalization");
			ySignal   = (float*)memoryAllocate(sizeof(float)*(n+1), "in lmrcImageDensityFittingForNormalization");
			sigBG     = (float*)memoryAllocate(sizeof(float)*(n+1), "in lmrcImageDensityFittingForNormalization");
			sigSignal = (float*)memoryAllocate(sizeof(float)*(n+1), "in lmrcImageDensityFittingForNormalization");
        
			tstBGMin   = info->tstBGMin;
			tstBGMax   = info->tstBGMax;
			tstBGDelta = info->tstBGDelta;
			minChi2 = 1e30;	
			minChi2Signal = minChi2BG = minTstBG = minRefBG = 0;
			amin          = bmin      = samin    = sbmin    = qmin = 0;
			for(tstBG=tstBGMin; tstBG<=tstBGMax; tstBG+=tstBGDelta) {
				nBG = nSignal = 0;			
				for(i=1; i<=n; i++) {
					if(tstBG < inx[i]) {
						nSignal++;
						xSignal[nSignal]   = inx[i];
						ySignal[nSignal]   = iny[i];
						sigSignal[nSignal] = insig[i];
					} else {
						nBG++;
						xBG[nBG]   = inx[i];
						yBG[nBG]   = iny[i];
						sigBG[nBG] = insig[i];
					}
				}
				/* Ref Background Estimation */
			    refBG = 0;		
				for(i=1; i<=nBG; i++) {
					refBG += yBG[i];
				}
				refBG /= nBG;
				chi2BG = 0;
				for(i=1; i<=nBG; i++) { /* chi-square calc */
					chi2BG += SQR((yBG[i] - refBG)/sigBG[i]);
					/*
					DEBUGPRINT5("tstBG %15.6f refBG %15.6f yBG %15.6f %15.6f chi2BG %15.6g\n", tstBG, refBG, yBG[i], sigBG[i], chi2BG);
					*/
				}

				/* Signal region estimation */
				fit(xSignal, ySignal, nSignal, sigSignal, 0, 		
					&a, &b, &sa, &sb, 
					&chi2Signal, &q);
				chi2 = chi2Signal + chi2BG;

				/* Check max or not */
				DEBUGPRINT3("chi2:  %15.6g %15.6g %15.6g ", chi2, chi2Signal, chi2BG);
				DEBUGPRINT6("param: %15.6f %15.6f %15.6f %15.6f %6d %6d\n", a, b, tstBG, refBG, nSignal, nBG);
				if(chi2<minChi2) {
					DEBUGPRINT("---- Min ----\n");
					DEBUGPRINT3("chi2:  %15.6g %15.6g %15.6g ", chi2, chi2Signal, chi2BG);
					DEBUGPRINT6("param: %15.6f %15.6f %15.6f %15.6f %6d %6d\n", a, b, tstBG, refBG, nSignal, nBG);
					amin          = a;
					bmin          = b;
					samin         = sa;
					sbmin         = sb;
					qmin          = q;
					minTstBG      = tstBG;
					minRefBG      = refBG;
					minChi2Signal = chi2Signal;
					minChi2BG     = chi2BG;
					minChi2       = chi2;
				}
			}
			info->a = amin;	
			info->b = bmin;	
			info->sigma_a = samin;	
			info->sigma_b = sbmin;	
			info->q       = qmin;	
			info->tstBG = minTstBG;
			info->refBG = minRefBG;
			info->chi2Signal = minChi2Signal;
			info->chi2BG     = minChi2BG;
			info->chi2 = info->chi2BG + info->chi2Signal;
			break;
		}
		default: {
			fprintf(stderr, "Not suportted mode in lmrcImageDensityNormalizationByImageFit: %d\n",
				info->fitMode);
			exit(EXIT_FAILURE);
			break;
		}
	}
}
