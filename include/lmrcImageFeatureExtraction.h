/*
# lmrcImageFeatureExtraction.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFeatureExtraction.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include<stdio.h>
#include<math.h>
#include "mrcImage.h"

typedef struct lmrcImageFeatureExtractionInfo {
	int co_r;
	int co_theta;
	int rl_theta;
	int rl_dev;
	int mode;
}lmrcImageFeatureExtractionInfo;




extern void lmrcImageFeatureExtraction(mrcImage* in, mrcImage* out, lmrcImageFeatureExtractionInfo info, int mode);
extern void lmrcImageFeatureExtraction_densityHist(mrcImage* in, double* out, int mode);
extern void lmrcImageFeatureExtractionCoOccurrence(mrcImage* in, double* out, lmrcImageFeatureExtractionInfo info, int mode); 
extern void lmrcImageFeatureExtractionRunLength(mrcImage* in, double* out, lmrcImageFeatureExtractionInfo info, int         mode);

