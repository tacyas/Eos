#include <math.h>
#undef DEBUG
#include "../inc/mrcImage.h"
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageDensity.h"

void
lmrcImageShift(mrcImage* out, mrcImage* in, mrcImageParaTypeRealCoord shift, mrcPixelDataHowToGet mode)
{
	float x, y, z;
	float ox, oy, oz;	
	double data;

	out->Header = in->Header;
	mrcInit(out, NULL);
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			for(z=0; z<in->HeaderN.z; z++) {
				ox = x - shift.x;
				oy = y - shift.y;
				oz = z - shift.z;
				mrcPixelDataGet(in, 
						ox, oy, oz,
						&data, mrcPixelRePart, mode); 

				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			}
		}
	}
}

void
lmrcImageShiftFollowingGC(mrcImage* out, mrcImage* in, int mode)
{
    lmrcImageDensityInfoInfo linfo;
	mrcImageParaTypeRealCoord shift;

	DEBUGPRINT("lmrcImageShiftFollowingGC\n");
    lmrcImageDensityInfo(&linfo, in, mrcImageDensityInfoCentreOfGravity);

	shift.x = -(linfo.centreOfGravity.x - in->HeaderN.x/2);
	shift.y = -(linfo.centreOfGravity.y - in->HeaderN.y/2);
	shift.z = -(linfo.centreOfGravity.z - in->HeaderN.z/2);

	DEBUGPRINT6("GC: %f %f %f Shift: %f %f %f\n", 
		linfo.centreOfGravity.x,
		linfo.centreOfGravity.y,
		linfo.centreOfGravity.z,
		shift.x,
		shift.y,
		shift.z);

	lmrcImageShift(out, in, shift, mrcPixelHowNearest);
}
