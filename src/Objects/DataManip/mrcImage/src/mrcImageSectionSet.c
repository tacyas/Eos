/*
# mrcImageSectionSet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSectionSet 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "../inc/mrcImage.h"


void
mrcImageSectionSet(mrcImage* dst, mrcImage* section, mrcImageParaTypeReal z, long mode)
{
	mrcImageParaTypeReal x, y;
	double data;	

	if(dst->HeaderN.z <= z) {
		fprintf(stderr, "in mrcImageSectionSet: Max < Section %f ", z);
		return;  
	}
	
	for(y=0; y<dst->HeaderN.y; y++) {
	for(x=0; x<dst->HeaderN.x; x++) {
		mrcPixelDataGet(section, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(dst, x, y, z, data, mrcPixelRePart);
	}
	}
}
