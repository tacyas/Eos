/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageScalarAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageScalarAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageScalarAdd ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

void lmrcImageScalarAdd(mrcImage* out ,mrcImage* in ,double v ,int mode);

void
main(int argc, char* argv[]) 
{
  /* variables */
	mrcImageScalarAddInfo info;
	mrcImage in,out;
	double data;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
  /* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT("Program Start\n");

	if (info.mode){
	  mrcPixelDataGet(&in,info.x,info.y,info.z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataSet(&in,info.x,info.y,info.z,data+info.Value ,mrcPixelRePart);
	  mrcStatDataSet(&in,0);
	  
	  mrcFileWrite(&in ,info.Out ,"in main" ,0);
	} else {
	  lmrcImageScalarAdd(&out,&in,info.Value,info.mode);
	  mrcFileWrite(&out ,info.Out ,"in main" ,0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0:Scalar value is added to each pixel.\n");
	fprintf(stderr, "mode 1:Scalar value is added to one pixel.\n");
}


void lmrcImageScalarAdd(mrcImage* out ,mrcImage* in ,double v ,int mode)
{
  int x,y,z;
  double data;

/* begin */
  out->Header = in->Header;
  mrcInit(out,0);

  for (z=0 ;z<in->HeaderN.z ;z++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (x=0 ;x<in->HeaderN.x ;x++){
	mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	data += v ;
	mrcPixelDataSet(out,x,y,z,data ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(out,0);  
}
