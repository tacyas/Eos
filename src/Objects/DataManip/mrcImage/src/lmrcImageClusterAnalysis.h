/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageClusterAnalysis ver %I%
#%Z% Created by Narita  
#%Z% Modified by Tac for AutoRotationMode 
#%Z%
#%Z% Usage : mrcImageClusterAnalysis
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#define DEBUG

#include "genUtil.h"
#include "mrcImage.h"
#include "nr2.h"
#include "mrcRefUtil.h"
#include "lmrcImageMultiplying.h"
#include "lmrcImageCorrelation.h"

/* struct begin */
typedef enum lmrcImageClusterAnalysisMode {
	lmrcImageClusterAnalysisModeCorrelation    = 0,
	lmrcImageClusterAnalysisModeEuclidDistance = 1,
	lmrcImageClusterAnalysisModeWardMethod     = 2,
	lmrcImageClusterAnalysisModeWardMethodLinearCorrelation     = 3,
	lmrcImageClusterAnalysisModeLinearCorrelation     = 4,
	lmrcImageClusterAnalysisModeMethodMask     = 7
} lmrcImageClusterAnalysisMode;

#ifdef GLOBAL_DECLARATION
char* lmrcImageClusterAnalysisModeMessage[17] = {
	"By Correlation",
	"By Euclid Distance",
	"By Ward Method (default) : Euclid Length (no rotation) or its square (rotation)",
	"By Ward Method using Linear Correlation : (1 - Correlation)/(1 + Correlation)",
	"By Linear Correlation :                   (1 - Correlation)/(1 + Correlation)",
	"Not supported",
	"Not supported",
	"used for method masking",
	"Not supported."
};
#endif

typedef struct lmrcImageClusterAnalysisInfo {
	lmrcImageClusterAnalysisMode mode;          /* ClusterAnalysisMode */
	int flagIteration;                          /* */
	int flagAutoRotation; 
	char** filename;                            /* filename */
	int correlationMode;                        /* correlationMode */
	mrcImage* averagedImage;
	lmrcImageAutoRotationCorrelationInfo arInitial;

	int flagPVM;

	int flagLogIn;
	FILE* fptLogIn;
	int previousFileNumber;

	int   flagLogBinary;
	FILE* fptLogBinary; /* Binary Log */

	int   flagLog;
	FILE* fptLog;  /* All Log */

	int   flagLog2;
	FILE* fptLog2; /* Cluster Node Log */

	int   NoRecalculation;
	/* Output */
	float** Distance;

} lmrcImageClusterAnalysisInfo;

/* struct end */

/* prototype begin */
#ifdef __cplusplus
extern "C" {
#endif

void lmrcImageClusterAnalysis(int* group, mrcImage* in, int finalclusternum, int N, lmrcImageClusterAnalysisInfo* linfo);
void lmrcImageClusterMerge(mrcImage* in1, mrcImage* in2, int* index, int* averagednum, int m, int n, int* N);
void lmrcImageDistanceCalc(float* dis, mrcImage* in1, mrcImage* in2, int mode);
void lmrcImageDistanceCalcByWardMethod(float* dis, mrcImage* in1, mrcImage* in2, int num1, int num2, int mode);

void lmrcImageDistanceCalcWithAutoRotation(float* dis, mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int mode);
void lmrcImageDistanceCalcByWardMethodWithAutoRotation(float* dis, mrcImage* out, mrcImage* cor, mrcImage* in1, mrcImage* in2, int num1, int num2,  lmrcImageAutoRotationCorrelationInfo* linfo, int lmode, int mode);

float lmrcImageClusterAnalysisByIteration(int* group, mrcImage* in, int clusternum, int N, int mode);

void lmrcImageClusterAnalysisDistanceToLog(FILE* fpt, int n, int m, int prevM, int prevN, float distance);
void lmrcImageClusterAnalysisDistanceFromLog(int* skip, float* distance, FILE* fpt);

#ifdef __cplusplus
};
#endif
/* prototype end */
