/*
# lmrcImageFeatureExtractionRunLength : $Revision$  
# $Descember 6,2005$ 
# Created by $kayabuki$
# Usage : lmrcImageFeatureExtractionRunLength 
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
#include "nr2.h"
#include "../inc/mrcImage.h"
#define EPS 0.000001

// Handbook of Image Analysis [Revised Edition] page1265 
void _calcMatrix1(mrcImage* in, float** mat, int theta, int mode);
void _calcMatrix2(mrcImage* in, float** mat, int theta, int mode);
double _calcSRE(float** mat, int pixmax, int dev, int mode);
double _calcLRE(float** mat, int pixmax, int dev, int mode);
double _calcGLN(float** mat, int pixmax, int dev, int mode);
double _calcRLN(float** mat, int pixmax, int dev, int mode);
double _calcRP(float** mat, int a, int pixmax, int dev, int mode);

void
lmrcImageFeatureExtractionRunLength(mrcImage* in, double* out, lmrcImageFeatureExtractionInfo linfo, int mode)
{
	mrcImage nord;
	int i, j, pixmax;
	float** mat;
	
	lmrcImagePosterization(in, &nord, linfo.rl_dev, 0); 
	pixmax = in->HeaderN.x;
	if(pixmax < in->HeaderN.y) pixmax = in->HeaderN.y;
	mat = matrix(0,linfo.rl_dev-1,1,pixmax); 

	if(linfo.rl_theta ==0 || linfo.rl_theta ==90) //calc Matrix
		_calcMatrix1(&nord,mat,linfo.rl_theta,0);
	else if(linfo.rl_theta ==45 || linfo.rl_theta ==135)
		_calcMatrix2(&nord,mat,linfo.rl_theta,0);
	else{
		fprintf(stderr,"\"rl_theta\" you input (%d) is unsupported angle, so 0 degree is used in this calculation.\n",linfo.rl_theta);
		_calcMatrix1(&nord,mat,0,0);
	}
		
	out[0] = _calcSRE(mat,pixmax,linfo.rl_dev,0);
	out[1] = _calcLRE(mat,pixmax,linfo.rl_dev,0);
	out[2] = _calcGLN(mat,pixmax,linfo.rl_dev,0);
	out[3] = _calcRLN(mat,pixmax,linfo.rl_dev,0);
	out[4] = _calcRP(mat,in->HeaderN.x*in->HeaderN.y,pixmax,linfo.rl_dev,0);
	
	for(i=0;i<5;i++)
		fprintf(stdout,"%f\n",out[i]);

}

void _calcMatrix1(mrcImage* in, float** mat, int theta, int mode)
{
	int i,j;
	double cdata, data;
	int counter=0;

	if(theta==0){
		for(i=0;i<in->HeaderN.y;i++){
			for(j=0;j<in->HeaderN.x;j++){
				mrcPixelDataGet(in, j, i, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(counter==0) {
					counter=1; cdata=data;
				}else{
					if(cdata==data) counter++;
					else {
						mat[(int)cdata][counter]++;
						counter=1; cdata=data;
					}
				}
			}
			mat[(int)cdata][counter]++;
			counter=0;
		}
	}else{
		for(i=0;i<in->HeaderN.x;i++){
			for(j=0;j<in->HeaderN.y;j++){
				mrcPixelDataGet(in, i, j, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(counter==0) {
                    counter=1; cdata=data;
                }else{
                    if(cdata==data) counter++;
                    else {
                        mat[(int)cdata][counter]++;
                        counter=1; cdata=data;
                    }
                }
            }
            mat[(int)cdata][counter]++;
            counter=0; 
        }
	}
}

void _calcMatrix2(mrcImage* in, float** mat, int theta, int mode)
{
	int i,x,y;
	double cdata,data;
	int counter=0;

	if(theta==45){
		for(i=0;i<in->HeaderN.x;i++){
			for(y=0,x=i; x>=0||y<in->HeaderN.y ; y++,x--){
				mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(counter==0) {
					counter=1; cdata=data;
				}else{
					if(cdata==data) counter++;
					else {
						mat[(int)cdata][counter]++;
						counter=1; cdata=data;
					}
				}
			}
			mat[(int)cdata][counter]++;
			counter=0;
		}
		for(i=1;i<in->HeaderN.y;i++){
			for(y=i,x=in->HeaderN.x-1; x>=0||y<in->HeaderN.y ; y++,x--){
				mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(counter==0) {
					counter=1; cdata=data;
				}else{
					if(cdata==data) counter++;
					else {
						mat[(int)cdata][counter]++;
						counter=1; cdata=data;
					}
				}
			}
			mat[(int)cdata][counter]++;
			counter=0;
		}
	}else{
		for(i=in->HeaderN.y-1 ; i>=0 ;i--){
			for(y=i,x=0; x<in->HeaderN.x||y<in->HeaderN.y ; y++,x++){
				mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(counter==0) {
					counter=1; cdata=data;
				}else{
					if(cdata==data) counter++;
					else {
						mat[(int)cdata][counter]++;
						counter=1; cdata=data;
					}
				}
			}
			mat[(int)cdata][counter]++;
			counter=0;
		}
		for(i=0 ; i<in->HeaderN.x ;i++){
			for(y=0,x=i; x<in->HeaderN.x||y<in->HeaderN.y ; y++,x++){
				mrcPixelDataGet(in, x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
				if(counter==0) {
					counter=1; cdata=data;
				}else{
					if(cdata==data) counter++;
					else {
						mat[(int)cdata][counter]++;
						counter=1; cdata=data;
					}
				}
			}
			mat[(int)cdata][counter]++;
			counter=0;
		}
	}
}

double _calcSRE(float** mat, int pixmax, int dev, int mode)
{
	int i,j;
	double ans, fac1=0, fac2=0;
	for(i=0;i<dev;i++){
		for(j=1;j<=pixmax;j++){
			fac1 += mat[i][j]/(j*j);
			fac2 += mat[i][j];
		}
	}
	ans = fac1/fac2;
	return ans;
}

double _calcLRE(float** mat, int pixmax, int dev, int mode)
{
	int i,j;
	double fac1=0, fac2=0, ans;
	for(i=0;i<dev;i++){
		for(j=1;j<=pixmax;j++){
			fac1 += mat[i][j]*j*j;
			fac2 += mat[i][j];
		}}
	ans = fac1/fac2;
	return ans;
}

double _calcGLN(float** mat, int pixmax, int dev, int mode)
{
	int i,j;
	double fac1=0, fac2=0, fac3=0, ans;
	for(i=0;i<dev;i++){
		for(j=1;j<=pixmax;j++){
			fac1 += mat[i][j];
			fac2 += mat[i][j];
		}
		fac3 += fac1*fac1;
		fac1=0;
	}
	ans = fac3/fac2;
	return ans;
}

double _calcRLN(float** mat, int pixmax, int dev, int mode)
{
	int i,j;
	double fac1=0, fac2=0, fac3=0, ans;
	for(j=1;j<=pixmax;j++){
		for(i=0;i<dev;i++){
			fac1 += mat[i][j];
			fac2 += mat[i][j];
		}
		fac3 += fac1*fac1;
		fac1=0;
	}
	ans = fac3/fac2;
	return ans;
}

double _calcRP(float** mat, int a, int pixmax, int dev, int mode)
{
	int i,j;
	double fac=0, ans;
	for(i=0;i<dev;i++){
		for(j=1;j<=pixmax;j++){
			fac += mat[i][j];
		}}
	ans = fac/a;
	return ans;
}
							  
