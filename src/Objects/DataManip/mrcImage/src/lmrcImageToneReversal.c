/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageToneReversal ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageToneReversal 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageToneReversal ver%I%; Date:%D% %Z%";

#include "./lmrcImageTone.h"


void 
lmrcImageToneReversal(mrcImage* out, mrcImage* in, int mode)
{
	mrcImageInformation info;
	mrcImageParaTypeReal x, y, z;
	double data, offset;
	int max, i;	

	info.mode = meanOfAll;
	lmrcImageInformation(&info, in);

	out->Header = in->Header;	
	mrcInit(out, NULL);

	offset = info.max + info.min;
	if(out->HeaderMode==mrcFloatImage) {
		max = out->HeaderN.x*out->HeaderN.y*out->HeaderN.z;
		for(i=0; i<max; i++) {
			out->ImageFloatImage[i] = offset - in->ImageFloatImage[i]; 
		}
	} else {
		for(z=0; z<out->HeaderN.z; z++) {	
		for(y=0; y<out->HeaderN.y; y++) {	
		for(x=0; x<out->HeaderN.x; x++) {
			mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
			mrcPixelDataSet(out, x, y, z, offset - data, mrcPixelRePart);
		}
		}
		}
	}
}
