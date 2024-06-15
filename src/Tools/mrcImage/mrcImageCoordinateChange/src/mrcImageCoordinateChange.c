/*
# mrcImageCoordinateChange.c  1.1
# The latest update : 12/04/96 at 17:13:53
#
#@(#) mrcImageCoordinateChange ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageCoordinateChange
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageCoordinateChange ver1.1; Date:96/12/04 @(#)";
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
void lmrcImageCoordinateChange(mrcImage* out ,mrcImage* in ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageCoordinateChangeInfo info;

/* variables */
        mrcImage in;
        mrcImage out; 

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
/* begin */
        mrcFileRead(&in ,info.In ,"in main" ,0);
        lmrcImageCoordinateChange(&out ,&in ,info.mode);
        mrcFileWrite(&out ,info.Out ,"in main" ,0);   
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---- mode ----\n");
fprintf(stdout,"0: (x,y,z)->(z,x,y)\n");
}

void lmrcImageCoordinateChange(mrcImage* out ,mrcImage* in ,int mode)
{

/* variables */
  int x,y,z;
  double data;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = in->HeaderN.z;
  out->HeaderN.y = in->HeaderN.x;
  out->HeaderN.z = in->HeaderN.y;
  mrcInit(out,NULL);

/* begin */
  for (x=0 ;x < in->HeaderN.x ;x++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      for (z=0 ;z < in->HeaderN.z ;z++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataSet(out,z ,x ,y ,data, mrcPixelRePart); 
      }
    }
  }
  mrcStatDataSet(out,0);
}
