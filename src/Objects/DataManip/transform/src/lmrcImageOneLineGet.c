/*
# lmrcImageOneLineGet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageOneLineGet 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

void
lmrcImageOneLineGet(mrcImage* out, mrcImage* in, float angle, int mode)
{       
	int    i;
    float  y;
    double work;
    double data;

    out->Header    = in->Header;
    out->HeaderN.y = 1;
    out->HeaderN.z = 1;
    mrcInit(out, NULL);

	y = angle/(in->HeaderLength.y*RADIAN);
    for(i=0; i<in->HeaderN.x; i++){
	    mrcPixelDataGet(in, i, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataSet(out, i, 0, 0, data, mrcPixelRePart);
    }
}

void
lmrcImageFTOneLineGet(mrcImage* out, mrcImage* in, float angle, int mode)
{
    int    i;
    float  y;
    double work;
    double re, im;

    out->Header    = in->Header;
    out->HeaderN.y = 1;
    out->HeaderN.z = 1;
    mrcInit(out, NULL);

	y = angle/(in->HeaderLength.y*RADIAN);
    for(i=0; i<=in->HeaderN.x/2; i++){
	    mrcPixelDataGet(in, i, y, 0, &re, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, i, y, 0, &im, mrcPixelImPart, mrcPixelHowNearest);
        mrcPixelDataSet(out, i, 0, 0, re, mrcPixelRePart);
        mrcPixelDataSet(out, i, 0, 0, im, mrcPixelImPart);
    }
}

void
lmrcImageOneLineFTCreate(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, 
	mrcImage* ref, 
	mrcImage* other,
    mrcImage* refOneLineFT, 
	mrcImage* otherOneLineFT, 
	float RefAngle, 
	float OtherAngle, 
	int mode)
{
	mrcImage refOneLine;
    mrcImage otherOneLine;

/*
	switch(linfo->mode){
	    case 0 :
            lmrcImageOneLineGet(&refOneLine, ref, RefAngle, 0);
            lmrcImageOneLineGet(&otherOneLine, other, OtherAngle, 0);
            lmrcImageFFT(refOneLineFT,   &refOneLine,   0);
            lmrcImageFFT(otherOneLineFT, &otherOneLine, 0);
            mrcImageFree(&refOneLine, "in lmrcImageOrientationSearchBySimultaneousMinimization");
            mrcImageFree(&otherOneLine, "in lmrcImageOrientationSearchBySimultaneousMinimization");
		break;
	    case 1 :
	        lmrcImageFTOneLineGet(refOneLineFT,   ref,   RefAngle,   0);
	        lmrcImageFTOneLineGet(otherOneLineFT, other, OtherAngle, 0);
	    break;
	}
*/
	lmrcImageFTOneLineGet(refOneLineFT,   ref,   RefAngle,   0);
	lmrcImageFTOneLineGet(otherOneLineFT, other, OtherAngle, 0);

}

