/*
# lmrcSinogramFETreferredCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETreferredCorrelation 
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
#include "lmrcSinogramFETreferredCorrelation.h"							  
#define RANKS 3
#define PI2 3.1415192654

void __inmrcFileRead(mrcImage* mrc, FILE* in, int mode);
double __compare2FETs(mrcImage* in, mrcImage* inR, int inz, int inRz, double* w, int* e3i, int mode);

void 
lmrcSinogramFETreferredCorrelation(lmrcSinogramFETreferredCorrelationInfo in, int mode)
{
	int i,j,k;
	int x, y, z, zr;
	mrcImage inD, inR;
	double data, datam;
	double datams[RANKS];
	float e1,e2,e3;
	int rank, e3i;
	int* pte3i;
	int ranks[RANKS];
	double w[NumOfFeature];
	char s[256], ss[256], sss[10];
	lmrcSinogramFETreferredCorrelationSelectInfo sinfo;
	
	if(in.flagw){
		for(i=0;i<NumOfFeature;i++){
			mrcPixelDataGet(in.weight,i,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			w[i] = data;
		}
	}else{ for(i=0;i<NumOfFeature;i++) w[i] = 1; }
	
	__inmrcFileRead(&inR, in.InR, in.nm);
	__inmrcFileRead(&inD, in.In, in.nm);
	x = inR.HeaderN.x; y = inR.HeaderN.y; z = inD.HeaderN.z; zr = inR.HeaderN.z;
	in.zr = zr;
	if(in.om!=0) lmrcSinogramFETreferredCorrelationSelectDataSet(&in,&sinfo,0);
	
	pte3i = &e3i;
	for(i=0; i<z; i++){
		if(i!=0) fprintf(in.Out,"\n");
		if(in.mode){ for(k=0; k<RANKS; k++) datams[k] = 1000+i; }
		datam = 1000;
		for(j=0; j<zr; j++){
			data = __compare2FETs(&inD,&inR,i,j,w,pte3i,0);
		    //fprintf(stdout,"\t%d",*pte3i); fflush(stdout);
			if(in.om!=0){
				sinfo.dise3[0][j] = data;   sinfo.dise3[1][j] = (double)e3i;
			}else{
				if(datam>data){ datam = data; rank = j; e3 = (float)e3i;}
			}
		}
		if(in.om==0){
			fseek(in.In, 0L, SEEK_SET); k=0;
			while(k<i){ stringGetFromFile(s, "", in.In, stdout, 1); k++; }
			stringGetFromFile(s, "", in.In, stdout, 1);
			fseek(in.InE, 0L, SEEK_SET); k=0;
			while(k<rank){ stringGetFromFile(ss, "", in.InE, stdout, 1); k++; }
			stringGetFromFile(ss, "", in.InE, stdout, 1);
			stringCopy(sss, stringGetNthWord(ss, 2, " ,\t"), 4);
			e1 = (float)stringGetNthRealData(ss, 3, " ,\t");
			e2 = (float)stringGetNthRealData(ss, 4, " ,\t");
			//e3 = (float)e3i;
			//e3 = (float)stringGetNthRealData(ss, 5, " ,\t");
			//fprintf(stdout,"\t%f\n",e3);
			fprintf(in.Out,"%s %s %f %f %f dis %f %d",s,sss,e1,e2,e3,datam,rank);
			fflush(stdout);
		}else{
			lmrcSinogramFETreferredCorrelationSelect(&sinfo,i,0);
		}
	}
	
}

void lmrcSinogramFETreferredCorrelationSelect(lmrcSinogramFETreferredCorrelationSelectInfo* in, int cur, int mode)
{
	int i,j,k;
	int start,t1,t2,t3,cpt,bpt;
	int ptmin;
	char s1[256],s2[256],sss[5];
	double min;
	
	start = 0;                            //    sort
	for(i=0; i<in->fnum; i++){ 
		in->ptdise3[i] = -1;
		in->refVote[i] = 0;
	}
	for(i=1; i<in->fnum; i++){
		cpt = start;
		t1 = 0;
		for(j=0; (j<in->tnum && cpt!=-1) && t1==0 ; j++){
			if(in->dise3[0][i] < in->dise3[0][cpt]){
				t1 = 1;
				if(j!=0){
					in->ptdise3[bpt] = i;
				}else{
					start = i;
				}
				in->ptdise3[i] = cpt;
			}
			bpt = cpt;
			cpt = in->ptdise3[cpt];
		}
		//if(j<in->tnum && t1==0){
		if(cpt==-1){
			in->ptdise3[bpt] = i;
		}
	}
/*
	cpt=start;
	for(i=0;i<in->tnum;i++){ fprintf(stdout,"%d\n",cpt);
		cpt=in->ptdise3[cpt];
	}
*/	
	cpt = start;                       //    angleListFile read
	for(i=0; i<in->tnum; i++){
		if(in->om==2){
			fseek(in->InE, 0L, SEEK_SET); k=0;
			while(k<cpt){ stringGetFromFile(s1, "", in->InE, stdout, 1); k++; }
			stringGetFromFile(s1, "", in->InE, stdout, 1);
			stringCopy(in->anglemode[i], stringGetNthWord(s1, 2, " ,\t"), 4);
			in->angled[0][i] = (double)stringGetNthRealData(s1, 3, " ,\t");
			in->angled[1][i] = (double)stringGetNthRealData(s1, 4, " ,\t");
			in->angled[2][i] = in->dise3[1][cpt];
			in->angled[3][i] = in->dise3[0][cpt];
		}else if(in->om==1){
			for(j=1; j<in->refpt[cpt][0]; j++){
				in->refVote[in->refpt[cpt][j]]++;
			}
			if(i<4) in->refVote[cpt] += 1+(12-i*i)/3;
			else in->refVote[cpt]++;
		}
		cpt = in->ptdise3[cpt];
	}
	if(in->om==1){
		min = in->refVote[0]; ptmin = 0;
		for(i=0; i<in->fnum; i++){
			if(in->refVote[i]>min){
				min = in->refVote[i];
				ptmin = i;
			}
		}	
		fseek(in->InE, 0L, SEEK_SET); k=0;
		while(k<ptmin){ stringGetFromFile(s1, "", in->InE, stdout, 1); k++; }
		stringGetFromFile(s1, "", in->InE, stdout, 1);
		stringCopy(in->anglemode[0], stringGetNthWord(s1, 2, " ,\t"), 4);
		in->angled[0][0] = (double)stringGetNthRealData(s1, 3, " ,\t");
		in->angled[1][0] = (double)stringGetNthRealData(s1, 4, " ,\t");
		in->angled[2][0] = in->dise3[1][ptmin];
		in->angled[3][0] = in->dise3[0][ptmin];
	}

	//   output
	fseek(in->In, 0L, SEEK_SET); k=0;
	while(k<cur){ stringGetFromFile(s1, "", in->In, stdout, 1); k++; }
	stringGetFromFile(s1, "", in->In, stdout, 1);

	if(in->om==2){
		fprintf(in->Out,"%s ",s1);
		cpt = start;
		for(i=0;i<in->tnum; i++){
			fprintf(in->Out,"%s %f %f %f %f %d ",in->anglemode[i],in->angled[0][i],in->angled[1][i],in->angled[2][i],in->angled[3][i],cpt);
			cpt = in->ptdise3[cpt];
		}
	}else if(in->om==1){
		fprintf(in->Out,"%s ",s1);
		fprintf(in->Out,"%s %f %f %f %f %d ",in->anglemode[0],in->angled[0][0],in->angled[1][0],in->angled[2][0],in->angled[3][0],ptmin);
	}

	
	//for(i=0;i<in->tnum;i++) fprintf(stdout,"%f\n",in->angled[3][i]);
	
	
}

double 
__compare2FETs(mrcImage* in, mrcImage* inR, int inz, int inRz, double* w, int* e3i, int mode)
{
	int i,j,k;
	int e3, d;
	double dis=1000, data, datar, datam, fets, datas;

	d = in->HeaderN.y;
	d = 360/d;
	for(i=0; i<in->HeaderN.y; i++){
		datas = 0;
		for(j=0; j<in->HeaderN.y; j++){
			fets = 0.0;
			for(k=0; k<in->HeaderN.x; k++){
				mrcPixelDataGet(in,k,i+j,inz,&data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(inR,k,j,inRz,&datar, mrcPixelRePart, mrcPixelHowNearest);
				data = pow((data-datar),2);
				fets += w[k]*data;
			}
			fets = pow(fets,0.5);
			datas += fets;
		}
		if(datas<dis){ dis=datas; e3=i; }
	}

	*e3i = (e3*d)-360;
	//if(inz==inRz) fprintf(stdout,"%d %d %f",e3,*e3i,dis);
	
	return(dis);
		
}

void lmrcSinogramFETreferredCorrelationSelectDataSet(lmrcSinogramFETreferredCorrelationInfo* in, lmrcSinogramFETreferredCorrelationSelectInfo* out, int mode)
{
	int i,j,k;
	double e1,e2,x,y,z,x1,x2,y1,y2,z1,z2,range,rangeL;
	char s[256],ss[256];
	double pi;

	out->In = in->In;
	out->InE = in->InE;
	out->Out = in->Out; 
	out->fnum = in->zr;
	out->tnum = in->tnum;
	out->om = in->om;
	//out->RR = in->RR;
	
	for(i=0; i<2; i++) out->dise3[i] = (double*)memoryAllocate(sizeof(double)*in->zr,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	out->ptdise3 = (int*)memoryAllocate(sizeof(int)*in->zr,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	for(i=0; i<4; i++) out->angled[i] = (double*)memoryAllocate(sizeof(double)*in->tnum,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	out->topn = (int*)memoryAllocate(sizeof(int)*in->tnum,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	out->anglemode = (char**)memoryAllocate(sizeof(char*)*in->tnum,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	for(i=0; i<in->tnum; i++){
		out->anglemode[i] = (char*)memoryAllocate(sizeof(char)*5,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	}
	out->refCart = (double**)memoryAllocate(sizeof(double*)*in->zr,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	out->refpt = (int**)memoryAllocate(sizeof(int*)*in->zr,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	out->refVote = (int*)memoryAllocate(sizeof(int)*in->zr,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
	for(i=0; i<in->zr; i++){
		out->ptdise3[i] = -1;
		out->refCart[i] = (double*)memoryAllocate(sizeof(double)*3,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
		out->refpt[i] = (int*)memoryAllocate(sizeof(int)*13,"in lmrcSinogramFETreferredCorrelationSelectDataSet");
		out->refpt[i][0] = 1;
		out->refVote[i] = 0;
	}

	pi = PI2;
	pi = pi/180;
	i=0;
	fseek(in->InE, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in->InE,stdout,1)){
		e1 = (double)stringGetNthRealData(s, 3, " ,\t");
		e2 = (double)stringGetNthRealData(s, 4, " ,\t");
		
		if(e2<=90.0) e2 = 90.0-e2;
		else if(e2>=270.0)  e2=450.0-e2;
		e1 *= pi;  e2 *= pi;
		x1 = sin(e2);
		y1 = x1*sin(e1);
		x1 *= cos(e1);
		z1 = cos(e2);
		out->refCart[i][0] = x1;
		out->refCart[i][1] = y1;
		out->refCart[i][2] = z1;
		i++;
	}
	x1 = 1.0; y1 = 0.0;
	x2 = cos((double)in->RR*pi); y2 = sin((double)in->RR*pi);
	x = x1-x2; y = y1-y2; x=pow(x,2); y=pow(y,2);
	rangeL = pow((x+y),0.5); rangeL = rangeL*1.3;
	//fprintf(stdout,"%f\n",rangeL);
	for(i=0; i<in->zr-1; i++){
		x1 = out->refCart[i][0];	y1 = out->refCart[i][1];	z1 = out->refCart[i][2];
		for(j=i+1;j<in->zr;j++){
			x2 = out->refCart[j][0];    y2 = out->refCart[j][1];    z2 = out->refCart[j][2];
			x = x1-x2;	y = y1-y2;	z = z1-z2;
			x = pow(x,2);	y=pow(y,2);	z=pow(z,2);
			range = pow((x+y+z),0.5);
			//fprintf(stdout,"%f\n",range);
			//scanf("%d",&k);
			if(range < rangeL){
				if(out->refpt[i][0]<13 && out->refpt[j][0]<13 ){
					out->refpt[i][out->refpt[i][0]] = j; out->refpt[i][0]++;
					out->refpt[j][out->refpt[j][0]] = i; out->refpt[j][0]++;
				}
			}
		}
	}
/*
	for(i=0; i<in->zr; i++){
		fprintf(stdout,"%d\t",i);
		for(j=0; j<13; j++){
			fprintf(stdout,"%d ",out->refpt[i][j]);
		}fprintf(stdout,"\n");
	}
*/	
}


void 
__inmrcFileRead(mrcImage* mrc, FILE* in, int mode)
{
	int i,j,k,l;
	int x,y,z;
	double ave[NumOfFeature], sd[NumOfFeature];
	double data;
	char s[256];
	mrcImage temp;

	fseek(in, 0L, SEEK_SET);
	i=0;
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)) i++;
	z=i;

	fseek(in, 0L, SEEK_SET);
    stringGetFromFile(s,"",in,stdout,1);
    mrcFileRead(&temp, s, "in lFETsmallMapSetCreate",0);
	mrc->Header = temp.Header;
	mrc->HeaderN.z = i;
	x = mrc->HeaderN.x = temp.HeaderN.x;
	y = mrc->HeaderN.y = temp.HeaderN.y;
	mrcInit(mrc,NULL);

	for(i=0; i<x || i<NumOfFeature; i++){ ave[i] = 0; sd[i] = 0; }
	k=0;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		mrcFileRead(&temp, s, "in lFETsmallMapSetCreate",0);
		for(i=0; i<x; i++){
			for(j=0; j<y; j++){
				mrcPixelDataGet(&temp,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(mrc,i,j,k,data, mrcPixelRePart);
				ave[i] += data; 
			}
		}
		k++;
	}
	
	if(mode==0){
		for(i=0; i<x || i<NumOfFeature; i++) ave[i] /= y*z;
		for(i=0;i<x;i++){ for(j=0;j<y;j++){ for(k=0;k<z;k++){
			mrcPixelDataGet(mrc,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
			sd[i] += pow((data-ave[i]),2);
		}}}
		for(i=0; i<x || i<NumOfFeature; i++) sd[i] = pow((sd[i]/(y*z)),0.5);
		for(i=0;i<x;i++){ for(j=0;j<y;j++){ for(k=0;k<z;k++){
			mrcPixelDataGet(mrc,i,j,k,&data, mrcPixelRePart, mrcPixelHowNearest);
			data -= ave[i];
			if(sd[i]!=0.0) data /= sd[i];
			mrcPixelDataSet(mrc,i,j,k,data, mrcPixelRePart);
		}}}
		mrcStatDataSet(mrc,0);
	}else ;
}

