/*
# lFETmapOrientationSearchBySimultaneousFitting.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETmapOrientationSearchBySimultaneousFitting.h 
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
//#include "lEvaluateCorrelationMapwithCommonLine.h"  


typedef struct lFETmapOrientationSearchBySimultaneousFittingInfo{
	FILE* InML;
	FILE* InNL;
	FILE* InCL;
	int PM;
	int PN;
	int filesN,filesM;
	double PDT;
	FILE* ChkPtOut;
	FILE* Out;
	int mode;
}lFETmapOrientationSearchBySimultaneousFittingInfo;

typedef struct FETmapPeakTable{
    int*** table;
	int filesN,filesM;
	int PN;
	int PM;
    int mode;
}FETmapPeakTable;
				   
typedef struct lFETmapPeakDetectAndTableMakeInfo{
	FILE* InML;
	FILE* InNL;
	int PM;
	int PN;
	int filesN,filesM;
	double PDT;
	FETmapPeakTable* tableP; 
	int mode;
}lFETmapPeakDetectAndTableMakeInfo;

typedef struct FETCoreTriad{
	int triad[6];
	int matchPosi[3][2];
	double angles[3][2][3];
	double* anglesOf4th;
	double matchingLevel;
	int matchFlag;
	int filesN;
	int mode;
}FETCoreTriad;

typedef struct lFETmapCoreTriadGenerateInfo{
	FILE* InCL;
	int filesN;
	//FETmapPeakTable* tableP;
	FETCoreTriad* CList;
	int mode;
}lFETmapCoreTriadGenerateInfo;

typedef struct RadonSpaceSimultaneousFittingParameters{
	double** table;
	int mode;
}RadonSpaceSimultaneousFittingParameters;

typedef struct lRadonSpaceSimultaneousFittingInfo{
	RadonSpaceSimultaneousFittingParameters* paras;
	FETmapPeakTable* tableP;
	int cycleMaxR;
	int cycleMax;
	int cycleMaxS;
	int coreNum;
	int mode;
}lRadonSpaceSimultaneousFittingInfo;

/*typedef struct lFETmapPeak{
	lmrcSCMEpeakDetectPixelInfo* peak;
	int mode;
}lFETmapPeak;*/

extern void lFETmapOrientationSearchBySimultaneousFitting(lFETmapOrientationSearchBySimultaneousFittingInfo info, int mode); 
extern void lFETmapPeakDetectAndTableMake(lFETmapPeakDetectAndTableMakeInfo* info, int mode);
extern void lFETmapCoreTriadGenerate(FETmapPeakTable* Table, lFETmapCoreTriadGenerateInfo* info, int mode);
extern int lFETBestCoreSearch(FETmapPeakTable* , FETCoreTriad* , int , int );
extern void lFETpointRotation(double axis[3], double point[3], double theta, double* ans, int mode);
extern double lFET4thMatching(FETmapPeakTable* , FETCoreTriad* , int , int , int , int , int );
extern void lRadonSpaceSimultaneousFitting(lRadonSpaceSimultaneousFittingInfo* info, int mode);
extern void lRadonSpaceSimultaneousFittingC(FETmapPeakTable* tableP,RadonSpaceSimultaneousFittingParameters* paras, int* sortN, int mode);
extern int lRadonSpaceSimultaneousFittingCoreSearch(FETmapPeakTable* tableP,RadonSpaceSimultaneousFittingParameters* paras, int* rS[10], int mode);
