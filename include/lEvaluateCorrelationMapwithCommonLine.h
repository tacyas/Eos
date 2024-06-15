/*
# lEvaluateCorrelationMapwithCommonLine.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lEvaluateCorrelationMapwithCommonLine.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include<stdio.h>
#include<math.h>
#include "mrcImage.h"
#include<stdlib.h> 

typedef struct lEvaluateCorrelationMapwithCommonLineInfo{
	FILE* In;
	int listLength;
	FILE* InC;
	FILE* Out;
	int PA;
	int PN;
	double PDT;
	int mode;
}lEvaluateCorrelationMapwithCommonLineInfo;

typedef struct lmrcSCMEpeakDetectPixelInfo{
	int x; 
	int y;
	double distance;
	int rank;
}lmrcSCMEpeakDetectPixelInfo;

typedef struct lmrcSCMEpeakDetectInfo{
	int flagOut;
	mrcImage* Out;
	int flagThreshold;
	double Threshold;
	int flagCount;
	int Count;
	lmrcSCMEpeakDetectPixelInfo peak[1000];  
	lmrcSCMEpeakDetectPixelInfo highestPeak[50];
	double MaxI;
	int PA;
	double PDT;
	int mode;
}lmrcSCMEpeakDetectInfo;

extern void lEvaluateCorrelationMapwithCommonLine(lEvaluateCorrelationMapwithCommonLineInfo info, int mode);
extern void lmrcSCMEpeakDetect(mrcImage* in, lmrcSCMEpeakDetectInfo* info, int mode);
