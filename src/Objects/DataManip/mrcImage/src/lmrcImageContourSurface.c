/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageContourSurface ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageContourSurface 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageContourSurface ver%I%; Date:%D% %Z%";

#include "lmrcImageContourSurface.h"
static void lmrcImageContourSurfaceCreate0(mrcImage* out, mrcImage* in, lmrcImageContourSurfaceInfo info);

void
lmrcImageContourSurfaceCreate(mrcImage* out, mrcImage* in, lmrcImageContourSurfaceInfo info, lmrcImageContourSurfaceMode mode) 
{
	out->Header = in->Header;
	mrcInit(out, NULL);
	switch(mode) {
		case lmrcImageContourSurfaceModeSimple: {
			lmrcImageContourSurfaceCreate0(out, in, info);
			break;
		}
		default: {
			break;
		}	
	}
}

void
lmrcImageContourSurfaceCreate0(mrcImage* out, mrcImage* in, lmrcImageContourSurfaceInfo info) 
{
	mrcImageParaTypeReal x, y, z;

	double data111;
	double data110;
	double data112;
	double data101;
	double data121;
	double data011;
	double data211;
	double contour;

	contour = info.Contour; 

	for(x=0; x<out->HeaderN.x; x++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(z=0; z<out->HeaderN.z; z++) {
		mrcPixelDataGet(in, x,   y,   z,   &data111, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x,   y,   z-1, &data110, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x,   y,   z+1, &data112, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x,   y-1, z,   &data101, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x,   y+1, z,   &data121, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x-1, y,   z,   &data011, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x+1, y,   z,   &data211, mrcPixelRePart, mrcPixelHowNearest);
		if((data111-contour)*(data110-contour)<=0
		 ||(data111-contour)*(data112-contour)<=0
		 ||(data111-contour)*(data101-contour)<=0
		 ||(data111-contour)*(data121-contour)<=0
		 ||(data111-contour)*(data011-contour)<=0
		 ||(data111-contour)*(data211-contour)<=0) {
			mrcPixelDataSet(out, x, y, z, 1.0, mrcPixelRePart);
		} else {
			mrcPixelDataSet(out, x, y, z, 0.0, mrcPixelRePart);
		}
	}
	}
	}
}

