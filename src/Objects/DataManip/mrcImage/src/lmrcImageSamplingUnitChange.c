/*
# lmrcImageSamplingUnitChange.c  1.2
# The latest update : 01/23/97 at 10:39:10
#
#@(#) lmrcImageSamplingUnitChange ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : lmrcImageSamplingUnitChange 
#@(#) Attention
#@(#)
*/

static char __sccs_id[] = "@(#)lmrcImageSamplingUnitChange ver1.2; Date:97/01/23 @(#)";

#include "lmrcImageSamplingUnitChange.h"

void 
lmrcImageSamplingUnitChange(mrcImage* out, mrcImage* in, lmrcImageSamplingUnitChangeInfo info, long mode)
{
    mrcImageParaTypeReal x, y, z;
    mrcImageParaTypeReal kx, ky, kz;
    double data;

    out->Header = in->Header;
    if(0.0 !=  info.L.x) {
        out->HeaderLength.x = info.L.x;
    }
    if(0.0 !=  info.L.y) {
        out->HeaderLength.y = info.L.y;
    }
    if(0.0 !=  info.L.z) {
        out->HeaderLength.z = info.L.z;
    }
    kx = in->HeaderLength.x/out->HeaderLength.x;
    ky = in->HeaderLength.y/out->HeaderLength.y;
    kz = in->HeaderLength.z/out->HeaderLength.z;

    if(1<in->HeaderN.x) {
        out->HeaderN.x = in->HeaderN.x*kx;
    } else {
        out->HeaderN.x = 1;
    }
    if(1<in->HeaderN.y) {
        out->HeaderN.y = in->HeaderN.y*ky;
    } else {
        out->HeaderN.y = 1;
    }
    if(1<in->HeaderN.z) {
        out->HeaderN.z = in->HeaderN.z*kz;
    } else {
        out->HeaderN.z = 1;
    }

	out->HeaderStartN.x = in->HeaderStartN.x*in->HeaderLength.x/out->HeaderLength.x;
	out->HeaderStartN.y = in->HeaderStartN.y*in->HeaderLength.y/out->HeaderLength.y;
	out->HeaderStartN.z = in->HeaderStartN.z*in->HeaderLength.z/out->HeaderLength.z;
    mrcInit(out, NULL);

    for(z=0; z<out->HeaderN.z; z++) {
    for(y=0; y<out->HeaderN.y; y++) {
    for(x=0; x<out->HeaderN.x; x++) {
        mrcPixelDataGet(in, x/kx, y/ky, z/kz, &data, mrcPixelRePart, info.SamplingMethodMode);
        mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
    }
    }   
    }
}
