/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHelicalMappingFrom2DImage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHelicalMappingFrom2DImage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageHelicalMappingFrom2DImage ver%I%; Date:%D% %Z%";
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

void lmrcImageHelicalMappingFrom2DImage(mrcImage* out, mrcImage* in, double dp, double dz, int Nz);

int
main(int argc, char* argv[]) 
{
	mrcImageHelicalMappingFrom2DImageInfo info;
	mrcImage in;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	lmrcImageHelicalMappingFrom2DImage(&out, &in, info.dp, info.dz, info.Nz);
	mrcFileWrite(&out, info.Out, "in main", 0);

       	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageHelicalMappingFrom2DImage(mrcImage* out, mrcImage* in, double dp, double dz, int Nz)
{
  int z;
  mrcImage tmp;
  double delphi;

  out->Header = in->Header;
  out->HeaderN.z = Nz;
  mrcInit(out,NULL);
  dz /= in->HeaderLength.z;
  delphi = dp / dz * RADIAN;
  
  for (z = 0; z < Nz; z++){
    DEBUGPRINT1("%d ",z);
    lmrcImageRotation2D(&tmp, in, delphi*z, 3);
    lmrc3DZ1ImgPut(out, &tmp, z);
  }
  mrcStatDataSet(out,0);
}

