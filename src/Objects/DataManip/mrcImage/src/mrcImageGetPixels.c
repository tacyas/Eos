/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageGetPixels ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageGetPixels 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageGetPixels ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosCuda.h"
#include "../inc/mrcImage.h"
#include "./mrcImageGetPixelsCUDA.h"

void
mrcPixelsDataGet(float* data, mrcImageParaTypeRealCoord* inCoord, int nPixel, mrcImage* in, mrcPixelDataType type, mrcPixelDataHowToGet howto)
{
	int i;
	double d;

	DEBUGPRINT("mrcPixelsDataGet Start\n");
	if(__eosCuda__) {
#ifdef CUDA
		if(sizeof(float)*3!=sizeof(mrcImageParaTypeRealCoord)) {
			fprintf(stderr, "mrcImageParaTypeRealCoord is not float*3.\n");
			exit(EXIT_FAILURE);
		} else {
			DEBUGPRINT("mrcImageParaTypeRealCoord is float*3.\n");
		}
		mrcPixelsDataGetCUDA(data, (float*)inCoord, nPixel, in->ImageFloatImage, in->HeaderMode, in->HeaderN.x, in->HeaderN.y, in->HeaderN.z, type, howto);
#else
		fprintf(stderr, "Not suppported CUDA\n");
		exit(EXIT_FAILURE);
#endif
	} else {
		for(i=0; i<nPixel; i++) {
			mrcPixelDataGet(in, inCoord[i].x, inCoord[i].y, inCoord[i].z, &d, type, howto); 
			DEBUGPRINT4("%f %f %f : %f\n", inCoord[i].x, inCoord[i].y, inCoord[i].z, d);
			data[i] = d;
		}
	}
}

void
mrcPixelDataGetbyMatrix3D(mrcImage* out, mrcImage* in, 
	Matrix3D mat,
	mrcPixelDataHowToGet mode, int mode2)
{
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal gx, gy, gz;
	floatVector v;
	double data;
	double offset;

	out->Header =  in->Header;
	mrcInit(out, NULL);

	floatVectorInit(&v, 4);
	v.data[3] = 1;
	gx = (in->HeaderN.x - 1)/2.0;
	gy = (in->HeaderN.y - 1)/2.0;
	gz = (in->HeaderN.z - 1)/2.0;

	switch(mode2&0xf) {
		case 1: {
			offset = in->HeaderAMean;	
			break;
		}
		default: {
			offset = 0.0;
			break;
		}
	}

	for(dstz=0; dstz<out->HeaderN.z; dstz++) {
	for(dsty=0; dsty<out->HeaderN.y; dsty++) {
	for(dstx=0; dstx<out->HeaderN.x; dstx++) {
		v.data[0] = dstx - gx;
		v.data[1] = dsty - gy;
		v.data[2] = dstz - gz;
		matrix3DMultiplyVector(&v, mat);

		switch(mode2&0xf0) {
			case 0: 
				if(SQR(v.data[0]/gx)+SQR(v.data[1]/gy)+SQR(v.data[2]/gz)<=1) {
					srcx = v.data[0] + gx;
					srcy = v.data[1] + gy;
					srcz = v.data[2] + gz;
					mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
					mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
				} else {
					mrcPixelDataSet(out, dstx, dsty, dstz, offset, mrcPixelRePart);
				}
				break;
			case 16: 	
				srcx = v.data[0] + gx;
				srcy = v.data[1] + gy;
				srcz = v.data[2] + gz;
				mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
				mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
				break;
			
		}
	}
	}
	}
}
