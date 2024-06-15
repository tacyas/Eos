/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcMirrorImageCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcMirrorImageCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcMirrorImageCreate ver%I%; Date:%D% %Z%";
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
void lmrcMirrorImageCreate(mrcImage* out ,mrcImage* in ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcMirrorImageCreateInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

	/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	mrcFileRead(&in ,info.In ,"in main" ,0); 
	lmrcMirrorImageCreate(&out ,&in ,info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"------ mode ------\n");
fprintf(stdout,"0:Normal image\n");
fprintf(stdout,"1:Ref image\n");
}

void lmrcMirrorImageCreate(mrcImage* out ,mrcImage* in ,int mode)
{
/* variables */
  int x,y,z;
  double data;

/* Initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);

/* begin */
  for (y = 0 ;y < in->HeaderN.y ;y++){
    for (x = 0 ;x < in->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      if (mode){
	mrcPixelDataSet(out ,x ,y ,0 ,data, mrcPixelRePart);
      } else {
	mrcPixelDataSet(out ,in->HeaderN.x -x -1 ,y ,0 ,data, mrcPixelRePart);
      }
    }
  }
  for (z = 1 ;z < in->HeaderN.z ;z++){
    for (y = 0 ;y < in->HeaderN.y ;y++){
      for (x = 0 ;x < in->HeaderN.x ;x++){
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataSet(out ,in->HeaderN.x -x -1 ,y ,z ,data, mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(out ,0);
}
    


