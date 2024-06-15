#ifndef LMRC_IMAGE_VOLUME_CALC_H 
#define LMRC_IMAGE_VOLUME_CALC_H 

/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageVolumeCalc.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lmrcImageVolumeCalc.h
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageVolumeCalcInfo {
	/* Input */
	int    Inverse;

    int nMolecule;
	double MolecularWeight;
	double Density;

		/* for CotourLevel */ 
	int    flagRange;
	double MinVol;
	double MaxVol;
	double DeltaVol;

		/* Change Sampling Units */
	int flagDelta; 
	double Delta;

		/* Change PrintFormat */
	char*  format;

	/* Input/Output */
	int     flagContourLevel;
	int     nContour;
	double* ContourLevel;

	/* Output */
	double* Contour;
	double* Volume;
	int*    VoxelNumber;
	int*    VoxelNumberInv;
} lmrcImageVolumeCalcInfo;
/* struct end */

/* prototype begin */

extern void lmrcImageVolumeCalc(mrcImage* mrc, lmrcImageVolumeCalcInfo* linfo, int mode);
extern void lmrcImageVolumeCalcPrint(FILE* fpt, lmrcImageVolumeCalcInfo* linfo, int mode);

/* prototype end */

#endif /* __LMRCIMAGEVOLUMECALC_H */
