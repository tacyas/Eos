/*
# lmrcImageMaxDataGet.c  1.1
# The latest update : 08/12/96 at 11:43:11
#
#@(#) lmrcImageMaxGet ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : lmrcImageMaxGet 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrcImageMaxGet ver1.1; Date:96/08/12 @(#)";

#include "../inc/mrcImage.h"

double
lmrcImageMaxDataGet(mrcImage* mrc, long mode)
{
	long x,y,z;
	double max, data;

	mrcPixelDataGet(mrc, 0.0, 0.0, 0.0, &max, mrcPixelRePart, mrcPixelHowNearest);
	for(x=0; x<mrc->HeaderN.x; x++) {
		for(y=0; y<mrc->HeaderN.y; y++) {
			for(z=0; z<mrc->HeaderN.z; z++) {
				mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(max<data) {
					max = data;
				}
			}
		}
	}
	return max;
}
