/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSinogram ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSinogram 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_SINOGRAM_H 
#define  LMRC_IMAGE_SINOGRAM_H

#include "mrcImage.h"

/* struct begin */
typedef struct lmrcImageSinogramInfo {
	double dphi;
	double Smalldphi;
	int correlationMode;
	int LengthMode;
	int LengthCorrelationMode;
	int LengthThresholdMode;

	double weightOf0thDerivation;
	double weightOf1stDerivation;
	double weightOf2ndDerivation;
	double threshold;
	double LengthCorrelationThreshold;
	double weightOfLength;
	double LengthThresholdRatio;

} lmrcImageSinogramInfo;
/* struct end */

/* prototype begin */
extern void lmrcImageSinogramCreate(mrcImage* out, mrcImage* in, lmrcImageSinogramInfo* linfo, int mode);

extern void lmrcImageSinogramCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
void lmrcImageSinogramCorrelation0(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
double lmrcImageOneLineSinogramCorrelation0(mrcImage* in, mrcImage* ref, int mode);

void lmrcImageSinogramCorrelation1(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
void lmrcImageSinogramCorrelation2(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);

void lmrcImageDerivationCalculation(mrcImage* out, mrcImage* in, int mode);
void lmrcImageOneLineDerivationCalculation(mrcImage* out, mrcImage* in, int mode);

void lmrcImageSinogramLengthCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageSinogramInfo* linfo, int mode);
/* prototype end */

#endif
