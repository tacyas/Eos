/* in lmrcImageCTFDetermination.c */
#include "ctfInfo.h"
typedef struct lmrcImageCTFDeterminationInfo {
	ctfInfo val;
	ctfInfo min;
	ctfInfo max;
	ctfInfo del;
	mrcImageParaTypeReal Rmax;
	mrcImage Dif;
	double minPhase;
	double minDef;
	double minRatio;
	FILE*   Out;
} lmrcImageCTFDeterminationInfo;
extern void lmrcImageCTFDetemination(lmrcImageCTFDeterminationInfo *linfo, mrcImage* in, mrcImage* ref);
