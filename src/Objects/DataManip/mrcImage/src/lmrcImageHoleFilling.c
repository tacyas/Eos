/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageHoleFilling ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageHoleFilling 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageHoleFilling ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h"

#include "./lmrcImageHoleFilling.h"
#include "./lmrcImageCalcArea.h"
#include "./lmrcImageTone.h"

void
lmrcImageHoleFilling(mrcImage* out, mrcImage* in, lmrcImageHoleFillingInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double area;
	double data; 

	out->Header = in->Header;
	mrcInit(out, NULL);

	lmrcImageToneReversal(&linfo->ToneReverse, in, 0);
	lmrcImageCalcArea(&linfo->areaBlack, &linfo->labelBlack, &linfo->ToneReverse, linfo->neighbor, 0);

	DEBUGPRINT("FILLING\n");
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {

		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(0<data) {
			mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);
		} else {
			mrcPixelDataGet(&linfo->areaBlack, x, y, z, &area, mrcPixelRePart, mrcPixelHowNearest);
			if(linfo->areaBlack.HeaderAMax==area) {
				mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);
			} else {
				mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);
			}
		}
	}
	}
	}
}
