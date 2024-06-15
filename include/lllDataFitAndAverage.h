#ifndef LLLDATA_FIT_AND_AVERAGE_INFO
#define LLLDATA_FIT_AND_AVERAGE_INFO
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFitAndAverage.h ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFitAndAverage.h 
#%Z% Attention
#%Z%
*/

#include "llData.h"
#include "lllDataFit.h"
#include "ctfInfo.h"

/* struct begin */
typedef struct lllDataFitAndAverageInfo {
	int nFile;
	int times;
	int flagOutParam2;
	char** OutParam2;
	char** In;

	int flagAveragingWithoutAntiPole;
	int flagAveragingBelowThreshold;
	float threshold; 

	FILE* fptLog;

	int flagCTF;
	int ctfMode;
	ctfInfo* CTF;
	
	int flagWeight;
	llDataParaTypeReal* weight;

	double noise;

	int mode;

	int flagPVM;
	lllDataFitPVMInfo vPVM;
} lllDataFitAndAverageInfo;

/* struct end */

/* prototype begin */
extern void lllDataFitAndAverage(llData* llAve, llData* llOut, 
                                 llData* llIn,  llData llRef, 
								 llDataFittedParam* paraFit, 
								 lllDataFitAndAverageInfo info);


extern void lllDataAverage(llData* llAve, llData* llOut, 
                                 llData* llIn,  llData llRef, 
								 llDataFittedParam* paraFit, 
								 lllDataFitAndAverageInfo info,
								 int mode);
/* prototype end */

#endif /* LLLDATA_FIT_AND_AVERAGE_INFO */
