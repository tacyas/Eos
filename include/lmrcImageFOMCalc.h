/*
# lmrcImageFOMCalc.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFOMCalc.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */


#include "mrcImage.h" 

typedef struct lmrcImageFOMCalcInfo {
	int     inImageNumber; // Number of InImages
	double* Weight;        // Weight of InImages

	// Ring Range 
	double minR; 		// min 1/A 
	double maxR; 		// max 1/A

	double deltaAlpha; // delta 

	// Sector Range
	double minSector; 
	double maxSector; 
	double delSector;
	
	// Scaling Factor
	double* Scale;

	//	
	int flagRScale;

	//
	double  XXMax;

	// Output
	double FOM;
	int	   Num;

} lmrcImageFOMCalcInfo;

double lmrcImageFOMCalc(mrcImage* in, mrcImage* ref, lmrcImageFOMCalcInfo* linfo, int mode);
double lmrcImageFOMScaleCalc(mrcImage* in, mrcImage* ref, lmrcImageFOMCalcInfo* linfo, int mode);
double lmrcImageFOMXMaxCalc(mrcImage* in, mrcImage* ref, lmrcImageFOMCalcInfo* linfo, int mode);
