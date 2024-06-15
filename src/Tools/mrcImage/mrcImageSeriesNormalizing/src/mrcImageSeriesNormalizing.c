/*
# mrcImageSeriesNormalizing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSeriesNormalizing
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
#include "Memory.h"
#include "mrcImage.h"
#include "eosNonLinearFitting.h"

typedef struct lmrcImageSeriesNormalizingInfo {
    int N;
    int useHigh;
	float High;
    int useLow;
	float Low;
	float thresOfLowValueArea;
	float thresOfHighValueArea;
    double A;
    double B;
    eosNonLinearFittingParams outHigh;
    eosNonLinearFittingParams outLow;
    int maxIter;
    FILE* paramOut;
    double* weight;
    mrcImageInformation* originalInfo;
    mrcImageInformation* normalizedInfo;
} lmrcImageSeriesNormalizingInfo;

typedef enum lmrcImageSeriesNormalizingMode {
	lmrcImageSeriesNormalizingModeLowValueAreaToHighValueArea=0
} lmrcImageSeriesNormalizingMode;


extern int lmrcImageSeriesNormalizingOutputParam(FILE* fpt, lmrcImageSeriesNormalizingInfo linfo,  lmrcImageSeriesNormalizingMode mode);
extern int lmrcImageSeriesNormalizing(mrcImage* out, mrcImage* in, lmrcImageSeriesNormalizingInfo* linfo, lmrcImageSeriesNormalizingMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImageSeriesNormalizingInfo  info;
	lmrcImageSeriesNormalizingInfo linfo;
    mrcImage* in;
    mrcImage* out;
    int i, j;
    char s[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    linfo.thresOfLowValueArea = info.thresOfLowValueArea;
    linfo.thresOfHighValueArea = info.thresOfHighValueArea;
    linfo.High = info.High;
    linfo.Low  = info.Low;
    linfo.outHigh.Ainit = info.AHigh;
    linfo.outHigh.Kinit = info.KHigh;
    linfo.outHigh.Binit = info.BHigh;
    linfo.outLow.Ainit = info.ALow;
    linfo.outLow.Kinit = info.KLow;
    linfo.outLow.Binit = info.BLow;
    linfo.N = info.flagIn;
    linfo.outLow.xtol = linfo.outHigh.xtol = info.xtol;
    linfo.outLow.gtol = linfo.outHigh.gtol = info.gtol;
    linfo.outLow.ftol = linfo.outHigh.ftol = info.ftol;
    linfo.outLow.maxIter = linfo.outHigh.maxIter = linfo.maxIter = info.maxIter;
    if(info.flagIn!=info.flagOut) {
        fprintf(stderr, "In num %ld is diffrenct from Out num %ld\n", info.flagIn, info.flagOut);
    }
    linfo.paramOut = info.fptParam;
    linfo.useLow  = info.UseLow;
    linfo.useHigh = info.UseHigh;
    in  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.N, "in main"); 
    out = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.N, "in main"); 
    linfo.weight = (double*)memoryAllocate(sizeof(double)*linfo.N, "in main"); 
    linfo.originalInfo= (mrcImageInformation*)memoryAllocate(sizeof(double)*linfo.N, "in main"); 
    linfo.normalizedInfo= (mrcImageInformation*)memoryAllocate(sizeof(double)*linfo.N, "in main"); 

    for(i=0; i<info.flagIn; i++) {
        mrcFileRead(&(in[i]), info.In[i], "in main", 0);
    }    

    if(info.flagWeight) {
        fseek(info.fptWeight, 0L, SEEK_SET);
        for(i=0; i<linfo.N; i++) {
            fgets(s, 1024, info.fptWeight);
            linfo.weight[i] = atof(s); 
        }
    } else {
        for(i=0; i<linfo.N; i++) {
            linfo.weight[i] =  1;
        }
    }

    lmrcImageSeriesNormalizing(out, in, &linfo, info.mode);
    
    lmrcImageSeriesNormalizingOutputParam(info.fptParam, linfo, info.mode);

    fprintf(info.fptParam, "# Original Images\n");
    for(i=0; i<info.flagOut; i++) {
        mrcStatDataSet(&(in[i]), 0); 
        switch(info.mode) {
            case lmrcImageSeriesNormalizingModeLowValueAreaToHighValueArea: {
                fprintf(info.fptParam, "original(name,min,LowMean,LowSD,LowMed,Low(%f),mean,High(%f),HighMed,HighMean,HighSD,max): %s %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f\n",
                   linfo.originalInfo[i].thresLow, linfo.originalInfo[i].thresHigh, 
                   info.In[i],
                   in[i].HeaderAMin, 
                   linfo.originalInfo[i].meanOfLowValueArea, linfo.originalInfo[i].sdOfLowValueArea, linfo.originalInfo[i].medianOfLowValueArea, linfo.originalInfo[i].maxOfLowValueArea, 
                   in[i].HeaderAMean, 
                   linfo.originalInfo[i].minOfHighValueArea,linfo.originalInfo[i].medianOfHighValueArea, linfo.originalInfo[i].meanOfHighValueArea, linfo.originalInfo[i].sdOfHighValueArea,
                   in[i].HeaderAMax);
                break;
            }
            default: {
                fprintf(info.fptParam, "original(name,min,mean,max): %s %f %f %f\n", info.Out[i], out[i].HeaderAMin, out[i].HeaderAMean, out[i].HeaderAMax); 
                break;
            }
        }
    } 
    fprintf(info.fptParam, "# Normalized Images\n");
    for(i=0; i<info.flagOut; i++) {
        mrcStatDataSet(&(out[i]), 0); 
        switch(info.mode) {
            case lmrcImageSeriesNormalizingModeLowValueAreaToHighValueArea: {
                fprintf(info.fptParam, "normal(name,min,LowMean,LowSD,LowMed,Low(%f),mean,High(%f),HighMed,HighMean,HighSD,max):   %s %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f %+-f\n",
                   linfo.normalizedInfo[i].thresLow, linfo.normalizedInfo[i].thresHigh,
                   info.Out[i],
                   out[i].HeaderAMin,
                   linfo.normalizedInfo[i].meanOfLowValueArea, linfo.normalizedInfo[i].sdOfLowValueArea,  linfo.normalizedInfo[i].medianOfLowValueArea, linfo.normalizedInfo[i].maxOfLowValueArea,
                   out[i].HeaderAMean,
                   linfo.normalizedInfo[i].minOfHighValueArea, linfo.normalizedInfo[i].medianOfHighValueArea, linfo.normalizedInfo[i].meanOfHighValueArea, linfo.normalizedInfo[i].sdOfHighValueArea,
                   out[i].HeaderAMax);
                break;
            }
            default: {
                fprintf(info.fptParam, "normal(name,min,mean,max): %s %f %f %f\n", info.Out[i], out[i].HeaderAMin, out[i].HeaderAMean, out[i].HeaderAMax); 
                break;
            }
        }
        mrcFileWrite(&(out[i]), info.Out[i], "in main", 0);
    }    
    //
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode: %d\n", lmrcImageSeriesNormalizingModeLowValueAreaToHighValueArea);
	fprintf(stderr, "    t  = i/N\n" );
	fprintf(stderr, "    low  = Alow  * exp(-Klow  t) * Blow\n" );
	fprintf(stderr, "    high = Ahigh * exp(-Khigh t) * Bhigh\n" );
	fprintf(stderr, "    Dnor= High*(D-low)/(high-low) + Low\n" );
}

int 
lmrcImageSeriesNormalizingOutputParam(FILE* fpt, lmrcImageSeriesNormalizingInfo linfo, lmrcImageSeriesNormalizingMode mode)
{
    int i;
    switch(mode) {
	    case lmrcImageSeriesNormalizingModeLowValueAreaToHighValueArea: {
            fprintf(fpt, "method: %s\n", linfo.outHigh.method);  
            fprintf(fpt, "iter(low,high): %d %d\n", linfo.outLow.iter, linfo.outHigh.iter);  
            fprintf(fpt, "functionEval(low,high): %f %f\n", linfo.outLow.functionEvaluations, linfo.outHigh.functionEvaluations);  
            fprintf(fpt, "JacobianEval(low,high): %f %f\n", linfo.outLow.JacobianEvaluations, linfo.outHigh.JacobianEvaluations);  
            fprintf(fpt, "reason(low,high): %s %s\n", linfo.outLow.reason, linfo.outHigh.reason);  
            fprintf(fpt, "status(low,high): %s %s\n", linfo.outLow.status, linfo.outHigh.status);  
            fprintf(fpt, "DegreeOfFreedom(low,high): %f %f\n", linfo.outLow.degreeOfFreedom, linfo.outHigh.degreeOfFreedom);  
            fprintf(fpt, "c(low,high): %f %f\n", linfo.outLow.c, linfo.outHigh.c);  
            fprintf(fpt, "chisq/degreeOfFreedom(low,high): %f %f\n", linfo.outLow.chisq_per_degreeOfFreedom, linfo.outHigh.chisq_per_degreeOfFreedom);  
            fprintf(fpt, "high(A,dA,K,dK,B,dB): %f %f %f %f %f %f\n", linfo.outHigh.A, linfo.outHigh.sigA, linfo.outHigh.K, linfo.outHigh.sigK, linfo.outHigh.B, linfo.outHigh.sigB);
            fprintf(fpt, "low(A,dA,K,dK,B,dB):  %f %f %f %f %f %f\n", linfo.outLow.A,  linfo.outLow.sigA,  linfo.outLow.K,  linfo.outLow.sigK,  linfo.outLow.B,  linfo.outLow.sigB);
            fprintf(fpt, "Iteration:High\n");
            for(i=0; i<=linfo.maxIter; i++) {
                if(linfo.outHigh.message[i]!=NULL) {
                    fprintf(fpt, "%s\n",linfo.outHigh.message[i]);  
                }
            }
            fprintf(fpt, "Iteration:Low\n");
            for(i=0; i<=linfo.maxIter; i++) {
                if(linfo.outLow.message[i]!=NULL) {
                    fprintf(fpt, "%s\n",linfo.outLow.message[i]);  
                }
            }
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode: %d\n", mode);
            exit(EXIT_FAILURE);
            break;
        }
    }
    return 0;
}

int
lmrcImageSeriesNormalizing(mrcImage* out, mrcImage* in, lmrcImageSeriesNormalizingInfo* linfo, lmrcImageSeriesNormalizingMode mode)
{
    double* frame;
    double* high;
    double* sighigh;
    double* low;
    double* siglow;
    int i, j, Nj;
    double data, highi, lowi;
    mrcImageParaTypeReal x, y, z;
    double High, Low;
    
    frame = (double*)memoryAllocate(sizeof(double)*linfo->N, "in main");
    low = (double*)memoryAllocate(sizeof(double)*linfo->N, "in main");
    high  = (double*)memoryAllocate(sizeof(double)*linfo->N, "in main");
    siglow = (double*)memoryAllocate(sizeof(double)*linfo->N, "in main");
    sighigh  = (double*)memoryAllocate(sizeof(double)*linfo->N, "in main");
    switch(mode) {
	    case lmrcImageSeriesNormalizingModeLowValueAreaToHighValueArea: {
            // low/high= A*exp(-Kt) + B 
            // ln low/high = ln A - K log t
            //mrcImageInformation inInfo;
            for(i=0, j=0; i<linfo->N; i++) {
                linfo->originalInfo[i].mode = meanOfLowValueAreaAndHighValueArea;
                linfo->originalInfo[i].thresLow  = linfo->thresOfLowValueArea;
                linfo->originalInfo[i].thresHigh = linfo->thresOfHighValueArea;
                lmrcImageInformation(&(linfo->originalInfo[i]), &(in[i]));
                if(0<linfo->weight[i]) {
                    frame[j] = (double)i/(double)linfo->N;
                    high[j] = linfo->originalInfo[i].meanOfHighValueArea;
                    sighigh[j] = linfo->originalInfo[i].sdOfHighValueArea;
                    low[j] = linfo->originalInfo[i].meanOfLowValueArea; 
                    siglow[j] = linfo->originalInfo[i].sdOfLowValueArea; 
                    j++;
                    Nj++;
                } else {
                }
            }
            DEBUGPRINT("HIGH\n");
            eosNonLinearFitting(&linfo->outHigh, frame, high, sighigh, Nj, eosNonLinearFittingModeSingleExpDecay);
            DEBUGPRINT("LOW\n");
            eosNonLinearFitting(&linfo->outLow,  frame, low,  siglow,  Nj, eosNonLinearFittingModeSingleExpDecay);

            if(linfo->useHigh) {
                High = linfo->High;
            } else {
                High = linfo->outHigh.A*exp( - linfo->outHigh.K * frame[0] ) + linfo->outHigh.B;
            }
            if(linfo->useLow) {
                Low  = linfo->Low;        
            } else {
                Low  = linfo->outLow.A *exp( - linfo->outLow.K  * frame[0] ) + linfo->outLow.B;
            }
            DEBUGPRINT2("Normalization(High,Low):%f %f", High, Low); 
            for(i=0; i<linfo->N; i++) {
                out[i].Header = in[i].Header;
                mrcInit(&out[i], NULL);
                for(z=0; z<in[i].HeaderN.z; z++) {
                for(y=0; y<in[i].HeaderN.y; y++) {
                for(x=0; x<in[i].HeaderN.x; x++) {
                    mrcPixelDataGet(&in[i], x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
                    lowi  = linfo->outLow.A *exp( - linfo->outLow.K  * (double)i/linfo->N) + linfo->outLow.B;
                    highi = linfo->outHigh.A*exp( - linfo->outHigh.K * (double)i/linfo->N) + linfo->outHigh.B;
                    data = High*(data-lowi)/(highi -lowi) + Low; 
                    mrcPixelDataSet(&out[i], x, y, z, data, mrcPixelRePart); 
                }
                }
                }
                //
                linfo->normalizedInfo[i].mode = meanOfLowValueAreaAndHighValueArea;
                linfo->normalizedInfo[i].thresLow  = linfo->thresOfLowValueArea;
                linfo->normalizedInfo[i].thresHigh = linfo->thresOfHighValueArea;
                lmrcImageInformation(&(linfo->normalizedInfo[i]), &(out[i]));
            }
            break;
        }
        default: {
            fprintf(stderr, "Not supported mode: %d\n", mode);
            exit(EXIT_FAILURE);
            break;
        }
    }
    return 0;
}
