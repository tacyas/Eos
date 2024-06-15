/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefFFTConvert ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefFFTConvert
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefFFTConvert ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
void lmrcRefFFTConvert(mrcImage* out ,mrcImage* in);
void lmrc3DZ1ImgGet(mrcImage* out ,mrcImage* in ,int z); 
void lmrc3DZ1FtPut(mrcImage* out ,mrcImage* in ,int z);
void lmrc3DRefImFtHeaderCopy(mrcImage* out ,mrcImage* in);
void lmrcImageMakeDump3DFourier(mrcImage* in);
void lmrc3DZ1FtGet(mrcImage* out ,mrcImage* in ,int Z);
void lmrcImageMakeDump2DFourier(mrcImage* in);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefFFTConvertInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	lmrcRefFFTConvert(&out ,&in);
/*  	lmrcImageMakeDump3DFourier(&out);  */
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcRefFFTConvert(mrcImage* out ,mrcImage* in)
{
/* variables */
  mrcImage tmpimg,tmpfft;
  int z;

/* initialization */
  tmpimg.Header = in->Header;
  tmpimg.HeaderN.z = 1;
  mrcInit(&tmpimg,NULL);

  lmrc3DZ1ImgGet(&tmpimg ,in ,1);
  /*
  lfft2d(&tmpfft ,&tmpimg);
  */
  lmrcImageFFT(&tmpfft ,&tmpimg, 0);
  out->Header = tmpfft.Header;
  out->HeaderN.z = (in->HeaderN.z % 2)?(in->HeaderN.z+1):(in->HeaderN.z);
  mrcInit(out,NULL);
  
  lmrc3DRefImFtHeaderCopy(out ,in);
  lmrc3DZ1FtPut(out ,&tmpfft ,1);
/*   lmrc3DZ1FtGet(&tmpfft ,out ,1 - out->HeaderN.z/2); */
/*   printf("%d \n",1- out->HeaderN.z/2); */
/*   lmrcImageMakeDump2DFourier(&tmpfft); */
   
/* begin */
  for (z = 2 ;z < in->HeaderN.z ;z++){
    lmrc3DZ1ImgGet(&tmpimg ,in ,z);
	/*
    lfft2d(&tmpfft ,&tmpimg);
	*/
    lmrcImageFFT(&tmpfft ,&tmpimg, 0);
    lmrc3DZ1FtPut(out ,&tmpfft ,z);
/*     lmrc3DZ1FtGet(&tmpfft ,out ,z - out->HeaderN.z/2); */
/*     printf("%d \n",z- out->HeaderN.z/2); */
/*     lmrcImageMakeDump2DFourier(&tmpfft); */
  }   
  mrcStatDataSet(out,0);
}



void lmrc3DZ1ImgGet(mrcImage* out ,mrcImage* in ,int z)
{

/* variables */
  int    x,y;
  double data;

/* Initialization */
  out->Header = in->Header;
  out->HeaderN.z = 1;
  mrcInit(out,NULL);
  
/* begin */
  for (y = 0; y < out->HeaderN.y ;y++){
    for (x = 0; x < out->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
/*    printf("%d %d %d %f ",x,y,z,data); */
      mrcPixelDataSet(out ,x ,y ,0 ,data, mrcPixelRePart);      
/*    mrcPixelDataGet(out ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); */
/*    printf("%f \n",data); */
    }
  }
  mrcStatDataSet(out,0);  
}

void lmrc3DZ1FtGet(mrcImage* out ,mrcImage* in ,int Z)
{

/* variables */
  int    X,Y;
  double data;

/* Initialization */
  out->Header = in->Header;
  out->HeaderN.z = 1;
  mrcInit(out,NULL);
  
/* begin */
  for (Y = - out->HeaderN.y / 2; Y < out->HeaderN.y/ 2 ;Y++){
    for (X = 0; X <= out->HeaderN.x / 2 ;X++){
      mrcPixelDataGet(in ,X ,Y ,Z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,Y ,0 ,data, mrcPixelRePart);      
      mrcPixelDataGet(in ,X ,Y ,Z ,&data ,mrcPixelImPart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,Y ,0 ,data, mrcPixelImPart);      
    }
  }
  mrcStatDataSet(out,0);  
}

void lmrc3DZ1FtPut(mrcImage* out ,mrcImage* in ,int Z)
{

/* variables */
  int    X,Y;
  double data;
  
/* begin */
  for (Y = - out->HeaderN.y / 2; Y < out->HeaderN.y / 2  ;Y++){
    for (X = 0; X <= out->HeaderN.x / 2 ;X++){
      mrcPixelDataGet(in  ,X ,Y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
/*       printf("%d %d %d %f ",X,Y,Z-out->HeaderN.z/2 ,data);  */
      mrcPixelDataSet(out ,X ,Y ,Z - out->HeaderN.z / 2  ,data  ,mrcPixelRePart);      
/*       mrcPixelDataGet(out  ,X ,Y ,Z-out->HeaderN.z/2 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); */
/*       printf("%f ",data);  */
      mrcPixelDataGet(in  ,X ,Y ,0 ,&data ,mrcPixelImPart ,mrcPixelHowNearest);
/*       printf("%f ",data);  */
      mrcPixelDataSet(out ,X ,Y ,Z - out->HeaderN.z / 2  ,data  ,mrcPixelImPart);      
/*       mrcPixelDataGet(out  ,X ,Y ,Z-out->HeaderN.z/2 ,&data ,mrcPixelImPart ,mrcPixelHowNearest); */
/*       printf("%f \n",data);  */
    }
  }
}

void lmrc3DRefImFtHeaderCopy(mrcImage* out ,mrcImage* in)
{
/* variables */
  int X;
  double data;

/* begin */
  for (X = 0; X < out->HeaderN.x / 2 ;X++){
    mrcPixelDataGet(in ,X ,0 ,0 ,&data ,mrcPixelRePart,mrcPixelHowNearest);
/*     printf("%d %f ",X,data); */
    mrcPixelDataSet(out ,X ,0 ,- out->HeaderN.z / 2 ,data ,mrcPixelRePart);
/*     mrcPixelDataGet(out ,X ,0 ,- out->HeaderN.z / 2 ,&data ,mrcPixelRePart,mrcPixelHowNearest); */
/*     printf("%f\n ",data); */
  }
}

void lmrcImageMakeDump3DFourier(mrcImage* in)
{

/* variables */
  int X,Y,Z;
  double rdata,idata;

/* begin */
  for (Z = - in->HeaderN.z / 2; Z < in->HeaderN.z / 2 ; Z++){
    for (Y = -in->HeaderN.y / 2; Y < in->HeaderN.y / 2  ; Y++){
      for (X = 0; X <= in->HeaderN.x / 2 ; X++){
	mrcPixelDataGet(in ,X ,Y ,Z ,&rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(in ,X ,Y ,Z ,&idata, mrcPixelImPart, mrcPixelHowNearest);
	fprintf(stdout,"%d %d %d %f %f \n",X,Y,Z,rdata,idata);
      }
    }
  }
}


void lmrcImageMakeDump2DFourier(mrcImage* in)
{

/* variables */
  int X,Y;
  double rdata,idata;

/* begin */
  for (Y = - in->HeaderN.y / 2; Y < in->HeaderN.y / 2 ; Y++){
    for (X = 0 ; X <= in->HeaderN.x / 2  ; X++){
      mrcPixelDataGet(in ,X ,Y ,0 ,&rdata, mrcPixelRePart, mrcPixelHowNearest);
      mrcPixelDataGet(in ,X ,Y ,0 ,&idata, mrcPixelImPart, mrcPixelHowNearest);
      fprintf(stdout,"%d %d %f %f \n",X,Y,rdata,idata);
    }
  }
}







