/*
# lFETOrientationSearchByAnnealing.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETOrientationSearchByAnnealing.h 
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
#include "lCommonLineCalculation.h"


typedef struct lFETOrientationSearchByAnnealingInfo{
	mrcImage* InMS;
	FILE* InFL;
	FILE* InML;
	int fnum;
	int flagInML;
	double ITemp;
	int as1;
	double as2;
	int as3;
	FILE* Out;
	int mode;
}lFETOrientationSearchByAnnealingInfo;

typedef struct lFETsimultaneousMinimizationDataSet{
	mrcImage* map;
	int dImage;
	unsigned* sflag; 
	double* cAngle[3];  //3 means euler angle set
	double dAngle[3];   //
	int** cPos[3];      //3  x, y, z
	int* dPos[3];       // 
	double** cUs;
	double* dUs;
	double cU;
	double dU;
	double* cUt;
	lCommonLineCalculationInfo* clc;
	int n, z;
	int mode;
}lFETsimultaneousMinimizationDataSet;



typedef struct lFETOrientationSearchByAnnealingDataSet{
	int fnum;
	mrcImage* FETs;
	mrcImage* maps; 
	double** angles;
	double** CPVtable;
	int current;
	double angle[3];
	double* CPVtemp;
	int mode;
}lFETOrientationSearchByAnnealingDataSet;








extern void lFETOrientationSearchByAnnealing(lFETOrientationSearchByAnnealingInfo info, int mode);
extern void lFETOrientationSearchByRigidSubsetCore(lFETOrientationSearchByAnnealingInfo info, int mode);
extern void lFETOrientationSearchByRigidSubsetCore_Search(lFETsimultaneousMinimizationDataSet* , int );
extern void lFETsimultaneousMinimizationDataSetMemoryAllocate(lFETsimultaneousMinimizationDataSet* in, int n, int mode);
extern void lFETsimultaneousMinimizationRandomParaSet(lFETsimultaneousMinimizationDataSet* in, int mode);
extern void lFETsimultaneousMinimizationLcalculate(lFETsimultaneousMinimizationDataSet* in, int mode);
extern void lFETsimultaneousMinimizationOverWrite(lFETsimultaneousMinimizationDataSet* in, int mode);










