/*
# lmrcImageSinogramCorrelationAdditionalWeight : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSinogramCorrelationAdditionalWeight 
# Attention
#   $Loccker$
#  	$State$ 
#
*/

#define DEBUG
#include "genUtil.h"
#include "./lmrcImageSinogram.h"
#include "./lmrcImageBinarization.h"
#include "Memory.h"

double 
lmrcImageOneLineSinogramCorrelationAdditionalWeight(mrcImage* in, mrcImage* ref, int mode);

double 
__OneLineCorrelationCalculationAdditionalWeight(mrcImage* in, mrcImage* ref, mrcImage* tmpIn, mrcImage* tmpRef, double* thresIn, double* thresRef, int i, int j, int mode);

void 
__DensitySubtractAdditionalWeight(mrcImage* tmp, mrcImage* in, double* thres, int y, int mode);

double
lmrcImageOneLineSinogramCorrelationAdditionalWeight(mrcImage* in, mrcImage* ref, int mode)
{
	int i, j;
	mrcImageParaTypeReal x;
	double data;
	mrcImage tmpIn, tmpRef;
	double thresIn;
	double thresRef;

	tmpIn.HeaderN.x = in->HeaderN.x;
	tmpIn.HeaderN.y = tmpIn.HeaderN.z = 1;
	tmpIn.HeaderLength.x = in->HeaderLength.x;
	tmpIn.HeaderLength.y = tmpIn.HeaderLength.z = 0;
	tmpIn.HeaderMode = mrcFloatImage;
	mrcInit(&tmpIn, NULL);

	tmpRef.HeaderN.x = ref->HeaderN.x;
	tmpRef.HeaderN.y = tmpRef.HeaderN.z = 1;
	tmpRef.HeaderLength.x = ref->HeaderLength.x;
	tmpRef.HeaderLength.y = tmpRef.HeaderLength.z = 0;
	tmpRef.HeaderMode = mrcFloatImage;
	mrcInit(&tmpRef, NULL);

	thresIn = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(in, 256, 0); 
	thresRef = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(ref, 256, 0); 

	__DensitySubtractAdditionalWeight(&tmpIn, in, &thresIn, 0, 0);
	__DensitySubtractAdditionalWeight(&tmpRef, ref, &thresRef, 0, 0);

	data = __OneLineCorrelationCalculationAdditionalWeight(in, ref, &tmpIn, &tmpRef, &thresIn, &thresRef, 0, 0, mode);

	mrcImageFree(&tmpIn, "in lmrcImageOneLineSinogramCorrelationAdditionalWeight");
	mrcImageFree(&tmpRef, "in lmrcImageOneLineSinogramCorrelationAdditionalWeight");
	return(data);
}

void
__DensitySubtractAdditionalWeight(mrcImage* tmp, mrcImage* in, double* thres, int y, int mode)
{
	int    x, count;
	double data;
	double avg;

	count = avg = 0;
	for(x=0; x<tmp->HeaderN.x; x++) {
		mrcPixelDataGet(in, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
		if(thres[y]<data) {
			count++;
			avg += data;
		}
	}
	if(count!=0) {
		avg /= count;
	} else {
		avg = 0;
	}
	for(x=0; x<tmp->HeaderN.x; x++) {
		mrcPixelDataGet(in,     x,   y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
		mrcPixelDataSet(tmp, x, 0.0, 0.0, data-avg, mrcPixelRePart);
	}
}

double
__OneLineCorrelationCalculationAdditionalWeight(mrcImage* in, mrcImage* ref, mrcImage* tmpIn, mrcImage* tmpRef, double* thresIn, double* thresRef, int i, int j, int mode)
{
	double data;
	double data1, data2;
	double sum1, sum2;
	int    k;

	data = sum1 = sum2 = 0 ;
	for(k=0; k<tmpIn->HeaderN.x; k++) {
		mrcPixelDataGet(in,   k, i, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(ref,  k, j, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);

		if(thresIn[i]<data1 && thresRef[j]<data2) {
			mrcPixelDataGet(tmpIn,  k, 0, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(tmpRef, k, 0, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
			switch(mode){
				case 2 :
					data1 *= SQR(k*tmpIn->HeaderLength.x)*tmpIn->HeaderLength.x;
					data2 *= SQR(k*tmpIn->HeaderLength.x)*tmpIn->HeaderLength.x;
					data += data1*data2;
					sum1 += SQR(data1);
					sum2 += SQR(data2);
				break;
				case 3:
					data += SQR(fabs(data1 - data2))*SQR(k*tmpIn->HeaderLength.x)*tmpIn->HeaderLength.x;
				break;
			}
		}
	}
	switch(mode){
		case 2 :
			data = data/(sqrt(sum1*sum2));
		break;
	}

	return(data);
}
