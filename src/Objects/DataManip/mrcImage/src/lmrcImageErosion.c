/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageErosion ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageErosion 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageErosion ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "lmrcImageMorphology.h"

void
lmrcImageErosion(mrcImage* dst, mrcImage* src, lmrcImageMorphologyInfo linfo, int mode)
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
		mrcPixelDataSet(dst, x, y, z, dst->HeaderAMax, mrcPixelRePart);
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
			DEBUGPRINT3("b  %d %d %d\n", bx,  by,  bz);	
			DEBUGPRINT3("rb %d %d %d\n", rbx, rby, rbz);	
			for(z=0; z<dst->HeaderN.z; z++) {
			for(y=0; y<dst->HeaderN.y; y++) {
			for(x=0; x<dst->HeaderN.x; x++) {
				mrcPixelDataGet(src, x-rbx, y-rby, z-rbz, &data,   mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(dst, x,     y,     z,     &data2,  mrcPixelRePart, mrcPixelHowNearest);
				if(se*data<data2) {
					mrcPixelDataSet(dst, x,     y,     z,     data*se, mrcPixelRePart);
				}
			}
			}
			}
		}
	}
	}
	}
}

