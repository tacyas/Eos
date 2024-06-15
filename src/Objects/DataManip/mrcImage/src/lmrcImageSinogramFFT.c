/*
# lmrcImageSinogramFFT : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSinogramFFT 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include "mrcImage.h"

void __OneLineGet(mrcImage* out, mrcImage* in, int delta, int mode);

void
lmrcImageSinogramFFT(mrcImage* out, mrcImage* in, int mode)
{
	int      i, j;
	mrcImage OneLine;
	mrcImage OneLineFT;
	double   re, im;

	out->Header = in->Header;
	out->HeaderMode = mrcFloatRadonFT;
	mrcInit(out, NULL);
	
	for(i=0; i<in->HeaderN.y; i++){
		__OneLineGet(&OneLine, in, i, 0);
		lmrcImageFFT(&OneLineFT, &OneLine, 0);
		for(j=0; j<=out->HeaderN.x/2; j++){
			mrcPixelDataGet(&OneLineFT, j, 0, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&OneLineFT, j, 0, 0, &im, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataSet(out, j, i, 0, re, mrcPixelRePart);
			mrcPixelDataSet(out, j, i, 0, im, mrcPixelImPart);
		}
	}
}

void
__OneLineGet(mrcImage* out, mrcImage* in, int delta, int mode)
{
	int    i;
	double data;

	out->Header = in->Header;
	out->HeaderN.y = out->HeaderN.z = 1;
	mrcInit(out, NULL);

	for(i=0; i<in->HeaderN.x; i++){
		mrcPixelDataGet(in, i, delta, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(out, i, 0, 0, data, mrcPixelRePart);
	}
}
