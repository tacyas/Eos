/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImagepwzCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImagepwzCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImagepwzCorrelation ver%I%; Date:%D% %Z%";
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
void lmrcRefImageCorrelation(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int dy ,int mode );
void lmrcRefImageCorrelationByFFT(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int mode );
void lmrcImageyPad(mrcImage* out ,mrcImage* in ,int size);
void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefImagepwzCorrelationInfo info;
	
/* variables */
        mrcImage in;
        mrcImage out;
        mrcImage ref; 

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	mrcFileRead(&ref ,info.Ref ,"in main",0);
	if (info.mode){
	  lmrcRefImageCorrelationByFFT(&out ,&in ,&ref ,info.mode2);
	} else {
	  lmrcRefImageCorrelation(&out ,&in ,&ref ,info.dy ,info.mode2);
	}
	DEBUGPRINT("done ");
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}


void
additionalUsage()
{
}

void lmrcRefImageCorrelation(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int dy ,int mode )
{
/* variables */
  mrcImage tmpref,tmpimg;
  int sy,ey,y,z,oy;
  mrcRefHeader rhead;
  double c;
  
/* initialization */

  sy = 0;
  ey = in->HeaderN.y - ref->HeaderN.y ;
  out->Header = in->Header;
  out->HeaderN.x = ref->HeaderN.z - 1;
  out->HeaderN.y = (ey - sy )/dy +1;
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  lmrcRefHeaderGet(&rhead ,ref);
  lmrcRefHeaderSet(out ,&rhead);
  oy=0;
  
/* begin */
  if (mode){
    lmrcRefNormalization(ref);
  }
  for (y = sy ;y <= ey ; y += dy){
    fprintf(stderr,"%d ",y);
    lmrcImageRectangleGet(&tmpimg ,in ,0 ,y ,ref->HeaderN.x - 1 ,y + ref->HeaderN.y - 1);
    lmrcImageZ1Normalization(&tmpimg,0);
    for (z = 1 ;z < ref->HeaderN.z  ;z++ ){
      lmrc3DZ1ImgGet(&tmpref ,ref ,z);
      c = lmrcRef2DImgCorrelation(&tmpimg ,&tmpref );
      DEBUGPRINT2("%d %f ",z,c);
      mrcImageFree(&tmpref ,"lmrcRefImageCorrelation");      
      mrcPixelDataSet(out ,z-1 ,oy ,1 ,c ,mrcPixelRePart);
    }
    mrcImageFree(&tmpimg ,"lmrcRefImageCorrelation");  
    oy ++ ;
  }

  mrcStatDataSet(out,0);
}


void lmrcRefImageCorrelationByFFT(mrcImage* out ,mrcImage* in ,mrcImage* ref ,int mode )
{
/* variables */
  mrcImage tmpref1,tmpref2,tmpout;
  int sy,ey,y,z,oy;
  mrcRefHeader rhead;
  double c;
  
/* initialization */
  DEBUGPRINT("start ");
  sy = 0;
  ey = in->HeaderN.y - ref->HeaderN.y ;
  out->Header = in->Header;
  out->HeaderN.x = ref->HeaderN.z - 1;
  out->HeaderN.y = ey - sy ;
  out->HeaderN.z = 2;
  mrcInit(out,NULL);
  lmrcRefHeaderGet(&rhead ,ref);
  lmrcRefHeaderSet(out ,&rhead);
  oy=0;
  DEBUGPRINT("start ");
  
/* begin */
  if (mode){
    lmrcRefNormalization(ref);
  }
  for (z = 1 ;z < ref->HeaderN.z  ;z++ ){
    DEBUGPRINT1("%d ",z);
    lmrc3DZ1ImgGet(&tmpref1 ,ref ,z);
    lmrcImageyPad(&tmpref2 ,&tmpref1 ,in->HeaderN.y);
    mrcImageFree(&tmpref1 ,"in lmrcRefImageCorrelationByFFT"  );
    lmrcImageCorrelation(&tmpout ,in ,&tmpref2 ,16);
    mrcImageFree(&tmpref2 ,"in lmrcRefImageCorrelationByFFT"  );
    for (y = sy ;y < ey ; y ++){
      mrcPixelDataGet(&tmpout ,0 ,y ,0 ,&c ,mrcPixelRePart , mrcPixelHowNearest);
      mrcPixelDataSet(out ,z-1 ,y ,1 ,c ,mrcPixelRePart);
    }
    mrcImageFree(&tmpout ,"in lmrcRefImageCorrelationByFFT"  );
  }
  mrcStatDataSet(out,0);
}

void lmrcImageyPad(mrcImage* out ,mrcImage* in ,int size)
{
/* variables */
  int x,y;
  double data;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.y = size;
  mrcInit(out,0);

/* begin */
  for (y=0 ;y < in->HeaderN.y ;y++){
    for (x=0 ;x < in->HeaderN.x ;x++){
      mrcPixelDataGet(in ,x ,y ,0 ,&data ,mrcPixelRePart , mrcPixelHowNearest);
      mrcPixelDataSet(out ,x ,y ,0 ,data ,mrcPixelRePart);
    }
  }
  for (y=in->HeaderN.y ;y < out->HeaderN.y ;y++){
    for (x=0 ;x < in->HeaderN.x ;x++){
      mrcPixelDataSet(out ,x ,y ,0 ,0.0 ,mrcPixelRePart);
    }
  }
  mrcStatDataSet(out,0);
}
  





