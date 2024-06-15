/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHelicalMaskingBy2DImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHelicalMaskingBy2DImage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageHelicalMaskingBy2DImage ver%I%; Date:%D% %Z%";
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
void lmrcImageHelicalMasking(mrcImage* out, mrcImage* in, mrcImage* mask, double dp, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageHelicalMaskingBy2DImageInfo info;

/* variables */
        mrcImage in;
        mrcImage out;
        mrcImage mask;
	double dp;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
        mrcFileRead(&in ,info.In ,"in main" ,0);
        mrcFileRead(&mask ,info.Mask ,"in main" ,0);
	
/* begin */
	DEBUGPRINT("Program Start\n");
	dp=-info.dphi/(info.dz / in.HeaderLength.z);
	lmrcImageHelicalMasking(&out, &in, &mask, dp, info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageHelicalMasking(mrcImage* out, mrcImage* in, mrcImage* mask, double dp, int mode)
{
/* variables */
  mrcImage romask,tmpin;
  int z;

/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);

/* begin */
  for (z=0 ;z < in->HeaderN.z ;z++){
    lmrc3DZ1ImgGet(&tmpin ,in ,z);
    lmrcImageRotation2D(&romask, mask, dp*z*RADIAN, 3); 
    lmrcImageMultiplysingbyFile(&tmpin ,&romask);
    lmrc3DZ1ImgPut(out, &tmpin, z);
    mrcImageFree(&tmpin,"");
    mrcImageFree(&romask,"");
  }
  mrcStatDataSet(out,0);
}









