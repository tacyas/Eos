/*
# lmrcImageOneneSimilarityCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageOneLineSimilarityCalc 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "lmrcImageOneLineSimilarityCalc.h"
								
double strengthCalc(mrcImage* in1, mrcImage* in2, int shift);
double differential1Calc(mrcImage* in1, mrcImage* in2, int shift);
double differential2Calc(mrcImage* in1, mrcImage* in2, int shift);
double lengthCalc(mrcImage* in1, mrcImage* in2, int shift);
			   
double
lmrcImageOneLineSimilarityCalc(mrcImage* in1, mrcImage* in2, lmrcImageOneLineSimilarityCalcInfo linfo)
{
	double L=0;
	double l1=1, l2=1, l4=1, l8=1;
	double w1=1, w2=1, w4=1, w8=1;
	int shift=0;
	int t;
	
/* making */
	t=linfo.methodmode&0x01;							
	if(t==1)
		l1=strengthCalc(in1,in2,shift);
	t=linfo.methodmode&0x02;
	if(t==2)
		l2=differential1Calc(in1,in2,shift);
	t=linfo.methodmode&0x04;
	if(t==4)
		l4=differential2Calc(in1,in2,shift);
	t=linfo.methodmode&0x08;
	if(t==8)
		l8=lengthCalc(in1,in2,shift);
	L=pow(l1,w1)*pow(l2,w2)*pow(l4,w4)*pow(l8,w8);			
	return L;
}	

double
strengthCalc(mrcImage* in1, mrcImage* in2, int shift)
{
	double L=0, L1=0, L2=0;
	double data1, sumdata1=0;
	double data2, sumdata2=0;
	int x;
	for(x=0 ;x < in1->HeaderN.x ;x++) {
		mrcPixelDataGet(in1, x, 0, 0, &data1, mrcPixelRePart,mrcPixelHowNearest);
        mrcPixelDataGet(in2, x+shift, 0, 0, &data2, mrcPixelRePart,mrcPixelHowNearest);
		sumdata1+=data1;
		sumdata2+=data2;
	}
	sumdata1/=x;
	sumdata2/=x;
	
	for(x=0 ;x < in1->HeaderN.x ;x++) {
		mrcPixelDataGet(in1, x, 0, 0, &data1, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataGet(in2, x+shift, 0, 0, &data2, mrcPixelRePart,mrcPixelHowNearest);
		L+=data1-sumdata1*data2-sumdata2;
		L1+=pow(data1-sumdata1,2);
		L2+=pow(data2-sumdata2,2);
	}
	
	L=L/pow((L1*L2),0.5);
		
	return L; 
}

double
differential1Calc(mrcImage* in1, mrcImage* in2, int shift)
{
	double L=0, L1=0, L2=0;
    double data1, data11, sumdata1=0;
    double data2, data22, sumdata2=0;
    int x;
    for(x=0 ;x < in1->HeaderN.x ;x++) {
        mrcPixelDataGet(in1, x+1, 0, 0, &data1, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataGet(in1, x-1, 0, 0, &data11, mrcPixelRePart,mrcPixelHowNearest);
        mrcPixelDataGet(in2, x+shift+1, 0, 0, &data2, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataGet(in2, x+shift-1, 0, 0, &data22, mrcPixelRePart,mrcPixelHowNearest);
        sumdata1+=fabs(data1-data11)/2;
        sumdata2+=fabs(data2-data22)/2;
    }

    sumdata1/=x;
    sumdata2/=x;
    
    for(x=0 ;x < in1->HeaderN.x ;x++) {
        mrcPixelDataGet(in1, x+1, 0, 0, &data1, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataGet(in1, x-1, 0, 0, &data11, mrcPixelRePart,mrcPixelHowNearest);
        mrcPixelDataGet(in2, x+shift+1, 0, 0, &data2, mrcPixelRePart,mrcPixelHowNearest);
		mrcPixelDataGet(in2, x+shift-1, 0, 0, &data22, mrcPixelRePart,mrcPixelHowNearest);
        L+=(fabs(data1-data11)/2-sumdata1)*(fabs(data2-data22)-sumdata2/2);
        L1+=pow(((data1-data11)/2-sumdata1),2);
        L2+=pow(((data2-data22)/2-sumdata2),2);
    }

    L=L/pow((L1*L2),0.5);
																															 
	return L;
	return 0.5;
}

double
differential2Calc(mrcImage* in1, mrcImage* in2, int shift)
{   
	return 0.5;
}

double              
lengthCalc(mrcImage* in1, mrcImage* in2, int shift)
{    
    return 0.5;
}
					
