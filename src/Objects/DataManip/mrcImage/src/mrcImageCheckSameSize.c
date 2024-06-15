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
lmrcImageCheckSameSize(mrcImage* in, mrcImage* ref)
{
	if(in->HeaderN.x!=ref->HeaderN.x
		||in->HeaderN.y!=ref->HeaderN.y
		||in->HeaderN.z!=ref->HeaderN.z) {
		fprintf(stderr, "Different Size (%d %d %d) != (%d %d %d)\n",
		(int)in->HeaderN.x, (int)in->HeaderN.y, (int)in->HeaderN.z,
		(int)ref->HeaderN.x, (int)ref->HeaderN.y, (int)ref->HeaderN.z);

		exit(EXIT_FAILURE);
	}
}
