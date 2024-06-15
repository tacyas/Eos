/*
# lmrcSinogramFETreferredCorrelation.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETreferredCorrelation.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include<math.h>
#include "mrcImage.h"


typedef struct lmrcSinogramFETreferredCorrelationInfo{
	FILE* In;
	FILE* InE;
	FILE* InR;
	FILE* Out;
	mrcImage* weight;
	int nm;
	int om;
	int flagw;
	int zr;
	int tnum;
	int RR;
	int mode;
}lmrcSinogramFETreferredCorrelationInfo;

typedef struct lmrcSinogramFETreferredCorrelationSelectInfo{
	FILE* In;
    FILE* InE;
	FILE* Out;
	int om;
	double* dise3[2];
	int* ptdise3;
	double* angled[4];
	int* topn; 
	char** anglemode;
	int fnum;
	int tnum;
	int RR;
	double** refCart;
	int** refpt;
	int* refVote;
	int mode;
}lmrcSinogramFETreferredCorrelationSelectInfo;


extern void lmrcSinogramFETreferredCorrelation(lmrcSinogramFETreferredCorrelationInfo in, int mode);
extern void lmrcSinogramFETreferredCorrelationSelectDataSet(lmrcSinogramFETreferredCorrelationInfo* in, lmrcSinogramFETreferredCorrelationSelectInfo* out, int mode);
extern void lmrcSinogramFETreferredCorrelationSelect(lmrcSinogramFETreferredCorrelationSelectInfo* in, int cur, int mode);

