/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefCorModify ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefCorModify
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefCorModify ver%I%; Date:%D% %Z%";
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
void lmrcRefCorAbsolute(mrcImage* out ,mrcImage* in);
void lmrcRefCorAbsNormalizeByMax(mrcImage* out ,mrcImage* in);
double lmrcRefCorMaxFind(mrcImage* in ,int x ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefCorModifyInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	DEBUGPRINT("init0 \n");
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("start \n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT3("%d %d %d ",in.HeaderN.x ,in.HeaderN.y ,in.HeaderN.z);
	if (info.mode) {
	  DEBUGPRINT("ABSNOR \n");
	  lmrcRefCorAbsNormalizeByMax(&out ,&in);
	} else {
	  DEBUGPRINT("ABS \n");
	  lmrcRefCorAbsolute(&out ,&in);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcRefCorAbsolute(mrcImage* out ,mrcImage* in)
{
/* variables */
  mrcRefCorHeader tmp; 
  int x,y;
  double data;
/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);
  DEBUGPRINT("headerGet\n");
  lmrcRefCorHeaderGet(&tmp ,in);
  DEBUGPRINT3("%d %d %d ",in->HeaderN.x ,in->HeaderN.y ,in->HeaderN.z);
  lmrcRefCorHeaderSet(out ,&tmp); 

/* begin */
  for (x=0 ;x < in->HeaderN.x ;x++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      DEBUGPRINT1("%f ",data);
      data = fabs(data);
      DEBUGPRINT1("%f   ",data);
      mrcPixelDataSet(out ,x ,y ,1 ,data ,mrcPixelRePart );
    }
  }
  mrcStatDataSet(out,0);
}

void lmrcRefCorAbsNormalizeByMax(mrcImage* out ,mrcImage* in)
{
/* variables */
  mrcRefCorHeader tmp;
  int x,y;
  double data,max;
 
/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);
  lmrcRefCorHeaderGet(&tmp ,in);
  lmrcRefCorHeaderSet(out,&tmp);

/* begin */
  for (x=0 ;x < in->HeaderN.x ;x++){
    max =lmrcRefCorMaxFind(in ,x ,1);
    for (y=0 ;y < in->HeaderN.y ;y++){
      mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      data = fabs(data) / max;
      mrcPixelDataSet(out ,x ,y ,1 ,data ,mrcPixelRePart );
    }
  }
  mrcStatDataSet(out,0);
}

double lmrcRefCorMaxFind(mrcImage* in ,int x ,int mode)
{
/* variables */
  int y;
  double data,max;

/* begin */
  mrcPixelDataGet(in ,x ,0 ,1 ,&max ,mrcPixelRePart ,mrcPixelHowNearest);
  if (mode == 1){
    max = fabs(max);
  }
  for (y=1 ;y < in->HeaderN.y ;y++){
    mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
    if (mode == 1){
      data = fabs(data);
    }
    max = MAX(max ,data);
  }
  return(max);
}
