/*
# lmrcImageTrans : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageTrans 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "../inc/mrcImage.h"
#include "Matrix3D.h"
#include "Vector.h"

void
lmrcImageTrans(mrcImage* out, mrcImage* in, Matrix3D mat, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;
	floatVector v;
	Matrix3D matinv; 
	double data;

	floatVectorInit(&v, 4);	
	out->Header = in->Header;
	mrcInit(out, NULL);

	matrix3DCopy(matinv, mat);
	matrix3DInverse(matinv);
	v.data[3] = 1;

	for(z=0; z<out->HeaderN.z; z++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(x=0; x<out->HeaderN.x; x++) {
		v.data[0] = (x + out->HeaderStartN.x)*out->HeaderLength.x;
		v.data[1] = (y + out->HeaderStartN.y)*out->HeaderLength.y;
		v.data[2] = (z + out->HeaderStartN.z)*out->HeaderLength.z;
		matrix3DMultiplyVector(&v, matinv);
		srcx = v.data[0]/in->HeaderLength.x - in->HeaderStartN.x;
		srcy = v.data[1]/in->HeaderLength.y - in->HeaderStartN.y;
		srcz = v.data[2]/in->HeaderLength.z - in->HeaderStartN.z;
		if(srcx<-0.5 || in->HeaderN.x - 0.5 < srcx
		 ||srcy<-0.5 || in->HeaderN.y - 0.5 < srcy
		 ||srcz<-0.5 || in->HeaderN.z - 0.5 < srcz) {
		 	fprintf(stderr, "Area Over at %f %f %f src %f %f %f\n", x, y, z, srcx, srcy, srcz);
		 	data = 0.0;
		} else {
			mrcPixelDataGet(in,  srcx, srcy, srcz, &data, mrcPixelRePart, mode);
		}
		mrcPixelDataSet(out, x,    y,    z,     data, mrcPixelRePart);
	}
	}
	}
/*
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		v.data[0] = (x + in->HeaderStartN.x)*in->HeaderLength.x;
		v.data[1] = (y + in->HeaderStartN.y)*in->HeaderLength.y;
		v.data[2] = (z + in->HeaderStartN.z)*in->HeaderLength.z;
		matrix3DMultiplyVector(&v, mat);
		dstx = v.data[0]/out->HeaderLength.x - out->HeaderStartN.x;
		dsty = v.data[1]/out->HeaderLength.y - out->HeaderStartN.y;
		dstz = v.data[2]/out->HeaderLength.z - out->HeaderStartN.z;
		if(dstx< -0.5 || out->HeaderN.x - 0.5 < dstx
		 ||dsty< -0.5 || out->HeaderN.y - 0.5 < dsty
		 ||dstz< -0.5 || out->HeaderN.z - 0.5 < dstz) {
		 	fprintf(stderr, "Area Over at %f %f %f src %f %f %f\n", x, y, z, dstx, dsty, dstz);
		} else {
			mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mode);
			mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
		}
	}
	}
	}
*/
}

