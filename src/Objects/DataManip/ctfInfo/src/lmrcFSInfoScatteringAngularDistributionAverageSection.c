/*
# lmrcFSInfoScatteringAngularDistributionAverageSection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcFSInfoScatteringAngularDistributionAverageSection 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#define DEBUG
#include  "genUtil.h"
#include "mrcImage.h"
#include "Vector.h"
#include "./lmrcFSInfoScatteringAngularDistributionAverageSection.h"

floatVector*
lmrcFSInfoScatteringAngularDistributionAverageSection(mrcImage* fft, double startAngle,double endAngle)
{
	floatVector* fv;
	floatVector* count;
	float iX, iY;
	double re, im, pow;
	double angle = 0.0;
	int flag, i, R;
	int startX,startY,endX,endY;
	float mul, mul2;
	float* data;
	unsigned long size;

	if(fft->HeaderN.x<fft->HeaderN.y) {
		flag = 0; 
		size = fft->HeaderN.x/2+1;
		mul = ((float)fft->HeaderN.x)/((float)fft->HeaderN.y);
	} else {
		flag = 1;
		size = fft->HeaderN.y/2+1;
		mul = ((float)fft->HeaderN.y)/((float)fft->HeaderN.x);
	}
	mul2 = mul*mul;
	DEBUGPRINT3("%d %d %d\n", fft->HeaderN.y, fft->HeaderN.x,size);
	
	fprintf(stdout,"%lf %lf \n",startAngle,endAngle);
	for(iX=-fft->HeaderN.x/2.0+1; iX<fft->HeaderN.x/2.0; iX++) {
		for(iY=-fft->HeaderN.y/2.0+1; iY<fft->HeaderN.y/2.0; iY++){
			angle = atan2(iY,iX)/M_PI*180;
			if( angle <0 ){
				angle += 180;
			}
			
			if( ((startAngle < angle/*(atan(iY/iX)/M_PI*180)*/) && (/*(atan(iY/iX)/M_PI*180)*/angle < endAngle)) || ((startAngle < (angle-180)) && ((angle-180) < endAngle)) ){
				//mrcPixelDataSet(fft, iX, iY, 0.0, mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest)*180/(endAngle - startAngle), mrcPixelPow);
			}
			else{
				mrcPixelDataSet(fft, iX, iY, 0.0, 0.0 * 180/(endAngle-startAngle), mrcPixelPow);
			}
			//mrcPixelDataGet(fft, iX, iY, 0.0, &pow, mrcPixelPow, mrcPixelHowNearest);
		}
	}
}
