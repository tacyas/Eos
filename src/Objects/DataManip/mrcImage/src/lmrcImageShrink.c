#include <stdlib.h>
#include <stdio.h>
#include "../inc/mrcImage.h"
#include "genUtil.h"

void
lmrcImageShrink(mrcImage* dst, mrcImage* src, mrcImageParaTypeIntegerCoord S, long mode)
{
	float x, y, z;
	double data, sum;
	long mx, my, mz, srcx, srcy, srcz;

	mx = src->HeaderN.x%S.x;
	my = src->HeaderN.y%S.y;
	mz = src->HeaderN.z%S.z;

	if(0 != mx) {
		fprintf(stderr, "mode(Nx:%d,Sx:%d) != 0. Nx := Nx - mode(Nx,Sx):%ld\n", src->HeaderN.x, S.x, mx);
	}
	if(0 != my) {
		fprintf(stderr, "mode(Ny:%d,Sy:%d) != 0. Ny := Ny - mode(Ny,Sy):%ld\n", src->HeaderN.y, S.y, my);
	}
	if(0 != mz) {
		fprintf(stderr, "mode(Nz:%d,Sz:%d) != 0. Nz := Nz - mode(Nz,Sz):%ld\n", src->HeaderN.z, S.z, mz);
	}

	dst->Header = src->Header;
	dst->HeaderN.x = src->HeaderN.x/S.x;
	dst->HeaderN.y = src->HeaderN.y/S.y;
	dst->HeaderN.z = src->HeaderN.z/S.z;

	dst->HeaderLength.x = src->HeaderLength.x*S.x;
	dst->HeaderLength.y = src->HeaderLength.y*S.y;
	dst->HeaderLength.z = src->HeaderLength.y*S.z;
	mrcInit(dst, NULL);

	for(z=0; z<dst->HeaderN.z; z++) {
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		mrcPixelDataSet(dst, x, y, z, 0.0, mrcPixelRePart);
	}
	}
	}
	for(z=0; z<dst->HeaderN.z; z++) {
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		sum = 0.0;
		for(srcz = z*S.z; srcz < (z+1)*S.z; srcz++) { 
		for(srcy = y*S.y; srcy < (y+1)*S.y; srcy++) { 
	    for(srcx = x*S.x; srcx < (x+1)*S.x; srcx++) { 
		    mrcPixelDataGet(src, (float)srcx, (float)srcy, (float)srcz, &data, mrcPixelRePart, mrcPixelHowNearest);
		    sum += data;
		}
		}		
	    }
	    sum = sum/((double)(S.x * S.y * S.z));
	    mrcPixelDataSet(dst, (float)x, (float)y, (float)z, sum, mrcPixelRePart);
	}
	}
	}
}


