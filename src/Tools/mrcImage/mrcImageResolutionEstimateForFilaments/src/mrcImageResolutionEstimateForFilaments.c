/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageResolutionEstimateForFilaments ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageResolutionEstimateForFilaments
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageResolutionEstimateForFilaments ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcImageResolutionEstimateForFilamentsInfo {
	float a;
	int   b;
} lmrcImageResolutionEstimateForFilamentsInfo;

typedef enum lmrcImageResolutionEstimateForFilamentsMode {
	a=0,
	b=1
} lmrcImageResolutionEstimateForFilamentsMode;
*/

void lmrcImageResolutionEstimateForZ(double* data ,mrcImage* in1 ,mrcImage* in2,double delta ,double H ,int mode);
void lmrcImageResolutionEstimateForR(double* data ,mrcImage* in1 ,mrcImage* in2,double delta ,double H ,int mode);


int
main(int argc, char* argv[]) 
{
	mrcImageResolutionEstimateForFilamentsInfo info;


/* variables */
	mrcImage in1;
	mrcImage in2;
	double* data,DX,DY,DZ;
	int max;
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	mrcFileRead(&in2 ,info.In2 ,"in main" ,0);
	
	DX=1/(in2.HeaderLength.x*in2.HeaderN.x);
	DY=1/(in2.HeaderLength.y*in2.HeaderN.y);
	DZ=1/(in2.HeaderLength.z*in2.HeaderN.z);
	if (!info.flagdelta){
	  if (info.mode2==0){
	    info.delta=1/(in2.HeaderLength.z*in2.HeaderN.z);
	  } else {
	    info.delta=1/(in2.HeaderLength.x*in2.HeaderN.x);
	  }	    
	}
	if (!info.flagH){
	  info.H = 1/in2.HeaderLength.x/2;
	}


/* begin */
	DEBUGPRINT("Program Start\n");
	max=floor(sqrt(SQR(1/in2.HeaderLength.x)+SQR(1/in2.HeaderLength.y)+SQR(1/in2.HeaderLength.z) ) /info.delta /2  +0.5)+1;
	if ( (data = (double *)malloc(sizeof(double)*max ) )== NULL ){
	  fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
	}
	mrcFileRead(&in1 ,info.In1 ,"in main" ,0);

	if (info.mode2 == 0){
	  lmrcImageResolutionEstimateForZ(data ,&in1 ,&in2 ,info.delta ,info.H ,info.mode);
	} else {
	  lmrcImageResolutionEstimateForR(data ,&in1 ,&in2 ,info.delta ,info.H ,info.mode);
	}	  
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0: Fourier shell correlation.\n");
	fprintf(stderr, "1: Fourier shell phase residual.\n");
}


void lmrcImageResolutionEstimateForZ(double* data ,mrcImage* in1 ,mrcImage* in2,double delta ,double H ,int mode)
{
/* variables */
     mrcImage ft1;
     mrcImage ft2;
     int X,Y,Z,max,tempmode,outZ;
     int *N;
     double *tmp1,*tmp2,*tmp3;
     double rdata1,idata1,rdata2,idata2,ZZ,R,f1,f2,nr1,nr2,ni1,ni2,dr,di,d,dp;
     
/* begin */
     max=floor(1/in1->HeaderLength.z /delta /2  +0.5)+1;
     DEBUGPRINT1("max=%d\n",max);
     if ( (tmp1 = (double *)malloc(sizeof(double)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
       exit(EXIT_FAILURE);
	}
     if ( (tmp2 = (double *)malloc(sizeof(double)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
       exit(EXIT_FAILURE);
	}
     if ( (tmp3 = (double *)malloc(sizeof(double)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
       exit(EXIT_FAILURE);
     }
     if ( (N = (int *)malloc(sizeof(int)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
     }
     
     for (Z=0 ;Z<max ;Z++){
       tmp1[Z]=tmp2[Z]=tmp3[Z]=0;
	  N[Z]=0;
     }
     lmrcImageFFT(&ft1 ,in1 ,0);
     lmrcImageFFT(&ft2 ,in2 ,0);
     
     for (Z=-ft1.HeaderN.z/2.0; Z<ft1.HeaderN.z/2.0; Z++) {
       for (X=0; X<=ft1.HeaderN.x/2.0; X++) {
	 for (Y=-ft1.HeaderN.y/2.0; Y<ft1.HeaderN.y/2.0; Y++) {
	   mrcPixelDataGet(&ft1, X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
	   mrcPixelDataGet(&ft1, X, Y, Z, &idata1, mrcPixelImPart, mrcPixelHowNearest);
	   mrcPixelDataGet(&ft2, X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
	   mrcPixelDataGet(&ft2, X, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
	   ZZ = Z/(ft1.HeaderLength.z*ft1.HeaderN.z);
	   R = SQR(X/(ft1.HeaderLength.x*ft1.HeaderN.x)) + SQR(Y/(ft1.HeaderLength.y*ft1.HeaderN.y)); 
	   if (R<H*H){
	     tempmode=mode;	  
	     outZ=floor( fabs(ZZ)/delta +0.5);	   
	     switch (tempmode%2){
	     case 0:
	       tmp1[outZ] += rdata1*rdata2 + idata1*idata2;
	       tmp2[outZ] += rdata1*rdata1 + idata1*idata1;
	       tmp3[outZ] += rdata2*rdata2 + idata2*idata2;
	       break;
	     case 1:
	       f1 = rdata1*rdata1 + idata1*idata1;
	       f2 = rdata2*rdata2 + idata2*idata2;
	       if (f1 != 0 && f2 != 0 ){
		 f1=sqrt(f1);
		 f2=sqrt(f2);
		 tmp2[outZ] += f1*f2;
		 nr1=rdata1/f1;
		 ni1=idata1/f1;
		 nr2=rdata2/f2;
		 ni2=idata2/f2;
		 dr=nr1-nr2;
		 di=ni1-ni2;
		 if (dr != 0.0 ){
		   d=sqrt(dr*dr+di*di);
		   if (d>2) d=2 ;
		   dp=2*asin(d/2);
		   tmp1[outZ] += f1*f2*dp;
		 }
	       }
	       break;
	     }
	     N[outZ]++;
	   }
	 }
       }
     }
     tempmode=mode;
     for (Z=0 ;Z<max ;Z++){
       switch (tempmode%2){
       case 0:
	 if (tmp2[Z]!=0 &&  tmp3[Z]!=0 ){
	   data[Z]=tmp1[Z]/sqrt(tmp2[Z]*tmp3[Z]);
	 }else{
	   data[Z]=0.0;
	 }
	 break;
       case 1:
	 if (tmp2[Z]!=0){
	   data[Z]=tmp1[Z]/tmp2[Z];
	 }else{
	   data[Z]=0.0;
	 }
	 break;
       }
       if (tempmode/2 == 0) {
	 fprintf(stdout,"%f %f %d \n",Z*delta ,data[Z],N[Z]);
       }
     }
     mrcImageFree(&ft1,"");
     mrcImageFree(&ft2,"");
     free(tmp1);
     free(tmp2);
     free(tmp3);
     free(N);
}
void lmrcImageResolutionEstimateForR(double* data ,mrcImage* in1 ,mrcImage* in2,double delta ,double H ,int mode)
{
/* variables */
     mrcImage ft1;
     mrcImage ft2;
     int X,Y,Z,max,tempmode,outR;
     int *N;
     double *tmp1,*tmp2,*tmp3;
     double rdata1,idata1,rdata2,idata2,XX,YY,ZZ,R2,f1,f2,nr1,nr2,ni1,ni2,dr,di,d,dp,R;
     
/* begin */
     max=floor(sqrt(SQR(1/in1->HeaderLength.x /delta /2) + SQR(1/in1->HeaderLength.y /delta /2))  +0.5)+1;
     DEBUGPRINT1("max=%d\n",max);
     if ( (tmp1 = (double *)malloc(sizeof(double)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
       exit(EXIT_FAILURE);
	}
     if ( (tmp2 = (double *)malloc(sizeof(double)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
       exit(EXIT_FAILURE);
	}
     if ( (tmp3 = (double *)malloc(sizeof(double)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
       exit(EXIT_FAILURE);
     }
     if ( (N = (int *)malloc(sizeof(int)*max ) )== NULL ){
       fprintf(stderr ,"Enough memoly is not available.");
	  exit(EXIT_FAILURE);
     }
     
     for (outR=0 ;outR<max ;outR++){
       tmp1[outR]=tmp2[outR]=tmp3[outR]=0;
       N[outR]=0;
     }
     lmrcImageFFT(&ft1 ,in1 ,0);
     lmrcImageFFT(&ft2 ,in2 ,0);
     
     for (Z=-ft1.HeaderN.z/2.0; Z<ft1.HeaderN.z/2.0; Z++) {
       for (X=0; X<=ft1.HeaderN.x/2.0; X++) {
	 for (Y=-ft1.HeaderN.y/2.0; Y<ft1.HeaderN.y/2.0; Y++) {
	   mrcPixelDataGet(&ft1, X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
	   mrcPixelDataGet(&ft1, X, Y, Z, &idata1, mrcPixelImPart, mrcPixelHowNearest);
	   mrcPixelDataGet(&ft2, X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
	   mrcPixelDataGet(&ft2, X, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
	   XX = SQR(X/(ft1.HeaderLength.x*ft1.HeaderN.x));
	   YY = SQR(Y/(ft1.HeaderLength.y*ft1.HeaderN.y));
	   ZZ = SQR(Z/(ft1.HeaderLength.z*ft1.HeaderN.z));
	   R2 = XX+YY; 
	   if (X!=0 || Y!=0){
	     R=sqrt(R2);
	   } else {
	     R=0;
	   }
	   if (ZZ<H*H){
	     tempmode=mode;	  
	     outR=floor( R/delta +0.5);	   
	     switch (tempmode%2){
	     case 0:
	       tmp1[outR] += rdata1*rdata2 + idata1*idata2;
	       tmp2[outR] += rdata1*rdata1 + idata1*idata1;
	       tmp3[outR] += rdata2*rdata2 + idata2*idata2;
	       break;
	     case 1:
	       f1 = rdata1*rdata1 + idata1*idata1;
	       f2 = rdata2*rdata2 + idata2*idata2;
	       if (f1 != 0 && f2 != 0 ){
		 f1=sqrt(f1);
		 f2=sqrt(f2);
		 tmp2[outR] += f1*f2;
		 nr1=rdata1/f1;
		 ni1=idata1/f1;
		 nr2=rdata2/f2;
		 ni2=idata2/f2;
		 dr=nr1-nr2;
		 di=ni1-ni2;
		 if (dr != 0.0 ){
		   d=sqrt(dr*dr+di*di);
		   if (d>2) d=2 ;
		   dp=2*asin(d/2);
		   tmp1[outR] += f1*f2*dp;
		 }
	       }
	       break;
	     }
	     N[outR]++;
	   }
	 }
       }
     }
     tempmode=mode;
     for (outR=0 ;outR<max ;outR++){
       switch (tempmode%2){
       case 0:
	 if (tmp2[outR]!=0 &&  tmp3[outR]!=0 ){
	   data[outR]=tmp1[outR]/sqrt(tmp2[outR]*tmp3[outR]);
	 }else{
	   data[outR]=0.0;
	 }
	 break;
       case 1:
	 if (tmp2[outR]!=0){
	   data[outR]=tmp1[outR]/tmp2[outR];
	 }else{
	   data[outR]=0.0;
	 }
	 break;
       }
       if (tempmode/2 == 0) {
	 fprintf(stdout,"%f %f %d \n",outR*delta ,data[outR],N[outR]);
       }
     }
     mrcImageFree(&ft1,"");
     mrcImageFree(&ft2,"");
     free(tmp1);
     free(tmp2);
     free(tmp3);
     free(N);
}
