/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageUntwist ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageUntwist
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageUntwist ver%I%; Date:%D% %Z%";
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
void lmrcImageUntwist(mrcImage* out ,mrcImage* in ,double dp ,int mode);


int
main(int argc, char* argv[]) 
{
	mrcImageUntwistInfo info;

/* variables */
	mrcImage in;
        mrcImage out;
	double dp;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
        mrcFileRead(&in ,info.In ,"in main" ,0);
	dp=-info.dphi/(info.dz / in.HeaderLength.z);
	lmrcImageUntwist(&out ,&in ,dp ,0);
        mrcFileWrite(&out ,info.Out ,"in main" ,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageUntwist(mrcImage* out ,mrcImage* in ,double dp ,int mode)
{
/* variables */
  mrcImage tmpin ,tmpout;
  int z;
  
/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);

/* begin */
  for (z=0 ;z < in->HeaderN.z ;z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z);
    lmrcImageRotation2D(&tmpout, &tmpin, dp*z*RADIAN , 3);
    lmrc3DZ1ImgPut(out ,&tmpout ,z);
    mrcImageFree(&tmpin,"");
    mrcImageFree(&tmpout,"");
    DEBUGPRINT3("%d %f %f\n",z,dp,dp*RADIAN*z);
  }
  mrcStatDataSet(out,0);
}



