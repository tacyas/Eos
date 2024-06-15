/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSSDA ver %I%
#%Z% Created by tacyas 
#%Z%
#%Z% Usage : lmrcImageSSDA 
#%Z% Attention
#%Z%
*/
#ifndef  LMRC_IMAGE_SSDA_H 
#define  LMRC_IMAGE_SSDA_H

#include "mrcImage.h"

/*
	SSDA: Sequential Smilarity Detection Algorithm
*/

/* struct begin */
typedef struct lmrcImageSSDAInfo {
	double Threshold; 	/* Threshold Level */
	double Error; 		/* Sum of residual differences at (x, y)*/
	mrcImageParaTypeRealCoord p; 		/* Lower Right Point Coordinate on Partial Image on the Input Image */
	mrcImageParaTypeRealCoord optimump; /* Optimum Point */
	mrcImageParaTypeRealCoord smin;     /* Search Area: Bottom Right */
	mrcImageParaTypeRealCoord smax; 	/* Search Area: Top Left */
	mrcImageParaTypeRealCoord predict;  /* Predictive Point */
	mrcImageParaTypeInteger n; 			/* Addition Times at (x, y)*/
} lmrcImageSSDAInfo;

/* struct end */

/* prototype begin */
extern void
lmrcImageSSDAAutomaticThresholdAndFineSearch(mrcImage* in,                 
											mrcImage* ref,
											lmrcImageSSDAInfo* info,
											mrcImageParaTypeInteger mode
											);
extern void
__lmrcImageResidualDifferenceAdditionForSSDA(mrcImage* in, 					/* Input Image */ 
											mrcImage* ref,					/* Template Image */ 
											lmrcImageSSDAInfo* info,		/* Required Information */ 
											mrcImageParaTypeInteger mode
											);

#ifdef PVM

extern void lmrcImageSSDAInfoSendByPVM(lmrcImageSSDAInfo* linfo, int tid, int mode);
extern void lmrcImageSSDAInfoRecieveByPVM(lmrcImageSSDAInfo* linfo, int tid, int mode);

#endif
/* prototype end */
#endif
