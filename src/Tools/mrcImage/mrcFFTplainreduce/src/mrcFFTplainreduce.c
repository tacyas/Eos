/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTplainreduce ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTplainreduce
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTplainreduce ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototypes */
void lmrcFFTplainreduce(mrcImage* out ,mrcImage* in ,int pos ,double v ,int mode);

void
main(int argc, char* argv[]) 
{
	mrcFFTplainreduceInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);

/* begin */
	DEBUGPRINT("Program Start\n");
	lmrcFFTplainreduce(&out ,&in,info.Pos,info.Value,info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0:pos=z.\n");
	fprintf(stderr, "mode 1:pos=x.\n");
	fprintf(stderr, "mode 2:pos=y.\n");
}

void lmrcFFTplainreduce(mrcImage* out ,mrcImage* in ,int pos ,double v ,int mode)
{
/* variables */
  mrcImage infft;
  int X,Y,Z,flag;
  double rdata,idata;

/* begin */
  lmrcImageFFT(&infft,in,0);
  flag=0;
  if (infft.HeaderN.z==1) flag=1;

  switch (mode){
  case 0:
    Z=pos;
    for(Y = -infft.HeaderN.y / 2.0; Y < infft.HeaderN.y / 2.0; Y += 1){
      for(X = 0; X <= infft.HeaderN.x / 2.0; X += 1){
	mrcPixelDataGet(&infft, X, Y, Z, &rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&infft, X, Y, Z, &idata, mrcPixelImPart, mrcPixelHowNearest);
	mrcPixelDataSet(&infft, X, Y, Z, rdata*v, mrcPixelRePart);
	mrcPixelDataSet(&infft, X, Y, Z, idata*v, mrcPixelImPart);
      }
    }
    break;
  case 1:
    X=pos;
    for(Z = -infft.HeaderN.z / 2.0; Z < infft.HeaderN.z / 2.0 + flag; Z += 1){
      for(Y = -infft.HeaderN.y / 2.0; Y < infft.HeaderN.y / 2.0; Y += 1){
	mrcPixelDataGet(&infft, X, Y, Z, &rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&infft, X, Y, Z, &idata, mrcPixelImPart, mrcPixelHowNearest);
	mrcPixelDataSet(&infft, X, Y, Z, rdata*v, mrcPixelRePart);
	mrcPixelDataSet(&infft, X, Y, Z, idata*v, mrcPixelImPart);
      }
    }
    break;
  case 2:
    Y=pos;
    for(Z = -infft.HeaderN.z / 2.0; Z < infft.HeaderN.z / 2.0 + flag; Z += 1){
      for(X = 0; X <= infft.HeaderN.x / 2.0; X += 1){
	mrcPixelDataGet(&infft, X, Y, Z, &rdata, mrcPixelRePart, mrcPixelHowNearest);
	mrcPixelDataGet(&infft, X, Y, Z, &idata, mrcPixelImPart, mrcPixelHowNearest);
	mrcPixelDataSet(&infft, X, Y, Z, rdata*v, mrcPixelRePart);
	mrcPixelDataSet(&infft, X, Y, Z, idata*v, mrcPixelImPart);
      }
    }
    break;
  }
  mrcStatDataSet(&infft,0); 
  lmrcImageFFT(out,&infft,0);
}
  
