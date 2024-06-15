/*
# mrcImage3DWindowing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DWindowing
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#undef DEBUG
#include "genUtil.h"
#include "./lmrcImage3DWindowing.h"

void
lmrcImage3DWindowingUsage(FILE* fpt) {
	fprintf(fpt, "%d: GaussianRectangularSolid\n", lmrcImage3DWindowingModeGaussianRectangularSolid);	
	fprintf(fpt, "%d: CosCylindar(+Offset)\n", lmrcImage3DWindowingModeCosCylinder);	
	fprintf(fpt, "%d: CosSphere\n", lmrcImage3DWindowingModeCosSphere);	
	fprintf(fpt, "%d: CosSphere(+Offset)\n", lmrcImage3DWindowingModeCosSphereOffset);	
}

void 
lmrcImage3DWindowing(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode)
{
	switch(mode) {
		case lmrcImage3DWindowingModeGaussianRectangularSolid: {
			lmrcImage3DWindowingGaussianRectanglularSolid(out, in, linfo, mode);
			break;
		}
		case lmrcImage3DWindowingModeCosCylinder: {
			lmrcImage3DWindowingCosCylinder(out, in, linfo, mode);
			break;
		}
		case lmrcImage3DWindowingModeCosSphere: {
			lmrcImage3DWindowingCosSphere(out, in, linfo, mode);
			break;
		}
		case lmrcImage3DWindowingModeCosSphereOffset: {
			lmrcImage3DWindowingCosSphereOffset(out, in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d", mode); 
			break;
		}
	}
}


void 
lmrcImage3DWindowingGaussianRectanglularSolid(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double weight;

	out->Header.Cont = in->Header.Cont;
	mrcInit(out, NULL);

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
		weight = exp(-SQR((x-linfo->center.x)/linfo->width.x)/2.0
		             -SQR((y-linfo->center.y)/linfo->width.y)/2.0
		             -SQR((z-linfo->center.z)/linfo->width.z)/2.0);
		DEBUGPRINT4("(%f %f %f): weight %g\n", x, y, z, weight);
		mrcPixelDataSet(out, x, y, z, weight*data, mrcPixelRePart); 
	}
	}
	}
}

void 
lmrcImage3DWindowingCosSphere(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;
	double weight;
	double R2, R;
	double r2in;
	double r2out;

	r2in =SQR(linfo->radius-linfo->widthofR/2.0);
	r2out=SQR(linfo->radius+linfo->widthofR/2.0);
	out->Header.Cont = in->Header.Cont;
	mrcInit(out, NULL);

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 

		R2 =  SQR(x-linfo->center.x);
		R2 += SQR(y-linfo->center.y);
		R2 += SQR(z-linfo->center.z);

		if(r2out<=R2) {
			weight = 0;
		} else if(R2<=r2in) {
			weight = 1;
		} else {
			R = sqrt(R2);
			weight =( cos( ( R-(linfo->radius-linfo->widthofR/2.0) )/linfo->widthofR*M_PI) + 1 )/2.0;
		}
		mrcPixelDataSet(out, x, y, z, weight*data, mrcPixelRePart); 
	}
	}
	}
}

void 
lmrcImage3DWindowingCosCylinder(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal xx, yy, zz, r;
	double data, sum, offset;
	double weight;
	int n;

	out->Header.Cont = in->Header.Cont;
	mrcInit(out, NULL);

	n = sum = 0;
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
		
		r = sqrt(SQR(x-linfo->center.x) + SQR(y-linfo->center.y));
		if(linfo->radius < r) {
			sum += data;
			n++;
		}
	}
	}
	}
	offset = sum/n;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
		
		r = sqrt(SQR(x-linfo->center.x) + SQR(y-linfo->center.y));
		zz = fabs(z-linfo->center.z);

		weight = 1;
		if(r <= linfo->radius - linfo->widthofR/2.0) {
			weight*=1;
		} else if(linfo->radius + linfo->widthofR/2.0 <= r) {
			weight*=0;
		} else {
			weight *= (cos(M_PI*(r - (linfo->radius - linfo->widthofR/2.0))/linfo->widthofR) + 1)/2; 
		}
		if(zz <= linfo->width.z - linfo->wz/2.0) {
			weight*=1;
		} else if(linfo->width.z + linfo->wz/2.0 <= zz) {
			weight*=0;
		} else {
			weight *= (cos(M_PI*(zz - (linfo->width.z - linfo->wz/2.0))/linfo->wz) + 1) /2; 
		}
		//DEBUGPRINT4("(%f %f %f): weight %g\n", x, y, z, weight);
		mrcPixelDataSet(out, x, y, z, weight*(data-offset), mrcPixelRePart); 
	}
	}
	}
}
void 
lmrcImage3DWindowingCosSphereOffset(mrcImage* out, mrcImage* in, lmrcImage3DWindowingInfo* linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	mrcImageParaTypeReal xx, yy, zz, r;
	double data, sum, offset;
	double weight;
	int n;

	out->Header.Cont = in->Header.Cont;
	mrcInit(out, NULL);

	n = sum = 0;
	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
		
		r = sqrt(SQR(x-linfo->center.x) + SQR(y-linfo->center.y) + SQR(z-linfo->center.z));
		if(linfo->radius < r) {
			sum += data;
			n++;
		}
	}
	}
	}
	offset = sum/n;

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 
		
		r = sqrt(SQR(x-linfo->center.x) + SQR(y-linfo->center.y) + SQR(z-linfo->center.z));

		weight = 1;
		if(r <= linfo->radius - linfo->widthofR/2.0) {
			weight*=1;
		} else if(linfo->radius + linfo->widthofR/2.0 <= r) {
			weight*=0;
		} else {
			weight *= (cos(M_PI*(r - (linfo->radius - linfo->widthofR/2.0))/linfo->widthofR) + 1)/2; 
		}
		//DEBUGPRINT4("(%f %f %f): weight %g\n", x, y, z, weight);
		mrcPixelDataSet(out, x, y, z, weight*(data-offset), mrcPixelRePart); 
	}
	}
	}
}
