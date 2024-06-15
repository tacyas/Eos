/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRotation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRotation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRotation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

/* prototype */
void llmrcImageRotation(mrcImage* out ,mrcImage* in ,double angle , int mode1, int mode);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageRotationInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	mrcFileRead(&in, info.In, "in main", 0);
	llmrcImageRotation(&out, &in, info.Angle*RADIAN, info.Periodic, info.mode);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
  	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "0:Nearest \n");
	fprintf(stderr, "1:Bi-linear Interpolation\n");
}

void llmrcImageRotation(mrcImage* out ,mrcImage* in ,double angle ,int mode1, int mode)
{
  int z;
  mrcImage tmpin,tmpout;

  if (in->HeaderN.z==1){
  	switch(mode1) {
		case 0: {
			lmrcImageRotation2D(out, in, angle, mode);
			break;
		}
		case 1: {
			lmrcImageRotation2DPeriodicBoundary(out, in, angle, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode1 in llmrcImageRotation: %d\n", mode1);
			break;
		}
	}
  }else{
    out->Header=in->Header;
    mrcInit(out,NULL);
    for (z=0 ;z<out->HeaderN.z ;z++){
      lmrc3DZ1ImgGet(&tmpin ,in ,z);
      lmrcImageRotation2D(&tmpout, &tmpin, angle, mode);
      lmrc3DZ1ImgPut(out ,&tmpout ,z);
      mrcImageFree(&tmpin,"");
      mrcImageFree(&tmpout,"");
    }
    mrcStatDataSet(out,0);
  }
}




