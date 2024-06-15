/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRefFFTConv2D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRefFFTConv2D
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRefFFTConv2D ver%I%; Date:%D% %Z%";
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
void lmrcRefFFTConv2D(mrcImage* out ,mrcImage* in);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageRefFFTConv2DInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	lmrcRefFFTConv2D(&out ,&in);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
void lmrcRefFFTConv2D(mrcImage* out ,mrcImage* in)
{
/* variables */
  int x,y,z,dp,dt,wt,t,p,x0,y0;
  double data;

/* initialization */
  mrcPixelDataGet(in ,0 ,0 ,-in->HeaderN.z / 2 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
  dp = (int)data;
  mrcPixelDataGet(in ,1 ,0 ,-in->HeaderN.z / 2 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
  dt = (int)data;
  mrcPixelDataGet(in ,2 ,0 ,-in->HeaderN.z / 2 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
  wt = (int)data;
  DEBUGPRINT3("%d ,%d ,%d \n",dp,dt,wt);
  out->Header = in->Header;
  out->HeaderN.z = 1;
  out->HeaderN.x = (in->HeaderN.x / 2+ 1)* (360 / dp) ;
  out->HeaderN.y = in->HeaderN.y * (wt / dt * 2 + 1) ;
  out->HeaderMode = mrcFloatImage ;
  out->HeaderStartN.x = out->HeaderStartN.y = out->HeaderStartN.z = 0; 
  mrcInit(out,NULL);
  z = 0;
  y0 = in->HeaderN.y / 2;

 
/* begin */
  for (t = 0 ;t <= wt/dt * 2 ;t++ ){
    x0 = 0;
    for (p = 0 ;p < 360/dp ;p++){
      z++;
      DEBUGPRINT1("%d ",z);
      for (y = - in->HeaderN.y / 2 ;y < in->HeaderN.y / 2  ;y++){
	for (x = 0 ;x <= in->HeaderN.x /2 ;x++){
	  mrcPixelDataGet(in  ,x    ,y    ,z ,&data ,mrcPixelMag ,mrcPixelHowNearest); 
	  mrcPixelDataSet(out ,x+x0 ,y+y0 ,0 ,data ,mrcPixelRePart);
	}
      }
      x0 += in->HeaderN.x / 2 + 1;
    }
    y0 += in->HeaderN.y;
  }      
  mrcStatDataSet(out,0);
}    

