/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefHeaderCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefHeaderCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefHeaderCreate ver%I%; Date:%D% %Z%";
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
void lmrcRefHeaderCreate(mrcImage* out, mrcImage* in, mrcRefHeaderCreateInfo* info, int mode);

int
main(int argc, char* argv[]) 
{
/* variables */
	mrcRefHeaderCreateInfo info;
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	
/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	lmrcRefHeaderCreate(&out, &in, &info, info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcRefHeaderCreate(mrcImage* out, mrcImage* in, mrcRefHeaderCreateInfo* info, int mode)
{
/* variables */
  int z;
  mrcImage tmp;
  mrcRefHeader refheader;
  mrcpwzCorHeader pwzheader;

/* Initialization */
  out->Header = in->Header;
  out->HeaderN.z = in->HeaderN.z + 1;
  mrcInit(out,0);

/* begin */
  if (!mode){
    refheader.ip = info->iP;
    refheader.iw = info->iW;
    refheader.ia = info->iA;
    refheader.dp = info->Dp;
    refheader.dw = info->Dw;
    refheader.da = info->Da;
    refheader.wp = info->Wp;
    refheader.ww = info->Ww;
    refheader.wa = info->Wa;
    lmrcRefHeaderSet(out ,&refheader);
  } else {
    pwzheader.ip = info->iP;
    pwzheader.iw = info->iW;
    pwzheader.ia = info->iA;
    pwzheader.dp = info->Dp;
    pwzheader.dw = info->Dw;
    pwzheader.da = info->Da;
    pwzheader.wp = info->Wp;
    pwzheader.ww = info->Ww;
    pwzheader.wa = info->Wa;
    pwzheader.sy = info->Sy;
    if (!info->flagEy){
      pwzheader.ey = in->HeaderN.y - 1;
    } else {
      pwzheader.ey = info->Ey;
    }
    pwzheader.refsize = info->Refsize;
    lmrcpwzCorHeaderSet(out ,&pwzheader);
  }
  
  for (z=0 ;z < in->HeaderN.z; z++){
    DEBUGPRINT1("%d ",z); 
    lmrc3DZ1ImgGet(&tmp ,in ,z);
    lmrc3DZ1ImgPut(out ,&tmp ,z+1);
    mrcImageFree(&tmp,"");
  }
  mrcStatDataSet(out,0);
}
