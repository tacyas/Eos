/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefz1ImageCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefz1ImageCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefz1ImageCorrelation ver%I%; Date:%D% %Z%";
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
double lmrcRefz1ImageCorrelation(mrcImage* in,mrcImage* ref,int z,int mode);
double lmrcImageCorrelationByInnerProduct(mrcImage* in1 ,mrcImage* in2 ,int mode);

void
main(int argc, char* argv[]) 
{
	mrcRefz1ImageCorrelationInfo info;

/* variables */
        mrcImage in;
        mrcImage ref; 
	double cor;
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	mrcFileRead(&ref ,info.Ref ,"in main",0);
	DEBUGPRINT("read");
	cor=lmrcRefz1ImageCorrelation(&in,&ref,info.z,info.mode);	
	fprintf(stdout,"%g\n",cor);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

double lmrcRefz1ImageCorrelation(mrcImage* in,mrcImage* ref,int z,int mode)
{
/* variables */
  mrcImage tmpref;
  double c;
  
/* initialization */
  lmrc3DZ1ImgGet(&tmpref ,ref ,z);
  if (tmpref.HeaderN.x != ref->HeaderN.x || tmpref.HeaderN.y != ref->HeaderN.y){
    fprintf(stderr,"Image size is different!");
    exit(1);
  }
  c = lmrcImageCorrelationByInnerProduct(in ,&tmpref ,mode);
  return(c);
}

double lmrcImageCorrelationByInnerProduct(mrcImage* in1 ,mrcImage* in2 ,int mode)
{
/* variables */
  mrcImage ft1,ft2;
  int X,Y,Z;
  double rdata1,idata1,rdata2,idata2,f1,f2,nr1,nr2,ni1,ni2,dr,di,d,dp,tmp1,tmp2,tmp3,data;
/* begin */
  tmp1=tmp2=tmp3=0;
  lmrcImageFFT(&ft1,in1,0);
  lmrcImageFFT(&ft2,in2,0);

  for (X=0; X<=ft1.HeaderN.x/2.0; X++) {
    DEBUGPRINT1("%d ",X);
    for (Y=-ft1.HeaderN.y/2.0; Y<ft1.HeaderN.y/2.0; Y++) {
      DEBUGPRINT1("%d ",Y);
      for (Z=-ft1.HeaderN.z/2.0; Z<ft1.HeaderN.z/2.0; Z++) {
	DEBUGPRINT1("%d ",Z);
	mrcPixelDataGet(&ft1, X, Y, Z, &rdata1, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&ft1, X, Y, Z, &idata1, mrcPixelImPart, mrcPixelHowNearest);
	mrcPixelDataGet(&ft2, X, Y, Z, &rdata2, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&ft2, X, Y, Z, &idata2, mrcPixelImPart, mrcPixelHowNearest);
	switch (mode){
	case 0:
	  tmp1 += rdata1*rdata2 + idata1*idata2;
	  tmp2 += rdata1*rdata1 + idata1*idata1;
	  tmp3 += rdata2*rdata2 + idata2*idata2;
	  DEBUGPRINT("0 ");
	  break;
	case 1:
	  DEBUGPRINT("1 ");
	  f1 = rdata1*rdata1 + idata1*idata1;
	  f2 = rdata2*rdata2 + idata2*idata2;
	  if (f1 != 0 && f2 != 0 ){
	    f1=sqrt(f1);
	    f2=sqrt(f2);
	    tmp2 += f1*f2;
	    nr1=rdata1/f1;
	    ni1=idata1/f1;
	    nr2=rdata2/f2;
	    ni2=idata2/f2;
	    dr=nr1-nr2;
	    di=ni1-ni2;
	    if (dr != 0.0 ){
	      d=sqrt(dr*dr+di*di);
	      dp=2*asin(d/2);
	      tmp1 += f1*f2*dp;
	    }
	    DEBUGPRINT("1 ");
	  }
	  break;
	}
      }
    }
  }
  switch (mode){
  case 0:
    if (tmp2!=0 &&  tmp3!=0 ){
      data=tmp1/sqrt(tmp2*tmp3);
    }else{
      data=0.0;
    }
    break;
  case 1:
    if (tmp2!=0){
      data=tmp1/tmp2;
    }else{
      data=0.0;
    }
    break;
  }
  return(data);
}

 
