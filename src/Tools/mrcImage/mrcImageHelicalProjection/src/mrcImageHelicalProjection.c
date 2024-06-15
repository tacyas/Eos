/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHelicalProjection ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHelicalProjection
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageHelicalProjection ver%I%; Date:%D% %Z%";
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

/* prototypes */
void lmrcImageHelicalProjection(mrcImage* out ,mrcImage* in ,double dp ,int mode);
void lmrcImageProjection(mrcImage *out ,mrcImage *in ,int mode );

void
main(int argc, char* argv[]) 
{
	mrcImageHelicalProjectionInfo info;

/* variables */
        mrcImage in;
        mrcImage out;
	double dp;
 
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
        mrcFileRead(&in ,info.In ,"in main" ,0);
	dp=-info.dphi/(info.dz / in.HeaderLength.z);
	lmrcImageHelicalProjection(&out ,&in ,dp ,0);
        mrcFileWrite(&out ,info.Out ,"in main" ,0);
 	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageHelicalProjection(mrcImage* out ,mrcImage* in ,double dp ,int mode)
{
/* variables */
  mrcImage tmpin ,tmpout,untwist;
  int z;
  mrcImageParaTypeRealCoord dummy;

/* initialization */
  untwist.Header = in->Header;
  mrcInit(&untwist,NULL);

/* begin */
  for (z=0 ;z < in->HeaderN.z ;z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z);
    lmrcImageRotation2D(&tmpout, &tmpin, dp*z*RADIAN , 2);
    lmrc3DZ1ImgPut(&untwist ,&tmpout ,z);
    mrcImageFree(&tmpin,"");
    mrcImageFree(&tmpout,"");
    DEBUGPRINT3("%d %f %f\n",z,dp,dp*RADIAN*z);
  }
  lmrcImageProjection(out,&untwist,0); 
  /*
  dummy.x=dummy.y=dummy.z=0;
  out->Header=in->Header;
  mrcInit(out,NULL);
  lmrcImageCopy(out,&untwist,dummy);
  */
  mrcStatDataSet(out,0);
}

void lmrcImageProjection(mrcImage *out ,mrcImage *in ,int mode )
{
/* variables */
  int x,y,z;
  double data,dataout;

/* begin */
  switch(mode) {
  case 1: {
    out->Header = in->Header;
    out->HeaderN.x = in->HeaderN.y;
    out->HeaderN.y = in->HeaderN.z;
    out->HeaderN.z = 1.0;
    mrcInit(out, NULL);
    for(x=0; x<in->HeaderN.x; x++) {
      for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
	  mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(out, y, z, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataSet(out, y, z, 0.0, dataout+data, mrcPixelRePart);
	}
      }
    }
    break;
  }
  case 0: {
    out->Header = in->Header;
    out->HeaderN.x = in->HeaderN.x;
    out->HeaderN.y = in->HeaderN.y;
    out->HeaderN.z = 1.0;
    mrcInit(out, NULL);
    for(x=0; x<in->HeaderN.x; x++) {
      for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
	  mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(out, x, y, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataSet(out, x, y, 0.0, dataout+data, mrcPixelRePart);
	}
      }
    }
    break;
  }
  case 2: {
    out->Header = in->Header;
    out->HeaderN.x = in->HeaderN.z;
    out->HeaderN.y = in->HeaderN.x;
    out->HeaderN.z = 1.0;
    mrcInit(out, NULL);
    for(x=0; x<in->HeaderN.x; x++) {
      for(y=0; y<in->HeaderN.y; y++) {
	for(z=0; z<in->HeaderN.z; z++) {
	  mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(out, z, x, 0.0, &dataout, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataSet(out, z, x, 0.0, dataout+data, mrcPixelRePart);
	}
      }
    }
    break;
  }
  default: {
    fprintf(stderr, "Not supported Mode: %d\n", mode);
  }
  } 
  mrcStatDataSet(out,0);
}
