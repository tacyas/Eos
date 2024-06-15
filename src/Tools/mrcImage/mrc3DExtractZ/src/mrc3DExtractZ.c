/*
# mrc3DExtractZ.c  1.1
# The latest update : 07/30/96 at 17:52:17
#
#@(#) mrc3DExtractZ ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrc3DExtractZ
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrc3DExtractZ ver1.1; Date:96/07/30 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "mrcImage.h"

/* prototype */
void lmrc3DExtractZ(mrcImage* out ,mrcImage* in ,int zb ,int zt);

void
main(int argc, char* argv[]) 
{
	long status;
	mrc3DExtractZInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	lmrc3DExtractZ(&out ,&in ,info.ZB ,info.ZT);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrc3DExtractZ(mrcImage* out ,mrcImage* in ,int zb ,int zt)
{

/* variables */
  int    x,y,z;
  double data;

/* Initialization */
  if ( zt == -1 ) zt = in->HeaderN.z ;
  if ( (zt - zb) < 0 || zt > in->HeaderN.z || zb < 0){
    fprintf(stderr ,"ZT or ZB is not correct!");
    exit(EXIT_FAILURE);
  }
  out->Header = in->Header;
  out->HeaderN.z = zt - zb + 1;
  mrcInit(out,NULL);
  
/* begin */
  for (z = zb; z <= zt; z++){
    for (y = 0; y <= in->HeaderN.y ;y++){
      for (x = 0; x <= in->HeaderN.x ;x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataSet(out ,x ,y ,z-zb ,data, mrcPixelRePart);      
      }
    }
  }
  mrcStatDataSet(out,0);  
}

