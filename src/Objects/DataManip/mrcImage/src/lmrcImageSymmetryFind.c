/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSymmetryFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSymmetryFind 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSymmetryFind ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "lmrcImageTransformDescartesIntoPolar.h"
#include "lmrcImageSymmetryFind.h"
#include "lmrcImageSubtractionCalc.h"
#include "lDescartesIntoPolar.h"
#include "lmrcImagesStatDataGet.h"
#include "lmrcFFTExpression.h"

void
lmrcImageSymmetryFindAlgorythmPrint(FILE* fpt)
{
	fprintf(fpt, ">> Add\n");
	fprintf(fpt, " Image: Descartes coordinates (2D) -> Polar coordinates (2D) : PolarImage   \n");
	fprintf(fpt, " Shift: Polar coordinates (2D) + Shift(360/n) -> Polar coordinates (2D) : ShiftImage   \n");
	fprintf(fpt, " Add:   AddImage(data2) := PolarImage(data1) + ShiftImage(data1_1)\n");
	fprintf(fpt, " Count: If 0<data1 && 0<data2 && data1*threshold1 <= data2 <= 2*data1 \n");
	fprintf(fpt, "                                 (threshodl1 - 1)*data1_1 <= data1 <= data1_1   \n");
	fprintf(fpt, ">> Correalation\n");
	fprintf(fpt, " Image: Descartes coordinates (2D) -> Polar coordinates (2D) : PolarImage   \n");
	fprintf(fpt, " Correlation: Polar coordinates (2D) -> Polar coordinates (2D) : Correlation\n");
	fprintf(fpt, " Average: each 360/n\n");
}

void
lmrcImageSymmetryFindModePrint(FILE* fpt)
{
	fprintf(fpt, ">>>> check type mode\n");
	fprintf(fpt, "    %d : Check by Add \n", lmrcImageSymmetryFindCheckTypeCheckByAdd);
	fprintf(fpt, "    %d : Check by Correlation \n", lmrcImageSymmetryFindCheckTypeCheckByCorrelation);
	fprintf(fpt, "    %d : Check by Fourier\n", lmrcImageSymmetryFindCheckTypeCheckByFourier);
	fprintf(fpt, "    %d : Check by TTest\n", lmrcImageSymmetryFindCheckTypeCheckByTTest);
	fprintf(fpt, "    %d : Check by SRP\n", lmrcImageSymmetryFindCheckTypeCheckBySRP);

	fprintf(fpt, ">>>> centre type mode\n");
	fprintf(fpt, "    %d : Centre is GC (gravity of centre)\n", lmrcImageSymmetryFindCheckTypeCentreGC);
	fprintf(fpt, "    %d : Centre is Rotational Symmetry\n", lmrcImageSymmetryFindCheckTypeCentreSymmetry);
	fprintf(fpt, "    %d : Centre is at Image Centre \n", lmrcImageSymmetryFindCheckTypeCentreCentre);
	fprintf(fpt, "    %d : Centre is at Image Origin\n", lmrcImageSymmetryFindCheckTypeCentreOrigin);
	

	fprintf(fpt, ">>>> subtrcation type mode\n");
	fprintf(fpt, "    %d : No Subtraction\n",   lmrcImageSymmetryFindCheckTypeNoSubtraction);
	fprintf(fpt, "    %d : Mean Subtraction\n", lmrcImageSymmetryFindCheckTypeMeanSubtraction);
	fprintf(fpt, "    %d : Min Subtraction\n",  lmrcImageSymmetryFindCheckTypeMinSubtraction);
}

void
lmrcImageSymmetryCentreFind(mrcImage* in, DescartesCoord* centre, int mode)
{
	switch(mode) {
		case lmrcImageSymmetryFindCheckTypeCentreGC: {
			lmrcImageSymmetryCentreFindGC(in, centre, mode);
			break;
		}
		case lmrcImageSymmetryFindCheckTypeCentreSymmetry: {
			lmrcImageSymmetryCentreFindSymmetry(in, centre, mode);
			break;
		}
		case lmrcImageSymmetryFindCheckTypeCentreCentre: {
            centre->x = in->HeaderN.x/2+1;
			centre->y = in->HeaderN.y/2+1;
			centre->z = in->HeaderN.z/2+1;
			break;
		}
		case lmrcImageSymmetryFindCheckTypeCentreOrigin: {
			centre->x = 0;
			centre->y = 0;
			centre->z = 0;
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in lmrcImageSymmetryCentreFind: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

void

lmrcImageSymmetryCentreFindSymmetry(mrcImage* in, DescartesCoord* centre, int mode)
{
	fprintf(stderr, "Not supported: pre\n");
}

void
lmrcImageSymmetryCentreFindGC(mrcImage* in, DescartesCoord* centre, int mode)
{
	DescartesCoord d, c, cMin, cMax, optimum;
	double est, tmp;
	mrcImageParaTypeReal x, y, z;
	int nR, iR;
	double* R;
	double* RR;
	double* N;
	double radius;
	int iradius;
	double data;
	int flag;

	nR = MIN(in->HeaderN.x/2, in->HeaderN.y/2);
	R   = (double*)memoryAllocate(sizeof(double)*nR, "in lmrcImageSymmetryCentreFind"); 
	RR  = (double*)memoryAllocate(sizeof(double)*nR, "in lmrcImageSymmetryCentreFind"); 
	N   = (double*)memoryAllocate(sizeof(double)*nR, "in lmrcImageSymmetryCentreFind"); 

	d.x = MAX(1,(int)(in->HeaderN.x/4));
	d.y = MAX(1,(int)(in->HeaderN.y/4));
	d.z = MAX(1,(int)(in->HeaderN.z/4));

	cMin.x = cMin.y = cMin.z = 0;
	cMax.x = in->HeaderN.x;
	cMax.y = in->HeaderN.y;
	cMax.z = in->HeaderN.z;

	optimum = cMin;

	est = 1.79769313486231470e+308;
	flag = 2;
	while(flag) {
		for(c.x=cMin.x; c.x<cMax.x; c.x+=d.x) {
		for(c.y=cMin.y; c.y<cMax.y; c.y+=d.y) {
		for(c.z=cMin.z; c.z<cMax.z; c.z+=d.z) {
			for(iR=0; iR<nR; iR++) {
				R[iR] = 0;
				RR[iR] = 0;
				N[iR] = 0;
			}

			for(x=0;x<in->HeaderN.x;x++) {
			for(y=0;y<in->HeaderN.y;y++) {
			for(z=0;z<in->HeaderN.z;z++) {
				radius = MIN(SQR(fabs(x-c.x)), SQR(in->HeaderN.x-fabs(x-c.x)))
					   + MIN(SQR(fabs(y-c.y)), SQR(in->HeaderN.y-fabs(y-c.y)));
				if(0<radius) {
					radius = sqrt(radius);
				} else {
					radius = 0;
				}
				iradius = (int)radius;
				if(iradius<nR) {
					mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
					R[iradius]  += data; 
					RR[iradius] += SQR(data); 
					N[iradius]++;
				} 
			}
			}
			}

			tmp = 0;
			for(iR=0; iR<nR; iR++) {
				double tmp2;
				if(0<N[iR])  {
					tmp2 = RR[iR]/N[iR] - SQR(R[iR]/N[iR]);
					if(tmp2<0) {
						DEBUGPRINT("Something Wrong\n");
						tmp2 = 0;
					}
					tmp += tmp2;
				}
			}
			if(0<tmp) {
				tmp = sqrt(tmp);
			} else {
				tmp = 0.0;
			}

			if(tmp<est) {
				optimum.x = c.x;
				optimum.y = c.y;
				optimum.z = c.z;
				est = tmp;
				DEBUGPRINT4("Est Down to %lf at %f %f %f\n", est, c.x, c.y, c.z);
			} else {
				DEBUGPRINT4("Est %lf at %f %f %f\n", tmp, c.x, c.y, c.z);
			}
		}
		}
		}
		
		cMin.x = MAX(0, optimum.x-d.x);
		cMax.x = MIN(in->HeaderN.x, optimum.x+d.x);
		d.x    = MAX(1,(int)(d.x/4));
		cMin.y = MAX(0, optimum.y-d.y);
		cMax.y = MIN(in->HeaderN.y, optimum.y+d.y);
		d.y    = MAX(1,(int)(d.y/4));
		cMin.z = MAX(0, optimum.z-d.z);
		cMax.z = MIN(in->HeaderN.z, optimum.z+d.z);
		d.z    = MAX(1,(int)(d.z/4));

		if(d.x==1 && d.y==1 && d.z==1) flag--;
	}
	*centre = optimum;
}

/*
	lmrcImageSymmetryFind
*/

void
lmrcImageSymmetryFind(mrcImage* in, lmrcImageSymmetryFindInfo* linfo, int mode)
{
	//lmrcImageSymmetryCentreFind(in, &linfo->centre, linfo->centreMode);	

	floatVectorInit(&(linfo->Value), linfo->maxNfold+1);
	floatVectorInit(&(linfo->Point), linfo->maxNfold+1);

    if(mode & lmrcImageSymmetryFindCheckTypeCheckByAdd) {
		DEBUGPRINT("Call lmrcImageSymmetryFindCheckByAdd\n");
        lmrcImageSymmetryFindCheckByAdd(in, linfo, mode);
		lmrcImageSymmetryFindResultOut(linfo->fptOut, in, linfo, lmrcImageSymmetryFindCheckTypeCheckByAdd);
    }
    if(mode & lmrcImageSymmetryFindCheckTypeCheckByCorrelation) {
		lmrcImageSymmetryFindCheckByCorrelation(in,linfo, mode);
		lmrcImageSymmetryFindResultOut(linfo->fptOut, in, linfo, lmrcImageSymmetryFindCheckTypeCheckByCorrelation);
    }
    if(mode & lmrcImageSymmetryFindCheckTypeCheckByFourier) {
		lmrcImageSymmetryFindCheckByFourier(in, linfo, mode);
		lmrcImageSymmetryFindResultOut(linfo->fptOut, in, linfo, lmrcImageSymmetryFindCheckTypeCheckByFourier);
    }       
    if(mode & lmrcImageSymmetryFindCheckTypeCheckByTTest) {
		lmrcImageSymmetryFindCheckByTTest(in, linfo, mode);
		lmrcImageSymmetryFindResultOut(linfo->fptOut, &(linfo->Image), linfo, lmrcImageSymmetryFindCheckTypeCheckByTTest);
    }       
    if(mode & lmrcImageSymmetryFindCheckTypeCheckBySRP) {
		lmrcImageSymmetryFindCheckBySRP(in, linfo, mode);
		lmrcImageSymmetryFindResultOut(linfo->fptOut, &(linfo->Image), linfo, lmrcImageSymmetryFindCheckTypeCheckBySRP);
    }       
		
}

void
lmrcImageSymmetryFindResultOut(FILE* fpt, mrcImage* in, lmrcImageSymmetryFindInfo* linfo,  int mode)
{
	double min, max;
	int    maxn;
	int    i;
	int    symn;
	char   filename[1024];

	max = min = linfo->Value.data[2];
	maxn = linfo->minNfold;
	for(i=linfo->minNfold; i<linfo->maxNfold; i++) {
		if(max<linfo->Value.data[i]) {
			max = linfo->Value.data[i];
			maxn = i;
		}
		if(linfo->Value.data[i]<min) {
			min = linfo->Value.data[i];
		}
	}	


	if(max<min) {
		fprintf(stderr, "Something wrong in lmrcImageSymmetryFindCheckResultOut: max <= min\n");
		exit(EXIT_FAILURE);
	}

	for(i=linfo->minNfold; i<=linfo->maxNfold; i++) {
		linfo->Point.data[i] = 100*(linfo->Value.data[i] - min)/(max - min);
        fprintf(fpt, "%2d -> value: %f point: %f\n",i,linfo->Value.data[i],linfo->Point.data[i]);
	}

    symn=maxn;
    for(i=linfo->minNfold;i*maxn<=linfo->maxNfold;i++){
        if(linfo->Point.data[maxn]*linfo->threshold2<=linfo->Point.data[i*maxn]) {
            symn=i*maxn;
		}
    }
	linfo->Symmetry = symn;

    fprintf(fpt, "Symmetry number %d.(Check by add, ", symn);
    switch(linfo->subtractionMode) {
		case lmrcImageSymmetryFindCheckTypeNoSubtraction: {
        	fprintf(fpt, "NoSubtraction");
			break;
		}
		case lmrcImageSymmetryFindCheckTypeMeanSubtraction:  {
        	fprintf(fpt, "MeanSubtraction");
			break;
    	}
		case lmrcImageSymmetryFindCheckTypeMinSubtraction: {
			fprintf(fpt, "MinSubtraction");
			break;
		}
    }
	fprintf(fpt, ")\n");
	fprintf(fpt, "Centre: %f %f %f\n", linfo->centre.x, linfo->centre.y, linfo->centre.z);
	if(linfo->flagAvg) {
		lmrcImageSymmetryAverage(&(linfo->avg), in, symn, linfo->centre, 0);
		mrcFileWrite(&(linfo->avg), linfo->avgName, "in lmrcImageSymmetryFindResultOut", 0);
		sprintf(filename, "%s.%02d", linfo->avgName, mode);   
		mrcFileWrite(&(linfo->avg), filename, "in lmrcImageSymmetryFindResultOut", 0);
	}
}

/*
	lmrcImageSymmetryFindCheckByTTest
		Method A: Student T

	lmrcImageSymmetryFindCheckBySRP
		Method B: spectral ratio product (SRP)
	From: 
	Kocsis,E Cerritelli,ME, Trus,BL, Cheng,N, and Steven,AC: Ultramicroscopy 60 (1965) 219-228.
		Improved methods for determination of rotational symmetries in macromolecules
*/

void
lmrcImageSymmetryFindCheckByTTest(mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode)
{
    int x,y, z;
    int i,j;
    int maxn,symn;
    double data1,data2,normal;
	double data3, data4, sum;
    double delta;
    lmrcImageTransformDescartesIntoPolarInfo linfo;
    lDescartesIntoPolarInfo                  linfo2;

	mrcImageParaTypeRealCoord centre;
	mrcImage residue;
	mrcImage subout;
	mrcImage polarout;
	mrcImage* subouts;
	mrcImage* polarouts;
	mrcImage* fftouts;
	mrcImage* powouts;
	mrcImage* pow1douts;
	mrcImage* suboutBacks;
	mrcImage* polaroutBacks;
	mrcImage* fftoutBacks;
	mrcImage* powoutBacks;
	mrcImage* pow1doutBacks;
	mrcImage  prob;
	mrcImage  ttest;
	double ymin, ymax;

	lmrcImageSymmetryFindSubtraction(&subout, in, info, mode);
	subouts = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagImages, "in lmrcImageSymmetryFindTTest");
	for(i=0; i<info->flagImages; i++) {
		lmrcImageSymmetryFindSubtraction(&(subouts[i]), &(info->Images[i]), info, mode); 	
	}
	suboutBacks = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagBacks, "in lmrcImageSymmetryFindTTest");
	for(i=0; i<info->flagBacks; i++) {
		lmrcImageSymmetryFindSubtraction(&(suboutBacks[i]), &(info->Backs[i]), info, mode); 	
	}

	/* Transform Descartes Coordinates Into Polar Coordinates */
    linfo.dr   = info->dr;
    linfo.dphi = info->dtheta;
    linfo.flagDescartesIntoPolarInfo     = 0;
    linfo.flagrWeight                    = 0;
	linfo.axisInfo = info->centreInfo;

	for(i=info->minNfold; i<=info->maxNfold; i++) {
		DEBUGPRINT1("%d-fold Start\n", i)
		if(1<i && info->centreMode==lmrcImageSymmetryFindCheckTypeCentreSymmetry) {
			linfo.nRotationalSymmetry = i;
    		linfo.flagImageCentreIsGravityCentre = 0;
			linfo.flagRotationalSymmetry         = 1;
			linfo.flagCentre                     = 0;
		} else {
    		linfo.flagImageCentreIsGravityCentre = 1;
			linfo.flagRotationalSymmetry         = 0;
			linfo.flagCentre                     = 0;
		}
    	lmrcImageTransformDescartesIntoPolar(&polarout, &subout, &linfo, &linfo2, 0);
		DEBUGPRINT3("%d %d %d\n", polarout.HeaderN.x, polarout.HeaderN.y, polarout.HeaderN.z);
    	linfo.flagImageCentreIsGravityCentre = 0;
		linfo.flagRotationalSymmetry         = 0;
		linfo.flagCentre                     = 1;	
		linfo.Centre.x                       = linfo2.centre.x;
		linfo.Centre.y                       = linfo2.centre.y;
		linfo.Centre.z                       = linfo2.centre.z;

		polarouts = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagImages, "in lmrcImageSymmetryFindTTest");
		fftouts = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagImages, "in lmrcImageSymmetryFindTTest");
		powouts = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagImages, "in lmrcImageSymmetryFindTTest");
		pow1douts = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagImages, "in lmrcImageSymmetryFindTTest");
		for(j=0; j<info->flagImages; j++) {
			lmrcImageTransformDescartesIntoPolar(&(polarouts[j]), &(subouts[j]), &linfo, &linfo2, 0);
			lmrcImageFFTFirstDimensionOnly(&(fftouts[j]), &(polarouts[j]), 0);

			/* Projection */
			pow1douts[j].Header    = fftouts[j].Header;
			pow1douts[j].HeaderN.x = fftouts[j].HeaderN.x/2.0 + 1;
			pow1douts[j].HeaderN.y = 1;
			pow1douts[j].HeaderN.z = 1;
			pow1douts[j].HeaderMode = mrcFloatImage;
			mrcInit(&(pow1douts[j]), NULL);
			
			if(info->rmin<=info->rmax) {
				ymin = info->rmin;
				ymax = info->rmax;
			} else {
				ymin = 0;
				ymax = fftouts[j].HeaderN.y-1;
			}
			for(x=0; x<pow1douts[j].HeaderN.x; x++) { 
				sum = 0.0;
				for(y=ymin; y<=ymax; y++) {
					mrcPixelDataGet(&(fftouts[j]), x, y, 0.0, &data1, mrcPixelPow, mrcPixelHowNearest);  
					sum += data1*y;
				}
				mrcPixelDataSet(&(pow1douts[j]), x, 0.0, sum, sum, mrcPixelRePart); 
			}

			/* Normalization */
			for(y=0; y<pow1douts[j].HeaderN.y; y++) { 
				sum = 0.0;
				for(x=0; x<=fftouts[j].HeaderN.x/2.0; x++) {
					mrcPixelDataGet(&(fftouts[j]), x, y, 0.0, &data1, mrcPixelPow, mrcPixelHowNearest);  
					sum += data1;
				}
				for(x=0; x<=fftouts[j].HeaderN.x/2.0; x++) {
					mrcPixelDataGet(&(fftouts[j]), x, y, 0.0, &data1, mrcPixelPow, mrcPixelHowNearest);  
					mrcPixelDataSet(&(fftouts[j]), x, y, 0.0, data1/sum, mrcPixelPow);
				}
			}
			lmrcFFTExpression(&(powouts[j]), &(fftouts[j]), 0, 2);

			/* Memory Free */
			mrcImageFree(&(polarouts[j]), "polarouts");
			mrcImageFree(&(fftouts[j]), "fftouts");
		}
		memoryFree(polarouts);
		memoryFree(fftouts);

		polaroutBacks = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagBacks, "in lmrcImageSymmetryFindTTest");
		fftoutBacks = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagBacks, "in lmrcImageSymmetryFindTTest");
		powoutBacks = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagBacks, "in lmrcImageSymmetryFindTTest");
		pow1doutBacks = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagBacks, "in lmrcImageSymmetryFindTTest");
		for(j=0; j<info->flagBacks; j++) {
			lmrcImageTransformDescartesIntoPolar(&(polaroutBacks[j]), &(suboutBacks[j]), &linfo, &linfo2, 0);
			lmrcImageFFTFirstDimensionOnly(&(fftoutBacks[j]), &(polaroutBacks[j]), 0);

			/* Projection */
			pow1doutBacks[j].Header    = fftoutBacks[j].Header;
			pow1doutBacks[j].HeaderN.x = fftoutBacks[j].HeaderN.x/2.0 + 1;
			pow1doutBacks[j].HeaderN.y = 1;
			pow1doutBacks[j].HeaderN.z = 1;
			pow1doutBacks[j].HeaderMode = mrcFloatImage;
			mrcInit(&(pow1doutBacks[j]), NULL);
			for(x=0; x<pow1doutBacks[j].HeaderN.x; x++) { 
				sum = 0.0;
				for(y=0; y<fftoutBacks[j].HeaderN.y; y++) {
					mrcPixelDataGet(&(fftoutBacks[j]), x, y, 0.0, &data1, mrcPixelPow, mrcPixelHowNearest);  
					sum += data1*y;
				}
				mrcPixelDataSet(&(pow1doutBacks[j]), x, 0.0, sum, sum, mrcPixelRePart); 
			}
	
			/* Normalization */
			for(y=0; y<pow1doutBacks[j].HeaderN.y; y++) { 
				sum = 0.0;
				for(x=0; x<=fftoutBacks[j].HeaderN.x/2.0; x++) {
					mrcPixelDataGet(&(fftoutBacks[j]), x, y, 0.0, &data1, mrcPixelPow, mrcPixelHowNearest);  
					sum += data1;
				}
				for(x=0; x<=fftoutBacks[j].HeaderN.x/2.0; x++) {
					mrcPixelDataGet(&(fftoutBacks[j]), x, y, 0.0, &data1, mrcPixelPow, mrcPixelHowNearest);  
					mrcPixelDataSet(&(fftoutBacks[j]), x, y, 0.0, data1/sum, mrcPixelPow);
				}
			}
			lmrcFFTExpression(&(powoutBacks[j]), &(fftoutBacks[j]), 0, 2);

			/* Memory Free */
			mrcImageFree(&(polaroutBacks[j]), "polaroutBacks");
			mrcImageFree(&(fftoutBacks[j]), "fftoutBacks");
		}
		memoryFree(polaroutBacks);
		memoryFree(fftoutBacks);

		lmrcImagesTTest(&prob, &ttest, powouts, info->flagImages, powoutBacks, info->flagBacks, 1);
#ifdef DEBUG
		{
			char s[1024];
			sprintf(s, "/tmp/ttest.%02d", i);
			mrcFileWrite(&ttest, s, "in lmrcImageSymmmetryFindTTest", 0);
			sprintf(s, "/tmp/ttestp.%02d", i);
			mrcFileWrite(&prob, s, "in lmrcImageSymmmetryFindTTest", 0);
		}
#endif
		mrcPixelDataGet(&prob,  i, 0, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);  
		lmrcImagesTTest(&prob, &ttest, pow1douts, info->flagImages, pow1doutBacks, info->flagBacks, 1);
		mrcPixelDataGet(&ttest, i, 0, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);  
		info->Value.data[i] = data1;
		DEBUGPRINT3("fold: %d prob: %g t: %g\n", i, data1, data2)
	
		/* Image Area Free */
		for(j=0; j<info->flagImages; j++) {
			mrcImageFree(&(powouts[j]), "powouts");
			mrcImageFree(&(pow1douts[j]), "powouts");
		}
		memoryFree(powouts);
		memoryFree(pow1douts);

		for(j=0; j<info->flagBacks; j++) {
			mrcImageFree(&(pow1doutBacks[j]), "powoutBacks");
		}
		memoryFree(powoutBacks);
		memoryFree(pow1doutBacks);
	}
}

void
lmrcImageSymmetryFindCheckBySRP(mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode)
{
	fprintf(stderr, "Not yet supported in lmrcImageSymmetryFindCheckBySRP\n");
	exit(EXIT_FAILURE);
}

/*
	Subtraction
*/
void
lmrcImageSymmetryFindSubtraction(mrcImage* subout, mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode)
{
	switch(info->subtractionMode) {
		case lmrcImageSymmetryFindCheckTypeNoSubtraction: {
			*subout = *in;
			break;
		}
		case lmrcImageSymmetryFindCheckTypeMeanSubtraction: {
        	lmrcImageMeanSubtraction(subout,in);
			break;
		}
    	case lmrcImageSymmetryFindCheckTypeMinSubtraction: {
        	lmrcImageMinSubtraction(subout,in);
			break;
		}
		default: {
			fprintf(stderr, "Not supported SubtractionMode %d\n", info->subtractionMode);
			exit(EXIT_FAILURE);
		}
   	} 
}

/*
	From: 
	Crowther, RA and Amos, LA: J. Mol. Biol. (1971) 60, 123-130
		Harmonic Analysis of Electron Microscope Images with Rotational Symmetry
*/

void
lmrcImageSymmetryFindCheckByFourier(mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode)
{

    mrcImage subout;
	mrcImage polarout;
	mrcImage onedimout;
	mrcImage* subouts;
	mrcImage* polarouts;
	mrcImage* onedimouts;
	mrcImage* suboutBacks;
	mrcImage* polaroutBacks;
	mrcImage* onedimoutBacks;

    int x,y;
    int i;
    double data1,data2;
    lmrcImageTransformDescartesIntoPolarInfo linfo;
    lDescartesIntoPolarInfo                  linfo2;
	double ymin, ymax;

	DEBUGPRINT("lmrcImageSymmetryFindCheckByFourierStart\n");
	/* Subtraction */
	lmrcImageSymmetryFindSubtraction(&subout, in, info, mode);

/*
	DEBUGPRINT1("flagImages: %d\n", info->flagImages);	
	DEBUGPRINT1("flagBacks:  %d\n", info->flagBacks);	
	subouts = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagImages, "in lmrcImageSymmetryFindTTest");
	for(i=0; i<info->flagImages; i++) {
		lmrcImageSymmetryFindSubtraction(&(subouts[i]), &(info->Images[i]), info, mode); 	
	}
	suboutBacks = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info->flagBacks, "in lmrcImageSymmetryFindTTest");
	for(i=0; i<info->flagBacks; i++) {
		lmrcImageSymmetryFindSubtraction(&(suboutBacks[i]), &(info->Backs[i]), info, mode); 	
	}
*/
	/* Transform Descartes Coordinates Into Polar Coordinates */
    linfo.dr   = info->dr;
    linfo.dphi = info->dtheta;
    linfo.flagrWeight                    = 0;
	linfo.axisInfo = info->centreInfo;

    linfo.flagRotationalSymmetry         = 0;
    linfo.flagImageCentreIsGravityCentre = 0;
    linfo.flagCentre                     = 0;

    switch(info->centreMode) {
        case lmrcImageSymmetryFindCheckTypeCentreGC: {
            lmrcImageSymmetryCentreFind(in, &info->centre, info->centreMode);   
            linfo.flagCentre                 = 1;
            linfo.Centre.x = info->centre.x;
            linfo.Centre.y = info->centre.y;
            linfo.Centre.z = info->centre.z;
            break;
        }   
        case lmrcImageSymmetryFindCheckTypeCentreSymmetry: { 
            linfo.flagRotationalSymmetry = 1;
            break;
        }   
        default: {
            lmrcImageSymmetryCentreFind(in, &info->centre, info->centreMode);   
            linfo.flagCentre                 = 1;
            linfo.Centre.x = info->centre.x;
            linfo.Centre.y = info->centre.y;
            linfo.Centre.z = info->centre.z;
            break;
        }   
    }          
    linfo.flagDescartesIntoPolarInfo     = 0;
    linfo.flagrWeight                    = 1;

	/* Fourier Component */
	for(i=info->minNfold; i<=info->maxNfold; i++) {
		DEBUGPRINT1("%d-fold Start\n", i)
		if(1<i && info->centreMode==lmrcImageSymmetryFindCheckTypeCentreSymmetry) {
			linfo.nRotationalSymmetry = i;
    		linfo.flagImageCentreIsGravityCentre = 0;
			linfo.flagRotationalSymmetry         = 1;
			linfo.flagCentre                     = 0;
		}
    	lmrcImageTransformDescartesIntoPolar(&polarout, &subout, &linfo, &linfo2, 0);
		DEBUGPRINT3("%d %d %d\n", polarout.HeaderN.x, polarout.HeaderN.y, polarout.HeaderN.z);

		/* Fourier Transform */
		lmrcImageFFTFirstDimensionOnly(&(info->fourier), &polarout, 0);
		info->flagFourier = 1;
		info->Value.data[i] = 0;

		if(info->rmin<=info->rmax) {
			ymin = info->rmin;
			ymax = info->rmax;
		} else {
			ymin = 0;
			ymax = info->fourier.HeaderN.y-1;
		}
		for(y=ymin; y<ymax; y++) { 
			mrcPixelDataGet(&(info->fourier), i, y, 0, &data1, mrcPixelPow, mrcPixelHowNearest);
			DEBUGPRINT3("%f at ( %d, %d)\n", data1, i, y);
			info->Value.data[i] += data1*y;
		}
	}
}

void
lmrcImageSymmetryFindCheckByAdd(mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode)
{
    mrcImage subout,polarout,shiftout;
    mrcImageParaTypeRealCoord shift;
    int x,y;
    int i;
    double data1,data2, ave;
    lmrcImageTransformDescartesIntoPolarInfo linfo;
    lDescartesIntoPolarInfo                  linfo2;
	double ymin, ymax;
	
	DEBUGPRINT("Start lmrcImageSymmetryFindCheckByAdd ---- \n");


	/* Subtraction */
	lmrcImageSymmetryFindSubtraction(&subout, in, info, mode);
    shift.y=0;
    shift.z=0;
    linfo.dr                             = info->dr;
    linfo.dphi                           = info->dtheta;

	linfo.flagRotationalSymmetry         = 0;
	linfo.flagImageCentreIsGravityCentre = 0;
	linfo.flagCentre 					 = 0;

	switch(info->centreMode) {
		case lmrcImageSymmetryFindCheckTypeCentreGC: {
			lmrcImageSymmetryCentreFind(in, &info->centre, info->centreMode);	
			linfo.flagCentre 				 = 1;
			linfo.Centre.x = info->centre.x;
			linfo.Centre.y = info->centre.y;
			linfo.Centre.z = info->centre.z;
			break;
		}
		case lmrcImageSymmetryFindCheckTypeCentreSymmetry: { 
		    linfo.flagRotationalSymmetry = 1;
			break;
		}
		default: {
			lmrcImageSymmetryCentreFind(in, &info->centre, info->centreMode);	
			linfo.flagCentre 				 = 1;
			linfo.Centre.x = info->centre.x;
			linfo.Centre.y = info->centre.y;
			linfo.Centre.z = info->centre.z;
			break;
		}
	}		
    linfo.flagDescartesIntoPolarInfo     = 0;
    linfo.flagrWeight                    = 1;

    lmrcImageTransformDescartesIntoPolar(&polarout, &subout, &linfo, &linfo2, 0);

	if(info->rmin<=info->rmax) {
		ymin = info->rmin;
		ymax = info->rmax;
	} else {
		ymin = 0;
		ymax = polarout.HeaderN.y-1;
	}
    for(i=info->minNfold; i<=info->maxNfold; i++) {
        info->Value.data[i]=0;
        shift.x=2*M_PI/info->dtheta/i+0.5;
		shift.y=0;
		shift.z=0;
        lmrcImageShift(&shiftout,&polarout,shift,mrcPixelHowLinear);
#ifdef DEBUG
	{
			char s[1024];
			sprintf(s, "/tmp/polar-%04d.mrc", i);
			mrcFileWrite(&polarout, s, "in ByAdd", 0); 
			sprintf(s, "/tmp/shift-%04d.mrc", i);
			mrcFileWrite(&shiftout, s, "in ByAdd", 0); 
	}
#endif
        llmrcImageAdd (&shiftout,&polarout);            /*in1=in1+in2*/

        for(x=0;x<polarout.HeaderN.x;x++){
            for(y=ymin;y<=ymax;y++){
                mrcPixelDataGet(&polarout, x,y,0,&data1,mrcPixelRePart,mrcPixelHowNearest);
                mrcPixelDataGet(&shiftout, x,y,0,&data2,mrcPixelRePart,mrcPixelHowNearest);
				ave = data2/2.0;
                if(0<data1 && 0<data2 && data1*info->threshold1 <= data2 && data2<= data1*2) {
                    info->Value.data[i]++;
                } else if(data1<0 && data2<0 && -1*data1*info->threshold1 <= -1*data2 && -1*data2<= -1*data1*2) {
                    info->Value.data[i]++;
                }
            }
        }
        DEBUGPRINT1("Finish until %2d.\n",i);
    }
	info->centre.x = linfo.Centre.x;
	info->centre.y = linfo.Centre.y;
	info->centre.z = linfo.Centre.z;
}


void
lmrcImageSymmetryFindCheckByCorrelation(mrcImage* in, lmrcImageSymmetryFindInfo* info, int mode)
{
    mrcImage subout,polarout,onedimout;
    int x,y;
    int i,j;
    double data1,data2,normal;
    double delta;
    lmrcImageTransformDescartesIntoPolarInfo linfo;
    lDescartesIntoPolarInfo                  linfo2;
	doubleVector sum;
	double ymin, ymax;

	/* Subtraction */
	lmrcImageSymmetryFindSubtraction(&subout, in, info, mode);

	doubleVectorInit(&sum, info->maxNfold+1);

	/* Transform Descartes coordinates into Polar coordinates */
    linfo.dr   = info->dr;
    linfo.dphi = info->dtheta;

   	linfo.flagRotationalSymmetry         = 0;
    linfo.flagImageCentreIsGravityCentre = 0;
    linfo.flagCentre                     = 0;

    switch(info->centreMode) {
        case lmrcImageSymmetryFindCheckTypeCentreGC: {
            lmrcImageSymmetryCentreFind(in, &info->centre, info->centreMode);   
            linfo.flagCentre                 = 1;
            linfo.Centre.x = info->centre.x;
            linfo.Centre.y = info->centre.y;
            linfo.Centre.z = info->centre.z;
            break;
        }   
        case lmrcImageSymmetryFindCheckTypeCentreSymmetry: { 
			fprintf(stderr, "Not supported for this algorythm.\n");
			exit(EXIT_FAILURE);
			break;
		}
        default: {
            lmrcImageSymmetryCentreFind(in, &info->centre, info->centreMode);   
            linfo.flagCentre                 = 1;
            linfo.Centre.x = info->centre.x;
            linfo.Centre.y = info->centre.y;
            linfo.Centre.z = info->centre.z;
            break;
        }   
    }          
    linfo.flagDescartesIntoPolarInfo     = 0;
    linfo.flagrWeight                    = 1;

    lmrcImageTransformDescartesIntoPolar(&polarout, &subout, &linfo, &linfo2, 0);

	switch(info->centreMode) {
		case  lmrcImageSymmetryFindCheckTypeCentreSymmetry: {
			linfo.Centre.x = linfo2.centre.x;
			linfo.Centre.y = linfo2.centre.y;
			linfo.Centre.z = linfo2.centre.z;
			break;
		}
		default:
			break;
	}
	/* Projection along radial axis */	
    onedimout.Header=polarout.Header;
    onedimout.HeaderN.y=1;
    mrcInit(&onedimout,NULL);
    data2=0;


	if(info->rmin<=info->rmax) {
		ymin = info->rmin;
		ymax = info->rmax;
	} else {
		ymin = 0;
		ymax = polarout.HeaderN.y-1;
	}

    for(x=0;x<polarout.HeaderN.x;x++) {
        for(y=ymin;y<=ymax;y++) {
            mrcPixelDataGet(&polarout,x,y,0,&data1,mrcPixelRePart,mrcPixelHowNearest);
            data2+=data1*y;
        }
        mrcPixelDataSet(&onedimout,x,0,0,data2,mrcPixelRePart);
        data2=0;
    }

	/* Correlation */
    info->correlation.Header=onedimout.Header;
    mrcInit(&(info->correlation),NULL);
	info->flagCorrelation = 1;
    lmrcImageCorrelation(&(info->correlation),&onedimout,&onedimout,0);

	/* Normalization */
    mrcPixelDataGet(&(info->correlation),0,0,0,&normal,mrcPixelRePart,mrcPixelHowNearest);
    for(x=0;x<info->correlation.HeaderN.x;x++){
        mrcPixelDataGet(&(info->correlation),x,0,0,&data1,mrcPixelRePart,mrcPixelHowNearest);
        mrcPixelDataSet(&(info->correlation),x,0,0,data1/normal,mrcPixelRePart);
    }
    mrcStatDataSet(&(info->correlation),0);

    for(i=info->minNfold;i<=info->maxNfold;i++) {
        sum.data[i]=0;
        delta=(int)(2.0*M_PI/info->dtheta/i+0.5);
        for(j=1;j<i;j++){
            mrcPixelDataGet(&(info->correlation),delta*j,0,0,&data1,mrcPixelRePart,mrcPixelHowNearest);
            sum.data[i]+=data1;
        }
    }

	info->Value.data[1] = 1.0;
    for(i=info->minNfold;i<=info->maxNfold;i++) {
      info->Value.data[i] = sum.data[i]/(i-1);
    }
}

void
lmrcImageSymmetryAverage(mrcImage* out, mrcImage* in, int num, DescartesCoord centre, int mode) 
{
	int i;
	float x, y, z;
	float sx, sy, sz;
	double r, angle, data1, data2;

	out->Header = in->Header;
	mrcInit(out, NULL);
	
	for(z=0; z<out->HeaderN.z; z++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(x=0; x<out->HeaderN.x; x++) {
		r = sqrt(SQR(MIN(fabs(x - centre.x), fabs(x - out->HeaderN.x - centre.x)))
		       + SQR(MIN(fabs(y - centre.y), fabs(y - out->HeaderN.y - centre.y))));
		angle = atan2(y-centre.y, x-centre.x);
		for(i=0; i<num; i++) {
			sx = centre.x + r*cos(angle+i*2*M_PI/num);
			sy = centre.y + r*sin(angle+i*2*M_PI/num);
			sz = 0;
			mrcPixelDataGet(out, x,  y,  z, &data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, sx, sy, sz, &data2, mrcPixelRePart, mrcPixelHowCubicConv);
			mrcPixelDataSet(out, x,  y, z,  data1+data2, mrcPixelRePart);
		}
	}
	}
	}
}

