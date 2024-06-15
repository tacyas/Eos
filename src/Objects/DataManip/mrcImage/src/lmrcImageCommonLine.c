/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCommonLine ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCommonLine 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageCommonLine ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"
#include "./lmrcImageSinogram.h"
#include "./lmrcImageCommonLine.h"
#include "./lmrcImageCentre.h"

static void lmrcImageCommonLineSearch0(mrcImage* out, mrcImage* in2, mrcImage* ref2, lmrcImageCommonLineInfo* linfo, int mode);
static void lmrcImageCommonLineSearch1(mrcImage* out, mrcImage* in2, mrcImage* ref2, lmrcImageCommonLineInfo* linfo, int mode);

void 
lmrcImageCommonLineInfoUsage(FILE* fpt)
{
	fprintf(fpt, ">>>> lmrcImageCommonLineInfo\n");
	fprintf(fpt, " ----  mode ----\n");
	fprintf(fpt, "    %d: Image Center is Centre of Gravity.\n", lmrcImageCommonLineModeImageCenterIsGC);
	fprintf(fpt, " ----  search mode ----\n");
	fprintf(fpt, "    %d: CommonLine Search in Fourier Space.\n", lmrcImageCommonLineSearchModeFourierSpace);
	fprintf(fpt, "    %d: CommonLine Search in Real Space.\n", lmrcImageCommonLineSearchModeRealSpace);
}

void
lmrcImageCommonLineInfoOutput(FILE* fpt, lmrcImageCommonLineInfo* linfo, int mode)
{
	fprintf(fpt, "thetaIn: %g thetaRef: %g cor: %g\n", linfo->optimumThetaIn*DEGREE, linfo->optimumThetaRef*DEGREE, linfo->optimumCor); 
}

void
lmrcImageCommonLineSearch(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageCommonLineInfo* linfo, int mode) 
{
	mrcImage in2;
	mrcImage ref2;

	/* Prepareing output file */  
	mrcDefaultHeaderValueSet(out);
	out->HeaderN.x = 2*M_PI/linfo->dtheta;
	out->HeaderN.y = 2*M_PI/linfo->dtheta;
	out->HeaderN.z = 1;
	out->HeaderMode = mrcFloatImage;
	out->HeaderLength.x = linfo->dtheta*DEGREE;
	out->HeaderLength.y = linfo->dtheta*DEGREE;
	out->HeaderLength.z = 0;
	mrcInit(out, NULL);
	
	if(lmrcImageCommonLineModeImageCenterIsGC&&mode) {
		lmrcImageShiftCenterOfMassIntoImageCenter(&in2,  in,  mrcPixelHowCubicConv);
		lmrcImageShiftCenterOfMassIntoImageCenter(&ref2, ref, mrcPixelHowCubicConv);
	} else {
		in2  = *in;
		ref2 = *ref;
	}
	switch(linfo->searchMode) {
		case lmrcImageCommonLineSearchModeFourierSpace: {
			lmrcImageCommonLineSearch0(out, &in2, &ref2, linfo, mode);
			break;
		}
		case lmrcImageCommonLineSearchModeRealSpace: {
			lmrcImageCommonLineSearch1(out, &in2, &ref2, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d in lmrcImageCommonLineSearch\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
}

void
lmrcImageCommonLineSearch1(mrcImage* out, mrcImage* in2, mrcImage* ref2, lmrcImageCommonLineInfo* linfo, int mode)
{
	mrcImage in;
	mrcImage tmpIn;
	mrcImage ref;
	mrcImage tmpRef;
	mrcImageParaTypeRealCoord centre;
	lmrcImageSinogramInfo linfo2;

	centre.x = (in2->HeaderN.x-1)/2.0;
	centre.y = (in2->HeaderN.y-1)/2.0;
	centre.z = (in2->HeaderN.z-1)/2.0;
	lmrcImageShift(&tmpIn, in2, centre, mrcPixelHowNearest);
	lmrcImageShift(&tmpRef, ref2, centre, mrcPixelHowNearest);

	DEBUGPRINT("#### Sinogram Create\n");
	linfo2.dphi = linfo->dtheta;	
	lmrcImageSinogramCreate(&in,  &tmpIn,  &linfo2, 0); 
	lmrcImageSinogramCreate(&ref, &tmpRef, &linfo2, 0); 
	DEBUGPRINT("#### Sinogram Correlation Calculation\n");
	lmrcImageSinogramCorrelation(out, &in, &ref, &linfo2, 0);
}

void
lmrcImageCommonLineSearch0(mrcImage* out, mrcImage* in2, mrcImage* ref2, lmrcImageCommonLineInfo* linfo, int mode) 
{
	mrcImage infft;
	mrcImage reffft;

	double thetai;
	double thetaj;

	int i, j, k;
	double re1, im1;
	double re2, im2;
	float Xi, Yi;
	float Xj, Yj;
	double sum1, sum2;
	double cor;
	int count;

	lmrcImageFFT(&infft,  in2, 0);
	lmrcImageFFT(&reffft, ref2, 0);

	linfo->optimumCor = -1;
	for(i=0; i<out->HeaderN.x; i++) {
		thetai = i*linfo->dtheta;
	for(j=0; j<out->HeaderN.y; j++) {
		thetaj = j*linfo->dtheta;
		sum1 = 0;
		sum2 = 0;
		cor  = 0;
		count = 0;
		for(k=MAX(1,reffft.HeaderN.x/2.0/100); k<reffft.HeaderN.x/2.0; k++) {
			Xi = k*cos(thetai);
			Yi = k*sin(thetai);
			Xj = k*cos(thetaj);
			Yj = k*sin(thetaj);
			mrcPixelDataGet(&reffft, Xj, Yj, 0, &re1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&reffft, Xj, Yj, 0, &im1, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataGet(&infft,  Xi, Yi, 0, &re2, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&infft,  Xi, Yi, 0, &im2, mrcPixelImPart, mrcPixelHowNearest);
			
			cor  += (re1*re2 + im1*im2);
			sum1 += (re1*re1 + im1*im1); 
			sum2 += (re2*re2 + im2*im2); 
			count++;
		}
		cor = cor/sqrt(sum1*sum2);
		mrcPixelDataSet(out, i, j, 0, cor, mrcPixelRePart);
		if(linfo->optimumCor <  cor) {
			linfo->optimumCor   = cor;
			linfo->optimumThetaIn  = thetai;
			linfo->optimumThetaRef = thetaj;
			DEBUGPRINT3("%15.6g %15.6g %15.6g\n", thetai*DEGREE, thetaj*DEGREE, cor);
		}
	}
	}
}


