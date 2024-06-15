/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageTopHatTransform ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageTopHatTransform 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageTopHatTransform ver%I%; Date:%D% %Z%";

#include "./lmrcImageSubtractionCalc.h"
#include "./lmrcImageMorphology.h"

void
lmrcImageTopHatTransform(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode)
{
	mrcImage tmpOpening;

	dst->Header.Cont = src->Header.Cont;
	mrcInit(dst, NULL);

	lmrcImageOpening(&tmpOpening, src, linfo, times, mode);
	lmrcImageSubtractionCalc(dst, src, &tmpOpening);
}
