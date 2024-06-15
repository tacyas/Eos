/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageRotation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageRotation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageRotation ver%I%; Date:%D% %Z%";
#include <math.h>
#include "../inc/mrcImage.h"
#undef DEBUG
#include "genUtil.h"


void 
lmrcImageRotation3DModePrint(FILE* fpt) 
{
	fprintf(fpt, " 0: padding 0 \n");
	fprintf(fpt, " 1: padding average \n");
	fprintf(fpt, " +0:  within ellipsoidal area.\n");
	fprintf(fpt, " +16: within square area.\n");
}

void
lmrcImageRotation2D(mrcImage* dst, mrcImage* src, double angle, mrcPixelDataHowToGet mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal orgx, orgy, orgz;
	double data;

	z    = 0.0;
	orgz = 0.0;
	dst->Header = src->Header;
#ifdef DEBUG
	mrcStatDataSet(src, 0);
#endif
	DEBUGPRINT("start \n");
	mrcInit(dst, NULL);
	for(x=0; x< dst->HeaderN.x; x++) {
		for(y=0; y< dst->HeaderN.y; y++) {
			orgx = (x - (dst->HeaderN.x-1)/2.0)*cos(-angle) 
				 - (y - (dst->HeaderN.y-1)/2.0)*sin(-angle)
				 + (src->HeaderN.x-1)/2.0;
			orgy = (x - (dst->HeaderN.x-1)/2.0)*sin(-angle) 
				 + (y - (dst->HeaderN.y-1)/2.0)*cos(-angle)
				 + (src->HeaderN.y-1)/2.0;
			if(  -0.5 <= orgx && orgx < src->HeaderN.x-0.5
			  && -0.5 <= orgy && orgy < src->HeaderN.y-0.5) { 
				mrcPixelDataGet(src, orgx, orgy, orgz, &data, mrcPixelRePart, mode);
#ifdef DEBUG
				if(src->HeaderAMax < data)	{
					DEBUGPRINT4("(%f,%f):%g: max%g\n", orgx, orgy, data, src->HeaderAMax);
				}
#endif
			} else {
				data = 0.0;
			}
			mrcPixelDataSet(dst, x, y, z, data, mrcPixelRePart);
		}
	}
}


void
lmrcImageRotation2DPeriodicBoundary(mrcImage* dst, mrcImage* src, double angle, mrcPixelDataHowToGet mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal orgx, orgy, orgz;
	double data;

	z    = 0.0;
	orgz = 0.0;
	dst->Header = src->Header;

	mrcInit(dst, NULL);
	for(x=0; x< dst->HeaderN.x; x++) {
		for(y=0; y< dst->HeaderN.y; y++) {
			orgx = (x - (dst->HeaderN.x-1)/2.0)*cos(-angle) 
				 - (y - (dst->HeaderN.y-1)/2.0)*sin(-angle)
				 + (src->HeaderN.x-1)/2.0;
			orgy = (x - (dst->HeaderN.x-1)/2.0)*sin(-angle) 
				 + (y - (dst->HeaderN.y-1)/2.0)*cos(-angle)
				 + (src->HeaderN.y-1)/2.0;
			mrcPixelDataGet(src, orgx, orgy, orgz, &data, mrcPixelRePart, mode);
			mrcPixelDataSet(dst, x, y, z, data, mrcPixelRePart);
		}
	}
}

void
lmrcImageRotation3DZXY(mrcImage* out, mrcImage* in, 
	mrcImageParaTypeReal rotx, mrcImageParaTypeReal roty, mrcImageParaTypeReal rotz,
	mrcPixelDataHowToGet mode, int mode2)
{
	lmrcImageRotation3DFollowingEulerAngle(out, in, "YOYS", roty, rotx, rotz, mode, mode2);
}

#include "Matrix3D.h"

void
lmrcImageRotation3DFollowingEulerAngle(mrcImage* out, mrcImage* in, 
	const char* EulerMode,
	mrcImageParaTypeReal rot1, mrcImageParaTypeReal rot2, mrcImageParaTypeReal rot3, 
	mrcPixelDataHowToGet mode, int mode2)
{
	Matrix3D mat;

	matrix3DRotationAntiSetFollowingEulerAngle(mat, EulerMode, rot1, rot2, rot3, MATRIX_3D_MODE_INITIALIZE);
	lmrcImageRotation3DFollowingMatrix3D(out, in, mat, mode, mode2);
}

void
lmrcImageRotation3DFollowingMatrix3D(mrcImage* out, mrcImage* in, 
	Matrix3D mat,
	mrcPixelDataHowToGet mode, int mode2)
{
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal sgx, sgy, sgz;
	mrcImageParaTypeReal srx, sry, srz;
	mrcImageParaTypeReal dgx, dgy, dgz;
	floatVector v;
	double data;
	double offset;

	out->Header =  in->Header;
	mrcInit(out, NULL);

	floatVectorInit(&v, 4);
	v.data[3] = 1;
	sgx = (in->HeaderN.x - 1)/2.0;
	sgy = (in->HeaderN.y - 1)/2.0;
	sgz = (in->HeaderN.z - 1)/2.0;

    srx = sgx; 
    sry = sgy; 
    srz = sgz; 

	dgx = (in->HeaderN.x - 1)/2.0;
	dgy = (in->HeaderN.y - 1)/2.0;
	dgz = (in->HeaderN.z - 1)/2.0;

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
		v.data[0] = dstx - dgx;
		v.data[1] = dsty - dgy;
		v.data[2] = dstz - dgz;
		matrix3DMultiplyVector(&v, mat);

		switch(mode2&0xf0) {
			case 0: 
				if(SQR(v.data[0]/srx)+SQR(v.data[1]/sry)+SQR(v.data[2]/srz)<=1) {
					srcx = v.data[0] + sgx;
					srcy = v.data[1] + sgy;
					srcz = v.data[2] + sgz;
					mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
					mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
				} else {
					mrcPixelDataSet(out, dstx, dsty, dstz, offset, mrcPixelRePart);
				}
				break;
			case 16: 	
				srcx = v.data[0] + sgx;
				srcy = v.data[1] + sgy;
				srcz = v.data[2] + sgz;
				mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
				mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
				break;
			
		}
	}
	}
	}
}

///

void
lmrcImageRotation3DFollowingEulerAngle2(mrcImage* out, mrcImage* in, 
	const char* EulerMode,
	mrcImageParaTypeReal rot1, mrcImageParaTypeReal rot2, mrcImageParaTypeReal rot3, 
	mrcPixelDataHowToGet mode, int mode2)
{
	Matrix3D mat;

	matrix3DRotationAntiSetFollowingEulerAngle(mat, EulerMode, rot1, rot2, rot3, MATRIX_3D_MODE_INITIALIZE);
	lmrcImageRotation3DFollowingMatrix3D2(out, in, mat, mode, mode2);
}

void
lmrcImageRotation3DFollowingMatrix3D2(mrcImage* out, mrcImage* in, 
	Matrix3D mat,
	mrcPixelDataHowToGet mode, int mode2)
{
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal sgx, sgy, sgz;
	mrcImageParaTypeReal srx, sry, srz;
	mrcImageParaTypeReal dgx, dgy, dgz;
	floatVector v;
	double data;
	double offset;

	//out->Header =  in->Header;
	//mrcInit(out, NULL);

	floatVectorInit(&v, 4);
	v.data[3] = 1;
	sgx = (in->HeaderN.x - 1)/2.0;
	sgy = (in->HeaderN.y - 1)/2.0;
	sgz = (in->HeaderN.z - 1)/2.0;

    srx = sgx;
    sry = sgy;
    srz = sgz;

	dgx = (out->HeaderN.x - 1)/2.0;
	dgy = (out->HeaderN.y - 1)/2.0;
	dgz = (out->HeaderN.z - 1)/2.0;

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
		v.data[0] = dstx - dgx;
		v.data[1] = dsty - dgy;
		v.data[2] = dstz - dgz;
		matrix3DMultiplyVector(&v, mat);

		switch(mode2&0xf0) {
			case 0: 
				if(SQR(v.data[0]/srx)+SQR(v.data[1]/sry)+SQR(v.data[2]/srz)<=1) {
					srcx = v.data[0] + sgx;
					srcy = v.data[1] + sgy;
					srcz = v.data[2] + sgz;
					mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
					mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
				} else {
					mrcPixelDataSet(out, dstx, dsty, dstz, offset, mrcPixelRePart);
				}
				break;
			case 16: 	
				srcx = v.data[0] + sgx;
				srcy = v.data[1] + sgy;
				srcz = v.data[2] + sgz;
				mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
				mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
				break;
			
		}
	}
	}
	}
}



