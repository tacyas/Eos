/*
# lmrcImageMirroing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageMirroing 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "./lmrcImageMirroring.h"

/*
	$lmrcImageMirroring: (mrcImage* out, mrcImage* in, lmrcImageMirroring mode) $
	$mode: lmrcImageMirroringModeYZPlane 
*/

void
lmrcImageMirroring(mrcImage* out, mrcImage* in, lmrcImageMirroringMode mode)
{
	out->Header = in->Header;
	mrcInit(out, NULL);

	switch(mode) {
		case lmrcImageMirroringModeYZPlane: {
			 lmrcImageMirroringYZPlane(out, in, mode);	
			break;
		}
		default: {
			break;
		}
	}
}

void 
lmrcImageMirroringUsage(FILE* fpt)
{
	fprintf(fpt, "lmrcImageMirroring >>>> Usage >>>>\n");
	fprintf(fpt, "%d: Mirroing against YZ-plane \n", lmrcImageMirroringModeYZPlane);
}


void
lmrcImageMirroringYZPlane(mrcImage* out, mrcImage* in, lmrcImageMirroringMode mode)
{
	double data;
	mrcImageParaTypeReal srcx, srcy, srcz;
	mrcImageParaTypeReal dstx, dsty, dstz;

	for(srcx=0; srcx<in->HeaderN.x; srcx++) {
	for(srcy=0; srcy<in->HeaderN.y; srcy++) {
	for(srcz=0; srcz<in->HeaderN.z; srcz++) {
		dstx = in->HeaderN.x - 1 - srcx;	
		dsty = srcy;
		dstz = srcz;

		mrcPixelDataGet(in, srcx, srcy, srcz, &data, mrcPixelRePart, mrcPixelHowNearest); 	
		mrcPixelDataSet(out, dstx, dsty, dstz, data, mrcPixelRePart);
	}
	}
	}
}


