/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageOpening ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageOpening 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageOpening ver%I%; Date:%D% %Z%";

#include "./lmrcImageMorphology.h"

void 
lmrcImageOpening(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int times, int mode)
{
	int i;
	mrcImage srctmp; 
	mrcImage dsttmp; 
	mrcImageParaTypeRealCoord to;

	to.x = to.y = to.z = 0;

	srctmp.Header = src->Header;	
	mrcInit(&srctmp, NULL);
	lmrcImageCopy(&srctmp, src, to);
	for(i=0; i<times; i++) {
		lmrcImageErosion(&dsttmp, &srctmp, linfo, 0);
		lmrcImageCopy(&srctmp, &dsttmp, to);
		mrcImageFree(&dsttmp, "lmrcImageClosing");
	}

	for(i=0; i<times; i++) {
		lmrcImageDilation(&dsttmp, &srctmp, linfo, 0);
		lmrcImageCopy(&srctmp, &dsttmp, to);
		mrcImageFree(&dsttmp, "lmrcImageClosing");
	}
	
	dst->Header = src->Header;
	mrcInit(dst, NULL);
	lmrcImageCopy(dst, &srctmp, to);
	mrcImageFree(&srctmp, "lmrcImageClosing");
}

