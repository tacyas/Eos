/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCheckSameSizeFFT ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCheckSameSizeFFT 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCheckSameSizeFFT ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>
#include "../inc/mrcImage.h"


void
lmrcImageCheckFFT(mrcImage* in, mrcImage* inFFT)
{
	if(IsImage(in, "", 0)) {
		lmrcImageFFT(inFFT, in, 0);
		fprintf(stderr, "Change to FFT\n");
	} else if(IsFT(in, "", 0)) {
		inFFT = in;
	} else {
		fprintf(stderr, "Not supported mode: %d\n", (int)in->HeaderMode);
		exit(EXIT_FAILURE);
	}
}
