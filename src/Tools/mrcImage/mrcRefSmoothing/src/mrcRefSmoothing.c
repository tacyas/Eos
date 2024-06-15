/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefSmoothing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefSmoothing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefSmoothing ver%I%; Date:%D% %Z%";
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
void lmrcRefSmoothing(mrcImage* out, mrcImage* in, lmrcImageSmoothingInfo* info, long mode );

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefSmoothingInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	lmrcImageSmoothingInfo linfo;

/* initialization */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	linfo.sx = info.sx;
	linfo.sy = info.sy;
	linfo.sz = info.sz;
	linfo.mode = info.mode;
/* begin */
	mrcFileRead(&in, info.In, "in main", 0);
	DEBUGPRINT("start  ");
     	lmrcRefSmoothing(&out, &in, &linfo, 0);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcRefSmoothing(mrcImage* out, mrcImage* in, lmrcImageSmoothingInfo* info, long mode )
{
/* variables */
  mrcImage tmpimg,tmpout;
  int z;

/* initialization */
  out->Header = in->Header;
  mrcInit(out,NULL);
  lmrc3DZ1ImgGet(&tmpimg ,in ,0);
  lmrc3DZ1ImgPut(out ,&tmpimg ,0);
  
/* begin */
  for (z = 1 ;z < in->HeaderN.z ;z++){
    fprintf(stderr,"%d " ,z);
    lmrc3DZ1ImgGet(&tmpimg ,in ,z);
    lmrcImageSmoothing(&tmpout ,&tmpimg ,info ,mode);
    lmrc3DZ1ImgPut(out ,&tmpout ,z ); 
    mrcImageFree(&tmpimg ,"in lmrcRefPhaseImageCreate");
    mrcImageFree(&tmpout ,"in lmrcRefPhaseImageCreate");
  }
  mrcStatDataSet(out,0);
}
