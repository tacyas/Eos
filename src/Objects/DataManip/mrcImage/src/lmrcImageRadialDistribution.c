/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageRadialDistribution ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageRadialDistribution 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageRadialDistribution ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageRadialDistribution.h"

floatVector
lmrcImageRadialDistribution(
	floatVector* dst,
	mrcImage* mrc,
	lmrcImageRadialDistributionInfo* linfo)
{
	int sx, sy, sz, size;
	float x, y, z;
	float length;
	float radius; 
	int i, ilength;
	floatVector count;
	double data;

	sx = MIN(mrc->HeaderN.x - 1 - linfo->Cx, linfo->Cx);
	sy = MIN(mrc->HeaderN.y - 1 - linfo->Cy, linfo->Cy);
	size = MIN(sx, sy) + 1;	
	DEBUGPRINT3("Size(%d %d %d)\n", sx, sy, size);
	radius = mrc->HeaderLength.x;

	dst->size = size;
	floatVectorInit(dst, size);
	count.size = size;
	floatVectorInit(&count, size);
	
	for(i=0; i<size; i++) {
		dst->data[i]   = 0;
		count.data[i] = 0;
	}
	for(z=0; z<mrc->HeaderN.z; z++) {
	for(y=linfo->Cy - size; y<linfo->Cy + size; y++) {
	for(x=linfo->Cx - size; x<linfo->Cx + size; x++) {
		length = sqrt(SQR(x-linfo->Cx)+SQR(y-linfo->Cy));
		ilength = floor(length+0.5);
		if(ilength<size) {
			mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
			dst->data[ilength]  += data;
			count.data[ilength] += 1;;
		}
	}
	}
	}
	if(linfo->flagAverage) {
		DEBUGPRINT("Averaging\n");
		for(i=0; i<size; i++) {
			DEBUGPRINT2("%f: %f\n", dst->data[i], count.data[i]);
			dst->data[i] = dst->data[i]/count.data[i];
		}
	} else {
		DEBUGPRINT("Integral\n");
		for(i=0; i<size; i++) {
			DEBUGPRINT2("%f: %f\n", dst->data[i], count.data[i]);
			dst->data[i] = dst->data[i]/count.data[i]*radius*i;
		}
	}

	return *dst;
}

floatVector
lmrcImageRadialDistributionSphericalCoordinates(
	floatVector* dst,
	mrcImage* mrc,
	lmrcImageRadialDistributionInfo* linfo)
{
	int sx, sy, sz, size;
	float x, y, z;
	float length;
	float radius; 
	int i, ilength;
	floatVector count;
	double data;

	sx = MIN(mrc->HeaderN.x - 1 - linfo->Cx, linfo->Cx);
	sy = MIN(mrc->HeaderN.y - 1 - linfo->Cy, linfo->Cy);
	sz = MIN(mrc->HeaderN.z - 1 - linfo->Cz, linfo->Cz);
	size = MIN(sx, MIN(sy, sz)) + 1;	
	DEBUGPRINT4("Size(%d %d %d) -> %d\n", sx, sy, sz, size);
	radius = mrc->HeaderLength.x;

	dst->size = size;
	floatVectorInit(dst, size);
	count.size = size;
	floatVectorInit(&count, size);
	
	for(i=0; i<size; i++) {
		dst->data[i]   = 0;
		count.data[i] = 0;
	}
	for(z=linfo->Cz - size; z<linfo->Cz + size; z++) {
	for(y=linfo->Cy - size; y<linfo->Cy + size; y++) {
	for(x=linfo->Cx - size; x<linfo->Cx + size; x++) {
		length = sqrt(SQR(x-linfo->Cx)+SQR(y-linfo->Cy)+SQR(z-linfo->Cz));
		ilength = floor(length+0.5);
		if(ilength<size) {
			mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
			dst->data[ilength]  += data;
			count.data[ilength] += 1;;
		}
	}
	}
	}
	if(linfo->flagAverage) {
		DEBUGPRINT("Averaging\n");
		for(i=0; i<size; i++) {
			DEBUGPRINT2("%f: %f\n", dst->data[i], count.data[i]);
			dst->data[i] = dst->data[i]/count.data[i];
		}
	} else {
		DEBUGPRINT("Integral\n");
		for(i=0; i<size; i++) {
			DEBUGPRINT2("%f: %f\n", dst->data[i], count.data[i]);
			dst->data[i] = dst->data[i]/count.data[i]*radius*i;
		}
	}

	return *dst;
}

