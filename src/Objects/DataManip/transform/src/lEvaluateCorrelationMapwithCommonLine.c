/*
# lEvaluateCorrelationMapwithCommonLine : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lEvaluateCorrelationMapwithCommonLine 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "File.h"
#include "../../mrcImage/inc/mrcImage.h"
#include "lEvaluateCorrelationMapwithCommonLine.h"

void __writeEva1(FILE* ,int* ,int );
void __writeEva2(FILE* ,int* ,int* ,int );
void __writeEva3(FILE* ,int* ,int );
void __writeNear(lmrcSCMEpeakDetectInfo* info, int comx, int comy, int mode);
void __corrDataChange(mrcImage* in, int mode);
int __HPcount(mrcImage* in, double com, int mode);

void
lEvaluateCorrelationMapwithCommonLine(lEvaluateCorrelationMapwithCommonLineInfo info, int mode)
{
	int i,j,k;
	mrcImage in, out;
	int comx, comy, rankc, rankh;
	int evaluate1[101];
	int evaluate3[50];
	int evaluate2[512];
	int evaluate22[100];
	char s[512];
	char ss[128];
	double data, data1, data2, data3;
	mrcImageInformation linfo;
	lmrcSCMEpeakDetectInfo pDinfo;

	fseek(info.In, 0L, SEEK_SET);
	info.listLength = 0;
	while(NULL!=stringGetFromFile(s,"",info.In,stdout,1)) info.listLength++;
	fseek(info.In, 0L, SEEK_SET);
	fseek(info.InC, 0L, SEEK_SET);

	for(i=0;i<101;i++) evaluate1[i]=0;
	for(i=0;i<512;i++) evaluate2[i]=0;
	for(i=0;i<100;i++) evaluate22[i]=0;
	for(i=0;i<50;i++) evaluate3[i]=0;
	pDinfo.flagOut=0; pDinfo.Out=&out;
	pDinfo.flagThreshold=1; 
	if(info.mode) pDinfo.Threshold=0.05;
	else pDinfo.Threshold=info.PDT;
	pDinfo.flagCount=1;
	pDinfo.PA=info.PA;
	i=0;	

	while(NULL!=stringGetFromFile(s,"",info.In,stdout,1)){
		mrcFileRead(&in, s, "in lEvaluateCorrelationMapwithCommonLine", 0);
		stringGetFromFile(ss,"",info.InC,stdout,1);
		data1 = (double)stringGetNthRealData(ss, 3, " ,\t");
		comx = (int)data1; comx += (int)((data1-(double)comx)*2);
		data2 = (double)stringGetNthRealData(ss, 4, " ,\t");
		comy = (int)data2; comy += (int)((data2-(double)comy)*2);

		if(info.mode){
			__corrDataChange(&in,0);
		}
		
		linfo.mode = meanOfAll;
		lmrcImageInformation(&linfo, &in);
		mrcPixelDataGet(&in, comx, comy, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		evaluate1[(int)((data/linfo.max)*100)]++;

		pDinfo.MaxI = linfo.max;
		i++;
		pDinfo.mode = i;
		if(i==1) pDinfo.flagOut=1;
		else if(i==8) pDinfo.flagOut=1;
		else pDinfo.flagOut=0;
		lmrcSCMEpeakDetect(&in, &pDinfo, 0);
		__writeNear(&pDinfo, comx, comy, info.PN);

		rankc = __HPcount(&in, data, 0); // pi = &rankc !
		if(rankc < 5110) evaluate2[(int)(rankc/10)]++; else evaluate2[511]++;
		if(rankc < 100) evaluate22[rankc]++;
	}
	__writeEva1(info.Out,evaluate1,0);
	__writeEva2(info.Out,evaluate2,evaluate22,0);
	//__writeEva3(info.Out,evaluate3,0);
}

int __HPcount(mrcImage* in, double com, int mode)
{
	int i, j;
	int count=0;
	double data;

	for(i=0;i<360;i++){
		for(j=0;j<180;j++){
			mrcPixelDataGet(in, i, j, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(com > data) count++;
		}
	}
	return count;
}

void
lmrcSCMEpeakDetect(mrcImage* in, lmrcSCMEpeakDetectInfo* info, int mode)
{
	int i, j, k, count, count2, count3;
	//int xsum, ysum;
	double data, data1, data2, data3, data4;
	int temp;

	if(info->flagOut){
		info->Out->Header = in->Header;
		info->Out->HeaderN.y = 180;
		mrcInit(info->Out,NULL);
	}
	info->Count=0;
	
	for(i=0;i<360;i++){
		for(j=0;j<180;j++){
			mrcPixelDataGet(in, i, j, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			if((data/info->MaxI)<info->Threshold){
				mrcPixelDataGet(in, i, j+1, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(in, i, j-1, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(in, i+1, j, 0, &data3, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(in, i-1, j, 0, &data4, mrcPixelRePart, mrcPixelHowNearest);
				if((data<data1 && data<data2) || (data<data3 && data<data4)){
					if((data<data1 && data<data2) && (data<data3 && data<data4)){
						mrcPixelDataGet(in, i+1, j-1, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(in, i-1, j-1, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(in, i+1, j+1, 0, &data3, mrcPixelRePart, mrcPixelHowNearest);
						mrcPixelDataGet(in, i-1, j+1, 0, &data4, mrcPixelRePart, mrcPixelHowNearest);
						if(data<data1 && data<data2 && data<data3 && data<data4){
							if(info->flagOut) mrcPixelDataSet(info->Out,i,j,0, 1.0, mrcPixelRePart);
							if(info->Count<1000){
								info->peak[info->Count].x=i; 
								info->peak[info->Count].y=j;
								info->peak[info->Count].distance=data;
							}
							info->Count++;
						}else if(info->flagOut) mrcPixelDataSet(info->Out,i,j,0, 0.75, mrcPixelRePart);
					}else if(info->flagOut) mrcPixelDataSet(info->Out,i,j,0, 0.5, mrcPixelRePart);
				}else if(info->flagOut) mrcPixelDataSet(info->Out,i,j,0, 0.25, mrcPixelRePart);
			}else if(info->flagOut) mrcPixelDataSet(info->Out,i,j,0, 0.0, mrcPixelRePart);
		}
	}
	if(info->flagOut){
		mrcStatDataSet(info->Out,0);
		mrcFileWrite(info->Out, "1-17.Pmap", "in lmrcSCMEpeakDetect", 0);
	}
	//if(info->mode == 1) mrcFileWrite(info->Out, "001-temp2", "in lmrcSCMEpeakDetect", 0);
	//if(info->mode == 8) mrcFileWrite(info->Out, "008-temp2", "in lmrcSCMEpeakDetect", 0);
	if(info->Count>1000) fprintf(stderr,"count=%d more than 1000, peak-detect may incomplete !\n",info->Count);

	for(i=0;i<1000&&i<info->Count;i++) info->peak[i].rank=0;
	data=5.0;
	data1=0.0;
	count2=0;
	for(i=0;i<info->Count&&i<1000;i++){
		//xsum=ysum=0;
		//count3=0;
		for(j=0;j<info->Count&&j<1000;j++){
			if(info->peak[j].distance<data && info->peak[j].distance>=data1 && info->peak[j].rank!=1000){
				if(info->peak[j].distance==data1 && temp<=j) ;
				else {
					data = info->peak[j].distance;
					count = j;
				}
			}
		}
		for(k=0;k<info->Count&&k<1000;k++){
			if(info->peak[k].rank==1000 || count==k) ;
			else if(abs(info->peak[count].x-info->peak[k].x)<=info->PA && abs(info->peak[count].y-info->peak[k].y)<=info->PA){
				info->peak[k].rank=1000;
				/*xsum+=info->peak[k].x;
				ysum+=info->peak[k].y;*/
				count2++;
				//count3++;
			}
		}
		/*if(i<3&&count3!=0) fprintf(stderr,"%d %d -> ",info->peak[count].x,info->peak[count].y);
		info->peak[count].x = (info->peak[count].x + xsum)/(count3+1);
		info->peak[count].y = (info->peak[count].y + ysum)/(count3+1);
		if(i<3&&count3!=0) fprintf(stderr,"%d %d \n",info->peak[count].x,info->peak[count].y);
		*/
		info->peak[count].rank = i;
		temp = count;
		data1=data;
		data=5.0;
	}
	for(i=0;i<info->Count&&i<1000;i++){
		if(info->peak[i].rank<50)
			info->highestPeak[info->peak[i].rank] = info->peak[i];
	}
	if(mode==0) fprintf(stdout,"%d\t",count2);
	//if(mode==1) fprintf(stdout,"%d\t",info->Count);
	info->Count -= count2;
}

void __writeNear(lmrcSCMEpeakDetectInfo* info, int comx, int comy, int mode)
{
	int i, nearest;
	int xdis, ydis;
	double comdistance=255, data;
	
	if(comy>=180){
		comy-=180; comx-=180;
		if(comx<0) comx+=360;
	}
	for(i=0; i<mode && i<info->Count; i++){
		xdis = abs(comx-info->highestPeak[i].x);
		ydis = abs(comy-info->highestPeak[i].y);
		data = (double)(pow(xdis,2)+pow(ydis,2));
		data = pow(data,0.5);
		if(data<comdistance){
			comdistance=data;
			nearest=i;
		}
	}
	fprintf(stdout,"%d\t%f\t%d\n",nearest,comdistance,info->Count);
}

void __writeEva3(FILE* out, int* eva3, int mode)
{
	int i, counter=0;
	fprintf(out,"\n\nevaluate 3\n");
	for(i=0;i<50;i++){
		counter += eva3[i];
		fprintf(out,"%d\t%d\t%d\n",i+1,eva3[i],counter);
	}
}

void __writeEva2(FILE* out, int* eva2, int* eva22, int mode)
{
	int i, counter=0.0;
	fprintf(out,"\n\nevaluate 2\n");
	fprintf(out,"rank\tnumber\n");
	for(i=0;i<512;i++){
		counter+=eva2[i];
		fprintf(out,"%d\t%d\t%d\n",(i+1)*10-5,eva2[i],counter);
	}
	counter=0.0;

	fprintf(out,"\n\nevaluate 22\n");
	fprintf(out,"rank\tnumber\n");
	for(i=0;i<100;i++){
		counter+=eva22[i];
		fprintf(out,"%d\t%d\t%d\n",i+1,eva22[i],counter);
	}
}

void __writeEva1(FILE* out, int* eva1, int mode)
{
	int i,j,counter=0;

	fprintf(out,"intensity of the pixel at commonLine when max=1.0\n");
	fprintf(out,"intensity\tnumber\ttotal\n");  
	for(i=0;i<101;i++){
		counter += eva1[i];
		fprintf(out,"%f\t%d\t%d\n",(double)i/100,eva1[i],counter);
	}
}

void
__corrDataChange(mrcImage* in, int mode)
{
	mrcImageInformation linfo;
	int i,j;
	double data, data1;

	linfo.mode = meanOfAll;
	lmrcImageInformation(&linfo,in);

	for(i=0;i<360;i++){
		for(j=0;j<360;j++){
			mrcPixelDataGet(in, i, j, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			data = (data*(-1))+linfo.max;
			mrcPixelDataSet(in,i,j,0,data,mrcPixelRePart);
		}
	}
	for(i=0;i<360;i++){
		for(j=0;j<180;j++){
			mrcPixelDataGet(in, i, j, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in, i+180, j+180, 0, &data1, mrcPixelRePart, mrcPixelHowNearest);
			data = pow(((data*data)+(data1*data1))/2,0.5);
			mrcPixelDataSet(in,i,j,0,data,mrcPixelRePart);
		}}
	for(i=0;i<360;i++){
		for(j=180;j<360;j++){
			mrcPixelDataGet(in, i-180, j-180, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataSet(in,i,j,0,data,mrcPixelRePart);
		}}
	mrcStatDataSet(in,0);
	mrcFileWrite(in, "tempmrc2", "in __corrDataChange", 0);
			
}

