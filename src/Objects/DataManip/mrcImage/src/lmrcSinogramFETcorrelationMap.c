/*
# lmrcSinogramFETcorrelationMap : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETcorrelationMap 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "lmrcSinogramFET.h"
#include "lmrcSinogramFETcorrelationMap.h"
							  

void
lmrcSinogramFETcorrelationMap(mrcImage* in1, mrcImage* in2, mrcImage* out, lmrcSinogramFETcorrelationMapInfo info, int mode)
{
	int i,j,k;
	double ans, data1, data2;
	mrcImage in, In;
	//mrcImage tout;
	mrcImage* inp;
	double* sd;
	double* weight;

	if(info.Nmode || info.flagSD) inp = &in;
	else inp = &In;
	inp->Header = in1->Header;
	inp->HeaderN.y = in1->HeaderN.y+in2->HeaderN.y;
	mrcInit(inp, NULL);
	for(i=0;i<in1->HeaderN.x;i++){
		for(j=0;j<in1->HeaderN.y;j++){
			mrcPixelDataGet(in1,i,j,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(inp,i,j,0,data1, mrcPixelRePart);
	}}
	for(i=0;i<in1->HeaderN.x;i++){
		for(j=0;j<in2->HeaderN.y;j++){
			mrcPixelDataGet(in2,i,j,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(inp,i,j+in1->HeaderN.y,0,data1, mrcPixelRePart);
	}}
	mrcStatDataSet(inp,0);
	
	if(info.flagSD){
		sd = (double*)memoryAllocate(sizeof(double)*in1->HeaderN.x,"in lmrcSinogramFETcorrelationMap");
		for(i=0;i<in1->HeaderN.x;i++){
			mrcPixelDataGet(info.SD,i,0,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
			sd[i] = data1;
		}
		lmrcSinogramFETnormalizeBySD(&in, &In, sd, 0);
	}else if(info.Nmode){
		lmrcSinogramFETc(&in, &In, 0);
		//mrcFileWrite(&In,"temp","in lmrcSinogramFETcorrelationMap",0);
		//mrcFileWrite(&In, "temp2", "in lmrcSinogramFETcorrelationMap", 0);
	}
	
	out->Header = in2->Header;
	out->HeaderN.x = in1->HeaderN.y;
	mrcInit(out,NULL);
	/*if(info.Cmode){
		tout.Header = in2->Header;
		tout.HeaderN.x = in1->HeaderN.y;
		tout.HeaderN.z = in1->HeaderN.x;
		mrcInit(&tout,NULL);
	}*/
	weight = (double*)memoryAllocate(sizeof(double)*in1->HeaderN.x,"in lmrcSinogramFETcorrelationMap");
	if(info.flagWeight){
		for(i=0;i<in1->HeaderN.x;i++){
			mrcPixelDataGet(info.Weight,i,0,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
			weight[i] = data1;
		}
	}else{
		for(i=0;i<in1->HeaderN.x;i++)  weight[i] = 1.0;
		weight[0] = 4.0;
	}
	
	if(info.Cmode){
		lmrcSinogramFETcorrelationMapDP(&In,out,weight,0);
	}else{
		for(i=0; i<out->HeaderN.x; i++){
		for(j=0; j<out->HeaderN.y; j++){
			ans = 0.0;
			for(k=0; k<in1->HeaderN.x ;k++){
				mrcPixelDataGet(&In,k,i,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&In,k,j+in1->HeaderN.y,0,&data2, mrcPixelRePart, mrcPixelHowNearest);
				ans += pow((data1-data2),2)*weight[k];
			}
			ans = pow(ans,0.5);	ans *= -1.0;		
			mrcPixelDataSet(out,i,j,0,ans, mrcPixelRePart);
		}}
	}
	mrcStatDataSet(out,0);
}

void lmrcSinogramFETcorrelationMapDP(mrcImage* in, mrcImage* out, double* w, int mode)
{
	int i,j,k;
	mrcImage tout;
	double data1,data2;
	double* datas; 
	double ave, sd;
	int flagminus;

	tout.Header = out->Header;
	tout.HeaderN.z = in->HeaderN.x;
	mrcInit(&tout,NULL);
	
	datas = (double*)memoryAllocate(sizeof(double)*in->HeaderN.x,"in lmrcSinogramFETcorrelationMapDP");
	for(k=0;k<in->HeaderN.x;k++){
		for(i=0; i<out->HeaderN.x; i++){
		for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(in,k,i,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in,k,j+out->HeaderN.y,0,&data2, mrcPixelRePart, mrcPixelHowNearest);
			data1 = -1.0*fabs(data1-data2);
			mrcPixelDataSet(&tout,i,j,k,data1, mrcPixelRePart);
		}}
		ave = sd = 0.0;
		for(i=0; i<out->HeaderN.x; i++){
		for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(&tout,i,j,k,&data1, mrcPixelRePart, mrcPixelHowNearest);
			ave += data1;
		}}
		ave /= pow((double)out->HeaderN.y,2);
		for(i=0; i<out->HeaderN.x; i++){
		for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(&tout,i,j,k,&data1, mrcPixelRePart, mrcPixelHowNearest);
			sd += pow((data1-ave),2);
		}}
		sd /= pow((double)out->HeaderN.y,2);
		for(i=0; i<out->HeaderN.x; i++){
		for(j=0; j<out->HeaderN.y; j++){
			mrcPixelDataGet(&tout,i,j,k,&data1, mrcPixelRePart, mrcPixelHowNearest);
			data1 -= ave;
			if(sd >= 0.000001) data1 /= sd;
			mrcPixelDataSet(&tout,i,j,k,data1, mrcPixelRePart);
		}}
	}

	for(i=0; i<out->HeaderN.x; i++){
	for(j=0; j<out->HeaderN.y; j++){
		data1 = 1.0;
		flagminus = 1;
		for(k=0;k<in->HeaderN.x;k++){
			mrcPixelDataGet(&tout,i,j,k,&(datas[k]), mrcPixelRePart, mrcPixelHowNearest);
			data1 *= fabs(datas[k]);
			if(datas[k] <= 0.0) flagminus = -1;
		}
		data1 *= (double)flagminus;
		mrcPixelDataSet(out,i,j,0,data1, mrcPixelRePart);
	}}
}

void
lmrcSinogramFETcorrelationMapCounterMatching(mrcImage* in, mrcImage* out, int mode)
{
	int i,j;
	int max, half;
	double data, data1, data2;

	max = in->HeaderN.x;
	half = max/2;
	out->Header = in->Header;
	mrcInit(out,NULL);
	for(i=0;i<max;i++){
		for(j=0;j<half;j++){
			mrcPixelDataGet(in,i,j,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in,i+half,j+half,0,&data2, mrcPixelRePart, mrcPixelHowNearest);
			data = pow((pow(data1,2)+pow(data2,2))/2,0.5);
			if(data1<0.0 || data2<0.0) data *= -1.0;
			mrcPixelDataSet(out,i,j,0,data, mrcPixelRePart);
			mrcPixelDataSet(out,i+half,j+half,0,data, mrcPixelRePart);
		}}
	mrcStatDataSet(out,0);
}

void
lmrcSinogramFETnormalizeBySD(mrcImage* in, mrcImage* out, double* sd, int mode)
{
	int i,j;
	double* ave;
	double data;

	ave = (double*)memoryAllocate(sizeof(double)*in->HeaderN.x,"in lmrcSinogramFETnormalizeBySD");

	out->Header = in->Header;
	mrcInit(out, NULL);
	for(i=0;i<in->HeaderN.x;i++){
		for(j=0;j<in->HeaderN.y;j++){
			mrcPixelDataGet(in,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			ave[i] += data/(double)in->HeaderN.y;
		}}
	for(i=0;i<in->HeaderN.x;i++) sd[i] = pow(sd[i],0.5);

	for(i=0;i<in->HeaderN.x;i++){
		for(j=0;j<in->HeaderN.y;j++){
			mrcPixelDataGet(in,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			data -= ave[i];
			if(sd[i]!=0.0) data /= sd[i];
			mrcPixelDataSet(out,i,j,0,data, mrcPixelRePart);
		}}
	mrcStatDataSet(out, 0);
}
