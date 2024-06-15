/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDensityInverse ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDensityInverse 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageDensityInverse ver%I%; Date:%D% %Z%";
#include "lmrcImageDensityInverse.h"

void
lmrcImageDensityInverse(mrcImage* mrc, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	
	for(x=0; x<mrc->HeaderN.x; x++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
			for(z=0; z<mrc->HeaderN.z; z++) {
				mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(data<mrc->HeaderAMin) {
					data = mrc->HeaderAMax;
				} else if(mrc->HeaderAMax<data) {
					data = mrc->HeaderAMin;
				} else {
					data = (mrc->HeaderAMax - data) + mrc->HeaderAMin;
				}
				mrcPixelDataSet(mrc, x, y, z, data, mrcPixelRePart);
			}
		}
	}
}

