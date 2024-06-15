/*
 lmrcSinogramFET : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFET 
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

#undef DEBUG
#include "lmrcImageBinarization.h"
#include "lmrcImagePosterization.h"

void __calcFeature(double* in, double* out, int maxX, int mode);
int __calcLength(double* in, int maxX, int* outl, int* outr, int mode);
void __calcMax(double* in, double* out, int maxX, int mode);
void __calcVal(double* in, int* val, int maxX, int mode);
int __calcACF(double* in, double* acf, int maxX);
double __symcor(double* in, double center, double ave, int maxX, int mode);
void __calcCOmain(double* in, double* out, int maxX, int range, int mode);
double __calcCO(double* in, int end, int mode);
void __smoothingShape(int* in, int maxY, int mode);
int __calcmedian(double* in, int frame);
	
void
lmrcSinogramFET(mrcImage* in, mrcImage* out, lmrcSinogramFETInfo info, int mode)
{
	int i,j,k;
	int maxX, maxY;
	double *oneLine, *oneLinebin, *oneLinepos;
	double oneLineFeature[NumOfFeature];
	double* ave;
	double* sd;
	double data;
	mrcImage pos;
	mrcImage tout;
	
	maxX = in->HeaderN.x;
	maxY = in->HeaderN.y;
	oneLine = (double*)memoryAllocate(sizeof(double)*maxX,"in lmrcSinogramFET");
	
	out->Header = in->Header;
	tout.Header = in->Header;
	out->HeaderN.x = NumOfFeature;
	mrcInit(&tout,NULL);
	mrcInit(out,NULL);
	//lmrcSinogramFETminimam_Zero(in, &pos, 0);
	//in = &pos;
	lmrcSinogramFETcutout(in, &pos, 0);
	//mrcFileWrite(in, "temp", "in mrcSinogramFET", 0);

	mrcFileWrite(&pos, "testout.temp", "in main" ,0);
	for(i=0;i<maxY;i++){
		for(j=0;j<maxX;j++){
			mrcPixelDataGet(&pos,j,i,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			oneLine[j] = data;
		}
		__calcFeature(oneLine, oneLineFeature, maxX, 0);
		/*for(j=0;j<maxX;j++){
			mrcPixelDataSet(&tout,j,i,0,oneLine[j], mrcPixelRePart);
		}*/
		for(j=0;j<NumOfFeature;j++){
			mrcPixelDataSet(out,j,i,0,oneLineFeature[j], mrcPixelRePart);
		}
	}
	if(info.flagsm && info.sm!=1){
		pos = *out;
		sinogramFETsmoothing(&pos, out ,info.sm, 0);
		//mrcStatDataSet(&pos,0);
		//out = &pos;
	}
	mrcStatDataSet(out,0);
	
	//mrcStatDataSet(&tout,0);
	//mrcFileWrite(&pos, "testout.temp", "in main" ,0);
}

void
__calcFeature(double* in, double* out, int maxX, int mode)
{
	int i,j,count=0;
	int length, center;
	int val[4];
	double outm[2];
	double out0;
	double ans=0.0, ave, dev, average;
	double* acf;

	
	for(i=0;i<maxX;i++) if(in[i]==0.0) count++;
	//out[FETlength] = (double)(maxX-count);

	
	acf = (double*)memoryAllocate(sizeof(double)*maxX,"in lmrcSinogramFET");
	
	for(i=0;i<maxX;i++) //normalize histgram
		ans += in[i];
	for(i=0;i<maxX;i++)
		in[i] /= ans;
	average = ans/maxX;
	ans = 0.0;  
	for(i=0;i<maxX;i++)  //calc center of balance
		ans += i*in[i];
	ave = ans;
	out0 = ans;
	ans = 0.0;
	for(i=0;i<maxX;i++) //calc deviation
		ans += pow((i-ave),2)*in[i];
	dev = pow(ans,0.5);
	//out[FETvariance] = dev;
	ans = 0.0;
	for(i=0;i<maxX;i++) //calc skewness
		ans += pow((i-ave),3)*in[i];
	ans /= pow(dev,3);
	out[FETasymmetry] = ans;
	ans = 0.0;
	for(i=0;i<maxX;i++) //calc kurtosis
		ans += pow((i-ave),4)*in[i];
	ans /= pow(dev,4);
	out[FETkur] = ans;
	ans = 0.0;
	
	center = __calcACF(in, acf, maxX);

	
	for(i=0;i<maxX;i++) //calc acf deviation
		ans += pow((i-center),2)*acf[i];
	dev = pow(ans,0.5);
	//out[FETACFvariance] = dev;
	ans = 0.0;
	for(i=0;i<maxX;i++) //calc acf kurtosis
		ans += pow((i-center),4)*acf[i];
	ans /= pow(dev,4);
	out[FETwidth] = ans;
	ans = 0.0;
	for(i=0;i<maxX;i++) //calc acf average
		ans += acf[i];
	ans /= maxX;
	//out[FETACFaverage] = ans;
	
	//__calcMax(in,outm,maxX,0);
	//out[FETintensity] = outm[0];
	//out[5] = (outm[1]-out0)*outm[0];
	
}

int __calcACF(double* in, double* acf, int maxX)
{
	int i, j, k, center;
	double up, down;

	center = maxX/2;	
	if(!(maxX%2)){  center--;  maxX--; }
	
	down=0;
	for(i=0;i<maxX;i++) down += pow(in[i],2);
	
	for(i=0; i<=center; i++){
		up=0.0; 
		for(j=0; j<maxX; j++){
			if(j+i<maxX) k=j;
			else k=j-maxX;
			up += in[i+k]*in[j];
		}
		acf[i+center] = up / down;
	}
	for(i=center-1,j=center+1; i>=0; i--,j++){
		acf[i] = acf[j];
	}
	return(center);
}

double __symcor(double* in, double center, double ave, int maxX, int mode)
{
	int i,j,k,cenin;
	double* in1;
	double ans=0.0, ans1=0.0, ans2=0.0;
	double cen1, cen2, fraction;
	
	in1=(double*)memoryAllocate(sizeof(double)*maxX*2, "in __symcor");
	for(i=0;i<maxX/2;i++) in1[i] = in[i+maxX/2];
	for(i=0;i<maxX;i++)   in1[i+maxX/2] = in[i];
	for(i=0;i<maxX/2;i++) in1[i+maxX/2+maxX] = in[i];

	center = center+(double)(maxX/2)-0.5;
	cenin = (int)center;
	fraction = center-(double)cenin;
	for(i=0;i<(maxX/2);i++){
		cen1 = (1.0-fraction)*in1[cenin+i] + fraction*in1[cenin+i+1];
		cen2 = fraction*in1[cenin-i] + (1.0-fraction)*in1[cenin-i-1];
		ans += (cen1-ave)*(cen2-ave);
		ans1 += pow((cen1-ave),2);
		ans2 += pow((cen2-ave),2);
	}
	ans = ans/pow(ans1*ans2,0.5);
	return ans;
}

void __calcMax(double* in, double* out, int maxX, int mode)
{
	double ans=0.0, data;
	int i,j;
	for(i=0; i<maxX-2; i++){
		data = in[i]+in[i+1]+in[i+2];
		if(ans<data){
			ans=data;
			j=i;
		}
	}
	data=0;
	for(i=0;i<3;i++){
		data += (double)(j+i)*in[j+i]/ans;
	}
	out[0] = ans/3.0;
	out[1] = data;
}

int __calcLength(double* in, int maxX, int *outl, int *outr, int mode)
{
	int n,i,j;
	int length, maxlength, start, maxstart;
	double* tp1;
	double* tp2;
	double ave=0.0;
	
	tp1 = (double*)memoryAllocate(sizeof(double)*maxX, "in __calcLength");
	tp2 = (double*)memoryAllocate(sizeof(double)*maxX, "in __calcLength");

	__calcCOmain(in, tp1, maxX, 3, 0); // mode 0:Close 1:Open
	__calcCOmain(tp1, tp2, maxX, 3, 0);
	__calcCOmain(tp2, tp1, maxX, 3, 1);
	__calcCOmain(tp1, tp2, maxX, 3, 1);
	__calcCOmain(tp2, tp1, maxX, 3, 1);
	
	for(i=0; i<maxX; i++)	ave += tp1[i];  
	ave /= maxX; 
	//ave *= 1.5; // bone threshold definition
	maxlength = 0;
	length=0;
	for(i=0; i<maxX; i++){
		if(tp1[i]<ave){
			if(length>maxlength){
				maxlength = length;
				maxstart = start;
			}
			length = 0;
		}else{
			if(length==0) start=i;
			length++;
		}
	}
	if(length>maxlength){
		maxlength = length;
		maxstart = start;
	}

	ave /= 5.0;                   // threshold definition 2
	*outl = maxstart;  *outr = maxstart+maxlength-1;
	for(i=*outl; i>=0 && tp1[i]>ave; i--);  *outl = ++i;
	for(i=*outr; i<maxX && tp1[i]>ave; i++); *outr = --i;
	maxlength = *outr - *outl + 1;
	
	return(maxlength);
}

void __calcCOmain(double* in, double* out, int maxX, int range, int mode)
{
	int i,j,k;
	int hr;
	double* pt;

	hr = range/2;
	for(i=hr; i<maxX-hr; i++){
		pt = in+i-hr;
		out[i] = __calcCO(pt,range,mode);
	}
	pt = in;
	for(i=0;i<hr;i++) out[i] = __calcCO(pt,range,mode);
	pt = in+maxX-range;
	for(i=maxX-hr;i<maxX;i++) out[i] = __calcCO(pt,range,mode);
}

double __calcCO(double* in, int end, int mode)
{
	double ans,temp;
	int i,j;
	ans = in[0];
	for(i=1;i<end;i++){
		if(mode){
			if(in[i]>ans) ans=in[i];
		}else{
			if(in[i]<ans) ans=in[i];
		}
	}
	return(ans);
}

void sinogramFETsmoothing(mrcImage* in, mrcImage* out, int sm, int mode)
{
	int i,j,k,smd;
	double data, datam, ave;

	//fprintf(stdout,"chkpoint in sm\n");

	out->Header = in->Header;
	mrcInit(out,NULL);

	smd = (int)(sm/2);
		
	for(i=0; i<in->HeaderN.x; i++){
		ave=0.0;
		for(k=(smd*-1)-1 ; k<smd ; k++){
			mrcPixelDataGet(in,i,k,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			ave += data;
		}
		ave /= (double)sm;
		for(j=0; j<in->HeaderN.y; j++){
			mrcPixelDataGet(in,i,j+smd,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in,i,j-smd,0,&datam, mrcPixelRePart, mrcPixelHowNearest);
			ave = ave-(datam/(double)sm)+(data/(double)sm);
			mrcPixelDataSet(out,i,j,0,ave, mrcPixelRePart);
		}
	}
}

void 
lmrcSinogramFETc(mrcImage* out, mrcImage* OutC, int mode)
{
	int i,j,maxY;
	double ave[NumOfFeature];
	double sd[NumOfFeature];
	double data;
	
	for(i=0;i<NumOfFeature;i++){
		ave[i]=0.0;
		sd[i] = 0.0;
	}
	OutC->Header = out->Header;
	maxY = out->HeaderN.y;
	mrcInit(OutC,NULL);
	for(i=0;i<maxY;i++){
		for(j=0;j<NumOfFeature;j++){
			mrcPixelDataGet(out,j,i,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			ave[j] += data/(double)maxY;
		}
	}
	for(i=0;i<maxY;i++){
		for(j=0;j<NumOfFeature;j++){
			mrcPixelDataGet(out,j,i,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			sd[j] += pow((data-ave[j]),2)/(double)maxY;
		}
	}
	for(i=0;i<NumOfFeature;i++)  sd[i] = pow(sd[i],0.5);
	
	for(i=0;i<maxY;i++){
		for(j=0;j<NumOfFeature;j++){
			mrcPixelDataGet(out,j,i,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			//fprintf(stdout,"%d %d %f\t%f\t%f\n",i,j,data,ave[j],sd[j]);
			data -= ave[j];
			if(sd[j] >= 0.0001) data /= sd[j];
			mrcPixelDataSet(OutC,j,i,0,data, mrcPixelRePart);
		}
	}
	mrcStatDataSet(OutC,0);
}

void
lmrcSinogramFETminimam_Zero(mrcImage* in, mrcImage* out, int mode)
{
	int i,j;
	double data;
	mrcImageInformation linfo;
	
	linfo.mode = meanOfAll;
	lmrcImageInformation(&linfo, in);
	out->Header = in->Header;
	mrcInit(out,NULL);
	for(i=0;i<in->HeaderN.x;i++){
		for(j=0;j<in->HeaderN.y;j++){
			mrcPixelDataGet(in,i,j,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			data -= linfo.min;
			mrcPixelDataSet(out,i,j,0,data, mrcPixelRePart);
		}}
	mrcStatDataSet(out,0);
}

void
lmrcSinogramFETcutout(mrcImage* in, mrcImage* out, int mode)
{
	int i, j, k, length;
	double data, data1, data2;
	double* inLine;
	int* lefts;
	int* rights;
	int pixels, pixels2, left, right, maxX, maxY;

	out->Header = in->Header;
	mrcInit(out,NULL);

	maxX = in->HeaderN.x;
	maxY = in->HeaderN.y;
	inLine = (double*)memoryAllocate(sizeof(double)*maxX, "in __cutout");
	lefts = (int*)memoryAllocate(sizeof(int)*maxY, "in __cutout");
	rights = (int*)memoryAllocate(sizeof(int)*maxY, "in __cutout");
	
	for(i=0; i<maxY; i++){
		for(j=0; j<maxX; j++){
			mrcPixelDataGet(in,j,i,0,&data, mrcPixelRePart, mrcPixelHowNearest);
			inLine[j] = data;
		}
		length = __calcLength(inLine, maxX, &left, &right, 0);
		lefts[i] = left;  rights[i] = right;
		//fprintf(stdout,"%d  %d\n",left,right);
	}
	__smoothingShape(lefts,maxY,0); 
	__smoothingShape(rights,maxY,0);

	for(i=0; i<maxY; i++){
		for(j=0; j<maxX; j++){
			if(j>=lefts[i] && j<=rights[i]){
				mrcPixelDataGet(in,j,i,0,&data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(out,j,i,0,data, mrcPixelRePart);
			}else{
				mrcPixelDataSet(out,j,i,0,0.0, mrcPixelRePart);
			}
		}
	}

	mrcStatDataSet(out,0);
}

void
__smoothingShape(int* in, int maxY, int mode)
{
	int i,j,k,median;
	double dframe[2][7];
	int* diff;
	int* tempin;
	double temp, ave, difave, dmedian;

	diff = (int*)memoryAllocate(sizeof(int)*maxY, "in __smoothingShape");
	tempin = (int*)memoryAllocate(sizeof(int)*maxY, "in __smoothingShape");
	for(i=0;i<maxY;i++) tempin[i] = in[i];
	for(i=0;i<maxY-1;i++){
		diff[i] = abs(in[i]-in[i+1]);
	}diff[maxY-1] = abs(in[maxY-1]-in[0]);

	ave=0.0; difave=0.0;
	for(i=-3; i<3; i++){
		if(i<0) j=i+maxY;
		else j=i;
		dframe[0][(i+7)%7] = (double)diff[j];
		dframe[1][(i+7)%7] = (double)tempin[j];
		difave += dframe[0][(i+3)%7]/7.0;
		ave += dframe[1][(i+3)%7]/7.0;
	}
	for(i=0;i<maxY;i++){
		if(i+3 >= maxY) j=i+3-maxY;
		else j=i+3;
		dframe[0][(i+3)%7] = (double)diff[j];
		dframe[1][(i+3)%7] = (double)tempin[j];
		difave += dframe[0][(i+3)%7]/7.0;
		ave += dframe[1][(i+3)%7]/7.0;
		if(difave>3.0){
			ave = 0.0;
			for(j=0;j<7;j++) ave += dframe[1][j]; ave /= 7.0;
			in[i] = (int)ave;
		}
		else{
			in[i] = __calcmedian(dframe[1],7);
		}
		if(i-3<0) j=i+4;
		else j=i;
		difave -= dframe[0][(j-3)%7]/7.0;
		ave -= dframe[1][(j-3)%7]/7.0;
	}
}



int
__calcmedian(double* in, int frame)
{
	int i, j, w, med, center;
	int max;
	int* intemp;
	intemp = (int*)memoryAllocate(sizeof(int)*frame, "in __smoothingShape");
	for(i=0;i<frame;i++) intemp[i] = (int)in[i];

	center = frame/2;
	max=0;
	for(i=0;i<=center;i++){
		for(j=i+1;j<frame;j++){
			if(intemp[i]<intemp[j]){
				w=intemp[i]; intemp[i]=intemp[j]; intemp[j]=w;
			}
		}}
	med=intemp[center];
	return med;
}





















