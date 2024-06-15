/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefLowPassFilter ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefLowPassFilter
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefLowPassFilter ver%I%; Date:%D% %Z%";
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
 void lmrcRefLowPassFilter(mrcImage* out ,mrcImage* in , lmrcImageLowPassFilterInfo* info, long mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefLowPassFilterInfo info;
	lmrcImageLowPassFilterInfo linfo;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	linfo.hvp = info.hvp;
	linfo.width = info.width;
	linfo.mode = info.mode;
	mrcFileRead(&in ,info.In ,"in main" ,0); 

/* begin */       
	lmrcRefLowPassFilter(&out ,&in ,&linfo ,0);
 	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>> Mode <<<< \n");
	fprintf(stderr, "    1: Step filter : required argumnent: -hvp\n");
	fprintf(stderr, "    2: Cos filter  : required argumnent: -hvp -w\n");
	fprintf(stderr, "    3: Exp filter  : required argumnent: -hvp\n");
	fprintf(stderr, "   +4: For 2D Image \n"); 
}

void lmrcRefLowPassFilter(mrcImage* out ,mrcImage* in , lmrcImageLowPassFilterInfo* info, long mode)
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
  if (info->mode > 4 ){
    info->mode -= 4;
    lmrcImageLowPassFilter(out ,in ,info ,0);
    mrcStatDataSet(out,0);
  } else { 
    for (z = 1 ;z < in->HeaderN.z ;z++){
      fprintf(stderr,"%d " ,z);
      lmrc3DZ1ImgGet(&tmpimg ,in ,z);
      lmrcImageLowPassFilter(&tmpout ,&tmpimg ,info ,0);
      lmrc3DZ1ImgPut(out ,&tmpout ,z ); 
      mrcImageFree(&tmpimg ,"in lmrcRefPhaseImageCreate");
      mrcImageFree(&tmpout ,"in lmrcRefPhaseImageCreate");
    }
    mrcStatDataSet(out,0);
  }
}
  
