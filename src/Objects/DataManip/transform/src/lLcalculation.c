/*
# lLcalculation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lLcalculation 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"
#include "lmrcImageSinogram.h"

double
lLcalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, 
			  mrcImage* refOneLineFT,
			  mrcImage* otherOneLineFT, 
			  mrcImage* refOneLineSino, 
			  mrcImage* otherOneLineSino, 
			  CommonLineData* commonlinedata, 
			  double delU, int Num, int mode)
{
	int m;
    double L;
	double ReRefData, ReOtherData;
	double ImRefData, ImOtherData;
	double length, lengthSum;
	double RefAngle, OtherAngle, DifferentialAngle;
	int min=0;
	double normalL=0, phaseL=0;

	switch(linfo->ModeCalculationArea){
		case 0 :
			min = 0;
		break;
		case 1 :
			min = (int)(linfo->ThresholdCalculationArea/delU);
		break;
	}

    L = 0;
	lengthSum = 0;
	switch(linfo->ModeL){
		case 0 :
		case 1 :{
		    for(m=min; m<=refOneLineFT->HeaderN.x/2; m++){
				mrcPixelDataGet(refOneLineFT,   m, 0, 0, &ReRefData,   mrcPixelRePart, mrcPixelHowNearest);
			    mrcPixelDataGet(otherOneLineFT, m, 0, 0, &ReOtherData, mrcPixelRePart, mrcPixelHowNearest);
			    mrcPixelDataGet(refOneLineFT,   m, 0, 0, &ImRefData,   mrcPixelImPart, mrcPixelHowNearest);
	   			mrcPixelDataGet(otherOneLineFT, m, 0, 0, &ImOtherData, mrcPixelImPart, mrcPixelHowNearest);
	
				switch(linfo->ModeL){
					case 0 :
						L += SQR(ReRefData - ReOtherData)*SQR(m*delU)*delU*commonlinedata[Num].angularweight;
						L += SQR(ImRefData - ImOtherData)*SQR(m*delU)*delU*commonlinedata[Num].angularweight;
					break;
					case 1 :
						length = (sqrt(SQR(ReRefData) + SQR(ImRefData)) + sqrt(SQR(ReOtherData) + SQR(ImOtherData)))/2;
						RefAngle   = atan2(ImRefData,   ReRefData);
						if(RefAngle < 0)   RefAngle   += 2*M_PI;
						OtherAngle = atan2(ImOtherData, ReOtherData);
						if(OtherAngle < 0) OtherAngle += 2*M_PI;
						if(RefAngle < OtherAngle){
							DifferentialAngle = MIN(         OtherAngle - OtherAngle,
													2*M_PI -(OtherAngle - OtherAngle));
						}
						else{
							DifferentialAngle = MIN(          RefAngle - OtherAngle,
													2*M_PI - (RefAngle - OtherAngle));
						}
						L += (length*SQR(DifferentialAngle))*SQR(m*delU)*delU*commonlinedata[Num].angularweight;
						lengthSum += length*SQR(m*delU)*delU*commonlinedata[Num].angularweight;
					break;
				}
			}
			break;
		}
	}

	switch(linfo->ModeL){
		case 1 :
			L /= lengthSum;
			L  = sqrt(L);
		break;
		case 2 :{ /* (1- sinogram correlation)*(1 - derivation1D correlation) */
			mrcImage RefDerivation1D;
			mrcImage OtherDerivation1D;
			double normalCor, derivation1DCor;
			
			lmrcImageOneLineDerivationCalculation(&RefDerivation1D,   refOneLineSino,   1);
			lmrcImageOneLineDerivationCalculation(&OtherDerivation1D, otherOneLineSino, 1);
			normalCor       = lmrcImageOneLineSinogramCorrelationAdditionalWeight(refOneLineSino, otherOneLineSino, linfo->ModeL);
			derivation1DCor = lmrcImageOneLineSinogramCorrelationAdditionalWeight(&RefDerivation1D,  &OtherDerivation1D,  linfo->ModeL);
			L = (1-normalCor)*(1-derivation1DCor)*commonlinedata[Num].angularweight;

			mrcImageFree(&RefDerivation1D, "in lLcalculation");
			mrcImageFree(&OtherDerivation1D, "in lLcalculation");
			break;
		}
		case 3 :{
			mrcImage RefDerivation1D;
			mrcImage OtherDerivation1D;
			double normalCor, derivation1DCor;

			lmrcImageOneLineDerivationCalculation(&RefDerivation1D,   refOneLineSino,   1);
			lmrcImageOneLineDerivationCalculation(&OtherDerivation1D, otherOneLineSino, 1);
			normalCor     = lmrcImageOneLineSinogramCorrelationAdditionalWeight(refOneLineSino, otherOneLineSino, linfo->ModeL);
			derivation1DCor = lmrcImageOneLineSinogramCorrelationAdditionalWeight(&RefDerivation1D,  &OtherDerivation1D,  linfo->ModeL);
			L = normalCor*derivation1DCor*commonlinedata[Num].angularweight;

			mrcImageFree(&RefDerivation1D, "in lLcalculation");
			mrcImageFree(&OtherDerivation1D, "in lLcalculation");
			break;
		}
	}
	return(L);
}
