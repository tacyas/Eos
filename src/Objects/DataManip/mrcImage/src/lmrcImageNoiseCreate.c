/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageNoiseCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageNoiseCreate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageNoiseCreate ver%I%; Date:%D% %Z%";

#include "Random.h"
#include "./lmrcImageNoiseCreate.h"

void 
lmrcImageNoiseCreate(mrcImage* out, mrcImage* in, float Noise, int mode)
{
	/* variables */
	int x,y,z;
	double data;

	/* begin */
	lRandShuffle();
	out->Header = in->Header;
	mrcInit(out,0);
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		data = randomNormalGet(0)*Noise;
		mrcPixelDataSet(out ,x ,y ,z ,data  ,mrcPixelRePart);
	}
	}
	}
	mrcStatDataSet(out,0);
}
