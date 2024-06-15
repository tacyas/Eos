/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRectangleGetByCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRectangleGetByCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRectangleGetByCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

/* prototype */
void lmrcImageRectangleGetByCorrelationPosEst(int* ox ,int* oy ,mrcImage* out ,mrcImage* in ,mrcImage* ref);
void lmrcImageRectangleGetByCorrelationPosEstByFFT(int* ox ,int* oy ,mrcImage* out ,mrcImage* in ,mrcImage* ref);
void lmrcImageRectangleGetByCorrelation(mrcImage* out,mrcImage* in,mrcImage* ref,int ix,int iy,int Nx,int Ny);


void
main(int argc, char* argv[]) 
{
	mrcImageRectangleGetByCorrelationInfo info;

/* variables */
        mrcImage in;
        mrcImage out;
        mrcImage ref; 
	mrcImage cor;
	int x,y;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	mrcFileRead(&ref ,info.Ref ,"in main",0);
	if (!info.mode){
	  lmrcImageRectangleGetByCorrelationPosEst(&x ,&y ,&cor ,&in ,&ref);
	} else {
	  lmrcImageRectangleGetByCorrelationPosEstByFFT(&x ,&y ,&cor ,&in ,&ref);
	}
	if (info.Nx==0) info.Nx=ref.HeaderN.x;
	if (info.Ny==0) info.Ny=ref.HeaderN.y;
	lmrcImageRectangleGetByCorrelation(&out,&in,&ref,x,y,info.Nx,info.Ny);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageRectangleGetByCorrelationPosEst(int* ox ,int* oy ,mrcImage* out ,mrcImage* in ,mrcImage* ref)
{
/* variables */
  mrcImage tmpimg;
  int sy,ey,sx,ex,x,y;
  double max;
  double c;
  
/* initialization */
  sx=0;
  ex = in->HeaderN.x - ref->HeaderN.x ;
  sy=0;
  ey = in->HeaderN.y - ref->HeaderN.y ;
  out->Header = in->Header;
  mrcInit(out,NULL);
  lmrcImageZ1Normalization(ref,0);
  max=-1e+10;
 
/* begin */
  for (y = sy ;y <= ey ; y ++){
    for (x = sx ;x <= ex ; x ++){
      lmrcImageRectangleGet(&tmpimg ,in ,x ,y ,x + ref->HeaderN.x - 1 ,y + ref->HeaderN.y - 1);   
      lmrcImageZ1Normalization(&tmpimg,0);
      c = lmrcRef2DImgCorrelation(&tmpimg ,ref );
      DEBUGPRINT3("%d %d %g \n ",x,y,c);
      mrcPixelDataSet(out ,x ,y ,0 ,c ,mrcPixelRePart);
      if (c > max){
	max=c;
	*ox=x;
	*oy=y;
      }
      mrcImageFree(&tmpimg ,"");
    }
  }
  fprintf(stdout,"start %d %d %g\n",*ox,*oy,max);
}

void lmrcImageRectangleGetByCorrelationPosEstByFFT(int* ox ,int* oy ,mrcImage* out ,mrcImage* in ,mrcImage* ref)
{
}

void lmrcImageRectangleGetByCorrelation(mrcImage* out,mrcImage* in,mrcImage* ref,int ix,int iy,int Nx,int Ny)
{
/* variables */
  float cx,cy;
  int sx,sy,ex,ey;
/* begin */
  cx=(ix+ref->HeaderN.x-1)/2;
  cy=(iy+ref->HeaderN.y-1)/2;
  sx=floor(cx - (Nx-1)/2 +0.5);
  sy=floor(cy - (Ny-1)/2 +0.5);
  ex=floor(cx + (Nx-1)/2 +0.5);
  ey=floor(cy + (Ny-1)/2 +0.5);
  lmrcImageRectangleGet(out ,in ,sx ,sy ,ex ,ey);
  if (sx < 0) fprintf(stdout,"error x > %d\n",-sx);
  if (ex > in->HeaderN.x-1 ) fprintf(stdout,"error x >%d \n",Nx-ex+in->HeaderN.x-2);
  if (sy < 0) fprintf(stdout,"error y > %d\n",-sy);
  if (ey > in->HeaderN.y-1 ) fprintf(stdout,"error y >%d \n",Ny-ey+in->HeaderN.y-2);
}


