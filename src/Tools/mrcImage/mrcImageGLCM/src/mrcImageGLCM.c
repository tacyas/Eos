/*
# mrcImageGLCM : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageGLCM
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
#include "Vector.h"
#include "mrcImage.h"

typedef struct lmrcImageGLCMInfo {
    // in
	double range; // SD*range
	double minThres;
	double maxThres;
    double exceptValue;
    int flagExceptValue;
    int    nHist;
    int    offset;
    int    angleMode; // 0: invariant direction
    double epsilon;
    double minAreaX, minAreaY, minAreaZ;
    double maxAreaX, maxAreaY, maxAreaZ;
    //out
    char* GLImageName;
    mrcImage GLImage;
    mrcImage GLCM;
    doubleVector GLDV;
    doubleVector pX;
    doubleVector pY;
    doubleVector avgX;
    doubleVector avgY;
    doubleVector sigX;
    doubleVector sigY;
    doubleVector varX;
    doubleVector varY;
    doubleVector entropyX;
    doubleVector entropyY;
    doubleVector pXminusY;
    doubleVector pXplusY;
    int nPixel;
    double avg;
    double sd;
    double min; 
    double max;
    double HX;
    double HY;
    double HXY;
    double HXY1;
    double HXY2;
    double jointMax;
    double jointAvgX;
    double jointAvgY;
    double muX;
    double muY;
    double jointVarX; 
    double jointVarY; 
    double jointSigX; 
    double jointSigY; 
    double jointEntropy;
    double differenceAvg;
    double differenceVar;
    double differenceEntropy;
    double sumAvg;
    double sumVar;
    double sumSig;
    double sumVar2;
    double sumSig2;
    double sumEntropy;
    double energy;
    double entropy;
    double contrast;
    double dissimilarity;
    double inverseDiff;
    double normalInverseDiff;
    double inverseDiffMoment;
    double normalInverseDiffMoment;
    double inverseVar;
    double correlation;
    double autocorrelation;
    double clusterTendency;
    double clusterShade;
    double clusterProminence;
    double informationCorrelation1;
    double informationCorrelation2;
    double homogeneity1;
    double homogeneity2;
    double IDM;
    double IDMN;
    double ID;
    double IDN;
    double IMC1;
    double IMC2;
} lmrcImageGLCMInfo;

extern void lmrcImageGLCMCalc(mrcImage* in, lmrcImageGLCMInfo* linfo, int mode);
extern void lmrcImageGLCMInformationPrint(FILE* fpt, lmrcImageGLCMInfo* linfo, int mode);

void
lmrcImageGLCMInformationPrint(FILE* fpt, lmrcImageGLCMInfo* linfo, int mode)
{
    int x, y; 
    double data;

    fprintf(fpt, "setting:      \n");
    fprintf(fpt, "    nHist:     %d\n", linfo->nHist);
    fprintf(fpt, "    range:     %f\n", linfo->range);
    fprintf(fpt, "    minThres:  %f\n", linfo->minThres);
    fprintf(fpt, "    maxThres:  %f\n", linfo->maxThres);
    fprintf(fpt, "    offset:    %d\n", linfo->offset);
    fprintf(fpt, "    angleMode: %d\n", linfo->angleMode);
    fprintf(fpt, "    epsilon:   %e\n", linfo->epsilon);
    fprintf(fpt, "    minArea:   %f %f %f\n", linfo->minAreaX, linfo->minAreaY, linfo->minAreaZ);
    fprintf(fpt, "    maxArea:   %f %f %f\n", linfo->maxAreaX, linfo->maxAreaY, linfo->maxAreaZ);
    fprintf(fpt, "image_information: \n");
    fprintf(fpt, "    avg: %f\n", linfo->avg);
    fprintf(fpt, "    SD:  %f\n", linfo->sd);
    fprintf(fpt, "    min:  %f\n", linfo->min);
    fprintf(fpt, "    max:  %f\n", linfo->max);
    fprintf(fpt, "    nPixel:  %d\n", linfo->nPixel);
    fprintf(fpt, "GLCM: \n"); for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    fprintf(fpt, "    %02d: ", y); for(x=0; x<linfo->GLCM.HeaderN.x; x++) { mrcPixelDataGet(&linfo->GLCM, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest); fprintf(fpt, "%8.2e ", data); } fprintf(fpt, "\n"); }
    fprintf(fpt, "GLCM_information: \n");
    fprintf(fpt, "    jointMax:   %f\n", linfo->jointMax);
    fprintf(fpt, "    energy:   %f\n", linfo->energy);
    fprintf(fpt, "    entropy:  %f \n", linfo->entropy);
    fprintf(fpt, "    HXY:      %f \n", linfo->entropy);
    fprintf(fpt, "    HXY1:  %f\n", linfo->HXY1);
    fprintf(fpt, "    HXY2:  %f\n", linfo->HXY2);
    fprintf(fpt, "    HX:  %f\n", linfo->HX);
    fprintf(fpt, "    HY:  %f\n", linfo->HY);
    fprintf(fpt, "    contrast: %f\n", linfo->contrast);
    fprintf(fpt, "    homogeneity1: %f\n", linfo->homogeneity1);
    fprintf(fpt, "    homogeneity2: %f \n", linfo->homogeneity2);
    fprintf(fpt, "    similarity: %f \n", linfo->homogeneity2);
    fprintf(fpt, "    correlation: %f\n", linfo->correlation);
    fprintf(fpt, "    autocorrelation: %f\n", linfo->autocorrelation);
    fprintf(fpt, "    clusterProminence: %f\n", linfo->clusterProminence);
    fprintf(fpt, "    clusterSHade: %f\n", linfo->clusterShade);
    fprintf(fpt, "    clusterTendency: %f\n", linfo->clusterTendency);
    fprintf(fpt, "    differenceAverage: %f\n", linfo->differenceAvg);
    fprintf(fpt, "    differenceEntropy: %f\n", linfo->differenceEntropy);
    fprintf(fpt, "    dissimilarity: %f\n", linfo->dissimilarity);
    fprintf(fpt, "    jointAvgX: %f\n", linfo->jointAvgX);
    fprintf(fpt, "    jointAvgY: %f\n", linfo->jointAvgY);
    fprintf(fpt, "    jointSigX: %f\n", linfo->jointSigX);
    fprintf(fpt, "    jointSigY: %f\n", linfo->jointSigY);
    fprintf(fpt, "    ID: %f\n", linfo->ID);
    fprintf(fpt, "    IDN: %f\n", linfo->IDN);
    fprintf(fpt, "    IDM: %f\n", linfo->IDM);
    fprintf(fpt, "    IDMN: %f\n", linfo->IDMN);
    fprintf(fpt, "    IMC1: %f\n", linfo->IMC1);
    fprintf(fpt, "    IMC2: %f\n", linfo->IMC2);
    fprintf(fpt, "    sumAvg: %f\n", linfo->sumAvg);
    fprintf(fpt, "    sumEntroy: %f\n", linfo->sumEntropy);
    fprintf(fpt, "    sumSig: %f\n", linfo->sumSig);
    fprintf(fpt, "    sumSig2: %f\n", linfo->sumSig2);
    fprintf(fpt, "    pX: "); for(x=0; x<linfo->pX.size; x++) { fprintf(fpt, "%8.2e ", linfo->pX.data[x]); } fprintf(fpt, "\n");
    fprintf(fpt, "    pY: "); for(x=0; x<linfo->pY.size; x++) { fprintf(fpt, "%8.2e ", linfo->pY.data[x]); } fprintf(fpt, "\n");
    fprintf(fpt, "    pX+Y: "); for(x=0; x<linfo->pXplusY.size; x++) { fprintf(fpt, "%8.2e ", linfo->pXplusY.data[x]); } fprintf(fpt, "\n");
    fprintf(fpt, "    pX-Y: "); for(x=0; x<linfo->pXminusY.size; x++) { fprintf(fpt, "%8.2e ", linfo->pXminusY.data[x]); } fprintf(fpt, "\n");
    fprintf(fpt, "GLDV_information: \n");
    fprintf(fpt, "    GLDV: "); for(x=0; x<linfo->GLDV.size; x++) { fprintf(fpt, "%8.2e ", linfo->GLDV.data[x]); } fprintf(fpt, " // pX-Y\n");
    mrcFileWrite(&linfo->GLImage, linfo->GLImageName, "in ", 0); 
}

void
lmrcImageGLCMCalc(mrcImage* in, lmrcImageGLCMInfo* linfo, int mode)
{
    mrcImageParaTypeReal x, y, z;
    double sum, avg, sd, min, max;
    int n;
    double src, src00, src01, src11, src10, src1_1;
    double dst, tex, data, data00, data10, data11, data01, data1_1;
    int minX, minY, minZ;
    int maxX, maxY, maxZ;

    linfo->GLImage.Header = in->Header;
    DEBUGPRINT3("size: GLImage %d %d %d\n", linfo->GLImage.HeaderN.x, linfo->GLImage.HeaderN.y, linfo->GLImage.HeaderN.z);
    mrcInit(&(linfo->GLImage), NULL);
    //
    minX = rint(linfo->minAreaX*in->HeaderN.x);
    minY = rint(linfo->minAreaY*in->HeaderN.y);
    minZ = rint(linfo->minAreaZ*in->HeaderN.z);
    maxX = rint(linfo->maxAreaX*in->HeaderN.x);
    maxY = rint(linfo->maxAreaY*in->HeaderN.y);
    maxZ = rint(linfo->maxAreaZ*in->HeaderN.z);


    // Average
    sum = 0;
    n = 0;
    for(z=minZ; z<maxZ; z++) {
    for(y=minY; y<maxY; y++) {
    for(x=minX; x<maxX; x++) {
        mrcPixelDataGet(in, x, y, z, &src, mrcPixelRePart, mrcPixelHowNearest);        
        if(linfo->minThres <= src && src <= linfo->maxThres) { 
            if(!linfo->flagExceptValue || linfo->epsilon < fabs(src-linfo->exceptValue)) {
                sum += src;  
                n += 1;
            }
        }
    }
    }
    }    
    if(0<n) {
        avg = sum/n;
    } else {
        fprintf(stderr, "No data: thresMin - thresMax\n");
        exit(EXIT_FAILURE);
    }
    linfo->avg = avg;
    linfo->nPixel = n;
    // SD
    sum = 0;
    n = 0;
    for(z=minZ; z<maxZ; z++) {
    for(y=minY; y<maxY; y++) {
    for(x=minX; x<maxX; x++) {
        mrcPixelDataGet(in, x, y, z, &src, mrcPixelRePart, mrcPixelHowNearest);        
        if(linfo->minThres <= src && src <= linfo->maxThres) { 
            if(!linfo->flagExceptValue || linfo->epsilon < fabs(src-linfo->exceptValue)) {
                sum += (src-avg)*(src-avg);  
                n += 1;
            }
        }
    }
    }
    }    
    if(0<n) {
        sd = sqrt(sum/n);
    } else {
        fprintf(stderr, "No data: thresMin - thresMax\n");
        exit(EXIT_FAILURE);
    }
    linfo->sd = sd;

    // GLImage
    min =  avg - linfo->range*sd;
    max =  avg + linfo->range*sd;
    linfo->min = min;
    linfo->max = max;
    n = 0;
    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &src, mrcPixelRePart, mrcPixelHowNearest);        
        if(linfo->minThres <= src && src <= linfo->maxThres) { 
            if(!linfo->flagExceptValue || linfo->epsilon < fabs(src-linfo->exceptValue)) {
                if(src < min) {
                    dst = -1;
                } else if(max <= src) {
                    dst = -1;
                } else {
                    dst = (int)((src - min)/(max - min)*linfo->nHist); 
                }
            }
        } else {
            dst = -1;
        }
        mrcPixelDataSet(&(linfo->GLImage), x, y, z, dst, mrcPixelRePart);        
    }
    }
    }    

    // GLCM
    linfo->GLCM.HeaderN.x = linfo->nHist; 
    linfo->GLCM.HeaderN.y = linfo->nHist; 
    linfo->GLCM.HeaderN.z = 1;
    linfo->GLCM.HeaderMode = mrcFloatImage;
    mrcInit(&linfo->GLCM, NULL);

    for(z=0; z<linfo->GLCM.HeaderN.z; z++) {
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
            mrcPixelDataSet(&linfo->GLCM, x, y, z, 0, mrcPixelRePart);
    }
    }
    }    

    n = 0;
    for(z=minZ; z<maxZ; z++) {
    for(y=minY; y<maxY; y++) {
    for(x=minX; x<maxX; x++) {
        mrcPixelDataGet(&linfo->GLImage, x, y, z, &data00, mrcPixelRePart, mrcPixelHowNearest);        
        if(0<=data00) {
            if(linfo->angleMode&0x1) { // 1 0 0 
                mrcPixelDataGet(&linfo->GLImage, x+linfo->offset, y, z, &data10,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data10) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data10, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data10, 0, data+1, mrcPixelRePart);   
                }
            }
            if(linfo->angleMode&0x2) { // 1 1 0
                mrcPixelDataGet(&linfo->GLImage, x+linfo->offset, y+linfo->offset, z, &data11,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data11) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data11, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data11, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x4) { // 0 1 0
                mrcPixelDataGet(&linfo->GLImage, x, y+linfo->offset, z, &data01,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data01) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data01, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data01, 0, data+1, mrcPixelRePart);  
                }
            }
            
            if(linfo->angleMode&0x8) { // -1 1 0
                mrcPixelDataGet(&linfo->GLImage, x-linfo->offset, y+linfo->offset, z, &data1_1, mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data1_1) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data1_1, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data1_1, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x16) { // 1 0 1
                mrcPixelDataGet(&linfo->GLImage, x+linfo->offset, y, z+linfo->offset, &data10,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data10) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data10, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data10, 0, data+1, mrcPixelRePart);   
                }
            }
            if(linfo->angleMode&0x32) { // 1 1 1 
                mrcPixelDataGet(&linfo->GLImage, x+linfo->offset, y+linfo->offset, z+linfo->offset, &data11,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data11) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data11, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data11, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x64) { // 0 1 1 
                mrcPixelDataGet(&linfo->GLImage, x, y+linfo->offset, z+linfo->offset, &data01,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data01) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data01, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data01, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x128) { // -1 1 1 
                mrcPixelDataGet(&linfo->GLImage, x-linfo->offset, y+linfo->offset, z+linfo->offset, &data1_1, mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data1_1) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data1_1, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data1_1, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x256) { // 1 0 -1
                mrcPixelDataGet(&linfo->GLImage, x+linfo->offset, y,               z-linfo->offset, &data10,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data10) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data10, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data10, 0, data+1, mrcPixelRePart);   
                }
            }
            if(linfo->angleMode&0x512) { // 1 1 -1 
                mrcPixelDataGet(&linfo->GLImage, x+linfo->offset, y+linfo->offset, z-linfo->offset, &data11,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data11) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data11, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data11, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x1024) { // 0 1 -1 
                mrcPixelDataGet(&linfo->GLImage, x, y+linfo->offset,               z-linfo->offset, &data01,  mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data01) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data01, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data01, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x2048) { // -1 1 -1 
                mrcPixelDataGet(&linfo->GLImage, x-linfo->offset, y+linfo->offset, z-linfo->offset, &data1_1, mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data1_1) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data1_1, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data1_1, 0, data+1, mrcPixelRePart);  
                }
            }
            if(linfo->angleMode&0x4096) { // 0 0 -1 
                mrcPixelDataGet(&linfo->GLImage, x, y,                             z-linfo->offset, &data1_1, mrcPixelRePart, mrcPixelHowNearest);        
                if(0<=data1_1) {
                    n++;
                    mrcPixelDataGet(&linfo->GLCM, data00, data1_1, 0, &data, mrcPixelRePart, mrcPixelHowNearest);   
                    mrcPixelDataSet(&linfo->GLCM, data00, data1_1, 0, data+1, mrcPixelRePart);  
                }
            }
        } 
    }
    }
    }    

    // GLCM
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        mrcPixelDataGet(&linfo->GLCM, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataSet(&linfo->GLCM, x, y, 0, data/n, mrcPixelRePart);
    }
    }
    
    // GLVD
    doubleVectorInit(&linfo->GLDV, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->pX, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->pY, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->avgX, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->avgY, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->sigX, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->sigY, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->varX, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->varY, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->entropyX, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->entropyY, linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->pXplusY,  2*linfo->GLCM.HeaderN.x);     
    doubleVectorInit(&linfo->pXminusY, linfo->GLCM.HeaderN.x);     
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        mrcPixelDataGet(&linfo->GLCM, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
        tex = (int)fabs(x-y); linfo->GLDV.data[(int)tex] +=data;  // GLDV
        linfo->pX.data[(int)x]     += data;       // pX: marginal row    probabilities
        linfo->pY.data[(int)y]     += data;       // pY: marginal column probalirities
        linfo->avgX.data[(int)x]   += data*x;     // avgX
        linfo->avgY.data[(int)y]   += data*y;     // avgY
        linfo->pXplusY.data[(int)(x+y)]      += data; // pX+Y 
        linfo->pXminusY.data[(int)fabs(x-y)] += data; // p|X-Y|, GLDV
    }
    }
    
    linfo->HXY1 = 0;
    linfo->HXY2 = 0;
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        mrcPixelDataGet(&linfo->GLCM, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
        linfo->varX.data[(int)x]+=SQR(data - linfo->avgX.data[(int)x]); 
        linfo->varY.data[(int)y]+=SQR(data - linfo->avgY.data[(int)y]); 
        linfo->HXY1 += (-data                                         *log2(linfo->pX.data[(int)x]*linfo->pY.data[(int)y] + linfo->epsilon)); // HXY1
        linfo->HXY2 += (-linfo->pX.data[(int)x]*linfo->pY.data[(int)y]*log2(linfo->pX.data[(int)x]*linfo->pY.data[(int)y] + linfo->epsilon)); // HXY2
    }
    }
    
    linfo->differenceAvg = 0;
    linfo->differenceEntropy = 0;
    linfo->HX = 0;
    linfo->HY = 0;
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        linfo->sigX.data[(int)x] = sqrt(linfo->varX.data[(int)x]);  // sig
        linfo->sigY.data[(int)x] = sqrt(linfo->varY.data[(int)x]); 
        linfo->entropyX.data[(int)x] += (-linfo->pX.data[(int)x]*log2(linfo->pX.data[(int)x] + linfo->epsilon)); // entropyX
        linfo->entropyY.data[(int)x] += (-linfo->pY.data[(int)x]*log2(linfo->pY.data[(int)x] + linfo->epsilon)); // entropyY
        linfo->differenceAvg += x*linfo->pXminusY.data[(int)x];                                                      // 8) Diff Avg
        linfo->differenceEntropy += (-linfo->pXminusY.data[(int)x]*log2(linfo->pXminusY.data[(int)x] + linfo->epsilon));       // 9) Diff Entropy
        linfo->HX += (-linfo->pX.data[(int)x]*log2(linfo->pX.data[(int)x] + linfo->epsilon)); // HX
        linfo->HY += (-linfo->pY.data[(int)x]*log2(linfo->pY.data[(int)x] + linfo->epsilon)); // HY
    }
    
    linfo->differenceVar = 0;
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        linfo->differenceVar     += SQR(1-linfo->differenceAvg)*linfo->pXminusY.data[(int)x]; // 10) Dif Var
    }

    linfo->sumAvg = 0;
    linfo->sumEntropy = 0;
    for(x=0; x<2*linfo->GLCM.HeaderN.x; x++) {
        linfo->sumAvg += linfo->pXplusY.data[(int)x]*x;                                                     // 24) Sum Average
        linfo->sumEntropy += (-linfo->pXplusY.data[(int)x]*log2(linfo->pXplusY.data[(int)x] + linfo->epsilon)); // 25) Sum Entropy
    }

    linfo->sumVar = 0;
    linfo->sumVar2 = 0;
    for(x=0; x<2*linfo->GLCM.HeaderN.x; x++) {
        linfo->sumVar  += linfo->pXplusY.data[(int)x]*SQR(x-linfo->sumEntropy);                                                     // 24) Sum Average
        linfo->sumVar2 += linfo->pXplusY.data[(int)x]*SQR(x-linfo->sumAvg);                                                     // 24) Sum Average
    }
    linfo->sumSig  = sqrt(linfo->sumVar);
    linfo->sumSig2 = sqrt(linfo->sumVar2);

    //
    n=linfo->GLCM.HeaderN.x*linfo->GLCM.HeaderN.y*linfo->GLCM.HeaderN.z;
    linfo->jointMax = 0;
    linfo->jointAvgX = 0;
    linfo->jointAvgY = 0;
    linfo->entropy = 0;
    linfo->energy=0;
    linfo->contrast = 0;
    linfo->dissimilarity =0;
    linfo->autocorrelation =0;
    linfo->homogeneity1 =0;
    linfo->homogeneity2 =0;
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        mrcPixelDataGet(&linfo->GLCM, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(linfo->jointMax<data) linfo->jointMax=data;     // MAX
        linfo->autocorrelation += x*y*data;        // 1) AutoCorrelation
        linfo->jointAvgX += x*data;                // 2) Joint Average muX
        linfo->jointAvgY += y*data;                // 2) Joint Average muY
        linfo->contrast += SQR(x-y)*data;          // 6) contrast
        linfo->dissimilarity += fabs(x-y)*data;    // 11) dissimilarity
        linfo->energy += data*data;                // 12) energy
        linfo->entropy += (-data*log2(data+linfo->epsilon)); // 13) entropy/HXY
        linfo->homogeneity1 += data/(1+fabs(x-y));  // 14) Homogeneity 1
        linfo->homogeneity2 += data/(1+SQR(x-y));   // 15) Homogeneity 2
        if(x!=y) linfo->inverseVar += data/SQR(x-y); // 22) Inverse Variance
    }
    }
    linfo->HXY = linfo->entropy;
    linfo->muX = linfo->jointAvgX;
    linfo->muY = linfo->jointAvgY;
    linfo->ID  = linfo->homogeneity1;
    linfo->IDM = linfo->homogeneity2;

    // joint
    linfo->jointVarX = 0;
    linfo->jointVarY = 0;
    linfo->correlation = 0;
    linfo->clusterProminence = 0;
    linfo->clusterShade= 0;
    linfo->clusterTendency= 0;
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        mrcPixelDataGet(&linfo->GLCM, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        if(linfo->jointMax<data) linfo->jointMax = data;
        linfo->jointVarX += SQR(x-linfo->jointAvgX)*data;
        linfo->jointVarY += SQR(y-linfo->jointAvgY)*data;
        linfo->clusterProminence += SQR(SQR( x + y - linfo->jointAvgX - linfo->jointAvgY))*data; // 3) cluster prominence   
        linfo->clusterShade      += CUBIC(   x + y - linfo->jointAvgX - linfo->jointAvgY )*data; // 4) cluster shade
        linfo->clusterTendency   += SQR(     x + y - linfo->jointAvgX - linfo->jointAvgY )*data; // 5) cluster tendency
    }
    }
    linfo->jointSigX = sqrt(linfo->jointVarX);
    linfo->jointSigY = sqrt(linfo->jointVarY);

    // Correlation
    linfo->correlation =0;
    linfo->IDMN = 0;
    for(y=0; y<linfo->GLCM.HeaderN.y; y++) {
    for(x=0; x<linfo->GLCM.HeaderN.x; x++) {
        mrcPixelDataGet(&linfo->GLCM, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
        linfo->correlation += data*(x-linfo->jointAvgX)*(y-linfo->jointAvgY)/linfo->jointSigX/linfo->jointSigY; // 7) Correlation
        linfo->IDMN += data/(1+SQR(x-y)/SQR(linfo->GLCM.HeaderN.x));
        linfo->IDN  += data/(1+fabs(x-y)/linfo->GLCM.HeaderN.x);
    }
    }
    linfo->IMC1 = (linfo->HXY - linfo->HXY1)/MAX(linfo->HX, linfo->HY);
    linfo->IMC2 = sqrt(1-exp(-2*(linfo->HXY2 - linfo->HXY)));
}

/*

typedef enum lmrcImageGLCMMode {
	a=0,
	b=1
} lmrcImageGLCMMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageGLCMInfo info;
	lmrcImageGLCMInfo linfo;
    mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    mrcFileRead(&in, info.In, "in main", 0);
    
    linfo.epsilon = info.epsilon;
    linfo.maxThres = info.thresHigh;
    linfo.minThres = info.thresLow;
    linfo.flagExceptValue= info.flagexceptValue;
    linfo.exceptValue= info.exceptValue;
    linfo.nHist = info.nHist;
    linfo.range = info.range;
    linfo.offset = info.offset;
    linfo.angleMode = info.angleMode;
    linfo.minAreaX = info.minAreaX;
    linfo.minAreaY = info.minAreaY;
    linfo.minAreaZ = info.minAreaZ;
    linfo.maxAreaX = info.maxAreaX;
    linfo.maxAreaY = info.maxAreaY;
    linfo.maxAreaZ = info.maxAreaZ;

    linfo.GLImageName = info.Out;

    lmrcImageGLCMCalc(&in, &linfo, info.mode);
    lmrcImageGLCMInformationPrint(info.fptOutInfo, &linfo, info.mode);
    
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "angleMode: 2^0-2^12, 2^13-1 for all\n");
	fprintf(stderr, "1: (1, 0, 0)\n");
	fprintf(stderr, "2: (1, 1, 0)\n");
	fprintf(stderr, "4: (0, 1, 0)\n");
	fprintf(stderr, "8: (-1,1, 0)\n");
	fprintf(stderr, "16: (1, 0, 1)\n");
	fprintf(stderr, "32: (1, 1, 1)\n");
	fprintf(stderr, "64: (0, 1, 1)\n");
	fprintf(stderr, "128: (-1,1, 1)\n");
	fprintf(stderr, "256: (1, 0,-1)\n");
	fprintf(stderr, "512: (1, 1,-1)\n");
	fprintf(stderr, "1024: (0, 1,-1)\n");
	fprintf(stderr, "2048: (-1,1,-1)\n");
	fprintf(stderr, "4096: ( 0, 0, 1)\n");
}
