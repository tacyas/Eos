/*
# lmrcFETnormalizeBySD.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcFETnormalizeBySD.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include<stdio.h>
#include<math.h>
#include "mrcImage.h"

typedef struct lmrcFETnormalizeBySDInfo{
	FILE* InList;
	long listLength;
	FILE* InSampleList;
	long flagWriteSD;
	mrcImage* writeSD;
	long flagReadSD;
	mrcImage* readSD;
	int flagOut;
	mrcImage* Out;
}lmrcFETnormalizeBySDInfo;
	
extern void lmrcFETnormalizeBySD(lmrcFETnormalizeBySDInfo info, int mode);
extern void calcSDofFET(FILE* list, int n, double* ave, double* sd, int mode);
extern void _normalizeBySDandDataWrite(FILE* list, int n, double* ave, double* sd, lmrcFETnormalizeBySDInfo info, int mode);




