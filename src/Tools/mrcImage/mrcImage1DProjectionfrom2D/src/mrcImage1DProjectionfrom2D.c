/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage1DProjectionfrom2D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage1DProjectionfrom2D
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage1DProjectionfrom2D ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
void lmrc1DProjectionfrom2DinImg(mrcImage* out ,mrcImage* in ,int mode);
void lmrcImage1DProjectionfrom2DVanishing(mrcImage* out, mrcImage* in, float phi );
void lmrcImageExtracty0andValueAdjustment(mrcImage* out, mrcImage* in ,int fftN);
void lmrcImage1DProjectionfrom2DExtendingfft(mrcImage* out, mrcImage* in, int outN );
void lmrcImage1DProjectionfrom2DExtendingimg(mrcImage* out, mrcImage* in, int outN );
void lmrcImage1DProjectionfrom2Dmaking2Ddata(mrcImage* out, mrcImage* in );

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImage1DProjectionfrom2DInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage temp;
	long outN,fftN;
	
/* input parameters ,file open */
	DEBUGPRINT("start\n");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Reading\n");
	mrcFileRead(&in, info.In, "in main" ,0);

	switch (info.mode){
	case 0:
	case 1:
	  lmrc1DProjectionfrom2DinImg(&out ,&in ,info.mode);
	  break;
	case 2:
	  DEBUGPRINT("FFT operating\n");
	  lmrcImageFFT(&out, &in ,0);
	  
	  DEBUGPRINT("Vanishing\n");    
	  lmrcImage1DProjectionfrom2DVanishing(&temp, &out, info.phi );  
	  
	  DEBUGPRINT("Adopting number of data\n");
	  outN = temp.HeaderN.x;
	  if (outN < 2){
	    fprintf(stderr ,"Number of Data is too small!" );
	    exit(EXIT_FAILURE);
	  }
	  for (fftN=2 ;fftN < outN ;fftN = fftN*2);
	  DEBUGPRINT1("fftN=%ld \n" ,fftN);
	  lmrcImage1DProjectionfrom2DExtendingfft(&out, &temp, fftN); 
	  DEBUGPRINT1("outN=%d\n" ,outN);
	  lmrcImage1DProjectionfrom2Dmaking2Ddata(&temp, &out );
	  
	  DEBUGPRINT("FFT operating\n");   
	  lmrcImageFFT(&out, &temp ,0);    
	  lmrcImageExtracty0andValueAdjustment(&temp, &out, fftN);         
	  lmrcImage1DProjectionfrom2DExtendingimg(&out, &temp, outN); 
	}
       	DEBUGPRINT("Writing\n");
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
fprintf(stdout,"----- mode -----\n");
fprintf(stdout,"0:Projection to y axis.\n");
fprintf(stdout,"1:Projection to x axis.\n");
fprintf(stdout,"2:Projection by fourier transform.\n");
}

void lmrc1DProjectionfrom2DinImg(mrcImage* out ,mrcImage* in ,int mode)
{
/* variables */
  int x,y;
  double data,sum;

/* begin */
  if (!mode){
    out->Header = in->Header;
    out->HeaderN.x = in->HeaderN.y;
    out->HeaderN.y = 2;
    mrcInit(out,0);
    for (y=0 ;y < in->HeaderN.y ;y++) {
      sum = 0;
      for (x=0 ;x< in->HeaderN.x ;x++) {
	mrcPixelDataGet(in , x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
	sum += data;
      }
      mrcPixelDataSet(out, y, 0, 0, sum, mrcPixelRePart);
      mrcPixelDataSet(out, y, 1, 0, sum, mrcPixelRePart);
    }
  } else {
    out->Header = in->Header;
    out->HeaderN.x = in->HeaderN.x;
    out->HeaderN.y = 2;
    mrcInit(out,0);
    for (x=0 ;x < in->HeaderN.x ;x++) {
      sum = 0;
      for (y=0 ;y< in->HeaderN.x ;y++) {
	mrcPixelDataGet(in , x, y, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
	sum += data;
      }
      mrcPixelDataSet(out, x, 0, 0, sum, mrcPixelRePart);
      mrcPixelDataSet(out, x, 1, 0, sum, mrcPixelRePart);
    }   
  }
  mrcStatDataSet(out,0);
}

void lmrcImage1DProjectionfrom2DVanishing(mrcImage* out, mrcImage* in, float phi )
{
/* variables */
  int    R ,RMAX;
  double data;

/* initialization */
  if (phi > -180 && phi < 180){
    if (phi < -90){
      phi = phi + 180;
    }
    else if (phi > 90){
      phi = phi -180;
    }
  }
  else{	
    fprintf(stderr, "Phi must be between -180 degree and 180 degree!");
    exit(EXIT_FAILURE);
  }
  phi = phi * RADIAN; 
  if ( fabs(phi) < fabs( atan( in->HeaderN.y / in->HeaderN.x ) ) ) {
    RMAX = abs( (int)( (in->HeaderN.x / 2 ) / cos(phi) / 2.0 ) ) *2  ;
  }
  else{
    RMAX = abs( (int)( (in->HeaderN.y / 2 ) / sin(phi) / 2.0 ) ) *2 ;
  }

  DEBUGPRINT1("RMAX=%d\n",RMAX);
  out->Header = in->Header;
  out->HeaderN.z = 1;
  out->HeaderN.y = 1;
  out->HeaderN.x = 2 * RMAX  ;
  mrcInit(out, NULL);
  
/* begin */
  for (R = 0 ;R <= RMAX ;R++){
    mrcPixelDataGet(in , R * cos(phi), R * sin(phi), 0, &data, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataSet(out, R           , 0           , 0,  data, mrcPixelRePart); 
    mrcPixelDataGet(in , R * cos(phi), R * sin(phi), 0, &data, mrcPixelImPart, mrcPixelHowNearest); 
    mrcPixelDataSet(out, R           , 0           , 0,  data, mrcPixelImPart);
  }
  mrcStatDataSet(out,0);
}


void lmrcImageExtracty0andValueAdjustment(mrcImage* out, mrcImage* in ,int fftN)
{
/* variables */
  int x ;
  double data ;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.y = 1;
  mrcInit(out, NULL);
  
/* begin */
  for (x = 0 ; x < in->HeaderN.x ; x++){ 
    mrcPixelDataGet(in  ,x ,0 , 0, &data, mrcPixelRePart, mrcPixelHowNearest);
    data = data * sqrt( (double)fftN / 2.0 );
    mrcPixelDataSet(out ,x ,0 , 0,  data, mrcPixelRePart);
  }
  mrcStatDataSet(out,0);  
}


void lmrcImage1DProjectionfrom2Dmaking2Ddata(mrcImage* out, mrcImage* in )
{
/* variables */
  int X;
  double data;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.y = 2;
  mrcInit(out, NULL);

/* begin */
  for (X = 0 ; X <= in->HeaderN.x / 2 ; X++){ 
    mrcPixelDataGet(in  ,X ,0 ,  0, &data, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataSet(out ,X ,0  , 0,  data, mrcPixelRePart);
    mrcPixelDataSet(out ,X ,-1 , 0,  data, mrcPixelRePart);

    mrcPixelDataGet(in  ,X , 0 , 0, &data, mrcPixelImPart, mrcPixelHowNearest);
    mrcPixelDataSet(out ,X , 0 , 0,  data, mrcPixelImPart);
    mrcPixelDataSet(out ,X ,-1 , 0,  data, mrcPixelImPart);
  }
  mrcStatDataSet(out,0);  
}  

void lmrcImage1DProjectionfrom2DExtendingfft(mrcImage* out, mrcImage* in, int Nout )
{
/* variables */
  int Xout;
  double temp;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nout;
  mrcInit(out,NULL);

/* begin */
  for (Xout = 0 ;Xout <= in->HeaderN.x / 2 ;Xout++ ){
    mrcPixelDataGet(in  ,Xout ,0 , 0, &temp, mrcPixelRePart, mrcPixelHowNearest);
    mrcPixelDataSet(out ,Xout ,0 , 0,  temp, mrcPixelRePart);
    mrcPixelDataGet(in  ,Xout ,0 , 0, &temp, mrcPixelImPart, mrcPixelHowNearest);
    mrcPixelDataSet(out ,Xout ,0 , 0,  temp, mrcPixelImPart);
  }
  for (Xout = in->HeaderN.x / 2 + 1  ;Xout <= Nout / 2 ;Xout++ ){
    mrcPixelDataSet(out ,Xout ,0 , 0,  0.0, mrcPixelRePart);
    mrcPixelDataSet(out ,Xout ,0 , 0,  0.0, mrcPixelImPart);
  }
  mrcStatDataSet(out,0);  
}  


void lmrcImage1DProjectionfrom2DExtendingimg(mrcImage* out, mrcImage* in, int Nout )
{
/* variables */
  int Xout;
  double Xin,data,temp;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nout;
  mrcInit(out,NULL);

/* begin */
  for (Xout=0 ;Xout < Nout - 1  ;Xout++ ){
    Xin = (double)Xout * (double)in->HeaderN.x / (double)Nout ;
    data = 0.0;
    mrcPixelDataGet(in  ,(int)Xin     ,0 ,0, &temp, mrcPixelRePart, mrcPixelHowNearest);
    data = data + (1.0 - (Xin - (int)Xin ) ) *temp;
    mrcPixelDataGet(in  ,(int)Xin + 1 ,0 ,0, &temp, mrcPixelRePart, mrcPixelHowNearest);
    data = data +      (Xin - (int)Xin )   *temp;
    mrcPixelDataSet(out ,Xout         ,0 ,0,  data, mrcPixelRePart);
  }
  mrcPixelDataGet(in  ,in->HeaderN.x - 1 ,0 ,0, &temp, mrcPixelRePart, mrcPixelHowNearest);
  mrcPixelDataSet(out ,Nout - 1          ,0 ,0,  temp, mrcPixelRePart);

  mrcStatDataSet(out,0);  
}








