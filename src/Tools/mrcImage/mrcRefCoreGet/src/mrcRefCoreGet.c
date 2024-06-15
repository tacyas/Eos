/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefCoreGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefCoreGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefCoreGet ver%I%; Date:%D% %Z%";
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
void lmrcRefCoreImageGet(mrcImage* out ,mrcImage* in ,double Cutoff ,int mode);
void lmrcCoreImageGet(mrcImage* out ,mrcImage* in ,double Cutoff ,int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefCoreGetInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	mrcFileRead(&in ,info.In ,"in main" ,0); 

/* begin */       
	lmrcRefCoreImageGet(&out ,&in ,info.Cutoff ,info.mode);
 	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcRefCoreImageGet(mrcImage* out ,mrcImage* in ,double Cutoff ,int mode)
{
/* variables */
  mrcImage tmpin,tmpout;
  int z;

/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);
  lmrc3DZ1ImgGet(&tmpin ,in ,0);
  lmrc3DZ1ImgPut(out ,&tmpin ,0);

/* begin */
  for (z = 1 ;z < in->HeaderN.z ;z++){
    fprintf(stderr,"%d " ,z);
    lmrc3DZ1ImgGet(&tmpin ,in ,z);
    lmrcCoreImageGet(&tmpout ,&tmpin ,Cutoff ,mode);
    lmrc3DZ1ImgPut(out ,&tmpout ,z ); 
    mrcImageFree(&tmpin ,"in lmrcRefPhaseImageCreate");
    mrcImageFree(&tmpout ,"in lmrcRefPhaseImageCreate");
  }   
  mrcStatDataSet(out,0);
}

void lmrcCoreImageGet(mrcImage* out ,mrcImage* in ,double Cutoff ,int mode)
{
/* variables */
  int x,y;
  double data;
 
/* Initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);
  if (mode){
    Cutoff *= sqrt(lmrcRefSqrAverageZ1(in ,0) );
  }
  DEBUGPRINT1("%f ",Cutoff);
/* begin */
  for (x=0 ;x < in->HeaderN.x ;x++){
    for (y=0 ;y < in->HeaderN.y ;y++){
      mrcPixelDataGet(in ,x ,y ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      if ( fabs(data)<Cutoff ){
	data = 0.0;
      }
      mrcPixelDataSet(out ,x ,y ,0 ,data, mrcPixelRePart);
    }
  }
}
