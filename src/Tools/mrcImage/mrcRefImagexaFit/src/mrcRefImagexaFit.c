/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImagexaFit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImagexaFit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImagexaFit ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "mrcImagefuncmin.h"
#include "nr2.h"

int ex_y;
mrcImage* ex_in;
mrcImage* ex_ref;
mrcRefHeader ex_refheader;
int ex_Mode;
int ex_xrange;
int ex_arange;
mrcImage tmp_img[100];
int tmp_x[100][100];
double tmp_c[100][100];
int tmp_num = 0;
int tmp_cnum[100] = {1};
int tmp_irefz;
int tmp_ix;

/* structure */
typedef struct {
  int inNx;
  int inNy;
  int refNx;
  int refNy;
  int dy;
}mrcxaFitTailer;

typedef struct {
	double	maxx;
	double 	maxa;
	double	maxc;
}mrcxaFitData;

/* prototype */
void lmrcxaFitTailerSet(mrcImage* out ,mrcxaFitTailer* in);
void lmrcxaFitConvert(mrcImage* out ,mrcImage* in ,double value ,int mode);
void lmrcxaFitTailerGet(mrcxaFitTailer* out ,mrcImage* in);
void lmrcRefImagexaFity1(mrcxaFitData* out ,mrcImage* in ,mrcImage* ref,mrcxaFitData* start ,int y);
void lmrcxaFitDataSet(mrcImage* out ,mrcxaFitData* in ,int y);
void lxaFitdataConvertSet(double* ox ,double* oy ,double* oa ,double* odata ,double x ,double y ,double a ,double data ,int size ,mrcxaFitTailer* tailer);
void lxaFitdataConvertTranse(double* ox ,double* oy ,double* oa, double* odata , int size ,int y ,mrcxaFitTailer* tailer);
void lxaFitdataConvertShift(double* ox,double* oy,double* oa,double* odata,int size);
void lxaFitdataConvertOutput(mrcImage* out ,double* ox ,double* oa ,double* odata ,int size ,int y ,double value ,mrcxaFitTailer* tailer ,int mode);
void lmrcRefImagexaFit(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int ix ,int ia ,int dy ,int mode );
float dummyfunc(float p[] );

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefImagexaFitInfo info;

/* variables */
        mrcImage in;
        mrcImage out;
        mrcImage ref; 

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	switch (info.mode){
	case 0:
	case 1:
	  mrcFileRead(&ref ,info.Ref ,"in main",0);
	  ex_in = &in;
	  ex_ref = &ref;
	  ex_Mode = info.mode2;
	  ex_xrange=info.xrange;
	  ex_arange=info.arange;
	  if (info.mode){
	    lmrcRefNormalization(&ref);      
	  }
	  lmrcRefImagexaFit(&out ,&in ,&ref ,info.ix ,info.ia ,info.Dy ,info.mode ); 
	  break;
	case 2:
	  lmrcxaFitConvert(&out ,&in ,info.Value ,0);
	  break;
	case 3:
	  lmrcxaFitConvert(&out ,&in ,info.Value ,1);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---- mode ----\n");
fprintf(stdout,"0:not normalize\n");
fprintf(stdout,"1:normalize \n");
fprintf(stdout,"2:Convert file to peak image.\n");
fprintf(stdout,"3:Convert file to peak and alpha image\n");
fprintf(stdout,"---- mode2 ---- \n");
fprintf(stdout,"0:Filament is black or white.\n");
fprintf(stdout,"1:Filament is black.\n");
fprintf(stdout,"2:Filament is white.\n");
}

void lmrcRefImagexaFit(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int ix ,int ia ,int dy ,int mode )
{
/* variables */
  mrcxaFitData data1,data2;
  int y,ey,i,j;
  mrcxaFitTailer tailer;
  tailer.inNx = in->HeaderN.x;
  tailer.inNy = in->HeaderN.y;
  tailer.refNx = ref->HeaderN.x;
  tailer.refNy = ref->HeaderN.y;
  tailer.dy = dy;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.y = in->HeaderN.y + 2;
  out->HeaderN.x = 3;
  mrcInit(out,0);
  y = 0;
  ey = in->HeaderN.y - ref->HeaderN.y ;
  lmrcRefHeaderGet(&ex_refheader ,ref);

/* begin */
  data2.maxa = ia;
  data2.maxx = ix - ref->HeaderN.x / 2;
  while (y < ey ) {
    lmrcRefImagexaFity1(&data1 ,in , ref ,&data2 ,y);
    for (i=0 ;i < tmp_num ;i++){
      mrcImageFree(&tmp_img[i] ,"in lmrcRefImagexaFit");
      for (j=0 ;j < tmp_cnum[i] ;j++){
	tmp_x[i][j]=0;
	tmp_c[i][j]=0;
      }
      tmp_cnum[i]=1;
    }
    tmp_num =0;
    lmrcxaFitDataSet(out ,&data1 ,y); 
    data2 = data1;
    fprintf(stderr,"%d %f %f %f  ",y,data1.maxx,data2.maxa,data1.maxc); 
    y += dy;
    data2.maxx += sin(data2.maxa * PI / 180) * dy;
    fprintf(stderr ,"%f \n",data2.maxx);
  }      
  lmrcxaFitTailerSet(out ,&tailer );
  mrcStatDataSet(out,0);
}

void lmrcxaFitTailerSet(mrcImage* out ,mrcxaFitTailer* in)
{
  mrcPixelDataSet(out ,0 ,out->HeaderN.y-2 ,0 ,in->inNx ,mrcPixelRePart );
  mrcPixelDataSet(out ,1 ,out->HeaderN.y-2 ,0 ,in->inNy ,mrcPixelRePart );
  mrcPixelDataSet(out ,0 ,out->HeaderN.y-1 ,0 ,in->refNx ,mrcPixelRePart );
  mrcPixelDataSet(out ,1 ,out->HeaderN.y-1 ,0 ,in->refNy ,mrcPixelRePart );
  mrcPixelDataSet(out ,2 ,out->HeaderN.y-1 ,0 ,in->dy    ,mrcPixelRePart );
}

void lmrcxaFitTailerGet(mrcxaFitTailer* out ,mrcImage* in)
{
  double data;
  mrcPixelDataGet(in ,0 ,in->HeaderN.y-2 ,0 ,&data ,mrcPixelRePart  ,mrcPixelHowNearest);
  out->inNx = data;
  mrcPixelDataGet(in ,1 ,in->HeaderN.y-2 ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest );
  out->inNy = data;
  mrcPixelDataGet(in ,0 ,in->HeaderN.y-1 ,0 ,&data ,mrcPixelRePart  ,mrcPixelHowNearest);
  out->refNx = data;
  mrcPixelDataGet(in ,1 ,in->HeaderN.y-1 ,0 ,&data ,mrcPixelRePart  ,mrcPixelHowNearest);
  out->refNy = data;
  mrcPixelDataGet(in ,2 ,in->HeaderN.y-1 ,0 ,&data ,mrcPixelRePart  ,mrcPixelHowNearest);
  out->dy = data;
}


void lmrcRefImagexaFity1(mrcxaFitData* out ,mrcImage* in ,mrcImage* ref,mrcxaFitData* start ,int y)
{
/* variables */
  int iter;
  mrcRefDegCoordinate maxa,dummy;
  double TOL;
  float* p;
  float** xi;
  float fc;

/* initialization */
  p=vector(1,2);
  xi=matrix(1,2,1,2);
  xi[1][1]=1.0;
  xi[1][2]=0.0;
  xi[2][1]=0.0;
  xi[2][2]=1.0;
  p[1]=(double)start->maxx;
  p[2]=(double)lmrcRefGetzCordinate(ex_refheader.ip ,ex_refheader.iw ,start->maxa  ,&ex_refheader);
  tmp_ix=p[1];
  tmp_irefz=p[2];
  TOL=1e-6;

/* begin */
  powell(p,xi,2,TOL,&iter,&fc, dummyfunc);
  out->maxx=p[1];
  ex_y=y;
  lmrcRefGetdegreeCoordinate(&dummy ,&dummy ,&maxa ,p[2] ,&ex_refheader );
  out->maxa=maxa;
  out->maxc=-fc;
}

float dummyfunc(float p[] )
{
  int x,refz,i,j,flag;
  mrcImage tmpref;
  double c;

  x = floor(p[1]+0.5);
  refz = floor(p[2]+0.5);
  
  flag=0;
/* begin */
  if (x < tmp_ix - ex_xrange ){
    fprintf(stderr ,"%d %d %f   ",x,refz, tmp_ix - ex_xrange - x + 10.0 );
    return( tmp_ix - ex_xrange - x + 10.0);
  } else if (x > tmp_ix + ex_xrange){
    fprintf(stderr ,"%d %d %f   ",x,refz,  x - tmp_ix - ex_xrange + 10.0 );
    return( x - tmp_ix - ex_xrange + 10.0);
  } else if ( refz < tmp_irefz - ex_arange/ex_refheader.da) {
    fprintf(stderr ,"%d %d %f   ",x,refz,  tmp_irefz - ex_arange/ex_refheader.da - refz + 10.0 );
    return( tmp_irefz - ex_arange/ex_refheader.da - refz + 10.0);
  } else if ( refz > tmp_irefz + ex_arange/ex_refheader.da) {
    fprintf(stderr ,"%d %d %f   ",x,refz,  refz - tmp_irefz -  ex_arange/ex_refheader.da + 10.0 );
    return( refz - tmp_irefz -  ex_arange/ex_refheader.da + 10.0);
  } else if (x<0 ){
    fprintf(stderr ,"%d %d %f   ",x,refz, -x + 10.0  );
    return( -x + 10.0 );
  } else if ( x >= ex_in->HeaderN.x - ex_ref->HeaderN.x ) {
    fprintf(stderr ,"%d %d %f   ",x,refz, x - (ex_in->HeaderN.x - ex_ref->HeaderN.x ) +10.0  );
    return( x - (ex_in->HeaderN.x - ex_ref->HeaderN.x ) +10.0 );
  } else if ( refz < 1 ) {
    fprintf(stderr ,"%d %d %f   ",x,refz, -refz + 10.0  );
    return( -refz + 10.0 );
  } else if ( refz >= ex_ref->HeaderN.z ) {
    fprintf(stderr ,"%d %d %f   ",x,refz, refz - ex_ref->HeaderN.z + 10.0  );
    return( refz - ex_ref->HeaderN.z + 10.0 );
  } else {
    flag=1;
    j=1;
    for (i=0 ;i < tmp_num ;i++){
      if (x == tmp_x[i][0]) {
	for (j=1 ;j < tmp_cnum[i] ;j++){
	  if (refz == tmp_x[i][j] ){
	    break;
	  }
	}
	break ;
      }
    }
    DEBUGPRINT3("%d %d %d",i,j,tmp_num);
    if (i < tmp_num && j < tmp_cnum[i] ){
      c = tmp_c[i][j];
    } else { 
      if (i == tmp_num){
	lmrcImageRectangleGet(&tmp_img[i] ,ex_in ,x ,ex_y ,x + ex_ref->HeaderN.x - 1 ,ex_y + ex_ref->HeaderN.y - 1);
	lmrcImageZ1Normalization(&tmp_img[i],0);
	tmp_x[i][0] = x;
	tmp_num ++;
	DEBUGPRINT("NORM");
      } 
      lmrc3DZ1ImgGet(&tmpref ,ex_ref ,refz);
      c =  lmrcRef2DImgCorrelation(&tmpref , &tmp_img[i]);
      tmp_cnum[i] ++;
      tmp_x[i][j] = refz;
      tmp_c[i][j] = c;
      mrcImageFree(&tmpref,"dummyfunc");
      DEBUGPRINT("Free ");
    }
    switch (ex_Mode){
    case 0:
      fprintf(stderr ,"%d %d %f   ",x,refz,-fabs(c) );
      if (flag) {
	return(-fabs(c) );
      } else {
	 return(fabs(c) );
      }
      break;
    case 1:
      fprintf(stderr ,"%d %d %f   ",x,refz,c );
      return(c);
      break;
    case 2:
      fprintf(stderr ,"%d %d %f   ",x,refz,-c );
      if (flag) {
	return(-c);
      }else{
	return(c);
      }
    }
    return(c);
  }
}

void lmrcxaFitDataSet(mrcImage* out ,mrcxaFitData* in , int y)
{
  mrcPixelDataSet(out ,0 ,y ,0 ,in->maxx ,mrcPixelRePart ); 
  mrcPixelDataSet(out ,1 ,y ,0 ,in->maxa ,mrcPixelRePart ); 
  mrcPixelDataSet(out ,2 ,y ,0 ,in->maxc ,mrcPixelRePart ); 
}


void lmrcxaFitConvert(mrcImage* out ,mrcImage* in ,double value ,int mode)
{
/* variables */
  int y,py,px,size,iy,ey;
  double data,x,a;
  double ox[1000];
  double odata[1000];
  double oa[1000];
  double oy[1000];
  mrcxaFitTailer tailer;
  int CUT=10;

/* intialization */
  lmrcxaFitTailerGet(&tailer ,in);
  out->Header=in->Header;
  out->HeaderN.x = tailer.inNx;
  out->HeaderN.y = tailer.inNy;
  mrcInit(out ,NULL);

/* begin */
  iy=-1;
  tailer.dy = 4;
  if (mode == 0){
    for (y=0 ;y < tailer.inNy ;y++){
      mrcPixelDataGet(in ,0 ,y ,0 ,&x ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataGet(in ,2 ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      if ( data != 0.0) { 
	if (iy < 0) iy=y;
	ey = y;
	px = x + (tailer.refNx - 1)/2;
	py = y + (tailer.refNy - 1)/2;
	mrcPixelDataSet(out ,px ,py ,0 ,data*value ,mrcPixelRePart);
	DEBUGPRINT6("%d %d %f %f %f %d \n",px,py,data,value,x,tailer.refNx);
      }
    }
    mrcPixelDataGet(in ,0 ,iy ,0 ,&x ,mrcPixelRePart ,mrcPixelHowNearest);
    mrcPixelDataGet(in ,1 ,iy ,0 ,&a ,mrcPixelRePart ,mrcPixelHowNearest);
    mrcPixelDataGet(in ,2 ,iy ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
    px = x + (tailer.refNx - 1)/2;
    py = iy + (tailer.refNy - 1)/2;
    x = px - sin(a * PI / 180) * (py-CUT);
    mrcPixelDataSet(out ,x ,CUT ,0 ,data*value ,mrcPixelRePart);
    DEBUGPRINT4("%d %d %f %f \n",px,py,x,a);
    mrcPixelDataGet(in ,0 ,ey ,0 ,&x ,mrcPixelRePart ,mrcPixelHowNearest);
    mrcPixelDataGet(in ,1 ,ey ,0 ,&a ,mrcPixelRePart ,mrcPixelHowNearest);
    mrcPixelDataGet(in ,2 ,ey ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
    px = x + (tailer.refNx - 1)/2;
    py = ey + (tailer.refNy - 1)/2;
    x = px + sin(a * PI / 180) *(tailer.inNy - py - CUT -1);
    mrcPixelDataSet(out ,x ,tailer.inNy - CUT -1 ,0 ,data*value ,mrcPixelRePart);
    DEBUGPRINT4("%d %d %f %f \n",px,py,x,a);

  }else{
    size = tailer.refNy / tailer.dy + 1;
    DEBUGPRINT1("%d \n",size);
/*    ox = (double *)malloc(size+1);
    oy = (double *)malloc(size+1);
    oa = (double *)malloc(size+1);
    odata = (double *)malloc(size+1);
    if(ox==NULL || oy==NULL || oa==NULL || odata==NULL ){
      fprintf(stderr,"Enough memony is not available.");
      exit(1);
    }
    */
    for (y=0 ;y < size ;y++) {
      odata[y]=ox[y]=oy[y]=oa[y]=0.0;
    }
    for (y=0 ;y < tailer.inNy  ;y++){
      DEBUGPRINT1("%d ",y);
      mrcPixelDataGet(in ,0 ,y ,0 ,&x ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataGet(in ,1 ,y ,0 ,&a ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataGet(in ,2 ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      DEBUGPRINT3("%f %f %f  ",x,a,data);
      if ( data != 0.0) { 
	lxaFitdataConvertTranse(ox ,oy ,oa ,odata ,size ,y ,&tailer);
	lxaFitdataConvertShift(ox ,oy ,oa ,odata ,size);
	lxaFitdataConvertSet(ox ,oy ,oa ,odata ,x, y ,a ,data ,size ,&tailer);
	lxaFitdataConvertOutput(out ,ox ,oa ,odata ,size ,y ,value ,&tailer ,0);
      } else {
	lxaFitdataConvertTranse(ox ,oy ,oa ,odata ,size ,y ,&tailer);
	lxaFitdataConvertOutput(out ,ox ,oa ,odata ,size ,y ,value ,&tailer ,0);
      }
    }   
  }
  DEBUGPRINT("END");
  mrcStatDataSet(out,0);
}

void lxaFitdataConvertTranse(double* ox ,double* oy ,double* oa, double* odata , int size ,int y ,mrcxaFitTailer* tailer)
{
/* variable */
  int iter;

/* begin */
  for (iter =0 ;iter < size ;iter++){
    if (odata[iter] != 0.0){
      if (y - oy[iter] < tailer->refNy){
	ox[iter] += sin(oa[iter] * PI / 180);
      } else {
	odata[iter] = 0.0;
      }
    }
  }
}
      
void lxaFitdataConvertShift(double* ox,double* oy ,double* oa,double* odata,int size)
{
/* variable */
  int iter;

/* begin */
  DEBUGPRINT4("%f %f %f %f \n",ox[5],oy[5],oa[5],odata[5]);
  for (iter =0 ;iter < size-1 ;iter++){
    odata[iter]=odata[iter+1];
    ox[iter]=ox[iter+1];
    oy[iter]=oy[iter+1];
    oa[iter]=oa[iter+1];
  }
  DEBUGPRINT4("%f %f %f %f \n",ox[4],oy[4],oa[4],odata[4]);
}

void lxaFitdataConvertSet(double* ox ,double* oy ,double* oa ,double* odata ,double x ,double y ,double a ,double data ,int size ,mrcxaFitTailer* tailer)
{
  ox[size-1] = x - sin(a*PI/180)*(tailer->refNy - 1)/2 ;
  oy[size-1] = y;
  oa[size-1] = a;
  odata[size-1] =data;
}

void lxaFitdataConvertOutput(mrcImage* out ,double* ox ,double* oa ,double* odata ,int size ,int y ,double value ,mrcxaFitTailer* tailer ,int mode)
{
/* variables */
  int iter;
  
/* begin */
  for (iter = 0 ;iter < size - 1 ;iter++){
    if (odata[iter] != 0.0){
      mrcPixelDataSet(out ,ox[iter]+(tailer->refNx - 1)/2 ,y ,0 ,odata[iter]*value ,mrcPixelRePart);
      DEBUGPRINT4("%d %f %f %f  ",iter ,ox[iter] ,oa[iter] ,odata[iter] );
    }
  }
  if (mode){
    mrcPixelDataSet(out ,ox[size-1]+(tailer->refNx - 1)/2 ,y ,0 ,odata[size-1]*value*5 ,mrcPixelRePart);
  }else{
    mrcPixelDataSet(out ,ox[size-1]+(tailer->refNx - 1)/2 ,y ,0 ,odata[size-1]*value ,mrcPixelRePart);
  }
  DEBUGPRINT4("%d %f %f %f \n ",size-1 ,ox[size-1] ,oa[iter] ,odata[size-1]);
}










