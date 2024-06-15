/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImagesStatDataGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImagesStatDataGet 
#%Z% Attention
#%Z%
*/

#ifndef  LMRC_IMAGES_STAT_DATA_GET_H 
#define  LMRC_IMAGES_STAT_DATA_GET_H

#include "genUtil.h"
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImagesStatDataGetInfo {
	int      numImage;

	int 	 flagAvg;
	mrcImage Avg;
	int 	 flagTrimmedAvg;
    double   TrimmedRange;
	mrcImage TrimmedAvg;
	int 	 flagMedian;
	mrcImage Median;
	int 	 flagSQRAvg;
	mrcImage SQRAvg;
	int      flagVar;
	mrcImage Var;
	int      flagSD;
	mrcImage SD;
	int      flagSN;
	mrcImage SN;
	int      flagSE;
	mrcImage SE;
	int      flagt;
	mrcImage t;
} lmrcImagesStatDataGetInfo;
/* struct end */

/* prototype begin */
extern void lmrcImagesStatDataGet(lmrcImagesStatDataGetInfo* linfo, mrcImage* srcs, int n, long mode);
extern void lmrcImagesTTest(mrcImage* Prob, mrcImage* TTest, mrcImage* srcs1, int n1, mrcImage* src2, int n2, long mode);
extern void lmrcImagesTTest2(mrcImage* Prob, mrcImage* TTest, mrcImage* Avg1, mrcImage* Var1, int n1, mrcImage* Avg2, mrcImage* Var2, int n2, long mode);
extern void lmrcImagesFTest(mrcImage* FProb, mrcImage* FTest, mrcImage* srcs1, int n1, mrcImage* src2, int n2, long mode);
extern void lmrcImagesFTest2(mrcImage* FProb, mrcImage* FTest, mrcImage* Avg1, mrcImage* Var1, int n1, mrcImage* Avg2, mrcImage* var2, int n2, long mode);

extern void lmrcImagesVarianceMapInformationPrint(FILE* fpt);
extern void lmrcImagesVarianceMap(mrcImage* FProb, mrcImage* FTest, mrcImage* srcs1, int n1, mrcImage* src2, int n2, long mode);
extern void lmrcImagesVarianceMap2(mrcImage* FProb, mrcImage* FTest, mrcImage* avg, mrcImage* var, mrcImage* avg1, mrcImage* var1, int n1, mrcImage* avg2, mrcImage* var2, int n2, long mode);

extern void lmrcImagesVarianceAnalysisInformationPrint(FILE* fpt);
extern void lmrcImagesVarianceAnalysis(mrcImage* FProb, mrcImage* FTest,  mrcImage** src, int* n1, int n2, long mode);
extern void lmrcImagesVarianceAnalysis2(mrcImage* FProb, mrcImage* FTest, mrcImage* avg, mrcImage* var, mrcImage* avgs, mrcImage* vars, int* n1, int n2, long mode);
/* prototype end */

#endif

