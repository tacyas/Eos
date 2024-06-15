/*
# lmrcImagePosterization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImagePosterization 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "lmrcImageFeatureExtraction.h"
#include "lmrcImagePosterization.h"
#include <stdlib.h>
#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
						 
void
lmrcImagePosterization(mrcImage* in, mrcImage* out, int level, int mode)
{
	int x,y,z,count;
	int temp;
	double data;
	double wholeintensity, oneLevel, current;
	mrcImageInformation linfo;

	out->Header = in->Header;
	mrcInit(out, NULL);
	linfo.mode = meanOfAll;
    lmrcImageInformation(&linfo, in);
    wholeintensity = linfo.max-linfo.min;
    oneLevel = (wholeintensity)/(level-1);
	for(z=0 ;z < in->HeaderN.z ;z++) {
	for(y=0 ;y < in->HeaderN.y ;y++) {
    for(x=0 ;x < in->HeaderN.x ;x++) {
		mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
		current = (data-linfo.min)/oneLevel+0.5;
		temp = (int)current;
		current = (double)temp;
		mrcPixelDataSet(out, x, y, z, current, mrcPixelRePart);
	}}}			 
	mrcStatDataSet(out,0);
}	

