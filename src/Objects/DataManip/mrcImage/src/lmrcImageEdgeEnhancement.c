/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageEdgeEnhancement ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageEdgeEnhancement 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageEdgeEnhancement ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include "Memory.h"
#include "./lmrcImageEdgeEnhancement.h"

void
lmrcImageEdgeEnhancementModePrint(FILE* fpt)
{
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeDifferentialSQRT, "Differential(SQRT)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeDifferentialABS, "Differential(ABS)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeRobertsCrossSQRT, "Roberts Cross(SQRT)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeRobertsCrossABS, "Roberts Cross(ABS)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModePrewittSQRT, "Prewitt(SQRT)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModePrewittABS, "Prewitt(ABS)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeSobelSQRT, "Sobel(SQRT)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeSobelABS, "Sobel(ABS)");
	fprintf(stderr, "mode: %d : %s\n", lmrcImageEdegeEnhancementModeNegativeLaplacian, "NegativeLaplacian");
}

void
lmrcImageEdgeEnhancement(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
{
	switch(mode) {
 		case lmrcImageEdegeEnhancementModeDifferentialSQRT:
			lmrcImageEdgeEnhancementDifferentialSQRT(out, in, linfo, mode);
			break;
		case lmrcImageEdegeEnhancementModeDifferentialABS:
			lmrcImageEdgeEnhancementDifferentialABS(out, in, linfo, mode);
			break;
		case lmrcImageEdegeEnhancementModeRobertsCrossSQRT:
			lmrcImageEdgeEnhancementRobertsCrossOperatorSQRT(out, in, linfo, mode);
			break;
    	case lmrcImageEdegeEnhancementModeRobertsCrossABS:
			lmrcImageEdgeEnhancementRobertsCrossOperatorABS(out, in, linfo, mode);
			break;
		case lmrcImageEdegeEnhancementModePrewittSQRT:
			lmrcImageEdgeEnhancementPrewittOperatorSQRT(out, in, linfo, mode);
			break;
		case lmrcImageEdegeEnhancementModePrewittABS:
			lmrcImageEdgeEnhancementPrewittOperatorABS(out, in, linfo, mode);
			break;
		case lmrcImageEdegeEnhancementModeSobelSQRT:
			lmrcImageEdgeEnhancementSobelOperatorSQRT(out, in, linfo, mode);
			break;
		case lmrcImageEdegeEnhancementModeSobelABS:
			lmrcImageEdgeEnhancementSobelOperatorABS(out, in, linfo, mode);
			break;
		default: 
			break;
	}
}

void
lmrcImageEdgeEnhancementPrepare(mrcImage* out, mrcImage* in, lmrcImageEdgeEnhancementInfo* linfo, int mode)
{
	int i, max;

	out->Header.Cont = in->Header.Cont;
	mrcInit(out, NULL);
	if(linfo->flagDirection) {
  		if(1<in->HeaderN.z) {
    		max = 2;
	 	} else {
	  		max = 1;
	   	}
		linfo->direction = (mrcImage*)memoryAllocate(sizeof(mrcImage)*max, "in lmrcImageEdgeEnhancementRobertsCrossOperator");
		for(i=0; i<max; i++) {
			linfo->direction[i].Header.Cont = in->Header.Cont;
			mrcInit(&(linfo->direction[i]), NULL);
		}
	}
}

