/*
# lmrcImageFeatureExtractionCoOccurrence : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFeatureExtractionCoOccurrence 
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
#include <math.h>
#include "genUtil.h"
#include "Memory.h"
#include "../inc/mrcImage.h"
#include "nr2.h"
#define EPS 0.000001
#define EPSF 0.0001
#define GLEVEL 16 
#define GLEVEL2 256

// Handbook of Image Analysis [Revised Edition] page1263-1264
double __calcAve(double* ,int );
double __calcVariance(double* ,double ,int );
double _calcASM(double* ,int );
double _calcConstant(double* ,int );
double _calcCorrelation(double* ,double ,double ,int );
double _calcSSV(double* ,double ,int );
double _calcIDM(double* ,int );
double _calcSumAve(double* ,int );
double _calcSumVar(double* ,double ,int );
double _calcSumEntropy(double* ,int );
double _calcEntropy(double* ,int );
double _calcDiffVar(double* ,int );
double _calcDiffEntropy(double* ,int );
double __calcHXY(double* ,int );
double __calcHX(double* ,int );
double __calcHY(double* ,int );
double __calcHXY1(double* ,int );
double __calcHXY2(double* ,int );
double _calcIMC(double hxy, double hxy1, double hx, double hy, int );
double _calcIMC2(double hxy2, double hxy, int );
double _calcMCC(double* ,int );
double _calcDiffSta(double* ,double* ,int );

void
lmrcImageFeatureExtractionCoOccurrence(mrcImage* in, double* out, lmrcImageFeatureExtractionInfo linfo, int mode)
{
	mrcImage nord;
	int x,y,count,wholepixel=0;
	int vertical, horizontal;
	double data, data2, ave, sigma2, hxy, hxy1, hxy2, hx, hy;
	double cOmatrix[GLEVEL2];

	for(count=0;count<GLEVEL2;count++) cOmatrix[count]=0;
	
	lmrcImagePosterization(in, &nord, GLEVEL, 0);
	
	vertical = (int)(linfo.co_r*sin(linfo.co_theta)+0.5);
	horizontal = (int)(linfo.co_r*cos(linfo.co_theta)+0.5);
	for(y=0 ;y < in->HeaderN.y ;y++) {
    for(x=0 ;x < in->HeaderN.x ;x++) {
    	mrcPixelDataGet(&nord, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(&nord, x+horizontal, y+vertical, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
		cOmatrix[(int)(data*GLEVEL+data2)]++;
		mrcPixelDataGet(&nord, x-horizontal, y-vertical, 0, &data2, mrcPixelRePart, mrcPixelHowNearest);
        cOmatrix[(int)(data*GLEVEL+data2)]++;
	}
	}

	wholepixel= in->HeaderN.x * in->HeaderN.y;
	wholepixel *= 2;
	for(count=0;count<GLEVEL2;count++)  cOmatrix[count] /= (double)wholepixel; //normalize
	
	ave = __calcAve(cOmatrix, 0);
	sigma2 = __calcVariance(cOmatrix, ave, 0);
	hxy = __calcHXY(cOmatrix, 0);
	hxy1 = __calcHXY1(cOmatrix, 0);
	hxy2 = __calcHXY2(cOmatrix, 0);
	hx = __calcHX(cOmatrix, 0);
	hy = __calcHY(cOmatrix, 0);
	out[0] = _calcASM(cOmatrix, 0);
	out[1] = _calcConstant(cOmatrix, 0);
	out[2] = _calcCorrelation(cOmatrix, ave, sigma2, 0);
	out[3] = _calcSSV(cOmatrix, ave, 0);
	out[4] = _calcIDM(cOmatrix, 0);
	out[5] = _calcSumAve(cOmatrix, 0);
	out[6] = _calcSumVar(cOmatrix, out[5], 0);
	out[7] = _calcSumEntropy(cOmatrix, 0);
	out[8] = _calcEntropy(cOmatrix, 0);
	out[9] = _calcDiffVar(cOmatrix, 0);
	out[10]= _calcDiffEntropy(cOmatrix, 0);
	out[11]= _calcIMC(hxy, hxy1, hx, hy, 0);
	out[12]= _calcIMC2(hxy2, hxy, 0);
	out[13]= _calcMCC(cOmatrix, 0);
	_calcDiffSta(cOmatrix,out,0);
	
	for(count=0; count<18; count++)fprintf(stdout,"%f\n",out[count]);
}

double __calcAve(double* mat, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			ans += mat[GLEVEL*i+j]*i;
		}}
	return ans;
}

double __calcVariance(double* mat, double ave, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			ans += mat[GLEVEL*i+j]*pow((i-ave),2);
		}}
	return ans;
}

double _calcDiffSta(double* mat, double* out, int mode)
{
	int i,j,k;
	double ans;
	double p[GLEVEL];

	for(i=0;i<GLEVEL;i++) p[i]=0;
	for(k=0;k<GLEVEL;k++){
		for(i=0;i<GLEVEL;i++){
			for(j=0;j<GLEVEL;j++){
				if(abs(i-j)==k) p[k] += mat[GLEVEL*i+j];
			}}
	}
	out[14]=out[15]=out[16]=out[17]=0;
	for(k=0;k<GLEVEL;k++) out[14] += k*k*p[k];
	for(k=0;k<GLEVEL;k++) out[15] += p[k]*p[k];
	for(k=0;k<GLEVEL;k++){ if(fabs(p[k])>EPS) out[16] += p[k]*log10(p[k]);}
	out[16] *= -1.0;
	for(k=0;k<GLEVEL;k++) out[17] += k*p[k];
}

double _calcASM(double* mat, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			ans += pow(mat[GLEVEL*i+j],2);
		}}
	return ans;
}

double _calcConstant(double* mat, int mode)
{
	int i, j, k;
	double ans=0.0, ans2=0.0;
	for(k=0;k<GLEVEL;k++){
		for(i=0;i<GLEVEL;i++){
			for(j=0;j<GLEVEL;j++){
				if(abs(i-j)==k) ans2 += mat[GLEVEL*i+j];
			}}
		ans += pow(k,2)*ans2;
		ans2=0.0;
	}
	return ans;
}

double _calcCorrelation(double* mat, double ave, double sigma2, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=1;i<GLEVEL;i++){
		for(j=1;j<GLEVEL;j++){
			ans += mat[GLEVEL*i+j]*i*j;
		}}
	ans -= pow(ave,2);
	ans /= sigma2;
	return ans;
}

double _calcSSV(double* mat, double ave, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			ans += mat[GLEVEL*i+j]*pow((i-ave),2);
		}}
	return ans;
}

double _calcIDM(double* mat, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			ans += mat[GLEVEL*i+j]* 1/(1+pow((i-j),2));
		}}
	return ans;
}

double _calcSumAve(double* mat, int mode)
{
	int i, j, k;
	double ans=0.0, ans2=0.0;
	for(k=0;k<31;k++){
		for(i=0;i<GLEVEL;i++){
			for(j=0;j<GLEVEL;j++){
				if(i+j==k) ans2 += mat[GLEVEL*i+j];
			}}
		ans += k*ans2;
		ans2=0.0;
	}
	return ans;
}

double _calcSumVar(double* mat, double sumave, int mode)
{
	int i, j, k;
	double ans=0.0, ans2=0.0;
	for(k=0;k<31;k++){
		for(i=0;i<GLEVEL;i++){
			for(j=0;j<GLEVEL;j++){
				if(i+j==k) ans2 += mat[GLEVEL*i+j];
			}}
		ans += pow((k-sumave),2)*ans2;
		ans2=0.0;
	}
	return ans;
}

double _calcSumEntropy(double* mat, int mode)
{
	int i, j, k;
	double ans=0.0, ans2=0.0;
	for(k=0;k<31;k++){
		for(i=0;i<GLEVEL;i++){
			for(j=0;j<GLEVEL;j++){
				if(i+j==k) ans2 += mat[GLEVEL*i+j];
			}}
		if(fabs(ans2)>EPS) ans += ans2*log10(ans2);
		ans2=0.0;
	}
	ans *= -1.0;
	return ans;
}

double _calcEntropy(double* mat, int mode)
{
	int i, j;
	double ans=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			if(mat[GLEVEL*i+j]>EPS) ans += mat[GLEVEL*i+j]*log10(mat[GLEVEL*i+j]);
		}}
	ans *= -1.0;
	return ans;
}

double _calcDiffVar(double* mat, int mode)
{
	int i, j, k;
	double ans=0.0, ans2=0.0, ans3=0.0;
	for(k=0;k<GLEVEL;k++){
		for(i=0;i<GLEVEL;i++){
			for(j=0;j<GLEVEL;j++){
				if(abs(i-j)==k) ans2 += mat[GLEVEL*i+j];
			}}
		ans3 += k*ans2;
		ans2 = 0.0;
	}
	for(k=0;k<GLEVEL;k++){
		for(i=0;i<GLEVEL;i++){
			 for(j=0;j<GLEVEL;j++){
				if(abs(i-j)==k) ans2 += mat[GLEVEL*i+j];
			}}
		ans += pow((k-ans3),2)*ans2;
		ans2=0.0;
	}
	return ans;
}

double _calcDiffEntropy(double* mat, int mode)
{
	int i, j, k;
    double ans=0.0, ans2=0.0;
    for(k=0;k<GLEVEL;k++){
        for(i=0;i<GLEVEL;i++){
            for(j=0;j<GLEVEL;j++){
                if(abs(i-j)==k) ans2 += mat[GLEVEL*i+j];
            }}
        if(fabs(ans2)>EPS) ans += ans2*log10(ans2);
        ans2=0.0;
    }
    ans *= -1.0;
    return ans;
}

double __calcHXY(double* mat, int mode)
{
	double ans;
	ans = _calcEntropy(mat,mode);
	return ans;
}

double __calcHX(double* mat, int mode)
{
	int i,j;
	double ans=0.0, ans2=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			ans2 += mat[GLEVEL*i+j];
		}
		if(fabs(ans2)>EPS) ans += ans2*log10(ans2);
		ans2=0.0;
	}
	ans *= -1.0;
	return ans;
} 

double __calcHY(double* mat, int mode)
{
	double ans;
	ans = __calcHX(mat,mode);
	return ans;
}

double __calcHXY1(double* mat, int mode)
{
	int i,j,l,m;
	double ans=0.0, pl=0.0, pm=0.0;
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			for(l=0;l<GLEVEL;l++) pl += mat[GLEVEL*i+l];
			for(m=0;m<GLEVEL;m++) pm += mat[GLEVEL*m+j];
			pl *= pm;
			if(fabs(pl)>EPS) ans += mat[GLEVEL*i+j]*log10(pl);
			pl=pm=0.0;
		}}
	ans *= -1.0;
	return ans;
}

double __calcHXY2(double* mat, int mode)
{
	int i,j,l,m;
    double ans=0.0, pl=0.0, pm=0.0;
    for(i=0;i<GLEVEL;i++){ 
        for(j=0;j<GLEVEL;j++){
            for(l=0;l<GLEVEL;l++) pl += mat[GLEVEL*i+l];
			for(m=0;m<GLEVEL;m++) pm += mat[GLEVEL*m+j];
            pl *= pm;
            if(fabs(pl)>EPS) ans += pl*log10(pl);
            pl=pm=0.0;
        }}  
    ans *= -1.0;
    return ans;
}

double _calcIMC(double hxy, double hxy1, double hx, double hy, int mode)
{
	double ans;
	ans = (hxy-hxy1)/hx;
	return ans;
}

double _calcIMC2(double hxy2, double hxy, int mode)
{
	double ans;
	ans = pow(1-exp(-2.0*(hxy2-hxy)),0.5);
	return ans;
}

double _calcMCC(double* mat,int mode)
{
	float** qp;
	float* d; 
	float** vp;
	int i,j,k,l;
	float fac=0, fac2=0, h1, h2;
	double ans;
	
	qp = matrix(1,GLEVEL,1,GLEVEL);
	vp = matrix(1,GLEVEL,1,GLEVEL);
	d = vector(1,GLEVEL);
	
	for(i=0;i<GLEVEL;i++){
		for(j=0;j<GLEVEL;j++){
			for(k=0;k<GLEVEL;k++){
				for(l=0;l<GLEVEL;l++){
					fac2 += mat[GLEVEL*k+l];
				}
				if(fabs(fac2) > EPSF) 
					fac += mat[GLEVEL*i+k]*mat[GLEVEL*k+j]/pow(fac2,2);
				fac2=0;
			}
			qp[i+1][j+1] = fac;
			fac=0;
		}
	}
	
	jacobi(qp, GLEVEL, d, vp, &l);

	
	for(i=1;i<=GLEVEL;i++){
		if(i==0) h1 = d[0];
		else if(i==1) {
			if(h1 < d[1]){
				h2 = h1;
				h1 = d[1];
			}else h2 = d[1];
		}
		else{
			if(d[i]>h1){
				h2 = h1;
				h1 = d[i];
			}else if(d[i]>h2) h2 = d[i];
			else ;
		}
	}
	
	ans = pow(h2,0.5);
	return ans;
}

