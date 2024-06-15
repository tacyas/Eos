/*
# mrcImageRefConv2D.c  1.3
# The latest update : 08/27/96 at 16:19:17
#
#@(#) mrcImageRefConv2D ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageRefConv2D
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageRefConv2D ver1.3; Date:96/08/27 @(#)";
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
void lmrcRefConvImg2D(mrcImage* out ,mrcImage* in);
void lmrcRefConvFou2D(mrcImage* out ,mrcImage* in ,int mode);
void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageRefConv2DInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	switch(in.HeaderMode ){
 	case mrcFloatImage:
	  lmrcRefConvImg2D(&out ,&in);
	  break;
	case mrcComplexFloatFT:
	  lmrcRefConvFou2D(&out ,&in ,info.mode);  
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcRefConvImg2D(mrcImage* out ,mrcImage* in)
{
/* variables */
  int x,y,z,x0,y0;
  mrcRefDegCoordinate a,w,p;
  double data;
  mrcRefHeader rheader;

/* initialization */
  lmrcRefHeaderGet(&rheader ,in);
  out->Header = in->Header;
  out->HeaderN.z = 2;
  out->HeaderN.x = in->HeaderN.x * (rheader.wp / rheader.dp * 2 + 1);
  out->HeaderN.y = in->HeaderN.y * (rheader.ww / rheader.dw * 2 + 1) * (rheader.wa / rheader.da * 2 + 1) ;
  mrcInit(out,NULL);
  lmrcRefHeaderSet(out ,&rheader);
  x0 = 0;
  y0 = 0;

/* begin */
  for (a = rheader.ia-rheader.wa ;a <= rheader.ia+rheader.wa  ;a += rheader.da){
      for (w = rheader.iw-rheader.ww ;w <= rheader.iw+rheader.ww  ;w += rheader.dw){
	x0 = 0;
	for (p = rheader.ip-rheader.wp ;p <= rheader.ip+rheader.wp  ;p += rheader.dp){
	  z = lmrcRefGetzCordinate(p,w,a, &rheader) ;
	  for (y = 0 ;y < in->HeaderN.y ;y++){
	  for (x = 0 ;x < in->HeaderN.x ;x++){
	    mrcPixelDataGet(in  ,x    ,y    ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
	    mrcPixelDataSet(out ,x+x0 ,y+y0 ,1 ,data ,mrcPixelRePart);
	  }
	}
	x0 += in->HeaderN.x;
      }
      y0 += in->HeaderN.y;
    }      
  }
  mrcStatDataSet(out,0);
}    


void lmrcRefConvFou2D(mrcImage* out ,mrcImage* in ,int mode)
{
}



