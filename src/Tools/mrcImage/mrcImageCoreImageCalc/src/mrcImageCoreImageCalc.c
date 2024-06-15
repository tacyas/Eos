/*
# mrcImageCoreImageCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageCoreImageCalc
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "nr2.h"

typedef enum lmrcImageCoreImageCalcMode {
	lmrcImageCoreImageCalcModeMultiWindow = 0,
	b=1
} lmrcImageCoreImageCalcMode;

typedef struct CoreLossImage {
	mrcImage Image;  // Image
	float    EELS;    // Electron Energy Loss Spect.
} CoreLossImage;

typedef struct lmrcImageCoreImageCalcInfo {
	CoreLossImage* 	Background; 
	int				numBackground;				
	CoreLossImage   EstimatedBG; 
	CoreLossImage   ChisqImage; 
	float BaseEELS; /* As 1.0 */		
	float initialBaseLine; /* CCD BaseLine */
	float initialDecay;    /* Decay */
	float limitDecayMin;   /* Decay */
	float limitDecayMax;   /* Decay */
	float initialDecayIntensity;   /* Decay */
} lmrcImageCoreImageCalcInfo;

void lmrcImageCoreImageCalcModePrint(FILE* fpt);
void lmrcImageCoreImageCalc(mrcImage* out, mrcImage* in, lmrcImageCoreImageCalcInfo* linfo, lmrcImageCoreImageCalcMode mode);
void lmrcImageCoreImageCalcMultiWindow(mrcImage* out, mrcImage* in, lmrcImageCoreImageCalcInfo* linfo, lmrcImageCoreImageCalcMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImageCoreImageCalcInfo info;
	lmrcImageCoreImageCalcInfo linfo;
	int i;
	char s[STRING_MAX_LENGTH];
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	linfo.BaseEELS = info.BaseEELS;
	linfo.EstimatedBG.EELS = info.EL; 
	linfo.initialBaseLine  = info.A1;
	linfo.initialDecayIntensity = info.A2;
	linfo.initialDecay     = info.A3;
	linfo.limitDecayMin    = info.LimitA3Min;
	linfo.limitDecayMax    = info.LimitA3Max;
	linfo.Background = (CoreLossImage*)memoryAllocate(sizeof(CoreLossImage)*info.flagBG, "for BG");
	linfo.numBackground	= info.flagBG; 
	fseek(info.fptBGList, 0L, SEEK_SET);
	for(i=0; i<info.flagBG; i++) {
		mrcFileRead(&(linfo.Background[i].Image), info.BG[i], "read BG", 0);
		stringGetFromFile(s, "FileList" , info.fptBGList, stdout,3);	
		linfo.Background[i].EELS = stringGetNthRealData(s, 2, " \t,") ;
		DEBUGPRINT2("%s %f\n", info.BG[i], linfo.Background[i].EELS);
	}


	lmrcImageCoreImageCalc(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	if(info.flagOutBG) {
		mrcFileWrite(&linfo.EstimatedBG.Image, info.OutBG, "in main BG", 0);
	}
	if(info.flagOutChi) {
		mrcFileWrite(&linfo.ChisqImage.Image, info.OutChi, "in main Chi", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>> BGFile List \n");
	fprintf(stderr, "FileName1 EEL\n");
	fprintf(stderr, "FileName2 EEL\n");
	fprintf(stderr, "AAA       160\n");
	fprintf(stderr, "BBB       170\n");
	lmrcImageCoreImageCalcModePrint(stderr);
}

void
lmrcImageCoreImageCalcModePrint(FILE* fpt)
{
	fprintf(fpt, ">>> Mode \n");
	fprintf(fpt, "Mode %d: Multi Window Method \n",  lmrcImageCoreImageCalcModeMultiWindow);
	fprintf(fpt, "        Need more than three pre- and post- edge images to calculate background\n");
}

void 
lmrcImageCoreImageCalc(mrcImage* out, mrcImage* in, lmrcImageCoreImageCalcInfo* linfo,  lmrcImageCoreImageCalcMode mode)
{
	out->Header = in->Header;
	linfo->EstimatedBG.Image.Header = in->Header;
	mrcInit(out, NULL);	
	mrcInit(&(linfo->EstimatedBG.Image), NULL);	
	switch(mode) {
		case  lmrcImageCoreImageCalcModeMultiWindow: {
			lmrcImageCoreImageCalcMultiWindow(out, in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not Supported Mode\n");
			exit(EXIT_FAILURE);
			break;
		}
	}
}

void __func(float x, float a[], float* y, float dyda[], int na)
{
	//
	*y = a[1] + a[2]*pow(x, a[3]);
	// Derivative
	dyda[1] = 1;
	dyda[2] = pow(x,a[3]);
	dyda[3] = a[2]*a[3]*pow(x, a[3]-1.0);
}

void 
lmrcImageCoreImageCalcMultiWindow(mrcImage* out, mrcImage* in, lmrcImageCoreImageCalcInfo* linfo, lmrcImageCoreImageCalcMode mode)
{
	mrcImageParaTypeReal x, y, z;
	int i;
	float* E;
	float* I; 
	float* S; 
	float* a;
	int*   ia;
	float** covar;
	float** alpha;
	float  chisq;
	float  alambda;
	int    ma = 3;
	double data;
	double bg;
	double min, xmin;
	double max, xmax;
	double oldchisq;
	E = (float*)memoryAllocate(sizeof(float)*(linfo->numBackground+1), "in CoreImage");
	I = (float*)memoryAllocate(sizeof(float)*(linfo->numBackground+1), "in CoreImage");
	S = (float*)memoryAllocate(sizeof(float)*(linfo->numBackground+1), "in CoreImage");

	a  = (float*)memoryAllocate(sizeof(float)*(ma+1), "in CoreImage");
	ia = (int*)  memoryAllocate(sizeof(int)*(ma+1),   "in CoreImage");
	//ia[3] = 0;
	alpha  = (float**)memoryAllocate(sizeof(float)*(ma+1), "in CoreImage");
	covar  = (float**)memoryAllocate(sizeof(float)*(ma+1), "in CoreImage");
	for(i=0; i<ma+1; i++) {
		alpha[i] = (float*)memoryAllocate(sizeof(float)*(ma+1), "in CoreImage");
		covar[i] = (float*)memoryAllocate(sizeof(float)*(ma+1), "in CoreImage");
	}

	linfo->ChisqImage.Image.Header = in->Header;
	mrcInit(&linfo->ChisqImage.Image, NULL);	

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		for(i=0; i<linfo->numBackground; i++) {					
			//E[i+1] = linfo->Background[i].EELS/linfo->EstimatedBG.EELS;
			E[i+1] = linfo->Background[i].EELS/linfo->BaseEELS;
			mrcPixelDataGet(&linfo->Background[i].Image, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			I[i+1] = data;
			S[i+1] = 1.0;
		}
		// Fitting for __func (A+B*E^r)
		alambda = -1;	

		a[1] = linfo->initialBaseLine;
		a[2] = linfo->initialDecayIntensity;
		a[3] = linfo->initialDecay;
		ia[1] = ia[2] = ia[3] = 1;
		oldchisq = 1e16;
		mrqmin(E, I, S, linfo->numBackground, a, ia, ma, covar, alpha, &chisq, __func, &alambda);
		while(1e-4<fabs(chisq-oldchisq) && linfo->limitDecayMin < a[3] && a[3] < linfo->limitDecayMax ) {
			oldchisq = chisq;
			mrqmin(E, I, S, linfo->numBackground, a, ia, ma, covar, alpha, &chisq, __func, &alambda);
		}
		bg = a[1] + a[2]*pow(linfo->EstimatedBG.EELS/linfo->BaseEELS, a[3]);	

		mrcPixelDataSet(&(linfo->EstimatedBG.Image), x, y, z, bg, mrcPixelRePart);
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(out, x, y, z, data-bg, mrcPixelRePart);
		mrcPixelDataSet(&linfo->ChisqImage.Image, x, y, z, chisq, mrcPixelRePart);
#undef DEBUG
#ifdef DEBUG
		DEBUGPRINT6(" %f + %f * E^ %f at %f %f %f\n", a[1], a[2], a[3], x, y, z);
		DEBUGPRINT4(" i %f = i %f - bg %f chisq %f \n", data-bg, data, bg, chisq);
#endif		
#define DEBUG
#ifdef DEBUG
		if(chisq<10) {
			DEBUGPRINT6(" %15.6f + %15.6f * E^ %15.6f at %10.2f %10.2f %10.2f\n", a[1], a[2], a[3], x, y, z);
			DEBUGPRINT5(" i %15.6f = i %15.6f - bg %15.6f chisq %15.6f E %f\n", data-bg, data, bg, chisq, linfo->EstimatedBG.EELS);
		}
#endif		
	}
	}
	}
}

