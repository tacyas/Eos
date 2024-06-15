/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCorrelationWithCTFCompensation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCorrelationWithCTFCompensation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageCorrelationWithCTFCompensation ver%I%; Date:%D% %Z%";
#include "mrcImage.h"

void
lmrcImageCorrelationWithCTFCompensation(mrcImage* out, mrcImage* in, ctfInfo* inctf, mrcImage* ref, ctfInfo* refctf, long mode)
{
	mrcImage inFFT;
	mrcImage refFFT;
	if(IsImage(in, "", 0)) {
		lmrcImageFFT(&inFFT, in ,0);
	} else {
		inFFT = *in;
	}
	if(IsImage(ref, "", 0)) {
		lmrcImageFFT(&refFFT, ref ,0);
	} else {
		refFFT = *ref;
	}

	lmrcImageCTFCompensation(&inFFT, inctf, 1); 
	lmrcImageCTFCompensation(&refFFT, inctf, 1); 

	lmrcImageCorrelation(out, in, ref, mode);
}
