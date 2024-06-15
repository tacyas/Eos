/*
# mrcSinogramFETcalcSDforNormalize : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcSinogramFETcalcSDforNormalize
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcSinogramFETcalcSDforNormalizeInfo {
	float a;
	int   b;
} lmrcSinogramFETcalcSDforNormalizeInfo;

typedef enum lmrcSinogramFETcalcSDforNormalizeMode {
	a=0,
	b=1
} lmrcSinogramFETcalcSDforNormalizeMode;
*/
void __calcAveSD(mrcImage* in, double* ave, double* sd, int mode);

int
main(int argc, char* argv[]) 
{
	mrcSinogramFETcalcSDforNormalizeInfo info;
	mrcImage in, sdf, libl;
	int i,j,k,n,sm, num;
	double data, *ave, *sd, data1, data2, data3;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&libl, info.Libl, "in main",0);

	if(info.mode == 1){
		mrcFileRead(&in, info.In, "in main",0);
		if(info.Sm == 0) sm=0; else if(info.Sm == 1) sm=2; else if(info.Sm == 2) sm=4; else sm=6;
		mrcPixelDataGet(&libl,0,sm,0,&data,mrcPixelRePart, mrcPixelHowNearest);
		num = (int)data;
		ave = (double*)memoryAllocate(sizeof(double)*in.HeaderN.x,"in main");
		sd = (double*)memoryAllocate(sizeof(double)*in.HeaderN.x,"in main");
		
		__calcAveSD(&in,ave,sd,0);
		for(i=0;i<in.HeaderN.x;i++){
			mrcPixelDataGet(&libl,i+1,sm,0,&data,mrcPixelRePart, mrcPixelHowNearest);
			data = (data*(double)num+ave[i])/(double)(num+1);
			mrcPixelDataSet(&libl,i+1,sm,0,data, mrcPixelRePart);
			mrcPixelDataGet(&libl,i+1,sm+1,0,&data,mrcPixelRePart, mrcPixelHowNearest);
			data = (data*(double)num+sd[i])/(double)(num+1);
			mrcPixelDataSet(&libl,i+1,sm+1,0,data, mrcPixelRePart);
		}
		mrcPixelDataSet(&libl,0,sm,0,(double)(num+1), mrcPixelRePart);
		mrcPixelDataSet(&libl,0,sm+1,0,(double)(num+1), mrcPixelRePart);
		mrcStatDataSet(&libl,0);
		mrcFileWrite(&libl, info.Libl, "in main",0);
	}else if(info.mode == 0){
		sdf.Header = libl.Header;
		sdf.HeaderN.x = libl.HeaderN.x-1;
		sdf.HeaderN.y = 1;
		mrcInit(&sdf, NULL);
		for(i=0;i<sdf.HeaderN.x;i++){
			mrcPixelDataGet(&libl,i+1,1,0,&data,mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&libl,i+1,3,0,&data1,mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&libl,i+1,5,0,&data2,mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&libl,i+1,0,0,&data3,mrcPixelRePart, mrcPixelHowNearest);
			data = data1*data/data2;
			mrcPixelDataSet(&sdf,i,0,0,data, mrcPixelRePart);
		}
		mrcStatDataSet(&sdf,0);
		mrcFileWrite(&sdf, info.Out, "in main",0);
		if(info.flagOW){
			for(i=0;i<sdf.HeaderN.x;i++){
				mrcPixelDataGet(&libl,i+1,0,0,&data,mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&libl,i+1,5,0,&data1,mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&libl,i+1,7,0,&data2,mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&libl,i+1,3,0,&data3,mrcPixelRePart, mrcPixelHowNearest);
				data = 1/(fabs(1.0-data3/data2)+0.11);
				mrcPixelDataSet(&sdf,i,0,0,data, mrcPixelRePart);
			}
			mrcPixelDataSet(&sdf,0,0,0,0, mrcPixelRePart);
			
			mrcStatDataSet(&sdf,0);
			mrcFileWrite(&sdf, info.OW, "in main",0);
		}
	}else{
		fprintf(stderr,"mode %d not supported \n", (int)info.mode);
	}
	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0: SDfile writeout from liblary file\n");
	fprintf(stderr, "        Library(option -l) is Essential\n");
	fprintf(stderr, "ow : weightfile writeout from liblary file when mode 0\n");
	fprintf(stderr, "mode 1: to overwrite data library\n");
	fprintf(stderr, "        Essential options are: -sm, -i, -l\n");
	fprintf(stderr, "        if you want to make new data library,\n");
	fprintf(stderr, "        you have to make 2Dmrc-format pre-library file using tool \"array2mrc\"\n");
	fprintf(stderr, "        Array:  x=(number of feature + 1), y=6, z=0, data: all 0.0\n");
	fprintf(stderr, "sm : 0 is noise-free refarence FETdata,\n");
	fprintf(stderr, "     1 is no-smoothing FET data\n");
	fprintf(stderr, "     17 or any other number is smoothed FET data\n");
}

void __calcAveSD(mrcImage* in, double* ave, double* sd, int mode)
{
	int i,j;
	double data; 

	for(i=0;i<in->HeaderN.x;i++)
		sd[i] = ave[i] = 0.0;
	for(j=0;j<in->HeaderN.y;j++){
		for(i=0;i<in->HeaderN.x;i++){
			mrcPixelDataGet(in,i,j,0,&data,mrcPixelRePart, mrcPixelHowNearest);
			ave[i] += data/(double)in->HeaderN.y;
		}}
	for(j=0;j<in->HeaderN.y;j++){
		for(i=0;i<in->HeaderN.x;i++){
			mrcPixelDataGet(in,i,j,0,&data,mrcPixelRePart, mrcPixelHowNearest);
			sd[i] += pow(data-ave[i],2)/(double)in->HeaderN.y;
		}}
}
	




