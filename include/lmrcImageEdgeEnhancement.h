/*
# lmrcImageEdgeEnhancement.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageEdgeEnhancement.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGEEDGEENHANCEMENT_H 
#define LMRCIMAGEEDGEENHANCEMENT_H 

#include <stdio.h>
#include "mrcImage.h"

/* constant begin */

typedef enum lmrcImageEdgeEnhancementMode {
	lmrcImageEdegeEnhancementModeDifferentialSQRT=0,
	lmrcImageEdegeEnhancementModeDifferentialABS,
	lmrcImageEdegeEnhancementModeRobertsCrossSQRT,
	lmrcImageEdegeEnhancementModeRobertsCrossABS,
	lmrcImageEdegeEnhancementModePrewittSQRT,
	lmrcImageEdegeEnhancementModePrewittABS,
	lmrcImageEdegeEnhancementModeSobelSQRT,
	lmrcImageEdegeEnhancementModeSobelABS,
	lmrcImageEdegeEnhancementModeNegativeLaplacian
} lmrcImageEdgeEnhancementMode;


/* constant end */

/* struct begin */

typedef struct lmrcImageEdgeEnhancementInfo {
	int flagDirection;
	mrcImage* direction;

	// Neigherboring Mode
	int mode;
} lmrcImageEdgeEnhancementInfo; 

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageEdgeEnhancementPrepare(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
extern void lmrcImageEdgeEnhancement(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
extern void lmrcImageEdgeEnhancementModePrint(FILE* fpt);

extern void lmrcImageEdgeEnhancementDifferentialSQRT(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
extern void lmrcImageEdgeEnhancementDifferentialABS(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);

extern void lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
extern void lmrcImageEdgeEnhancementRobertsCrossOperatorABS(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);

extern void lmrcImageEdgeEnhancementPrewittOperatorSQRT(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
extern void lmrcImageEdgeEnhancementPrewittOperatorABS(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);

extern void lmrcImageEdgeEnhancementSobelOperatorSQRT(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
extern void lmrcImageEdgeEnhancementSobelOperatorABS(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);

extern void lmrcImageEdgeEnhancementNegativeLaplacian(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode);
/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
