/*
# lmrcImageFeatureExtraction : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFeatureExtraction 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "lmrcImageFeatureExtraction.h"
#include <stdlib.h>
#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#define EPS 0.000001


double _calcAVE(double* ,int L, int mode);
double _calcVALIANCE(double* ,int L, double ave, int mode);
double _calcSKEWNESS(double* ,int L, double ave, double variance, int mode);
double _calcKURTOSIS(double* ,int L, double ave, double variance, int mode);
double _calcCONTRAST(double* ,int L, int mode);
double _calcENERGY(double* ,int L, int mode);
double _calcENTROPY(double* ,int L, int mode);

void
lmrcImageFeatureExtraction(mrcImage* in, mrcImage* out, lmrcImageFeatureExtractionInfo info, int mode)
{
	int x;
	int n;
	double densityHist[7];
	double coOccurrence[18];
	double runLength[5];

	out->Header = in->Header;
	out->HeaderN.x = 30;
    out->HeaderN.y = 1;
    out->HeaderN.z = 1;
	mrcInit(out, NULL);
	lmrcImageFeatureExtraction_densityHist(in, densityHist, 0);
	lmrcImageFeatureExtractionCoOccurrence(in, coOccurrence, info, 0);
	lmrcImageFeatureExtractionRunLength(in, runLength, info, 0);
	
	for(x=0;x<7;x++) 
		mrcPixelDataSet(out, x, 0, 0, densityHist[x], mrcPixelRePart);
	for(x=7;x<25;x++)  
		mrcPixelDataSet(out, x, 0, 0, coOccurrence[x-7], mrcPixelRePart);
	for(x=25;x<30;x++)
		mrcPixelDataSet(out, x, 0, 0, runLength[x-25], mrcPixelRePart);
	
	mrcStatDataSet(out,0);
	
}

void
lmrcImageFeatureExtraction_densityHist(mrcImage* in, double* out, int mode)
{
	int x,y,n,count;
	double hist[256];
	double wholeintensity, oneLevel, current;
	double ave, variance, data;
	mrcImageInformation linfo;

	linfo.mode = meanOfAll;
	lmrcImageInformation(&linfo, in);
	wholeintensity = linfo.max-linfo.min;
    oneLevel = (wholeintensity+1)/256;
	for(count=0;count<256;count++) hist[count]=0;
	count=0;
	
	for(y=0 ;y < in->HeaderN.y ;y++) {
	for(x=0 ;x < in->HeaderN.x ;x++) {
		mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
        current = (data-linfo.min)/oneLevel;
        hist[(int)current] += 1.0;
        count ++;
	}
	}
	for(n=0;n<256;n++) hist[n] /= (double)count; //normalize
	
	ave= out[0]= _calcAVE(hist, 256, 0);
	variance= out[1]= _calcVALIANCE(hist, 256, ave, 0);
	out[2]= _calcSKEWNESS(hist, 256, ave, variance, 0);
	out[3]= _calcKURTOSIS(hist, 256, ave, variance, 0);
	out[4]= _calcCONTRAST(hist, 256, 0);
	out[5]= _calcENERGY(hist, 256, 0);
	out[6]= _calcENTROPY(hist, 256, 0);
	for(n=0 ;n<7 ;n++)
		fprintf(stdout,"%f  \n",out[n]);
}

double _calcAVE(double* hist, int L, int mode)
{
	int n;
	double ave=0;
	for(n=0; n<L; n++)
		ave += (double)n*hist[n];
	return ave;
}

double _calcENTROPY(double* hist, int L, int mode)
{
    int n;
    double epy=0;
    for(n=0; n<L; n++){
		if(hist[n]-0.0 < EPS);
		else	epy += hist[n]*log10(hist[n]);
	}
	epy *= -1.0;
    return epy;
}

double _calcENERGY(double* hist, int L, int mode)
{   
    int n; 
    double egy=0; 
    for(n=0; n<L; n++)
        egy += pow(hist[n],2);
    return egy;
}

double _calcCONTRAST(double* hist, int L, int mode)
{   
    int n; 
    double contrast=0; 
    for(n=0; n<L; n++)
        contrast += pow((double)n,2)*hist[n];
    return contrast;
}
									  

double _calcVALIANCE(double* hist,int L, double ave, int mode)
{
	int n;
	double variance=0;
	for(n=0; n<L; n++)
		variance += pow(((double)n-ave),2)*hist[n];
	return variance;
}

double _calcSKEWNESS(double* hist,int L, double ave, double variance, int mode)
{
	int n;
	double skewness=0;
	for(n=0; n<L; n++)
		skewness += pow(((double)n-ave),3)*hist[n];
	skewness /= pow(variance,1.5);
	return skewness;
}

double _calcKURTOSIS(double* hist ,int L, double ave, double variance, int mode)
{
	int n;
	double kurtosis=0;
	for(n=0; n<L; n++)
		kurtosis += pow(((double)n-ave),4)*hist[n];
	kurtosis /= pow(variance,2);
	return kurtosis;
}
