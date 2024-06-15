/*
# lmrcSinogramFETcorrelationMap.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETcorrelationMap.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include<math.h>
#include "mrcImage.h"


typedef struct lmrcSinogramFETcorrelationMapInfo {
	int flagWeight;
	mrcImage* Weight;
	int flagSD;
	mrcImage* SD;
	int Nmode,Cmode;
	int mode;
}lmrcSinogramFETcorrelationMapInfo;

extern void lmrcSinogramFETcorrelationMap(mrcImage* ,mrcImage* ,mrcImage* ,lmrcSinogramFETcorrelationMapInfo ,int );
extern void lmrcSinogramFETnormalizeBySD(mrcImage* ,mrcImage* ,double* ,int );
extern void lmrcSinogramFETcorrelationMapCounterMatching(mrcImage* ,mrcImage* ,int );
extern void lmrcSinogramFETcorrelationMapDP(mrcImage* in, mrcImage* out, double* w, int mode);
