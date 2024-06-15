/*
# lmrcSinogramFETnormalizedMap : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETnormalizedMap 
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
#include "eosString.h"
#include "File.h"
#include "../inc/mrcImage.h"
#include "lmrcSinogramFET.h"
#include "lmrcSinogramFETnormalizedMap.h"
#include "lmrcImageBinarization.h"

static int __inFileRead(FILE* in, mrcImage* out);
static int __MapChkTest(mrcImage* in, double x, double y, int* rk, int mode); 
static void __MapCounterMatch(mrcImage* in, mrcImage* out, int mode);
static void __MapCreate(mrcImage* in, mrcImage* out, double* weight, int in1, int in2, int mode);
static void __RankPrint(int** in, int xmax, int ymax, int mode);
static void __mapchker(mrcImage* in, mrcImage* out);
static void __mapDependencyChker(mrcImage* in, double** out, int mode);


void
lmrcSinogramFETnormalizedMap(lmrcSinogramFETnormalizedMapInfo in, int mode)
{
	int i;
	mrcImage inI;
	lmrcSinogramFETnormalizedMapNormalizeInfo ninfo;
	lmrcSinogramFETnormalizedMapAAtestInfo cinfo;
	lmrcSinogramFETPCAInfo pcainfo;


	in.fetz = __inFileRead(in.In,&inI);
	
	ninfo.in = &inI; ninfo.out = in.outFET;
	lmrcSinogramFETnormalizedMapNormalize(ninfo,0);

	if(in.mode){
		pcainfo.inList = in.In;
		pcainfo.flagInImage = 1;
		pcainfo.inImage = ninfo.out;
		pcainfo.Out = in.fptOut;
		//fprintf(stdout,"in FETnormalizedMap mode 1\n");
		lmrcSinogramFETPCA(pcainfo,0);
	 }else{
			 

	//fprintf(stderr,"in lmain normalized\n");
	if(in.flagcomList){
		cinfo.aatestmode = in.aatestmode;
		cinfo.in = ninfo.out; //cinfo.out = in.outMAP;
		cinfo.comList = in.comList;
		if(in.flagWeight){
			cinfo.weight = in.weight;
		}else{
			for(i=0;i<inI.HeaderN.x;i++)
				mrcPixelDataSet(&inI,i,0,0,1.0, mrcPixelRePart);
			cinfo.weight = &inI;
		}
		//fprintf(stderr,"in lmain before AAtest\n");
		lmrcSinogramFETnormalizedMapAAtest(cinfo,0);
	}

	}
}

void 
lmrcSinogramFETnormalizedMapAAtest(lmrcSinogramFETnormalizedMapAAtestInfo in, int mode)
{
	int i,j,k;
	int counter=0;
	int x,y,z,zm,half;
	int* ranks;
	int** rank;
	double* weight;
	int rk;
	char s[256];
	char name[50] = "map";
	double data,data1,data2;
	double** dep;
	mrcImage map1,map2,map;
	
	x = in.in->HeaderN.x;  y = in.in->HeaderN.y;  z = in.in->HeaderN.z;
	weight = (double*)memoryAllocate(sizeof(double)*x,"in lmrcSinogramFETnormalizedMapC");
	for(i=0;i<x;i++){
		mrcPixelDataGet(in.weight,i,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
		weight[i] = data;
	}
	                       // malloc and initialize rank
	rank = (int**)memoryAllocate(sizeof(int*)*(x+1),"in lmrcSinogramFETnormalizedMapC");
	ranks = (int*)memoryAllocate(sizeof(int)*(x+1),"in lmrcSinogramFETnormalizedMapC");
	if(in.aatestmode){
		dep = (double**)memoryAllocate(sizeof(double*)*(x+1),"in lmrcSinogramFETnormalizedMapC");
		for(i=0;i<x+1;i++){ 
			rank[i] = (int*)memoryAllocate(sizeof(int)*(y*y*0.05),"in lmrcSinogramFETnormalizedMapC");
			for(j=0;j<(int)(y*y*0.05);j++) rank[i][j] = 0;
			dep[i] = (double*)memoryAllocate(sizeof(double)*(x+1),"in lmrcSinogramFETnormalizedMapC");
			for(j=0;j<x+1;j++) dep[i][j] = 0.0;
			
		}
	}else{ 
		rank[x] = (int*)memoryAllocate(sizeof(int)*(y*y*0.05),"in lmrcSinogramFETnormalizedMapC");
		for(j=0;j<(int)(y*y*0.05);j++) rank[x][j] = 0;
	}
	map1.Header = in.in->Header;
	map.Header = in.in->Header;
	map1.HeaderN.x = map.HeaderN.x = y;
	map1.HeaderN.y = map.HeaderN.y = y;
	if(in.aatestmode) map1.HeaderN.z = map.HeaderN.z = x+1;
	else map1.HeaderN.z = map.HeaderN.z = 1;
	mrcInit(&map1,NULL); mrcInit(&map,NULL);
	
	//fprintf(stderr,"in AAtest after initialize\n");
	                       // main
	fseek(in.comList, 0L, SEEK_SET);
	//fprintf(stderr,"in AAtest before mainloop\n");
	for(i=0; i<z-1; i++){
		//fprintf(stdout,"start %d th\n",i);
	for(j=i+1; j<z; j++){
		stringGetFromFile(s, "", in.comList, stdout, 1);
		//if(i!=52 || j!=54);
		//else{
		data1 = (double)stringGetNthRealData(s, 1, " ,\t");
		data2 = (double)stringGetNthRealData(s, 2, " ,\t");
		__MapCreate(in.in,&map1,weight,i,j,in.aatestmode);
		__MapCounterMatch(&map1,&map,in.aatestmode);
		fprintf(stderr,"map %d-%d\t",i,j);
		if(in.aatestmode){
			__mapchker(&map,&map1);
			__mapDependencyChker(&map1,dep,0);
		}
		rk = __MapChkTest(&map, data1, data2, ranks, in.aatestmode);
		fprintf(stderr,"rank: %d\n",rk);
		/*rank[x][(rk/10)]++;
		if(in.aatestmode){
			for(k=0;k<x;k++) rank[k][(ranks[k]/10)]++;
		}*/		
		//mrcFileWrite(&map1, "./binmap/testmap52-54.temp", "in main" ,0);
		//}
		//counter++;
	}} 

	__mapDependencyChker(&map1,dep,1);
	
	//fprintf(stderr,"in AAtest before print\n");
	
	//__RankPrint(rank,x,y*y*0.05,in.aatestmode);
	
}

void
__mapDependencyChker(mrcImage* in, double** out, int mode)
{
	int i,j,k,l;
	int dots;
	int in1,in2,in0;
	double data1,data2,data;

	if(mode==0){
	dots=in->HeaderN.x*in->HeaderN.x/2;
	for(i=0;i<in->HeaderN.z-2;i++){
	for(j=i+1;j<in->HeaderN.z-1;j++){
		data = 0.0;
		for(k=0;k<in->HeaderN.x;k++){
		for(l=0;l<in->HeaderN.y/2;l++){
			mrcPixelDataGet(in,k,l,i,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in,k,l,j,&data2, mrcPixelRePart, mrcPixelHowNearest);
			in1=(int)data1; in2=(int)data2; if(in1==in2) data += 1;
		}}
		data /= dots;
		out[i][j] += data;
		out[j][i] += data;
	}}
	data=0;
	for(k=0;k<in->HeaderN.x;k++){
	for(l=0;l<in->HeaderN.y/2;l++){
		mrcPixelDataGet(in,k,l,in->HeaderN.z-1,&data1, mrcPixelRePart, mrcPixelHowNearest);
		if((int)data1==0) data++;
	}}
	data /= dots;
	out[in->HeaderN.z-1][in->HeaderN.z-1] += data;
	fprintf(stderr,"%f\t%f\t%f\t",out[0][6],out[4][7],data);
	}
	
	else{					// mode=1: print dependency 
		for(i=0;i<in->HeaderN.z;i++){
		for(j=0;j<in->HeaderN.z;j++){
			if(i==in->HeaderN.z-1 && j==in->HeaderN.z-1)
				fprintf(stdout,"%f\t",out[i][j]/4950);
			else if(i==j || (i==in->HeaderN.z-1 || j==in->HeaderN.z-1))
				fprintf(stdout,"----\t");
			else
				fprintf(stdout,"%f\t",out[i][j]/4950);
		}fprintf(stdout,"\n");
		}
	}
}

void
__mapchker(mrcImage* in, mrcImage* out)
{
	int i,j,k;
	double p[10]={0.4,0.15,0.15,0.21,0.38,0.01,0.43,0.5,0.46,0.39};
	mrcImage temp,tout;
	double data,data1,data2;
	lmrcImageBinarizationInfo info;

	temp.Header=in->Header; temp.HeaderN.z=1;
	mrcInit(&temp,NULL);
	info.thresHold=0.0;
	info.value=0.0;
	info.flagNear=0;
	info.near=0.0;
	info.nLevel=256;
	

	for(i=0;i<in->HeaderN.z-1;i++){
		for(j=0;j<in->HeaderN.x;j++){
		for(k=0;k<in->HeaderN.y;k++){
			mrcPixelDataGet(in,j,k,i,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(&temp,j,k,0,data1, mrcPixelRePart);
		}}mrcStatDataSet(&temp,0);
		info.p = p[i];
		lmrcImageBinarization(&tout,&temp,info,48);
		for(j=0;j<in->HeaderN.x;j++){   
        for(k=0;k<in->HeaderN.x;k++){
            mrcPixelDataGet(&tout,j,k,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
            mrcPixelDataSet(out,j,k,i,data1, mrcPixelRePart);
			if(i==0)	data = data1;
			else{
				mrcPixelDataGet(out,j,k,in->HeaderN.z-1,&data, mrcPixelRePart, mrcPixelHowNearest);
				data += data1;
			}
			mrcPixelDataSet(out,j,k,in->HeaderN.z-1,data, mrcPixelRePart);
        }}
		mrcImageFree(&tout,"in __mapchker");
	}mrcStatDataSet(out,0);
	mrcImageFree(&temp,"in __mapchker");
}

void 
__MapCreate(mrcImage* in, mrcImage* out, double* weight, int in1, int in2, int mode)
{
	int i,j,k;
	int wholedis;
	int x,y,z;
	double data1,data2,data,sum;

	if(mode) wholedis = in->HeaderN.x;
	else wholedis = 0;
	
	for(i=0;i<in->HeaderN.y;i++){
	for(j=0;j<in->HeaderN.y;j++){
		sum = 0.0;
		for(k=0; k<in->HeaderN.x; k++){
			mrcPixelDataGet(in,k,i,in1,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in,k,j,in2,&data2, mrcPixelRePart, mrcPixelHowNearest);
			data = pow((data1-data2),2);
			if(mode) mrcPixelDataSet(out,i,j,k,data, mrcPixelRePart);
			sum += data * weight[k];
		}
		mrcPixelDataSet(out,i,j,wholedis,sum, mrcPixelRePart);
	}}
	mrcStatDataSet(out,0);
}

void 
__MapCounterMatch(mrcImage* in, mrcImage* out, int mode)
{
	int i,j,k;
	int half;
	double data1,data2,data;

	//fprintf(stderr,"in countermatch\n");
	half = in->HeaderN.y/2;
	//fprintf(stderr,"%d %d %d\n",half,in->HeaderN.z,in->HeaderN.x);
	for(k=0; k<in->HeaderN.z; k++){
		for(i=0; i<in->HeaderN.x; i++){
		for(j=0; j<half; j++){
			mrcPixelDataGet(in,i,j,k,&data1, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in,i+half,j+half,k,&data2, mrcPixelRePart, mrcPixelHowNearest);
			data = pow((pow(data1,2)+pow(data2,2))/2,0.5);
			mrcPixelDataSet(out,i,j,k,data, mrcPixelRePart);
			mrcPixelDataSet(out,i+half,j+half,k,data, mrcPixelRePart);
		}}
	}
	mrcStatDataSet(out,0);
}

int
__MapChkTest(mrcImage* in, double x, double y, int* rk, int mode)
{
	int i,j,k,ix,iy,tx,ty;
	int count = 0;
	double temp;
	double cldata, data;
	int end;

	if(in->HeaderN.x != 360){
		temp = 360 / in->HeaderN.x;
		x /= temp; y /= temp;
	}
	tx = (int)x;  ty = (int)y;
	ix = tx + (int)((x-(double)tx)*2);  iy = ty + (int)((y-(double)ty)*2);

	/*if(mode) end = in->HeaderN.z;
	else end = 1;*/
	//fprintf(stderr,"%d\t",in->HeaderN.z);
	for(k=0; k<in->HeaderN.z; k++){
		//fprintf(stderr,"in the loop %dth \t",k);
		count=0;
		mrcPixelDataGet(in,ix,iy,k,&cldata, mrcPixelRePart, mrcPixelHowNearest);
	
		//fprintf(stderr,"cldata %f got \n",cldata);
		for(i=0; i<in->HeaderN.x; i++){
		for(j=0; j<in->HeaderN.x/2; j++){
			mrcPixelDataGet(in,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
			if(data <= cldata) count++;
		}}
		//fprintf(stderr,"counted \n");
		rk[k] = --count;
		
	}
	fprintf(stderr,"cl: %d\t%d\t value%f\t",ix,iy,cldata);
	return(count); 
}

void 
lmrcSinogramFETnormalizedMapNormalize(lmrcSinogramFETnormalizedMapNormalizeInfo in, int mode)
{
	int i,j,k,x,y,z;
	double* ave;
	double* sd;
	double data, temp;
	char ss;

	x = in.in->HeaderN.x;  y = in.in->HeaderN.y;  z = in.in->HeaderN.z;

	ave = (double*)memoryAllocate(sizeof(double)*x,"in lmrcSinogramFETnormalizedMapN");
	sd = (double*)memoryAllocate(sizeof(double)*x,"in lmrcSinogramFETnormalizedMapN");
	for(i=0;i<x;i++){ ave[i] = 0.0; sd[i] = 0.0; }
	
	in.out->Header = in.in->Header;
	in.out->HeaderN = in.in->HeaderN;
	mrcInit(in.out,NULL);

	
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
			for(k=0;k<z;k++){
				mrcPixelDataGet(in.in,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
				ave[i] += data;
			}}
		ave[i] /= (double)(y*z);
	}
	for(i=0;i<x;i++){
        for(j=0;j<y;j++){
			temp = 0;
            for(k=0;k<z;k++){
                mrcPixelDataGet(in.in,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
				temp += pow(data-ave[i],2);
			}
			sd[i] += temp;
		}
		sd[i] /= (double)(y*z);
		sd[i] = pow(sd[i],0.5);
	}
	for(i=0;i<x;i++){
        for(j=0;j<y;j++){
           for(k=0;k<z;k++){
                mrcPixelDataGet(in.in,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
				data -= ave[i];
				if(sd[i]!=0.0) data /= sd[i];
				mrcPixelDataSet(in.out,i,j,k,data, mrcPixelRePart);
		   }}
	}
	mrcStatDataSet(in.out,0);
	free(ave);
	free(sd);
}

int
__inFileRead(FILE* in, mrcImage* out)
{
	int i,j,k,count;
	char s[256];
	double data;
	mrcImage temp;

	count = 0;
	fseek(in, 0L, SEEK_SET);
	stringGetFromFile(s,"",in,stdout,1);
	mrcFileRead(&temp, s, "in lmrcSinogramFETnormalizedMap__inFileRead",0);
	out->Header = temp.Header;
	out->HeaderN.x = temp.HeaderN.x;    out->HeaderN.y = temp.HeaderN.y;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)) count++;
	out->HeaderN.z = count;
	mrcInit(out,NULL);
	
	k=0;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		mrcFileRead(&temp, s, "in lmrcSinogramFETnormalizedMap__inFileRead",0);
		for(i=0;i<temp.HeaderN.x;i++){
			for(j=0;j<temp.HeaderN.y;j++){
				mrcPixelDataGet(&temp,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out,i,j,k,data, mrcPixelRePart);
			}}
		k++;
	}
	mrcStatDataSet(out,0);

	return(count);
}

void 
__RankPrint(int** in, int xmax, int ymax, int mode)
{
	int i,j;
	
	fprintf(stdout,"rank\t");
	if(mode) for(i=0; i<xmax; i++) fprintf(stdout,"f%d\t",i);
	fprintf(stdout,"whole\n");

	for(i=0; i<ymax; i++){
		fprintf(stdout,"%d-%d\t",i*10,i*10+9);
		if(mode)	for(j=0; j<xmax; j++) fprintf(stdout,"%d\t",in[j][i]);
		fprintf(stdout,"%d\n",in[xmax][i]);
	}
}





















