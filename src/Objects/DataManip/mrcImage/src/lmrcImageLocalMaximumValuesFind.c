/*
# mrcImageLocalMaximumValuesFind : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageLocalMaximumValuesFind
# Attention
#   $Loccker$
#  	$State$ 
#
*/

#define DEBUG
#include "genUtil.h"
#include "./lmrcImageLocal.h"

void 
lmrcImageLocalMaximumValuesFind(mrcImage* out, mrcImage* in, lmrcImageLocalMaximumValuesFindInfo* linfo, int mode) 
{
	int x, y, z;
	int X, Y, Z;
	double data, d, dst, rr;
	int flag;

	out->Header = in->Header;
	mrcInit(out, NULL);

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataSet(out, x, y, z, 1, mrcPixelRePart);	
	}
	}
	}

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
		if(linfo->threshold<data) {
			flag = 1;
			for(X=x-linfo->size/2; X<=x+linfo->size/2 && flag==1; X++) {		
			for(Y=y-linfo->size/2; Y<=y+linfo->size/2 && flag==1; Y++) {		
			for(Z=z-linfo->size/2; Z<=z+linfo->size/2 && flag==1; Z++) {		
				rr = SQR(X-x)+SQR(Y-y)+SQR(Z-z);
				if(0 < rr && rr <= SQR(linfo->size)) {
					mrcPixelDataGet(in, X, Y, Z, &d, mrcPixelRePart, mrcPixelHowNearest);
					if(data<d) {
						flag = 0;
					}
				}
			}
			}
			}
			if(flag==1) {
				mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
			} else {
				mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);
			}
		} else {
			mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);
		}
	}
	}
	}
}
