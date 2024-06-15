/*
# mrcRefCorrelationConv.c  1.1
# The latest update : 08/28/96 at 15:12:08
#
#@(#) mrcRefCorrelationConv ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcRefCorrelationConv
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcRefCorrelationConv ver1.1; Date:96/08/28 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

void lmrcPhiOmegaCor(mrcImage* out ,mrcImage* in );
void lmrcPhiAlphaCor(mrcImage* out ,mrcImage* in );
void lmrcOmegaAlphaCor(mrcImage* out ,mrcImage* in );
void lmrcRefCorrelationGetRefCordinate(int* phi ,int* omega ,int* alpha ,int x ,mrcImage* in ,mrcRefCorHeader* header);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefCorrelationConvInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	switch(info.mode){
	case 0:
	  lmrcPhiOmegaCor(&out ,&in );
	  break;
	case 1:
	  lmrcPhiAlphaCor(&out ,&in );
	  break;
	case 2:
	  lmrcOmegaAlphaCor(&out ,&in ); 
	}   
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcPhiOmegaCor(mrcImage* out ,mrcImage* in )
{
/* variables */
  double data;
  mrcRefDegCoordinate a1,p1,w1,p2,w2;
  int x,y;
  mrcRefCorHeader header;

/* initialization */
  DEBUGPRINT("header \n");
  lmrcRefCorHeaderGet(&header ,in);

/* Out Header Create */
  out->Header = in->Header;
  out->HeaderN.x = header.wp/header.dp * 2 + 1;
  out->HeaderN.y = header.ww/header.dw * 2 +1;
  out->HeaderN.z = in->HeaderN.x+1;
  DEBUGPRINT("init \n");
  mrcInit(out ,NULL);
  lmrcRefCorHeaderSet(out ,&header);
  DEBUGPRINT6("%d,%d,%d,%d,%d,%d \n",header.dp,header.dw,header.da,header.wp,header.ww,header.wa);
  
/* begin */
  for (x = 0 ;x < in->HeaderN.x ;x++){
    for (w2 = header.iw-header.ww ;w2 <= header.iw+header.ww ;w2+=header.dw){
      for (p2 = header.ip-header.wp ;p2 <= header.ip+header.wp ;p2+=header.dp){
	/*	    DEBUGPRINT5("%d %d %d %d %d \n",a1,w1,p1,w2,p2);  */
	lmrcRefCorrelationGetRefxCordinate(&p1,&w1,&a1,x ,in ,&header );
/* 	DEBUGPRINT5("%d %d %d %d %d \n",a1,w1,p1,w2,p2); */
	y = lmrcRefCorrelationGetCordinate(p2,w2,a1,&header);
	mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
	mrcPixelDataSet(out ,(p2-header.ip+header.wp)/header.dp ,(w2-header.iw+header.ww)/header.dw ,x+1 ,data ,mrcPixelRePart);
/* 	DEBUGPRINT3("%d %d %d\n",(p2-header.ip+header.wp)/header.dp,(w2-header.iw+header.ww)/header.dw ,x+1 ); */
      }
    }
  }
  mrcStatDataSet(out ,0);
}


void lmrcPhiAlphaCor(mrcImage* out ,mrcImage* in )
{
/* variables */
  double data;
  mrcRefDegCoordinate a1,p1,w1,p2,a2;
  int x,y;
  mrcRefCorHeader header;

/* initialization */
  DEBUGPRINT("header \n");
  lmrcRefCorHeaderGet(&header ,in);

/* Out Header Create */
  out->Header = in->Header;
  out->HeaderN.x = header.wp/header.dp * 2 + 1;
  out->HeaderN.y = header.wa/header.da * 2 + 1;
  out->HeaderN.z = in->HeaderN.x+1;
  DEBUGPRINT("init \n");
  mrcInit(out ,NULL);
  lmrcRefCorHeaderSet(out ,&header);
  DEBUGPRINT6("%d,%d,%d,%d,%d,%d \n",header.dp,header.dw,header.da,header.wp,header.ww,header.wa);
  
/* begin */
  for (x = 0 ;x < in->HeaderN.x ;x++){
    for (a2 = header.ia-header.wa ;a2 <= header.ia+header.wa ;a2+=header.da){
      for (p2 = header.ip-header.wp ;p2 <= header.ip+header.wp ;p2+=header.dp){
	/*	    DEBUGPRINT5("%d %d %d %d %d \n",a1,w1,p1,w2,p2);  */
	lmrcRefCorrelationGetRefxCordinate(&p1,&w1,&a1,x ,in ,&header );
/* 	DEBUGPRINT5("%d %d %d %d %d \n",a1,w1,p1,w2,p2); */
	y = lmrcRefCorrelationGetCordinate(p2,w1,a2,&header);
	mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
	mrcPixelDataSet(out ,(p2-header.ip+header.wp)/header.dp ,(a2-header.ia+header.wa)/header.da ,x+1 ,data ,mrcPixelRePart);
/* 	DEBUGPRINT3("%d %d %d\n",(p2-header.ip+header.wp)/header.dp,(w2-header.iw+header.ww)/header.dw ,x+1 ); */
      }
    }
  }
  mrcStatDataSet(out ,0);
}


void lmrcOmegaAlphaCor(mrcImage* out ,mrcImage* in )
{
/* variables */
  double data;
  mrcRefDegCoordinate a1,p1,w1,w2,a2;
  int x,y;
  mrcRefCorHeader header;

/* initialization */
  DEBUGPRINT("header \n");
  lmrcRefCorHeaderGet(&header ,in);

/* Out Header Create */
  out->Header = in->Header;
  out->HeaderN.x = header.wa/header.da * 2 + 1;
  out->HeaderN.y = header.ww/header.dw * 2 + 1;
  out->HeaderN.z = in->HeaderN.x+1;
  DEBUGPRINT("init \n");
  mrcInit(out ,NULL);
  lmrcRefCorHeaderSet(out ,&header);
  DEBUGPRINT6("%d,%d,%d,%d,%d,%d \n",header.dp,header.dw,header.da,header.wp,header.ww,header.wa);
  
/* begin */
  for (x = 0 ;x < in->HeaderN.x ;x++){
    for (w2 = header.iw-header.ww ;w2 <= header.iw+header.ww ;w2+=header.dw){
      for (a2 = header.ia-header.wa ;a2 <= header.ia+header.wa ;a2+=header.da){
	/*	    DEBUGPRINT5("%d %d %d %d %d \n",a1,w1,p1,w2,p2);  */
	lmrcRefCorrelationGetRefxCordinate(&p1,&w1,&a1,x ,in ,&header );
/* 	DEBUGPRINT5("%d %d %d %d %d \n",a1,w1,p1,w2,p2); */
	y = lmrcRefCorrelationGetCordinate(p1,w2,a2,&header);
	mrcPixelDataGet(in ,x ,y ,1 ,&data ,mrcPixelRePart ,mrcPixelHowNearest); 
	mrcPixelDataSet(out ,(w2-header.iw+header.ww)/header.dw ,(a2-header.ia+header.wa)/header.da ,x+1 ,data ,mrcPixelRePart);
/* 	DEBUGPRINT3("%d %d %d\n",(p2-header.ip+header.wp)/header.dp,(w2-header.iw+header.ww)/header.dw ,x+1 ); */
      }
    }
  }
  mrcStatDataSet(out ,0);
}




