/*
# mrcMaskedImageInfo : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcMaskedImageInfo
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
#include "mrcImage.h"

typedef struct lmrcMaskedImageInfoInfo {
    // in
	double MaskedValue;
    double epsilon;
    int nQuantile;
    // out
    double avg;
    double var;
    double sd;
    double skewness;
    double kurtosis;
    double kurtosis2;
    double area;
    double median;
    double min;
    double max;
    double Q1;
    double Q2;
    double Q3;
    double* nQ;
    int N;
} lmrcMaskedImageInfoInfo;

typedef enum lmrcMaskedImageInfoMode {
	a=0,
	b=1
} lmrcMaskedImageInfoMode;

extern void lmrcMaskedImageInfo(mrcImage* in, lmrcMaskedImageInfoInfo* linfo, int mode);
extern void lmrcMaskedImageInfoPrint(FILE* fpt, lmrcMaskedImageInfoInfo* linfo, int mode);

static int __compare(const void* a, const void* b)
{
    double dif;
    dif = *(double*)a - *(double*)b;
    if(dif<0) {
        return -1;
    } else if(0<dif) {
        return +1;
    } else {
        return 0;
    }
}

void 
lmrcMaskedImageInfo(mrcImage* in, lmrcMaskedImageInfoInfo* linfo, int mode)
{
    mrcImageParaTypeReal x, y, z;
    double data;
    double sum, sum2, sum3, sum4;
    int n, i;
    double* vec;


    DEBUGPRINT("Average/N/AREA\n");
    sum = 0;
    n = 0;
    linfo->min = +FLT_MAX;
    linfo->max = -FLT_MAX;
    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(linfo->epsilon < fabs(data-linfo->MaskedValue)) {
            sum += data;
            n++;
        }
    }
    }
    }
    linfo->N = n;
    linfo->avg = sum/n;
    linfo->area = ((double)n)/((double)in->HeaderN.x*in->HeaderN.y*in->HeaderN.z);
    

    DEBUGPRINT("MEDIAN/SORT/N-QUANTILE\n");
    vec = (double*)malloc(sizeof(double)*n); 
    if(vec==NULL) { 
        fprintf(stderr, "Not Allocated: %d\n", n); 
        exit(EXIT_FAILURE); 
    }

    n = 0;
    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(linfo->epsilon < fabs(data-linfo->MaskedValue)) {
            vec[n] = data;
            n++;
        }
    }
    }
    }
    qsort(vec, n, sizeof(double), __compare);
    if(n%2) {
        linfo->median = vec[(n-1)/2];
    } else {
        linfo->median = (vec[n/2]+vec[n/2+1])/2;
    } 
    linfo->Q1 = vec[n/4];
    linfo->Q2 = linfo->median;
    linfo->Q3 = vec[3*n/4];
    
    linfo->nQ = (double*)malloc(sizeof(double)*linfo->nQuantile);
    if(linfo->nQ==NULL) { 
        fprintf(stderr, "Not Allocated: %d\n", linfo->nQuantile); 
        exit(EXIT_FAILURE); 
    }
    linfo->min = vec[0];
    linfo->max = vec[n-1];
    for(i=0; i<linfo->nQuantile-1; i++) {
        linfo->nQ[i] = vec[linfo->N*(i+1)/linfo->nQuantile];
    }

    DEBUGPRINT("SD\n");
    sum2 = 0;
    n = 0;
    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(linfo->epsilon < fabs(data-linfo->MaskedValue)) {
            sum2 += SQR(data-linfo->avg);
            n++;
        }
    }
    }
    }
    linfo->sd = sqrt(sum2/n);

    DEBUGPRINT("Skew/Kurtosis\n");
    sum3 = 0;
    sum4 = 0;
    n = 0;
    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(linfo->epsilon < fabs(data-linfo->MaskedValue)) {
            sum3 += CUBIC((data-linfo->avg)/linfo->sd);
            sum4 += QUAD ((data-linfo->avg)/linfo->sd);
            n++;
        }
    }
    }
    }
    DEBUGPRINT1("n: %d\n", n);
    linfo->skewness  = sum3*n      /(n-1)/(n-2);
    linfo->kurtosis  = sum4*n*(n+1)/(n-1)/(n-2)/(n-3);
    linfo->kurtosis2 = linfo->kurtosis - 3.0*(n-1)*(n-1)/(n-2)/(n-3);
}

void 
lmrcMaskedImageInfoPrint(FILE* fpt, lmrcMaskedImageInfoInfo* linfo, int mode)
{
    int i;
    fprintf(fpt, "area[%%]: %g\n", linfo->area);
    fprintf(fpt, "N[pix]: %g\n", linfo->area);
    fprintf(fpt, "avg: %g\n", linfo->avg);
    fprintf(fpt, "sd: %g\n", linfo->sd);
    fprintf(fpt, "skewness: %g\n", linfo->skewness);
    fprintf(fpt, "kurtosis: %g\n", linfo->kurtosis);
    fprintf(fpt, "kurtosis2: %g\n", linfo->kurtosis2);
    fprintf(fpt, "median: %g\n", linfo->median);
    fprintf(fpt, "1/4Q: %g\n", linfo->Q1);
    fprintf(fpt, "2/4Q: %g\n", linfo->Q2);
    fprintf(fpt, "3/4Q: %g\n", linfo->Q3);
    fprintf(fpt, "min: %g\n", linfo->min);
    fprintf(fpt, "max: %g\n", linfo->max);
    fprintf(fpt, "nQ: %d\n", linfo->nQuantile);
    for(i=0; i<linfo->nQuantile-1; i++) {
        fprintf(fpt, "%dQ%d: %g\n", linfo->nQuantile, i+1, linfo->nQ[i]);
    }
}

int
main(int argc, char* argv[]) 
{
    mrcImage in;
	mrcMaskedImageInfoInfo info;
	lmrcMaskedImageInfoInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    linfo.MaskedValue = info.MaskedValue;
    linfo.epsilon = info.Epsilon;
    linfo.nQuantile= info.nQuantile;

    mrcFileRead(&in, info.In, "in main", 0);

    lmrcMaskedImageInfo(&in, &linfo, info.mode);
    lmrcMaskedImageInfoPrint(info.fptOut, &linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
