/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCenterGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCenterGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCenterGet ver%I%; Date:%D% %Z%";
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

/* prototype */
void lmrcImageCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy);
void lmrcImageCenterGetByCubicConv(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy);
void lmrcRefCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy);
void lmrcRefCenterGetByCubicConv(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageCenterGetInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);


/* initialization */
	mrcFileRead(&in ,info.In ,"in main" ,0); 
	if (!info.flagNx){
	  info.Nx = (in.HeaderN.x % 2)?(in.HeaderN.x - 1):(in.HeaderN.x);
	}
	if (!info.flagNy){
	  info.Ny = (in.HeaderN.y % 2)?(in.HeaderN.y - 1):(in.HeaderN.y);
	}
	if (info.Nx > in.HeaderN.x || info.Ny > in.HeaderN.y){
	  fprintf(stderr,"Nx or Ny is larger than inputfile");
	  exit(EXIT_FAILURE);
	}
	DEBUGPRINT2("%d,%d \n",info.Nx,info.Ny);
	if (!info.flagCx){
	  info.Cx=( (float)in.HeaderN.x-1)/2;
	}
	if (!info.flagCy){
	  info.Cy=( (float)in.HeaderN.y-1)/2;
	}
	switch (info.mode2){
	case 0:
	  if (info.Nx != in.HeaderN.x || info.Ny != in.HeaderN.y){
	    if (info.mode){
	      lmrcImageCenterGetByCubicConv(&out ,&in ,info.Nx ,info.Ny ,info.Cx ,info.Cy);
	    } else {
	      lmrcImageCenterGet(&out ,&in ,info.Nx ,info.Ny ,info.Cx ,info.Cy);
	    }
	    DEBUGPRINT2("%d %d\n",out.HeaderN.x,out.HeaderN.y);
	    mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	  }else{
	    mrcFileWrite(&in ,info.Out ,"in main" ,0); 
	  }
	  break;
	case 1:
	  if (info.Nx != in.HeaderN.x || info.Ny != in.HeaderN.y){
	    if (info.mode){
	      lmrcRefCenterGetByCubicConv(&out ,&in ,info.Nx ,info.Ny ,info.Cx ,info.Cy);
	    } else {
	      lmrcRefCenterGet(&out ,&in ,info.Nx ,info.Ny ,info.Cx ,info.Cy);
	    }
	    DEBUGPRINT2("%d %d\n",out.HeaderN.x,out.HeaderN.y);
	    mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	  }else{
	    mrcFileWrite(&in ,info.Out ,"in main" ,0); 
	  }
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"----- mode -----\n");
fprintf(stdout,"0:No interpolation\n");
fprintf(stdout,"1:Cubic convolute\n");
fprintf(stdout,"----- mode 2 ----- \n");
fprintf(stdout,"0:Normal Image\n");
fprintf(stdout,"1:Ref Image\n");
}

void lmrcImageCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy)
{
/* variables */
  int x,y,ix,iy;
  double data;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  mrcInit(out,NULL);

/* begin */
  ix = floor( (float)Cx - (float)(Nx-1)/2.0 );
  iy = floor( (float)Cy - (float)(Ny-1)/2.0 );
  DEBUGPRINT2("%d %d \n",ix,iy);
  for (x = ix ;x < ix+Nx ;x++){
    for (y = iy ;y < iy+Ny ;y++){
      mrcPixelDataGet(in ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,x-ix ,y-iy ,0 ,data, mrcPixelRePart);
    }
  }
  mrcStatDataSet(out,0);
}


void lmrcImageCenterGetByCubicConv(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy)
{
/* variables */
  double data,x,y,ix,iy;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  mrcInit(out,NULL);

/* begin */
  ix =  (float)Cx - (float)(Nx-1)/2.0;
  iy =  (float)Cy - (float)(Ny-1)/2.0;
  for (x = ix ;x < ix+Nx ;x+=1.0){
    for (y = iy ;y < iy+Ny ;y+=1.0){
      data=mrcImagecubicConvolutionInterpolation(in,x,y);
      mrcPixelDataSet(out ,x-ix ,y-iy ,0 ,data, mrcPixelRePart);
    }
  }
}

void lmrcRefCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy)
{
/* variables */
  int z;
  mrcImage tmpin,tmpout;
  mrcRefHeader ref;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  mrcInit(out,NULL);

/* begin */
  lmrcRefHeaderGet(&ref ,in);
  lmrcRefHeaderSet(out ,&ref);
  for (z=1 ; z<out->HeaderN.z ; z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z); 
    lmrcImageCenterGet(&tmpout ,&tmpin ,Nx ,Ny ,Cx ,Cy);
    lmrc3DZ1ImgPut(out ,&tmpout, z);
    mrcImageFree(&tmpout,"");
    mrcImageFree(&tmpin,"");
  }
  mrcStatDataSet(out,0);
}

void lmrcRefCenterGetByCubicConv(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,float Cx ,float Cy)
{
/* variables */
  int z;
  mrcImage tmpin,tmpout;
  mrcRefHeader ref;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  mrcInit(out,NULL);

/* begin */
  lmrcRefHeaderGet(&ref ,in);
  lmrcRefHeaderSet(out ,&ref);
  for (z=1 ; z<out->HeaderN.z ; z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z); 
    lmrcImageCenterGetByCubicConv(&tmpout ,&tmpin ,Nx ,Ny ,Cx ,Cy);
    lmrc3DZ1ImgPut(out ,&tmpout, z);
    mrcImageFree(&tmpout,"");
    mrcImageFree(&tmpin,"");
  }
  mrcStatDataSet(out,0);
}
