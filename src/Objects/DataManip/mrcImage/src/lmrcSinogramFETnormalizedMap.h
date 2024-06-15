/*
# lmrcSinogramFETnormalizedMap.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETnormalizedMap.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include<math.h>
#include "mrcImage.h"

typedef struct lmrcSinogramFETnormalizedMapInfo {
	FILE* In;
	mrcImage* outFET;
	mrcImage* outMAP;
	mrcImage* weight;
	FILE* fptOut;
	FILE* comList;
	int fetz, mapz;
	int flagcomList;
	int flagWeight;
	int flagOutMAP;
	int mode;
	int aatestmode;
}lmrcSinogramFETnormalizedMapInfo;

typedef struct lmrcSinogramFETnormalizedMapAAtestInfo {
	mrcImage* in;
	FILE* comList;
	//mrcImage* out;
	mrcImage* weight;
	int mode;
	int aatestmode;
}lmrcSinogramFETnormalizedMapAAtestInfo; 

typedef struct lmrcSinogramFETnormalizedMapNormalizeInfo {
	mrcImage* in;
	mrcImage* out;
	mrcImage* avesd;
	int mode;
}lmrcSinogramFETnormalizedMapNormalizeInfo;

extern void lmrcSinogramFETnormalizedMap(lmrcSinogramFETnormalizedMapInfo in, int mode);
extern void lmrcSinogramFETnormalizedMapNormalize(lmrcSinogramFETnormalizedMapNormalizeInfo in, int mode);
extern void lmrcSinogramFETnormalizedMapAAtest(lmrcSinogramFETnormalizedMapAAtestInfo in, int mode);




