#ifndef LLTLG_2_MRC_H
#define LLTLG_2_MRC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DEBUG
#include "genUtil.h"
#include "File.h"
#include "eosString.h"
#include "ltlgData.h"
#include "mrcImage.h"

/* struct begin */
typedef struct lltlg2mrcInfo {
	    long flagIn;
   		char* In;
    	FILE* fptIn;
    	long flagOut;
    	char* Out;
    	FILE* fptOut;
    	long flagconfigFile;
    	FILE* fptconfigFile;
    	long flagTitle;
    	char* Title;
    	long flagdelta;
    	float delta;
	    long flagRepeatDistance;
   	 	float RepeatDistance;
    	long flagrMax;
    	float rMax;
    	long flagphiStart;
    	float phiStart;
    	long flagzMin;
    	float zMin;
    	long flagzMax;
    	float zMax;
    	long flagdeltaz;
    	float deltaz;
    	long flagWeightOf0thLayer;
    	float WeightOf0thLayer;
    	long flagLayer;
		FILE* fptLayer;
    	long f99;
    	long flagCUT;
    	float CUT;
    	long flagMean;
    	float Mean;
    	long flagSigma;
    	float Sigma;
    	long Inverse;
    	long notInteractive;
    	long AntiPole;
    	long mode;
} lltlg2mrcInfo;
/* struct end */

/* prototype begin */
extern void lltlg2mrc(ltlgData* ltlg, mrcImage* mrc, lltlg2mrcInfo* linfo);
extern void ltlg2mrcConfigFileRead(lltlg2mrcInfo* linfo, FILE* fpt);
/* prototype end */

#endif /* LLTLG_2_MRC_H */
