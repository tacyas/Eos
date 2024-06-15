/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcMask ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcMask
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcMask ver%I%; Date:%D% %Z%";
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
void lmrcMask1D(mrcImage* out ,mrcImage* in ,double v1x ,int sizeX ,int init ,int fn ,int mode ,int exnum);
void lmrcMask2D(mrcImage* out ,mrcImage* in ,mrcMaskInfo* info);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcMaskInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage tmp;
	int flag;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	mrcFileRead(&in ,info.In ,"in main" ,0);

/* begin */
	flag = 0;
	if (in.HeaderMode==2){
	  lmrcImageFFT(&tmp ,&in ,0);
	  flag = 1;
	  in = tmp;
	}
	if (info.mode){
	  lmrcMask1D(&out ,&in ,info.v1x ,info.sizeX ,info.inum ,info.num ,info.mode ,info.exnum);
	} else {
	  lmrcMask2D(&out ,&in ,&info);
	}
	if (flag) {
	  mrcImageFree(&tmp,"main");
	  lmrcImageFFT(&tmp ,&out ,0);
	  out = tmp;
	}
 	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---- mode ----\n");
fprintf(stdout,"0:2D Image\n");
fprintf(stdout,"1:1D Image\n");
fprintf(stdout,"2:1D Image included extra number.\n");
}

void lmrcMask1D(mrcImage* out ,mrcImage* in ,double v1x ,int sizeX ,int init ,int fn ,int mode ,int exnum)
{
/* variables */
  int X,tmpsize,n;
  double data,Xi,d,data2;
  
/* initialization */
  out->Header = in->Header;
  mrcInit(out ,0);
  v1x=fabs(v1x);
  v1x *= in->HeaderN.x * in->HeaderLength.x ;
  DEBUGPRINT1("%f ",v1x);
  tmpsize = (sizeX-1);
  d = tmpsize/2;
  if (fn == 0){
    fn = out->HeaderN.x ;
  }

/* begin */
  n = 0;
  Xi = 0;
  while (Xi+v1x+tmpsize <= in->HeaderN.x/2 ){
    Xi += v1x;
    if ( (n >= init-1 && n < fn) || (mode==2 && n==exnum-1) || (mode==3 && n<fn ) ){
      for (X=floor(Xi+0.5)-tmpsize ;X<=floor(Xi+0.5)+tmpsize ;X++){
	DEBUGPRINT1("%d ",X);
	mrcPixelDataGet(in ,X ,0 ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataGet(out ,X ,0 ,0 ,&data2 ,mrcPixelRePart ,mrcPixelHowNearest);
	data *= exp(- (X-Xi)*(X-Xi) /d /d);
	DEBUGPRINT1("%f ", data );
	if (mode==3 && n < init-1){
	  data *= 0.9;
	  DEBUGPRINT1("%f ", data );
/*	  if (n==1){
	    data *= 0.5;
	    DEBUGPRINT1("%f ", data );
	  }  */
	}
	data += data2;
	mrcPixelDataSet(out ,X ,0 ,0 ,data, mrcPixelRePart);
	mrcPixelDataGet(in ,X ,0 ,0 ,&data ,mrcPixelImPart ,mrcPixelHowNearest);
	mrcPixelDataGet(out ,X ,0 ,0 ,&data2 ,mrcPixelImPart ,mrcPixelHowNearest);      
	DEBUGPRINT1("%f ", data );
	if (mode==3 && n < init-1){
	  data *= 0.9;
	  DEBUGPRINT1("%f ", data );
/*	  if (n==1){
	    data *= 0.5;
	    DEBUGPRINT1("%f ", data );
	  }  */	  
	}
	data *= exp( -(X-Xi)*(X-Xi) /d /d); 
	data += data2;
	mrcPixelDataSet(out ,X ,0 ,0 ,data, mrcPixelImPart);
      }
    } 
    n++;
  }
  Xi += v1x;
  if (n < fn){
    for (X=floor(Xi+0.5)-tmpsize ;X<= in->HeaderN.x/2 ;X++){
      DEBUGPRINT1(" %d ",X);
      mrcPixelDataGet(in ,X ,0 ,0 ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,0 ,0 ,data, mrcPixelRePart);
      mrcPixelDataGet(in ,X ,0 ,0 ,&data ,mrcPixelImPart ,mrcPixelHowNearest);
      mrcPixelDataSet(out ,X ,0 ,0 ,data, mrcPixelImPart);
    }
  }
  mrcStatDataSet(out,0);
}


void lmrcMask2D(mrcImage* out ,mrcImage* in ,mrcMaskInfo* info)
{
}

