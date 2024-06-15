/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageToFFT ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageToFFT 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageToFFT ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"

#include <stdlib.h>
#include "./lmrcImageToFFT.h"

void
lmrcImageToFFT(mrcImage* out, mrcImage* in, mrcImageParaTypeRealCoord centre, int mode)
{
	mrcImageParaTypeReal X, Y, Z;
	mrcImageParaTypeReal srcX, srcY, srcZ;
	double data;

	DEBUGPRINT("lmrcImageToFFT Start\n");
	out->Header = in->Header;
	out->HeaderMode = mrcComplexFloatFT;
	mrcInit(out, NULL);

	
	for(Z=-out->HeaderN.z/2; Z<MAX(1,out->HeaderN.z/2); Z++) {
	for(Y=-out->HeaderN.y/2; Y<MAX(1,out->HeaderN.y/2); Y++) {
	for(X=0;                 X<=out->HeaderN.x/2; X++) {
		srcX = X + centre.x;
		srcY = Y + centre.y;
		srcZ = Z + centre.z;

		mrcPixelDataGet(in,  srcX, srcY, srcZ, &data, mrcPixelRePart, mrcPixelHowNearest);
		DEBUGPRINT4("%f %f %f %f\n", srcX, srcY, srcZ, data);
		switch(mode) {
			case 0: 
				mrcPixelDataSet(out,    X,    Y,    Z,  data, mrcPixelRePart);
				break;
			case 1:
				mrcPixelDataSet(out,    X,    Y,    Z,  pow(10,data), mrcPixelRePart);
				break;
			case 2:
				mrcPixelDataSet(out,    X,    Y,    Z,  sqrt(data), mrcPixelRePart);
				break;
			case 3:
				mrcPixelDataSet(out,    X,    Y,    Z,  pow(10,sqrt(data)), mrcPixelRePart);
				break;
			case 4:
				mrcPixelDataSet(out,    X,    Y,    Z,  cos(data), mrcPixelRePart);
				mrcPixelDataSet(out,    X,    Y,    Z,  sin(data), mrcPixelImPart);
				break;
			case 5:
				mrcPixelDataSet(out,    X,    Y,    Z,  data, mrcPixelRePart);
				break;
			default: {
				fprintf(stderr, "Not supported mode: %d\n", mode);
				exit(EXIT_FAILURE);
			}
		}
	}
	}
	}
}
