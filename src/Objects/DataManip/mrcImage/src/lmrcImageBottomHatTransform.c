/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageBottomHatTransform ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageBottomHatTransform 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageBottomHatTransform ver%I%; Date:%D% %Z%";

#include "./lmrcImageSubtractionCalc.h"
#include "./lmrcImageMorphology.h"

void
lmrcImageBottomHatTransform(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode)
{
	mrcImage tmpClose;

	dst->Header.Cont = src->Header.Cont;
	mrcInit(dst, NULL);

	lmrcImageClosing(&tmpClose, src, linfo, times, mode);
	lmrcImageSubtractionCalc(dst, &tmpClose, src);
}
