/*
# mrcImageCopy.c  1.1
# The latest update : 05/08/96 at 17:34:02
#
#@(#) mrcImageCopy ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageCopy 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageCopy ver1.1; Date:96/05/08 @(#)";
#include <math.h>
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"

void
lmrcImageCopy(mrcImage* dst, mrcImage* src, mrcImageParaTypeRealCoord to)
{
	mrcImageParaTypeInteger ix, iy, iz;
	double data;
	mrcImageParaTypeInteger x, y, z;
	int k;

	DEBUGPRINT3("to: %g %g %g in lmrcImageCopy\n", to.x, to.y, to.z);
	DEBUGPRINT3("src: %d %d %d in lmrcImageCopy\n", src->HeaderN.x, src->HeaderN.y, src->HeaderN.z);
	DEBUGPRINT3("dst: %d %d %d in lmrcImageCopy\n", dst->HeaderN.x, dst->HeaderN.y, dst->HeaderN.z);
    for(iz=0; iz<src->HeaderN.z; iz++) {
    for(iy=0; iy<src->HeaderN.y; iy++) {
    for(ix=0; ix<src->HeaderN.x; ix++) {
		x = (int)(ix + to.x + 0.5);
		y = (int)(iy + to.y + 0.5);
		z = (int)(iz + to.z + 0.5);
    	mrcPixelDataGet(src, ix, iy, iz, &data, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataSet(dst,  x,  y,  z, data,  mrcPixelRePart);
    }
    }
    }
}
