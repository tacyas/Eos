/*
# lmrcSinogramFETcalcWeight : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETcalcWeight 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lmrcSinogramFETcalcWeight.h"
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "nr2.h"
#define SUFF ".tmp-k"
#define DISMAP "dismap-"
#define CURMAP "curmap"
#define COMLIST "comList"
#define EPS 1.0e-2
#define STEP 0.005
#define ITMAX 50

mrcImage _Dismap[NumOfFeature], _Curmap, _Comlist; 
long long int _Cur;

void __dfpmin_k(float p[], int n, float ftol, int *iter, float *fret, float (*func)(float* ), void (*dfunc)(float* , float* )); 

void
lmrcSinogramFETcalcWeight(mrcImage* out, lmrcSinogramFETcalcWeightInfo info, int mode)
{
	int c=0,i,j;
	double data, data1, data2;
	mrcImage in;
	mrcImage* fet;
	char s[256],ss[2];
	float p[NumOfFeature-1];
	float fto1;

	fseek(info.In, 0L, SEEK_SET);
    while(NULL!=stringGetFromFile(s,"",info.In,stdout,1))
		c++;
	fseek(info.In, 0L, SEEK_SET);
	stringGetFromFile(s,"",info.In,stdout,1);
	mrcFileRead(&in, s, "in lmrcSinogramFETcalcWeight",0);
	fet = (mrcImage*)memoryAllocate(sizeof(mrcImage)*c,"in lmrcSinogramFETcalcWeight");
    for(i=0;i<c;i++){
        fet[i].Header = in.Header;
        mrcInit(&fet[i],NULL);
    }
	i = lmrcSinogramFETcalcWeightFETnormalize(info.In, fet, 0);
	lmrcSinogramFETcalcWeightCalcDistance(fet, c, 0);
	free(fet);
	
	lmrcSinogramFETcalcWeightCalcCommonLinePickUp(info.InC, c, 0);
	
	/*mrcFileRead(&_Comlist,"comList.tmp-k", "in lmrcSinogramFETcalcWeight",0);
	for(i=1;i<NumOfFeature;i++){
		strcpy(s,DISMAP); ss[0]=i+48; strncat(s,ss,1); strcat(s,SUFF);
		mrcFileRead(&_Dismap[i],s, "in lmrcSinogramFETcalcWeight",0);
	}*/
	_Curmap.Header = _Comlist.Header;
	//i=c*(c-1)/2;
	//_Curmap.HeaderN.z=i; 
	_Curmap.HeaderN.x=360; _Curmap.HeaderN.y=180;
	mrcInit(&_Curmap,NULL);
	//for(i=1;i<NumOfFeature;i++) p[i]=1.0;
	p[1]=0.9;
	p[2]=0.3;
	p[3]=0.5;
	p[4]=0.8;
	p[5]=0.9;
	p[6]=0.2;
	__dfpmin_k(p,NumOfFeature-3,EPS,&j,&fto1,lmrcSinogramFETcalcWeight_func,lmrcSinogramFETcalcWeight_dfunc);
	
	out->Header = _Comlist.Header;
	out->HeaderN.x=NumOfFeature; out->HeaderN.y=1; out->HeaderN.z=1;
	mrcInit(out,NULL);
	for(i=1;i<4;i++){
		fprintf(stdout,"%f\n",p[i]);
		mrcPixelDataSet(out,i,0,0,(double)p[i],mrcPixelRePart);
	}
	mrcPixelDataSet(out,4,0,0,0.0,mrcPixelRePart);
	fprintf(stdout,"1.000000\n");
	mrcPixelDataSet(out,5,0,0,p[4],mrcPixelRePart);
	mrcPixelDataSet(out,6,0,0,1.0,mrcPixelRePart);
	for(i=7;i<NumOfFeature;i++){
        fprintf(stdout,"%f\n",p[i-2]);
        mrcPixelDataSet(out,i,0,0,(double)p[i-2],mrcPixelRePart);
    }
	mrcPixelDataSet(out,0,0,0,0.0,mrcPixelRePart);
	mrcStatDataSet(out,0);
	//mrcFileWrite(&in, "weight001.mrc","in lmrcSinogramFETcalcWeight",0);
	fprintf(stdout,"iter = %d, L=%f\n",j,fto1);
}

void 
__dfpmin_k(float p[], int n, float ftol, int *iter, float *fret, float (*func)(float* ), void (*dfunc)(float* , float* ))
{
	int j,i,its;
	float fp,fae,fad,fac;
	float *xi,*g,*dg,*hdg;
	float **hessin;
	void linmin(float p[], float xi[], int n, float *fret, float (*func)(float []));
	
	hessin=matrix(1,n,1,n);
	xi=vector(1,n);
	g=vector(1,n);
	dg=vector(1,n);
	hdg=vector(1,n);
	fp=(*func)(p);
	(dfunc)(p,g);
	for(i=1;i<=n;i++){
		fprintf(stdout,"%f ",g[i]);
		for(j=1;j<=n;j++) hessin[i][j]=0.0;
		hessin[i][i]=1.0;
		xi[i] = -g[i];
	}
	fprintf(stdout,"initial calc end\n");
	for(its=1;its<=ITMAX;its++){
		*iter = its;
		linmin(p,xi,n,fret,func);
		for(i=1;i<=n;i++) fprintf(stdout,"%f ",p[i]);
		fprintf(stdout,"1.0\n");
		fprintf(stdout,"linmin end\n");
		if(2.0*fabs(*fret-fp) <= ftol*(fabs(*fret)+fabs(fp)+EPS)){
			free_vector(hdg,1,n);
			free_vector(dg,1,n);
			free_vector(g,1,n);
			free_vector(xi,1,n);
			free_matrix(hessin,1,n,1,n);
			return;
		}
		fp=(*fret);
		for(i=1;i<=n;i++) dg[i]=g[i];
		*fret=(*func)(p);
		(*dfunc)(p,g);
		for(i=1;i<=n;i++) fprintf(stdout,"%f ",g[i]);
		for(i=1;i<=n;i++) dg[i]=g[i]-dg[i];
		for(i=1;i<=n;i++) {
			hdg[i]=0.0;
			for(j=1;j<=n;j++) hdg[i] += hessin[i][j]*dg[j];
		}
		fac=fae=0.0;
		for(i=1;i<=n;i++){
			fac += dg[i]*xi[i];
			fae += dg[i]*hdg[i];
		}
		fac=1.0/fac;
		fad=1.0/fae;
		for(i=1;i<=n;i++) dg[i]=fac*xi[i]-fad*hdg[i];
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				hessin[i][j] += fac*xi[i]*xi[j]-fad*hdg[i]*hdg[j]+fae*dg[i]*dg[j];
		for(i=1;i<=n;i++){
			xi[i]=0.0;
			for(j=1;j<=n;j++) xi[i] -= hessin[i][j]*g[j];
		}
	}
	fprintf(stderr,"Too many iterations in dfpmin\n");
}

void
lmrcSinogramFETcalcWeight_dfunc(float* p, float* g)
{
	int c,i,x,y;
	long long int counter, ucounter;
	char name[20], ss[2];
	float* inp;
	double data,datac,datac2,data1,data2;
	double* cl;
	float dataf;
	float step;

	fprintf(stdout,"in dfunc\t");
	data=0.0;
	inp = (float*)memoryAllocate(sizeof(float)*NumOfFeature,"in lmrcSinogramFETcalcWeight");
	for(i=1;i<NumOfFeature-1;i++) dataf+=p[i];
	for(i=1;i<4;i++) inp[i] = p[i]/(dataf+1.0);
	inp[5]=p[4]/(dataf+1.0);
	inp[6]=1.0/(dataf+1.0);
	for(i=7;i<NumOfFeature;i++) inp[i] = p[i-2]/(dataf+1.0);
	inp[4] = 0.0;
	//strcpy(name,COMLIST); strcat(name,SUFF);
	//mrcFileRead(&_Comlist, name, "in lmrcSinogramFETcalcWeight",0);
	cl = (double*)memoryAllocate(sizeof(double)*_Comlist.HeaderN.z,"in lmrcSinogramFETcalcWeight");
	for(c=0;c<_Comlist.HeaderN.z;c++){
		mrcPixelDataGet(&_Comlist,NumOfFeature,1,c,&data, mrcPixelRePart, mrcPixelHowNearest);
		cl[c] = data;
	}
	//strcpy(name,CURMAP); strcat(name,SUFF);
	//mrcFileRead(&_Curmap, name, "in lmrcSinogramFETcalcWeight",0);
	//mrcPixelDataGet(&glov_mrc2,0,0,0,&data, mrcPixelRePart, mrcPixelHowNearest);
	//cur=(long long int)data;
	for(i=1;i<NumOfFeature;i++){
		//strcpy(name,DISMAP); ss[0]=i+48; strncat(name,ss,1); strcat(name,SUFF);
		//mrcFileRead(&_Dismap[i], name, "in lmrcSinogramFETcalcWeight",0);
		step = STEP;
		counter=0;
		ucounter=0;
		for(c=0;c<_Curmap.HeaderN.z;c++){
			if((int)(cl[c])==(-1234)) ;
			else{
				mrcPixelDataGet(&_Comlist,i,0,c,&data, mrcPixelRePart, mrcPixelHowNearest);
				datac = cl[c]+data*step;
				datac2 = cl[c]-data*step;
				for(x=0;x<360;x++){
				for(y=0;y<180;y++){
					mrcPixelDataGet(&_Curmap,x,y,c,&data, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&_Dismap[i],x,y,c,&data1, mrcPixelRePart, mrcPixelHowNearest);
					data2 = data-data1*step;
					data += data1*step;
					if(data<datac) counter++;
					if(data2<datac2) ucounter++;
				}}
			}
		}
		if(i<4) g[i] = (float)(counter-ucounter)/(step*2*(dataf+1.0))/100000;
		else if(i==5) g[4] = (float)(counter-ucounter)/(step*2*(dataf+1.0))/100000;
		else if(i>=7) g[i-2] = (float)(counter-ucounter)/(step*2*(dataf+1.0))/100000;
		else ;
	}
	fprintf(stdout,"dfunc out\n");
}

float
lmrcSinogramFETcalcWeight_func(float* p)
{
	int c,i,j,x,y;
	long long int counter=0;
	float* inp;
	char name[20];
	char ss[2];
	double *cl;
	double data, data1;
	float dataf;
	

	fprintf(stdout,"in func\t");
	data=0.0;
	inp = (float*)memoryAllocate(sizeof(float)*NumOfFeature,"in lmrcSinogramFETcalcWeight");
	for(i=1;i<NumOfFeature-1;i++) dataf+=p[i];
	for(i=1;i<4;i++) inp[i] = p[i]/(dataf+1.0);
	inp[5]=p[4]/(dataf+1.0);
	inp[6]=1.0/(dataf+1.0);
	for(i=7;i<NumOfFeature;i++) inp[i] = p[i-2]/(dataf+1.0);
	inp[4] = 0.0;
	//strcpy(name,COMLIST); strcat(name,SUFF); 
	//mrcFileRead(&_Comlist, name, "in lmrcSinogramFETcalcWeight",0);
	cl = (double*)memoryAllocate(sizeof(double)*_Comlist.HeaderN.z,"in lmrcSinogramFETcalcWeight");
	for(c=0;c<_Comlist.HeaderN.z;c++){
		mrcPixelDataGet(&_Comlist,NumOfFeature,0,c,&data, mrcPixelRePart, mrcPixelHowNearest);
		if(1!=(int)data){
			data1=0.0;
			for(i=1;i<NumOfFeature;i++){
				mrcPixelDataGet(&_Comlist,i,0,c,&data, mrcPixelRePart, mrcPixelHowNearest);
				data *= (double)inp[i];
				data1 += data;
				mrcPixelDataSet(&_Comlist,i,1,c,data, mrcPixelRePart);
			}
			mrcPixelDataSet(&_Comlist,NumOfFeature,1,c,data1, mrcPixelRePart);
			cl[c]=data1;
		}else{
			cl[c]=(-1234);
			mrcPixelDataSet(&_Comlist,NumOfFeature,1,c,-1234, mrcPixelRePart);
		}
	}
	//_Curmap.Header = _Comlist.Header;
	//_Curmap.HeaderN.y=180; _Comlist.HeaderN.x=360;
	//mrcInit(&_Curmap,NULL);
	//inf = (mrcImage*)memoryAllocate(sizeof(mrcImage)*NumOfFeature,"in lmrcSinogramFETcalcWeight");
	/*for(i=1;i<NumOfFeature;i++){
		strcpy(name,DISMAP); ss[0]=48+i; strncat(name,ss,1); strcat(name,SUFF);
		mrcFileRead(&_Dismap[i],name,"in lmrcSinogramFETcalcWeight",0);
	}*/
	for(c=0;c<_Comlist.HeaderN.z;c++){
		if((int)cl[c]==(-1234)) ;
		else{
			for(x=0;x<360;x++){
			for(y=0;y<180;y++){
				data1 = 0.0;
				for(i=1;i<NumOfFeature;i++){
					mrcPixelDataGet(&_Dismap[i],x,y,c,&data, mrcPixelRePart, mrcPixelHowNearest);
					data1 += data*(double)inp[i];
				}
				if(cl[c]>data1) counter++;
				mrcPixelDataSet(&_Curmap,x,y,c,data, mrcPixelRePart);
			}}
		}
	}
	//free(inf);
	mrcStatDataSet(&_Curmap,0);
	strcpy(name,CURMAP);
	strcat(name,SUFF);
	mrcFileWrite(&_Curmap,name,"in lmrcSinogramFETcalcWeight",0);
	fprintf(stdout,"L=%f\tfunc out\n",(float)counter/100000);
	_Cur = counter;
	return (float)counter/100000;
}

void
lmrcSinogramFETcalcWeightCalcCommonLinePickUp(FILE* comLine, int cfet, int mode)
{
	int i,j,c,map;
	char s[512];
	float data1,data2;
	double data;
	int *comx, *comy;
	char ss[20];
	char name2[20];

	//strcpy(name2,DISMAP);
	//strcat(name2,"1");
	//strcat(name2,SUFF);
	//mrcFileRead(&in, name2,"in lmrcSinogramFETcalcWeight",0);
	_Comlist.Header = _Dismap[1].Header;
	_Comlist.HeaderN.x = NumOfFeature+1;
	_Comlist.HeaderN.y = 2;
	mrcInit(&_Comlist,NULL);

	map = cfet*(cfet-1)/2;
	//load commonLine point into comx,comy
	comx = (int*)memoryAllocate(sizeof(int)*map,"in lmrcSinogramFETcalcWeight");
	comy = (int*)memoryAllocate(sizeof(int)*map,"in lmrcSinogramFETcalcWeight");
	fseek(comLine, 0L, SEEK_SET);
	c=0;
	while(NULL!=stringGetFromFile(s,"",comLine,stdout,1)){
		data1 = atof(stringGetNthWord(s, 11, " ,\t"));
		data2 = atof(stringGetNthWord(s, 12, " ,\t"));
		//fprintf(stdout,"getx:%f\tgety:%f\n",data1,data2);
		if(1==atoi(stringGetNthWord(s, 13, " ,\t"))){
			comx[c] = (int)data1; comx[c] += (int)((data1-(float)comx[c])*2);
			comy[c] = (int)data2; comy[c] += (int)((data2-(float)comy[c])*2);
			if(comy[c]>180){
				comy[c] -= 180;
				if(comx[c]>180) comx[c] -= 180;
				else comx[c] += 180;
			}
		}else{
			comx[c]=comy[c]=200;
		}
		//fprintf(stdout,"c:%d\tx:%d\ty:%d\n",c,comx[c],comy[c]); 
		c++;
	}
			
	for(i=1;i<NumOfFeature;i++){
		//fprintf(stdout,"in %dth feature copying\n",i);
		ss[0] = i+48;
		//strcpy(name2,DISMAP);
		//strncat(name2,ss,1);
		//strcat(name2,SUFF);
		//mrcFileRead(&_Dismap[i], name2,"in lmrcSinogramFETcalcWeight",0);
		for(c=0;c<map;c++){
			if(comx[c]==200){
				mrcPixelDataSet(&_Comlist,NumOfFeature,0,c,1,mrcPixelRePart);
			}else{
				mrcPixelDataGet(&_Dismap[i],comx[c],comy[c],c,&data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(&_Comlist,i,0,c,data,mrcPixelRePart);
			}
		}
		//fprintf(stdout,"%d  %dth feature copied\n",NumOfFeature,i);
	}
	//fprintf(stdout,"roop out\n");
	free(comx);
	free(comy);
	//fprintf(stdout,"freed\n");
	mrcStatDataSet(&_Comlist,0);
	strcpy(name2,COMLIST);
	strcat(name2,SUFF);
	mrcFileWrite(&_Comlist,name2,"in lmrcSinogramFETcalcWeight",0);
	fprintf(stdout,"comLinepickUp end\n");
}

void
lmrcSinogramFETcalcWeightCalcDistance(mrcImage* fet, int cfet, int mode)
{
	int c,i,j,j1,j2,k,l,map,mapcount=0;
	double data1, data2, data;
	char name[20];
	char current[2];
	
	map = (cfet*(cfet-1))/2;
	for(i=1;i<NumOfFeature;i++){
		_Dismap[i].Header=fet[0].Header;
		_Dismap[i].HeaderN.y = fet[0].HeaderN.y/2;
		_Dismap[i].HeaderN.x = fet[0].HeaderN.y;
		_Dismap[i].HeaderN.z = map;
		mrcInit(&_Dismap[i],NULL);
		mapcount=0;
		for(k=0;k<cfet;k++){
		for(l=1;l<cfet;l++){
			if(k<l){
				for(j1=0;j1<fet[0].HeaderN.y;j1++){
				for(j2=0;j2<fet[0].HeaderN.y/2;j2++){	
					mrcPixelDataGet(&fet[k],i,j1,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&fet[l],i,j2,0,&data2, mrcPixelRePart, mrcPixelHowNearest);
					data = pow((data1-data2),2);
					mrcPixelDataSet(&_Dismap[i],j1,j2,mapcount,data,mrcPixelRePart);
				}
				}
				for(j1=0;j1<fet[0].HeaderN.y;j1++){
				for(j2=fet[0].HeaderN.y/2;j2<fet[0].HeaderN.y;j2++){
					mrcPixelDataGet(&fet[k],i,j1,0,&data1, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(&fet[l],i,j2,0,&data2, mrcPixelRePart, mrcPixelHowNearest);
					data = pow((data1-data2),2);
					mrcPixelDataGet(&_Dismap[i],j1+180,j2+180,mapcount,&data1, mrcPixelRePart, mrcPixelHowNearest);
					data = (data+data1)/2;
					mrcPixelDataSet(&_Dismap[i],j1+180,j2+180,mapcount,data,mrcPixelRePart);
				}
				}
				mapcount++;
			}
		}
		}
		mrcStatDataSet(&_Dismap[i],0);
		strcpy(name,DISMAP);
		current[0]=i+48;
		strncat(name,current,1);
		strcat(name,SUFF);
		mrcFileWrite(&_Dismap[i], name, "in lmrcSinogramFETcalcWeight", 0);
		fprintf(stdout,"did dismap-%d\n",i); 
	}
		
}
	
int
lmrcSinogramFETcalcWeightFETnormalize(FILE* in, mrcImage* out, int mode)
{
	int c=0,i,j;
	double data;
	double ave[NumOfFeature], sd[NumOfFeature];
	char s[512];
	mrcImage temp1;
	
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		mrcFileRead(&temp1, s, "in lmrcSinogramFETcalcWeight", 0);
		for(i=1;i<NumOfFeature;i++){
			for(j=0;j<temp1.HeaderN.y;j++){
				mrcPixelDataGet(&temp1,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				ave[i]+=data;
			}
		}
		c++;
	}
	for(i=1;i<NumOfFeature;i++)
		ave[i] = ave[i]/temp1.HeaderN.y/c;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		mrcFileRead(&temp1, s, "in lmrcSinogramFETcalcWeight", 0);
		for(i=1;i<NumOfFeature;i++){
			for(j=0;j<temp1.HeaderN.y;j++){
				mrcPixelDataGet(&temp1,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				sd[i] += pow((data-ave[i]),2);
			}
		}
	}
	for(i=1;i<NumOfFeature;i++){
		sd[i] = sd[i]/temp1.HeaderN.y/c;
		sd[i] = pow(sd[i],0.5);
	}
	c=0;
	fseek(in, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s,"",in,stdout,1)){
		mrcFileRead(&temp1, s, "in lmrcSinogramFETcalcWeight", 0);
		for(i=1;i<NumOfFeature;i++){
			for(j=0;j<temp1.HeaderN.y;j++){
				mrcPixelDataGet(&temp1,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				data -= ave[i];
				if(sd[i]!=0.0) data /= sd[i];
				mrcPixelDataSet(&out[c],i,j,0,data, mrcPixelRePart);
			}
		}
		mrcStatDataSet(&out[c],0);
		/*strcat(s,".nord");
		mrcFileWrite(&out[c], s, "in lmrcSinogramFETcalcWeight", 0);*/
		c++;
	}
	return(c);
}


