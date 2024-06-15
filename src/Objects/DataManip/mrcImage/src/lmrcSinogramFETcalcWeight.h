/*
# lmrcSinogramFETcalcWeight.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETcalcWeight.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <math.h>
#include "mrcImage.h"
#include "lmrcSinogramFET.h"


typedef struct lmrcSinogramFETcalcWeightInfo {
	FILE* In;
	FILE* InC;
	int mode;
}lmrcSinogramFETcalcWeightInfo;

extern void lmrcSinogramFETcalcWeight(mrcImage* out, lmrcSinogramFETcalcWeightInfo info, int mode);
extern void lmrcSinogramFETcalcWeightRankCount(float* );
extern void lmrcSinogramFETcalcWeight_dRankCount(float* , float* );
extern int lmrcSinogramFETcalcWeightFETnormalize(FILE* in, mrcImage* out, int mode);
extern void lmrcSinogramFETcalcWeightCalcDistance(mrcImage *, int , int );
extern void lmrcSinogramFETcalcWeightCalcCommonLinePickUp(FILE* comLine, int cfet, int mode);	
extern float lmrcSinogramFETcalcWeight_func(float* );
extern void lmrcSinogramFETcalcWeight_dfunc(float* , float* );
