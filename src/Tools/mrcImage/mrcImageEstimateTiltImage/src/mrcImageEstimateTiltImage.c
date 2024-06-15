/*
# mrcImageEstimateTiltImage : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageEstimateTiltImage
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "Matrix3D.h"
#include "mrcImage.h"

typedef struct lmrcImageEstimateTiltImageInfo {
	double tiltAngle;
	double tiltAxisAngle;
	int    flagInverse;
	mrcPixelDataHowToGet mode;
} lmrcImageEstimateTiltImageInfo;
/*
typedef enum lmrcImageEstimateTiltImageMode {
	a=0,
	b=1
} lmrcImageEstimateTiltImageMode;
*/

extern void	lmrcImageEstimateTiltImage(mrcImage* out, mrcImage* in, lmrcImageEstimateTiltImageInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageEstimateTiltImageInfo  info;
	lmrcImageEstimateTiltImageInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.tiltAngle		= info.TiltAngle*RADIAN;
	linfo.tiltAxisAngle = info.TiltAxis*RADIAN;
	linfo.mode          = info.mode; 
	linfo.flagInverse	= info.Inverse;
	mrcFileRead(&in, info.In, "in main", 0); 

	lmrcImageEstimateTiltImage(&out, &in, linfo, 0);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-i in :2D or 3D\n");
}

void	
lmrcImageEstimateTiltImage(
	mrcImage* out, 
	mrcImage* in, 
	lmrcImageEstimateTiltImageInfo linfo, 
	int mode)
{
	mrcImageParaTypeReal dstx, dsty, dstz;
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal cx, cy, cz;
	double dataIn;
	double dataOut;
	double r, phi;
	Matrix3D m;
	floatVector v;

	if(1<in->HeaderN.z) {
		fprintf(stderr, "This routine is for 2D image, but Nz=%d\n", in->HeaderN.z);
		exit(EXIT_FAILURE);	
	}
	out->Header = in->Header;
	out->HeaderN.z = 1;
	mrcInit(out, NULL);

	floatVectorInit(&v, 4);
	v.data[3] = 1;

	if(linfo.flagInverse) {
		matrix3DRotationSetFollowingEulerAngle(m, "ZENS", 
			-linfo.tiltAxisAngle,
			-linfo.tiltAngle,
			 linfo.tiltAxisAngle, MATRIX_3D_MODE_INITIALIZE);
	} else {
		matrix3DRotationSetFollowingEulerAngle(m, "ZENS", 
			-linfo.tiltAxisAngle,
			 linfo.tiltAngle,
			 linfo.tiltAxisAngle, MATRIX_3D_MODE_INITIALIZE);
	}
	cx = in->HeaderN.x/2;
	cy = in->HeaderN.y/2;
	cz = in->HeaderN.z/2;

	for(dsty=0; dsty<in->HeaderN.y; dsty++) {	
	for(dstx=0; dstx<in->HeaderN.x; dstx++) {	
		mrcPixelDataGet(out, dstx, dsty, 0, &dataOut, mrcPixelRePart, linfo.mode);
		v.data[0] = dstx-cx;	
		v.data[1] = dsty-cy;	
		if(linfo.flagInverse) {
			v.data[2] = 0 - cz;	
		} else { 
			r = sqrt(SQR(v.data[0]) + SQR(v.data[1]));
			if(0<r) {
				phi = atan2(v.data[1], v.data[0]);
			} else {
				phi = 0;
			}
			v.data[2] = r*sin(linfo.tiltAxisAngle - phi)*tan(linfo.tiltAngle) -cz;	
		}
		matrix3DMultiplyVector(&v, m);
		srcx = v.data[0]+cx;
		srcy = v.data[1]+cy;
		if(-0.5<=srcx && srcx<in->HeaderN.x
		 &&-0.5<=srcy && srcy<in->HeaderN.y) {
			for(srcz=0; srcz<in->HeaderN.z; srcz++) {
				mrcPixelDataGet(in,  srcx, srcy, srcz, &dataIn,  mrcPixelRePart, linfo.mode);
				dataOut += dataIn;
			}
		} else {
			dataOut = in->HeaderAMean; 	
		}
		mrcPixelDataSet(out, dstx, dsty, 0, dataOut, mrcPixelRePart);
	}
	}

/*
	for(srcz=0; srcz<in->HeaderN.z; srcz++) {	
	for(srcy=0; srcy<in->HeaderN.y; srcy++) {	
	for(srcx=0; srcx<in->HeaderN.x; srcx++) {	
		mrcPixelDataGet(in, srcx, srcy, srcz, &dataIn,  mrcPixelRePart, linfo.mode);
		v.data[0] = srcx-cx;	
		v.data[1] = srcy-cy;	
		v.data[2] = srcz-cz;	
		matrix3DMultiplyVector(&v, m);
		dstx = v.data[0]+cx;
		dsty = v.data[1]+cy;
		dstz = 0;
		mrcPixelDataGet(out, dstx, dsty, dstz, &dataOut, mrcPixelRePart, linfo.mode);
		dataOut += dataIn;
		mrcPixelDataSet(out, dstx, dsty, 0, dataOut, mrcPixelRePart);
	}
	}
	}
*/
}

