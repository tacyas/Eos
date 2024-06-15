/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMergebyside ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMergebyside
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMergebyside ver%I%; Date:%D% %Z%";
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
void lmrcImageMergebyside(mrcImage* out,mrcImage* in1,mrcImage* in2,double sep ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMergebysideInfo info;

/* variables */
	mrcImage in1;
	mrcImage in2;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in1 ,info.In1 ,"in main" ,0);
	mrcFileRead(&in2 ,info.In2 ,"in main" ,0);
	lmrcImageMergebyside(&out,&in1,&in2,info.sep,info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"----- mode -----\n");
fprintf(stdout,"1:Separater included\n");
}

void lmrcImageMergebyside(mrcImage* out,mrcImage* in1,mrcImage* in2 ,double sep ,int mode)
{
/* variables */
  int x,y,flag;
  double data;

/* Initializing */
  out->Header = in1->Header;
  out->HeaderN.x = in1->HeaderN.x + in2->HeaderN.x;
  flag=0;
  if (mode){
    (out->HeaderN.x) ++ ;
    flag=1;
  }
  mrcInit(out ,NULL);

/* begin */
  for (y = 0 ;y < in1->HeaderN.y ;y++){
    for (x = 0 ;x < in1->HeaderN.x ;x++){
      mrcPixelDataGet(in1 ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,x ,y ,0 ,data ,mrcPixelRePart );
    }
    mrcPixelDataSet(out ,in1->HeaderN.x ,y ,0 ,sep ,mrcPixelRePart );
    for (x = in1->HeaderN.x+flag ;x < out->HeaderN.x ;x++){
      mrcPixelDataGet(in2 ,x- in1->HeaderN.x-flag ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,x ,y ,0 ,data ,mrcPixelRePart );
    }
  }
  mrcStatDataSet(out,0);
}






