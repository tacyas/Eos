/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageDilation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageDilation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageDilation ver%I%; Date:%D% %Z%";

#include "../inc/mrcImage.h"
#include "lmrcImageMorphology.h"

void
lmrcImageDilation(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int mode)
{
	int bx, by, bz;
	int rbx, rby, rbz;
	int x, y, z;
	double data, data2;
	double se;

	dst->Header = src->Header;
	mrcInit(dst, NULL);

	for(z=0; z<dst->HeaderN.z; z++) {
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		mrcPixelDataSet(dst, x, y, z, src->HeaderAMin, mrcPixelRePart);
	}
	}
	}

	for(bz=0; bz<linfo.SE.HeaderN.z; bz++) {
	for(by=0; by<linfo.SE.HeaderN.y; by++) {
	for(bx=0; bx<linfo.SE.HeaderN.x; bx++) {
		mrcPixelDataGet(&linfo.SE, bx, by, bz, &se, mrcPixelRePart, mrcPixelHowNearest);
		if(0!=se) {
			rbx = bx + linfo.SE.HeaderStartN.x;
			rby = by + linfo.SE.HeaderStartN.y;
			rbz = bz + linfo.SE.HeaderStartN.z;
			for(z=0; z<dst->HeaderN.z; z++) {
			for(y=0; y<dst->HeaderN.y; y++) {
			for(x=0; x<dst->HeaderN.x; x++) {
				mrcPixelDataGet(src, x+rbx, y+rby, z+rbz, &data,   mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(dst, x,     y,     z,     &data2,  mrcPixelRePart, mrcPixelHowNearest);
				if(data2<se*data) {
					mrcPixelDataSet(dst, x,     y,     z,  se*data, mrcPixelRePart);
				} 
			}
			}
			}
		}
	}
	}
	}
}

