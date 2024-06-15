/*
# lmrcImageSinogramCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSinogramCorrelation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/

#undef DEBUG
#include "genUtil.h"
#include "./lmrcImageSinogram.h"
#include "./lmrcImageBinarization.h"
#include "Memory.h"

void lmrcImageSinogramCorrelation0(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
double lmrcImageOneLineSinogramCorrelation0(mrcImage* in, mrcImage* ref, int mode);
double __OneLineCorrelationCalculation(mrcImage* in, mrcImage* ref, mrcImage* tmpIn, mrcImage* tmpRef, double* thresIn, double* thresRef, int i, int j, int mode);

void lmrcImageSinogramCorrelation1(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
void lmrcImageSinogramCorrelation2(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
void lmrcImageSinogramCorrelation3(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
void lmrcImageSinogramLengthCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);

void lmrcImageDerivationCalculation(mrcImage* out, mrcImage* in, int mode);
void lmrcImageOneLineDerivationCalculation(mrcImage* out, mrcImage* in, int mode);

void __DensitySubtract(mrcImage* tmp, mrcImage* in, double* thres, int y, int mode);

void
lmrcImageSinogramCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode)
{
	int i,j;
	mrcImage* LenCor;
	double Outdata, Lendata;

	switch(mode) { /* lmrcImageSinogramCorrelation */
		case 0: { 
			DEBUGPRINT("/** mode=0: Normal Correlation **/");
			lmrcImageSinogramCorrelation0(out, in, ref, linfo, mode);
			break;
		}
		case 1: { /* lmrcImageSinogramCorrelation+1Dderivation+2Dderivation */
			DEBUGPRINT("/** mode=1: Sum of Weighted Correlation of corr, corr of 1st dev, and corr of 2nd dev   **/");
			lmrcImageSinogramCorrelation1(out, in, ref, linfo, mode);
			break;
		}
		case 2: { /* lmrcImageSinogramCorrelation0*1Dderivation*2Dderivation */
			DEBUGPRINT("/** mode=2:  Mupltipying of Correlation of crr, corr of 1st dev, and corr of 2nd dev **/");
			lmrcImageSinogramCorrelation2(out, in, ref, linfo, mode);
			break;
		}
		case 3: {
			DEBUGPRINT("/** mode=3;  Mupltipying of Weighted Correlation of crr, corr of 1st dev, and corr of 2nd dev  **/");
			lmrcImageSinogramCorrelation3(out, in, ref, linfo, mode);
			break;
		}
	}

	switch(linfo->LengthMode) {
		case 1: { /* LengthCorrelation */
			DEBUGPRINT("/** LengthMode=1;  particle size calculated from 1st dev  **/");
			LenCor  =(mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation");
			lmrcImageSinogramLengthCorrelation(LenCor, in , ref, linfo, mode);
			switch(linfo->LengthCorrelationMode) {       /* Threshold of LengthCorrelation */
				case 0: {  /* weight of LengthCorrelation */
					for(i=0; i<out->HeaderN.x; i++){
					for(j=0; j<out->HeaderN.y; j++){
						mrcPixelDataGet(   out, i, j, 0, &Outdata, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(LenCor, i, j, 0, &Lendata, mrcPixelRePart, mrcPixelHowNearest);
						Outdata += Lendata*linfo->weightOfLength;
						mrcPixelDataSet(out, i, j, 0, Outdata, mrcPixelRePart);
					}
					}
					break;
				}
				case 1: {
					for(i=0; i<out->HeaderN.x; i++){
					for(j=0; j<out->HeaderN.y; j++){
						mrcPixelDataGet(   out, i, j, 0, &Outdata, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(LenCor, i, j, 0, &Lendata, mrcPixelRePart, mrcPixelHowNearest);
						Outdata *= Lendata;
						mrcPixelDataSet(out, i, j, 0, Outdata, mrcPixelRePart);
					}
					}
					break;
				}	
				case 2: {  /* MultiplicationWeight of LengthCorrelation */
					for(i=0; i<out->HeaderN.x; i++){
					for(j=0; j<out->HeaderN.y; j++){
						mrcPixelDataGet(   out, i, j, 0, &Outdata, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(LenCor, i, j, 0, &Lendata, mrcPixelRePart, mrcPixelHowNearest);
			    		Outdata = pow(Outdata+Lendata, 1/(linfo->weightOf0thDerivation+linfo->weightOf1stDerivation+linfo->weightOf2ndDerivation+linfo->weightOfLength));
						mrcPixelDataSet(out, i, j, 0, Outdata, mrcPixelRePart);
					}
					}
					break;
				}
			}
			break;
		}	
	}
}

void
lmrcImageSinogramLengthCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode)
{
	int i,j;
	int left, right;
	int* InLength;
	int* RefLength;
	double derivation1Ddata;
	double* derivation1DIndataMax;
	double* derivation1DRefdataMax;
	double LengthCorrelation;
	
	mrcImage* derivation1DIn;
	mrcImage* derivation1DRef;

	out->HeaderN.x = in->HeaderN.y;
	out->HeaderN.y = ref->HeaderN.y;
	out->HeaderN.z = 1;
	out->HeaderLength.x = in->HeaderLength.y;
	out->HeaderLength.y = ref->HeaderLength.y;
	out->HeaderLength.z = 0;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	derivation1DIn  =(mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramLengthCorrelation");
	derivation1DRef =(mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramLengthCorrelation");

	InLength = (int*)memoryAllocate(sizeof(int)*in->HeaderN.y, "in lmrcImageSinogramLengthCorrelation");
	RefLength = (int*)memoryAllocate(sizeof(int)*ref->HeaderN.y, "in lmrcImageSinogramLengthCorrelation");

	lmrcImageDerivationCalculation(derivation1DIn,   in, 1);
	lmrcImageDerivationCalculation(derivation1DRef, ref, 1);

	derivation1DIndataMax = (double*)memoryAllocate(sizeof(double)*derivation1DIn->HeaderN.y, "in lmrcImageSinogramLengthCorrelation");
	derivation1DRefdataMax = (double*)memoryAllocate(sizeof(double)*derivation1DRef->HeaderN.y, "in lmrcImageSinogramLengthCorrelation");

	if(linfo->LengthThresholdMode == 0){
		for(i=0; i<derivation1DIn->HeaderN.y; i++){
			derivation1DIndataMax[i] = 0;
		for(j=0; j<derivation1DIn->HeaderN.x; j++){
			mrcPixelDataGet(derivation1DIn, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
			if(derivation1DIndataMax[i] < derivation1Ddata){
				derivation1DIndataMax[i] = derivation1Ddata;
			}
		}
		}

		for(i=0; i<derivation1DRef->HeaderN.y; i++){
			derivation1DRefdataMax[i] = 0;
		for(j=0; j<derivation1DRef->HeaderN.x; j++){
			mrcPixelDataGet(derivation1DRef, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
			if(derivation1DRefdataMax[i] < derivation1Ddata){
				derivation1DRefdataMax[i] = derivation1Ddata;
			}
		}
		}
	}
	else if(linfo->LengthThresholdMode == 1){
		for(i=0; i<derivation1DIn->HeaderN.y; i++){
		for(j=0; j<derivation1DIn->HeaderN.x; j++){
			mrcPixelDataGet(derivation1DIn, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
				derivation1DIndataMax[i] += derivation1Ddata;
		}
		derivation1DIndataMax[i] /=derivation1DIn->HeaderN.x;
		}

		for(i=0; i<derivation1DRef->HeaderN.y; i++){
		for(j=0; j<derivation1DRef->HeaderN.x; j++){
			mrcPixelDataGet(derivation1DRef, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
				derivation1DRefdataMax[i] += derivation1Ddata;
		}
		derivation1DRefdataMax[i] /= derivation1DRef->HeaderN.x;
		}
	}
	
    for(i=0; i<in->HeaderN.y; i++){
		j = 0;
		do{
			mrcPixelDataGet(derivation1DIn, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
			j++;	
		} while(pow(derivation1DIndataMax[i]*linfo->LengthThresholdRatio,2.0) > pow(derivation1Ddata,2.0) && j<in->HeaderN.x);
		left = j-1;

		j = in->HeaderN.x-1;
		do{
			mrcPixelDataGet(derivation1DIn, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
			j--;
		}while(pow(derivation1DIndataMax[i]*linfo->LengthThresholdRatio,2.0) > pow(derivation1Ddata,2.0) && 0 <= j);
		right = j+1;
	
		InLength[i] = right-left+1;
	}	

    for(i=0; i<ref->HeaderN.y; i++){
		j = 0;
		do{
			mrcPixelDataGet(derivation1DRef, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
			j++;	
		} while(pow(derivation1DRefdataMax[i]*linfo->LengthThresholdRatio,2.0) > pow(derivation1Ddata,2.0) && j<ref->HeaderN.x);
		left = j-1;

		j = ref->HeaderN.x-1;
		do {
			mrcPixelDataGet(derivation1DRef, j, i, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest);
			j--;
		} while(pow(derivation1DRefdataMax[i]*linfo->LengthThresholdRatio,2.0) > pow(derivation1Ddata,2.0) && 0 <= j);
		right = j+1;
		RefLength[i] = right-left+1;
	}	

	for(i=0; i< in->HeaderN.y; i++) {
	for(j=0; j<ref->HeaderN.y; j++) {
		if(InLength[i]<=0 || RefLength[j]<=0) {
			LengthCorrelation = 0;
		} else {
			LengthCorrelation = 1-fabs((double)(InLength[i]-RefLength[j]))/(InLength[i]+RefLength[j]);
			if(LengthCorrelation < 0 ) {
				fprintf(stderr, "Something Wrong !! Length : In %d Ref %d LengthCorrelation %f\n", InLength[i], RefLength[j], LengthCorrelation);
			}
		}
		switch(linfo->LengthCorrelationMode) {
			case 1: {
				if(LengthCorrelation > linfo->LengthCorrelationThreshold){
					mrcPixelDataSet(out, i, j, 0, LengthCorrelation, mrcPixelRePart);
				} else{
					mrcPixelDataSet(out, i, j, 0, 0.0, mrcPixelRePart);
				}
				break;
			}
			default: {
				mrcPixelDataSet(out, i, j, 0, LengthCorrelation, mrcPixelRePart);
				break;
			}
		}
DEBUGPRINT5("LengthCorrelation=%f InLength[%d]=%d RefLength[%d]=%d\n", LengthCorrelation, i, InLength[i], j, RefLength[j]);
	}
	}
	free(derivation1DIn);
	free(derivation1DRef);
	free(InLength);
	free(RefLength);
	free(derivation1DIndataMax);
	free(derivation1DRefdataMax);
}

/*
	Sinogram Correlation

	Linear Correlation
*/
void
lmrcImageSinogramCorrelation0(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode)
{
	int i, j;
	mrcImageParaTypeReal x;
	double data;
	mrcImage tmpIn, tmpRef;
	double* thresIn;
	double* thresRef;

	out->HeaderN.x = in->HeaderN.y;
	out->HeaderN.y = ref->HeaderN.y;
	out->HeaderN.z = 1;
	out->HeaderLength.x = in->HeaderLength.y;	
	out->HeaderLength.y = ref->HeaderLength.y;	
	out->HeaderLength.z = 0;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

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

	thresIn  = (double*)memoryAllocate(sizeof(double)*out->HeaderN.x, "tmpIn");
	for(i=0; i<out->HeaderN.x; i++) { /* in */
		for(x=0; x<tmpIn.HeaderN.x; x++) {
			mrcPixelDataGet(in,    x, i, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataSet(&tmpIn, x, 0.0, 0.0, data, mrcPixelRePart);
		}
		thresIn[i]  = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(&tmpIn, 256, 0); 
	}

	thresRef = (double*)memoryAllocate(sizeof(double)*out->HeaderN.y, "tmpRef");
	for(j=0; j<out->HeaderN.y; j++) { /* ref */		
		for(x=0; x<tmpRef.HeaderN.x; x++) {
			mrcPixelDataGet(ref,    x, j, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataSet(&tmpRef, x, 0.0, 0.0, data, mrcPixelRePart);
		}
		thresRef[j]  = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(&tmpRef, 256, 0); 
	}

	for(i=0; i<out->HeaderN.x; i++) { /* in */
		__DensitySubtract(&tmpIn, in, thresIn, i, 0);
	for(j=0; j<out->HeaderN.y; j++) { /* ref */		
		__DensitySubtract(&tmpRef, ref, thresRef, j, 0);

		data = __OneLineCorrelationCalculation(in, ref, &tmpIn, &tmpRef, thresIn, thresRef, i, j, 0);
		
		mrcPixelDataSet(out, i, j, 0.0, data, mrcPixelRePart);
	}
	}
}

double
lmrcImageOneLineSinogramCorrelation0(mrcImage* in, mrcImage* ref, int mode)
{
	int i, j;
	mrcImageParaTypeReal x;
	double data;
	mrcImage tmpIn, tmpRef;
	double thresIn;
	double thresRef;

	thresIn = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(in, 256, 0); 
	thresRef = lmrcImageDeterminationOfThresholdForBinarizationByOhtsuMethod(ref, 256, 0); 

	__DensitySubtract(&tmpIn, in, &thresIn, 0, 0);
	__DensitySubtract(&tmpRef, ref, &thresRef, 0, 0);

	data = __OneLineCorrelationCalculation(in, ref, &tmpIn, &tmpRef, &thresIn, &thresRef, 0, 0, 0);
		
	return(data);
}

void
__DensitySubtract(mrcImage* tmp, mrcImage* in, double* thres, int y, int mode)
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
__OneLineCorrelationCalculation(mrcImage* in, mrcImage* ref, mrcImage* tmpIn, mrcImage* tmpRef, double* thresIn, double* thresRef, int i, int j, int mode)
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
			data += data1*data2;
			sum1 += SQR(data1);
			sum2 += SQR(data2);
		}
	}
	data = data/(sqrt(sum1*sum2));

	return(data);
}

void
lmrcImageDerivationCalculation(mrcImage* out, mrcImage* in, int mode)
{
	int i,j;
	double Zerodata, Plusdata, Minusdata;
	double Derivationdata;


	out->Header = in->Header;
	mrcInit(out, NULL);
	
	switch(mode){
		case 1 :
		case 2 :{
			for(i=0; i<in->HeaderN.y; i++){
			for(j=0; j<in->HeaderN.x; j++){
				mrcPixelDataGet(in, j, i, 0.0, &Zerodata, mrcPixelRePart, mrcPixelHowNearest);
				if(j==0) mrcPixelDataGet(in, in->HeaderN.x-1, i, 0.0, &Minusdata, mrcPixelRePart, mrcPixelHowNearest); 
				else     mrcPixelDataGet(in, j-1, i, 0.0, &Minusdata, mrcPixelRePart, mrcPixelHowNearest); 

				if(j==in->HeaderN.x-1) mrcPixelDataGet(in, 0, i, 0.0, &Plusdata, mrcPixelRePart, mrcPixelHowNearest);
				else                   mrcPixelDataGet(in, j+1, i, 0.0, &Plusdata, mrcPixelRePart, mrcPixelHowNearest); 

				if(mode==1)      Derivationdata = (Plusdata-Minusdata)/2;
				else if(mode==2) Derivationdata = Plusdata+Minusdata-2*Zerodata;

				mrcPixelDataSet(out, j, i, 0.0, Derivationdata, mrcPixelRePart);
			}
			}
			break;
		}
		default :
			fprintf(stderr, "Not supported !");
		break;
	}
}

void
lmrcImageOneLineDerivationCalculation(mrcImage* out, mrcImage* in, int mode)
{
	int j;
	double Zerodata, Plusdata, Minusdata;
	double Derivationdata;

	out->Header = in->Header;
	mrcInit(out, NULL);

	for(j=0; j<in->HeaderN.x; j++){
		mrcPixelDataGet(in, j, 0, 0.0, &Zerodata, mrcPixelRePart, mrcPixelHowNearest);
		if(j==0) mrcPixelDataGet(in, in->HeaderN.x-1, 0, 0.0, &Minusdata, mrcPixelRePart, mrcPixelHowNearest); 
		else     mrcPixelDataGet(in, j-1, 0, 0.0, &Minusdata, mrcPixelRePart, mrcPixelHowNearest); 

		if(j==in->HeaderN.x-1) mrcPixelDataGet(in, 0, 0, 0.0, &Plusdata, mrcPixelRePart, mrcPixelHowNearest);
		else                   mrcPixelDataGet(in, j+1, 0, 0.0, &Plusdata, mrcPixelRePart, mrcPixelHowNearest); 

		if(mode==1)      Derivationdata = (Plusdata-Minusdata)/2;
		else if(mode==2) Derivationdata = Plusdata+Minusdata-2*Zerodata;
		else             break; 

		mrcPixelDataSet(out, j, 0, 0.0, Derivationdata, mrcPixelRePart);
	}
}

void
lmrcImageSinogramCorrelation1(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode)
{
	int i, j;
	double weight1, weight2, weight3;
	double derivation1Ddata, derivation2Ddata, Correlationdata;
	double data;
	mrcImage* CorrelationOut;
	mrcImage* derivation1DOut;
	mrcImage* derivation2DOut;
	mrcImage* derivation1DRef;
	mrcImage* derivation2DRef;
	mrcImage* derivation1DIn;
	mrcImage* derivation2DIn;

	out->HeaderN.x = in->HeaderN.y;
	out->HeaderN.y = ref->HeaderN.y;
	out->HeaderN.z = 1;
	out->HeaderLength.x = in->HeaderLength.y;	
	out->HeaderLength.y = ref->HeaderLength.y;	
	out->HeaderLength.z = 0;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	CorrelationOut  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation1DOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation2DOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation1DRef = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation2DRef = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation1DIn  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation2DIn  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");

	lmrcImageSinogramCorrelation0(CorrelationOut, in, ref, linfo, mode);
	
	lmrcImageDerivationCalculation(derivation1DIn,   in, 1);
	lmrcImageDerivationCalculation(derivation1DRef, ref, 1);
	lmrcImageSinogramCorrelation0(derivation1DOut, derivation1DIn, derivation1DRef, linfo, mode);
	
	lmrcImageDerivationCalculation(derivation2DIn,   in, 2);
	lmrcImageDerivationCalculation(derivation2DRef, ref, 2);
	lmrcImageSinogramCorrelation0(derivation2DOut, derivation2DIn, derivation2DRef, linfo, mode);
 
	weight1=linfo->weightOf0thDerivation;
	weight2=linfo->weightOf1stDerivation;
	weight3=linfo->weightOf2ndDerivation;
	for(i=0; i<out->HeaderN.x; i++){
	for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(derivation1DOut,    i, j, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(derivation2DOut,    i, j, 0.0, &derivation2Ddata, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(CorrelationOut ,    i, j, 0.0, &Correlationdata , mrcPixelRePart, mrcPixelHowNearest); 
			data = weight1*Correlationdata+weight2*derivation1Ddata+weight3*derivation2Ddata;
			mrcPixelDataSet(out, i, j, 0, data, mrcPixelRePart);
	}
	}
		mrcImageFree(CorrelationOut, 0);
		mrcImageFree(derivation1DOut, 0);
		mrcImageFree(derivation2DOut, 0);
		mrcImageFree(derivation1DRef, 0);
		mrcImageFree(derivation2DRef, 0);
		mrcImageFree(derivation1DIn, 0);
		mrcImageFree(derivation2DIn, 0);
}

void
lmrcImageFiltering(mrcImage* in, lmrcImageSinogramInfo* linfo)
{
	int i,j;
	double data;

	for(i=0; i<in->HeaderN.x; i++){
	for(j=0; j<in->HeaderN.y; j++){
		mrcPixelDataGet(in, i, j, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest); 
		if(data<linfo->threshold){
			data = 0.0;
		}
		mrcPixelDataSet(in, i, j, 0, data, mrcPixelRePart);
	}
	}

}

void
lmrcImageSinogramCorrelation2(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode)
{
	int i, j;
	double derivation1Ddata, derivation2Ddata, Correlationdata;
	double data;
	mrcImage* CorrelationOut;
	mrcImage* derivation1DOut;
	mrcImage* derivation2DOut;
	mrcImage* derivation1DRef;
	mrcImage* derivation2DRef;
	mrcImage* derivation1DIn;
	mrcImage* derivation2DIn;

	out->HeaderN.x = in->HeaderN.y;
	out->HeaderN.y = ref->HeaderN.y;
	out->HeaderN.z = 1;
	out->HeaderLength.x = in->HeaderLength.y;	
	out->HeaderLength.y = ref->HeaderLength.y;	
	out->HeaderLength.z = 0;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	CorrelationOut  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");
	derivation1DOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");
	derivation2DOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");
	derivation1DRef = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");
	derivation2DRef = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");
	derivation1DIn  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");
	derivation2DIn  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation2");

	lmrcImageSinogramCorrelation0(CorrelationOut, in, ref, linfo, mode);
	
	lmrcImageDerivationCalculation(derivation1DIn,     in, 1);
	lmrcImageDerivationCalculation(derivation1DRef, ref, 1);
	lmrcImageSinogramCorrelation0(derivation1DOut, derivation1DIn, derivation1DRef, linfo, mode);
	
	lmrcImageDerivationCalculation(derivation2DIn,     in, 2);
	lmrcImageDerivationCalculation(derivation2DRef, ref, 2);
	lmrcImageSinogramCorrelation0(derivation2DOut, derivation2DIn, derivation2DRef, linfo, mode);

for(i=0; i<out->HeaderN.x; i++){
for(j=0; j<out->HeaderN.y; j++){
	mrcPixelDataGet(derivation1DOut,    i, j, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest); 
	mrcPixelDataGet(derivation2DOut,    i, j, 0.0, &derivation2Ddata, mrcPixelRePart, mrcPixelHowNearest); 
	mrcPixelDataGet(CorrelationOut ,    i, j, 0.0, &Correlationdata , mrcPixelRePart, mrcPixelHowNearest); 
	DEBUGPRINT5("Correlation[%d][%d]=%f derication1D=%f derivation2D=%f\n",i, j, Correlationdata, derivation1Ddata, derivation2Ddata);
}
}

	lmrcImageFiltering(CorrelationOut, linfo);
	lmrcImageFiltering(derivation1DOut, linfo);
	lmrcImageFiltering(derivation2DOut, linfo);

	for(i=0; i<out->HeaderN.x; i++){
	for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(derivation1DOut,    i, j, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(derivation2DOut,    i, j, 0.0, &derivation2Ddata, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(CorrelationOut ,    i, j, 0.0, &Correlationdata , mrcPixelRePart, mrcPixelHowNearest); 
			data = Correlationdata*derivation1Ddata*derivation2Ddata;
			mrcPixelDataSet(out, i, j, 0, data, mrcPixelRePart);
	}
	}
		mrcImageFree(CorrelationOut, 0);
		mrcImageFree(derivation1DOut, 0);
		mrcImageFree(derivation2DOut, 0);
		mrcImageFree(derivation1DRef, 0);
		mrcImageFree(derivation2DRef, 0);
		mrcImageFree(derivation1DIn, 0);
		mrcImageFree(derivation2DIn, 0);
}

void
lmrcImageSinogramCorrelation3(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode)
{
	int i, j;
	double weight1, weight2, weight3;
	double derivation1Ddata, derivation2Ddata, Correlationdata;
	double data;
	mrcImage* CorrelationOut;
	mrcImage* derivation1DOut;
	mrcImage* derivation2DOut;
	mrcImage* derivation1DRef;
	mrcImage* derivation2DRef;
	mrcImage* derivation1DIn;
	mrcImage* derivation2DIn;

	out->HeaderN.x = in->HeaderN.y;
	out->HeaderN.y = ref->HeaderN.y;
	out->HeaderN.z = 1;
	out->HeaderLength.x = in->HeaderLength.y;	
	out->HeaderLength.y = ref->HeaderLength.y;	
	out->HeaderLength.z = 0;
	out->HeaderMode = mrcFloatImage;
	mrcInit(out, NULL);

	CorrelationOut  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation1DOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation2DOut = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation1DRef = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation2DRef = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation1DIn  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");
	derivation2DIn  = (mrcImage*)memoryAllocate(sizeof(mrcImage), "in lmrcImageSinogramCorrelation1");

	lmrcImageSinogramCorrelation0(CorrelationOut, in, ref, linfo, mode);
	
	lmrcImageDerivationCalculation(derivation1DIn,     in, 1);
	lmrcImageDerivationCalculation(derivation1DRef, ref, 1);
	lmrcImageSinogramCorrelation0(derivation1DOut, derivation1DIn, derivation1DRef, linfo, mode);
	
	lmrcImageDerivationCalculation(derivation2DIn,     in, 2);
	lmrcImageDerivationCalculation(derivation2DRef, ref, 2);
	lmrcImageSinogramCorrelation0(derivation2DOut, derivation2DIn, derivation2DRef, linfo, mode);
 
	weight1=linfo->weightOf0thDerivation;
	weight2=linfo->weightOf1stDerivation;
	weight3=linfo->weightOf2ndDerivation;
	for(i=0; i<out->HeaderN.x; i++){
	for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(derivation1DOut,    i, j, 0.0, &derivation1Ddata, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(derivation2DOut,    i, j, 0.0, &derivation2Ddata, mrcPixelRePart, mrcPixelHowNearest); 
			mrcPixelDataGet(CorrelationOut ,    i, j, 0.0, &Correlationdata , mrcPixelRePart, mrcPixelHowNearest); 
			data = weight1*Correlationdata+weight2*derivation1Ddata+weight3*derivation2Ddata;
			data = pow(Correlationdata, weight1)*pow(derivation1Ddata, weight2)*pow(derivation2Ddata, weight3);
			mrcPixelDataSet(out, i, j, 0, data, mrcPixelRePart);
	}
	}
		mrcImageFree(CorrelationOut, 0);
		mrcImageFree(derivation1DOut, 0);
		mrcImageFree(derivation2DOut, 0);
		mrcImageFree(derivation1DRef, 0);
		mrcImageFree(derivation2DRef, 0);
		mrcImageFree(derivation1DIn, 0);
		mrcImageFree(derivation2DIn, 0);
}
