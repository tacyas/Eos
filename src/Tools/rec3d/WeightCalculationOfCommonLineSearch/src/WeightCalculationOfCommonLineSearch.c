/*
# WeightCalculationOfCommonLineSearch : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : WeightCalculationOfCommonLineSearch
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
#include "eosString.h"
#include "mrcImage.h"
#include "Matrix3D.h"
#include "lmrcImageSinogram.h"

#include "lmrcImageFileListAndEulerAngleDataRead.h"
#include "lCommonLineCalculation.h"

typedef struct lWeightCalculationOfCommonLineSearchInfo {
	double* CorrelationWeight;
	int     LengthThresholdMode;
	double  LengthThresholdRatio;
	int     mode;
}lWeightCalculationOfCommonLineSearchInfo;

typedef enum lWeightCalculationOfCommonLineSearchMode {
	AdditionWeightMode       = 0,
	MultiplicationWeightMode = 1,
} lWeightCalculationOfCommonLineSearchMode;


extern void lWeightCalculationOfCommonLineSearch(mrcImage* in, lWeightCalculationOfCommonLineSearchInfo* linfo, int mode);
extern void lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication(mrcImage* in, lWeightCalculationOfCommonLineSearchInfo* linfo, int mode);
extern void lmrcImageOneLineGet(mrcImage* out, mrcImage* in, float angle, int mode);
extern void inv1(double* a, int n, int nn);
extern void AdditionWeightCalculation(double* NormalCorrelation, double* Derivation1DCorrelation, double* Derivation2DCorrelation, 
                                      double* LengthCorrelation, lWeightCalculationOfCommonLineSearchInfo* linfo, int pairNumber);
extern void MultiplicationWeightCalculation(double* NormalCorrelation, double* Derivation1DCorrelation, double* Derivation2DCorrelation, 
                                            double* LenghtCorrelation, lWeightCalculationOfCommonLineSearchInfo* linfo, int pairNumber);

int
main(int argc, char* argv[]) 
{
	WeightCalculationOfCommonLineSearchInfo info;
	lWeightCalculationOfCommonLineSearchInfo linfo;
	mrcImage In;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	linfo.LengthThresholdMode  = info.LengthThresholdMode;
	linfo.LengthThresholdRatio = info.LengthThresholdRatio;
	linfo.mode                 = info.mode;
	
	linfo.CorrelationWeight = (double *)memoryAllocate(sizeof(double)*4, "in main");

	DEBUGPRINT("Program Start\n");

	lmrcImageFileListAndEulerAngleDataRead(&In, info.In, info.flagIn, info.fptInList, 0);
	lWeightCalculationOfCommonLineSearch(&In, &linfo, 0);

	fprintf(info.fptOut, "Weight of NormalCorrelation       is %f\n", linfo.CorrelationWeight[0]);
	fprintf(info.fptOut, "Weight of Derivation1DCorrelation is %f\n", linfo.CorrelationWeight[1]);
	fprintf(info.fptOut, "Weight of Derivation2DCorrelation is %f\n", linfo.CorrelationWeight[2]);
	fprintf(info.fptOut, "Weight of LengthCorrelation       is %f\n", linfo.CorrelationWeight[3]);
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "-m :\n");
	fprintf(stderr, "    0 : Addition weight\n");
	fprintf(stderr, "    1 : Multiplication weight\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- input file format -----\n");
	fprintf(stderr, "filename(sin) rotationalmode angle angle angle\n");
	fprintf(stderr, "   .                .          .     .     .  \n");
	fprintf(stderr, "   .                .          .     .     .  \n");
	fprintf(stderr, "   .                .          .     .     .  \n");
	fprintf(stderr, "   .                .          .     .     .  \n");
	fprintf(stderr, "\n");
}

void
lWeightCalculationOfCommonLineSearch(mrcImage* in, lWeightCalculationOfCommonLineSearchInfo* linfo, int mode)
{
	switch(linfo->mode){
	case AdditionWeightMode:
	case MultiplicationWeightMode:
		lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication(in, linfo, linfo->mode);
	break;
	}
}

void
lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication(mrcImage* in, lWeightCalculationOfCommonLineSearchInfo* linfo, int mode)
{
	mrcImageParaTypeInteger    ImageNumber;
	int                        i, j;
	mrcImage                   sino1;
	mrcImage                   sino2;
	mrcImage                   sino1oneline;
	mrcImage                   sino2oneline;
	mrcImage                   sino1onelineDerivation1D;
	mrcImage                   sino1onelineDerivation2D;
	mrcImage                   sino2onelineDerivation1D;
	mrcImage                   sino2onelineDerivation2D;
	lCommonLineCalculationInfo CommonLineInfo;
	double*                    NormalCorrelation;
	double*                    LengthCorrelation;
	double*                    Derivation1DCorrelation;
	double*                    Derivation2DCorrelation;
	mrcImage                   NormalCorrelationImage;
	mrcImage                   LengthCorrelationImage;
	mrcImage                   Derivation1DCorrelationImage;
	mrcImage                   Derivation2DCorrelationImage;
	lmrcImageSinogramInfo      SinogramInfo;
	int                        pair = 0;
    int                        pairNumber;

	ImageNumber = in->numTailer;
	pairNumber  = ImageNumber*(ImageNumber-1)/2;

	NormalCorrelation       = (double *)memoryAllocate(sizeof(double)*pairNumber, "in lWeightCalculationOfCommonLineSearch");
	LengthCorrelation       = (double *)memoryAllocate(sizeof(double)*pairNumber, "in lWeightCalculationOfCommonLineSearch");
	Derivation1DCorrelation = (double *)memoryAllocate(sizeof(double)*pairNumber, "in lWeightCalculationOfCommonLineSearch");
	Derivation2DCorrelation = (double *)memoryAllocate(sizeof(double)*pairNumber, "in lWeightCalculationOfCommonLineSearch");

	SinogramInfo.LengthCorrelationMode = 0;
	SinogramInfo.LengthThresholdMode   = linfo->LengthThresholdMode;
	SinogramInfo.LengthThresholdRatio  = linfo->LengthThresholdRatio;
	SinogramInfo.dphi                  = in->HeaderLength.y*RADIAN;
	SinogramInfo.correlationMode       = 0;

	CommonLineInfo.I1Angle1 = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I1Angle2 = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I1Angle3 = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I2Angle1 = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I2Angle2 = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I2Angle3 = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.CLAngleOnI1AgainstI2  = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.CLAngleOnI2AgainstI1  = MemoryAllocate(float, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.flag     = MemoryAllocate(int,   pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I1RotationalMode  = MemoryAllocate(char*, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	CommonLineInfo.I2RotationalMode  = MemoryAllocate(char*, pairNumber, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	for(i=0; i<pairNumber; i++){
		CommonLineInfo.I1RotationalMode[i]  = MemoryAllocate(char, 5, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
		CommonLineInfo.I2RotationalMode[i]  = MemoryAllocate(char, 5, "in lWeightCalculationOfCommonLineSearchByAdditionAndMultiplication");
	}
	
	for(i=0;   i<ImageNumber-1; i++){
		mrcImageSectionGet(&sino1, in, i, 1);
	for(j=i+1; j<ImageNumber;   j++){
		
		/* angle1 and angle2 are calculated by CommonLineCalculation*/		
		CommonLineInfo.I1Angle1[pair] = in->Tailer[i].Cont.Rot1;
		CommonLineInfo.I1Angle2[pair] = in->Tailer[i].Cont.Rot2;
		CommonLineInfo.I1Angle3[pair] = in->Tailer[i].Cont.Rot3;
		CommonLineInfo.I2Angle1[pair] = in->Tailer[j].Cont.Rot1;
		CommonLineInfo.I2Angle2[pair] = in->Tailer[j].Cont.Rot2;
		CommonLineInfo.I2Angle3[pair] = in->Tailer[j].Cont.Rot3;
		strcpy(CommonLineInfo.I1RotationalMode[pair], in->Tailer[i].Cont.EulerAngleMode);
		strcpy(CommonLineInfo.I2RotationalMode[pair], in->Tailer[j].Cont.EulerAngleMode);

		lCommonLineCalculation1(&CommonLineInfo, pair, 0);
		
		/* each correlations are calculated */		
		mrcImageSectionGet(&sino2, in, j, 1);

		lmrcImageOneLineGet(&sino1oneline, &sino1, CommonLineInfo.CLAngleOnI1AgainstI2[pair], 0);
		lmrcImageOneLineGet(&sino2oneline, &sino2, CommonLineInfo.CLAngleOnI2AgainstI1[pair], 0);

		lmrcImageSinogramCorrelation0(&NormalCorrelationImage, &sino1oneline, &sino2oneline, &SinogramInfo, 0);
		
		lmrcImageDerivationCalculation(&sino1onelineDerivation1D ,&sino1oneline, 1);
		lmrcImageDerivationCalculation(&sino2onelineDerivation1D ,&sino2oneline, 1);
		lmrcImageSinogramCorrelation0(&Derivation1DCorrelationImage, &sino1onelineDerivation1D, &sino2onelineDerivation1D, &SinogramInfo, 0);
		
		lmrcImageDerivationCalculation(&sino1onelineDerivation2D ,&sino1oneline, 2);
		lmrcImageDerivationCalculation(&sino2onelineDerivation2D ,&sino2oneline, 2);
		lmrcImageSinogramCorrelation0(&Derivation2DCorrelationImage, &sino1onelineDerivation2D, &sino2onelineDerivation2D, &SinogramInfo, 0);

		lmrcImageSinogramLengthCorrelation(&LengthCorrelationImage, &sino1oneline, &sino2oneline, &SinogramInfo, 0);

		mrcPixelDataGet(&NormalCorrelationImage,       0, 0, 0, &NormalCorrelation[pair],       mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&Derivation1DCorrelationImage, 0, 0, 0, &Derivation1DCorrelation[pair], mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&Derivation2DCorrelationImage, 0, 0, 0, &Derivation2DCorrelation[pair], mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&LengthCorrelationImage,       0, 0, 0, &LengthCorrelation[pair],       mrcPixelRePart, mrcPixelHowNearest);

		pair++;
	
		mrcImageFree(&sino1oneline, 0);
		mrcImageFree(&sino2oneline, 0);
		mrcImageFree(&sino1onelineDerivation1D, 0);
		mrcImageFree(&sino1onelineDerivation2D, 0);
		mrcImageFree(&sino2onelineDerivation1D, 0);
		mrcImageFree(&sino2onelineDerivation2D, 0);
		mrcImageFree(&NormalCorrelationImage, 0);
		mrcImageFree(&Derivation1DCorrelationImage, 0);
		mrcImageFree(&Derivation2DCorrelationImage, 0);
		mrcImageFree(&LengthCorrelationImage, 0);
	
	}
	}
	mrcImageFree(in, 0);

	/* Matrix calculation for each weight*/

	switch(mode){
	case AdditionWeightMode:
		AdditionWeightCalculation(NormalCorrelation, Derivation1DCorrelation, Derivation2DCorrelation, LengthCorrelation, linfo, pairNumber);
	break;
	case MultiplicationWeightMode:
		MultiplicationWeightCalculation(NormalCorrelation, Derivation1DCorrelation, Derivation2DCorrelation, LengthCorrelation, linfo, pairNumber);
	break;
	}
}

void
AdditionWeightCalculation(double* NormalCorrelation, double* Derivation1DCorrelation, double* Derivation2DCorrelation,
                          double* LengthCorrelation, lWeightCalculationOfCommonLineSearchInfo* linfo, int pairNumber)
{
	int      i, j;
	double*  CorrelationSum;
	double** CorrelationMultiplication;
	double** InverseCorrelationMultiplication;
	double   workMatrix[4][4];
	double*  workvector;
	double   weightSum;

		CorrelationSum = (double *)memoryAllocate(sizeof(double)*4, "in lWeightCalculationOfCommonLineSearch");
		for(i=0; i<4; i++){
			CorrelationSum[i] = 0;
		}
		for(i=0; i<pairNumber; i++){
			CorrelationSum[0] += NormalCorrelation[i];
			CorrelationSum[1] += Derivation1DCorrelation[i];
			CorrelationSum[2] += Derivation2DCorrelation[i];
			CorrelationSum[3] += LengthCorrelation[i];
		}

		CorrelationMultiplication        = (double **)memoryAllocate(sizeof(double*)*4, "in lWeightCalculationOfCommonLineSearch");
		for(i=0; i<4; i++){
			CorrelationMultiplication[i]        = (double *)memoryAllocate(sizeof(double)*4, "in lWeightCalculationOfCommonLineSearch");
		}

		for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			CorrelationMultiplication[i][j]        = 0;
		}
		}
	
		for(i=0; i<pairNumber; i++){
			CorrelationMultiplication[0][0] += NormalCorrelation[i]*NormalCorrelation[i];
			CorrelationMultiplication[1][0] += NormalCorrelation[i]*Derivation1DCorrelation[i];
			CorrelationMultiplication[2][0] += NormalCorrelation[i]*Derivation2DCorrelation[i];
			CorrelationMultiplication[3][0] += NormalCorrelation[i]*LengthCorrelation[i];
			CorrelationMultiplication[0][1] += Derivation1DCorrelation[i]*NormalCorrelation[i];
			CorrelationMultiplication[1][1] += Derivation1DCorrelation[i]*Derivation1DCorrelation[i];
			CorrelationMultiplication[2][1] += Derivation1DCorrelation[i]*Derivation2DCorrelation[i];
			CorrelationMultiplication[3][1] += Derivation1DCorrelation[i]*LengthCorrelation[i];
			CorrelationMultiplication[0][2] += Derivation2DCorrelation[i]*NormalCorrelation[i];
			CorrelationMultiplication[1][2] += Derivation2DCorrelation[i]*Derivation1DCorrelation[i];
			CorrelationMultiplication[2][2] += Derivation2DCorrelation[i]*Derivation2DCorrelation[i];
			CorrelationMultiplication[3][2] += Derivation2DCorrelation[i]*LengthCorrelation[i];
			CorrelationMultiplication[0][3] += LengthCorrelation[i]*NormalCorrelation[i];
			CorrelationMultiplication[1][3] += LengthCorrelation[i]*Derivation1DCorrelation[i];
			CorrelationMultiplication[2][3] += LengthCorrelation[i]*Derivation2DCorrelation[i];
			CorrelationMultiplication[3][3] += LengthCorrelation[i]*LengthCorrelation[i];
		}
		
		/*inverse matrix is calculated*/
		InverseCorrelationMultiplication = (double **)memoryAllocate(sizeof(double*)*4, "in lWeightCalculationOfCommonLineSearch");
		for(i=0; i<4; i++){
			InverseCorrelationMultiplication[i] = (double *)memoryAllocate(sizeof(double)*4, "in lWeightCalculationOfCommonLineSearch");
		}

		for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			workMatrix[i][j] = CorrelationMultiplication[i][j];
			InverseCorrelationMultiplication[i][j] = 0;
		}
		}

		inv1(workMatrix, 4, 4);

		for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			InverseCorrelationMultiplication[i][j] = workMatrix[i][j];
		}
		}

		workvector = (double *)memoryAllocate(sizeof(double)*4, "in lWeightCalculationOfCommonLineSearch");
		for(i=0; i<4; i++){
			workvector[i] = 0;
		}

		for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			workvector[i] += InverseCorrelationMultiplication[i][j]*CorrelationSum[j];
		}
		}

		linfo->CorrelationWeight[0] = workvector[0];
		linfo->CorrelationWeight[1] = workvector[1];
		linfo->CorrelationWeight[2] = workvector[2];
		linfo->CorrelationWeight[3] = workvector[3];

		weightSum = 0;
		for(i=0; i<4; i++){
			weightSum += linfo->CorrelationWeight[i];
		}
		for(i=0;i<4; i++){
			linfo->CorrelationWeight[i] /= weightSum;
		}
}

void
MultiplicationWeightCalculation(double* NormalCorrelation, double* Derivation1DCorrelation, double* Derivation2DCorrelation, 
                               double* LengthCorrelation, lWeightCalculationOfCommonLineSearchInfo* linfo, int pairNumber)
{
	int i;
	double weight0, weight1, weight2, weight3;
	double weight0OfFinalCorrelationMin;
	double weight1OfFinalCorrelationMin;
	double weight2OfFinalCorrelationMin;
	double weight3OfFinalCorrelationMin;
	double weight0Max, weight0Min;
	double weight1Max, weight1Min;
	double weight2Max, weight2Min;
	double weight3Max, weight3Min;
	double deltaweight;
	double FinalCorrelation;
	double FinalCorrelationMin;
	double power0, power1, power2, power3, powerFinal;

	weight0Max = weight1Max = weight2Max = weight3Max = 8.0;
	weight0Min = weight1Min = weight2Min = weight3Min = pow(2, 0.5);
	weight0OfFinalCorrelationMin = 0;
	weight1OfFinalCorrelationMin = 0;
	weight2OfFinalCorrelationMin = 0;
	weight3OfFinalCorrelationMin = 0;
	FinalCorrelation = 0;
	FinalCorrelationMin = 10000000;
	deltaweight         = pow(2, 0.5);

	while(deltaweight > 1.001){
		for(weight0 = weight0Min; weight0 <= weight0Max; weight0 += deltaweight){
		for(weight1 = weight1Min; weight1 <= weight1Max; weight1 += deltaweight){
		for(weight2 = weight2Min; weight2 <= weight2Max; weight2 += deltaweight){
		for(weight3 = weight3Min; weight3 <= weight3Max; weight3 += deltaweight){
			FinalCorrelation = 0;
			for(i=0; i<pairNumber; i++){
				power0 = pow(1-NormalCorrelation[i],       weight0);
				power1 = pow(1-Derivation1DCorrelation[i], weight1);
				power2 = pow(1-Derivation2DCorrelation[i], weight2);
				power3 = pow(1-LengthCorrelation[i],       weight3);
				powerFinal = pow(power0*power1*power2*power3, 1/(weight0+weight1+weight2+weight3));
				FinalCorrelation += powerFinal;
			}
			if(FinalCorrelation < FinalCorrelationMin){
				FinalCorrelationMin          = FinalCorrelation;
				weight0OfFinalCorrelationMin = weight0;
				weight1OfFinalCorrelationMin = weight1;
				weight2OfFinalCorrelationMin = weight2;
				weight3OfFinalCorrelationMin = weight3;
			}
		}
		}
		}
		}
		deltaweight = pow(deltaweight, 0.5);
		weight0Min = weight0OfFinalCorrelationMin/pow(deltaweight, 2);
		weight1Min = weight1OfFinalCorrelationMin/pow(deltaweight, 2);
		weight2Min = weight2OfFinalCorrelationMin/pow(deltaweight, 2);
		weight3Min = weight3OfFinalCorrelationMin/pow(deltaweight, 2);
		weight0Max = weight0OfFinalCorrelationMin*pow(deltaweight, 2);
		weight1Max = weight1OfFinalCorrelationMin*pow(deltaweight, 2);
		weight2Max = weight2OfFinalCorrelationMin*pow(deltaweight, 2);
		weight3Max = weight3OfFinalCorrelationMin*pow(deltaweight, 2);
	}
	linfo->CorrelationWeight[0] = weight0OfFinalCorrelationMin;
	linfo->CorrelationWeight[1] = weight1OfFinalCorrelationMin;
	linfo->CorrelationWeight[2] = weight2OfFinalCorrelationMin;
	linfo->CorrelationWeight[3] = weight3OfFinalCorrelationMin;

}

void
lmrcImageOneLineGet(mrcImage* out, mrcImage* in, float angle, int mode)
{
	int    i;
	float  y;
	double data;

	out->Header = in->Header;
	out->HeaderN.y = 1;
	out->HeaderN.z = 1;
	mrcInit(out, NULL);

	y /= (in->HeaderLength.y*RADIAN);

	for(i=0; i<in->HeaderN.x; i++){
		mrcPixelDataGet(in , i, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(out, i, 0, 0,  data, mrcPixelRePart);
	}
}

void
inv1(double* a, int n ,int nn)
{
	int i,j,k;
	double p,q;
	double *ak,*ai;

	for(k=0, ak=a; k<n; ++k, ak+=nn){
		p=ak[k];
		ak[k]=1.0;
		for(j=0; j<n; ++j){
			ak[j] /= p;
		}
		for(i=0, ai=a; i<n; ++i, ai+=nn){
			if(i!=k){
				q     = ai[k];
				ai[k] = 0.0;
				for(j=0; j<n; ++j){
					ai[j] -= q*ak[j];
				}
			}
		}
	}
}
