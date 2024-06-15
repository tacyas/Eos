/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageCenterOfMassCalculate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageCenterOfMassCalculate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageCenterOfMassCalculate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCentre.h"

int
main(int argc, char* argv[]) 
{
  mrcImageCenterOfMassCalculateInfo info;
  lmrcImageCenterOfMass gc;
  mrcImage in1;

  
  init0(&info);
  argCheck(&info, argc, argv);
  init1(&info);
  
  mrcFileRead(&in1, info.In, "in main", 0);
  
  lmrcImageCenterOfMassCalculate(&gc, in1);
  
  fprintf(info.fptOut, "%15.6g %15.6g %15.6g [pixel]\n", gc.x, gc.y, gc.z);
  fprintf(info.fptOut, "%15.6g %15.6g %15.6g [A] Origin is Bottom Right\n", gc.x*in1.HeaderLength.x, gc.y*in1.HeaderLength.y, gc.z*in1.HeaderLength.z);
  fprintf(info.fptOut, "%15.6g %15.6g %15.6g [A] Origin is Centre\n", (gc.x-(in1.HeaderN.x-1)/2.0)*in1.HeaderLength.x, 
                                                     (gc.y-(in1.HeaderN.y-1)/2.0)*in1.HeaderLength.y, 
						     (gc.z-(in1.HeaderN.z-1)/2.0)*in1.HeaderLength.z);
  exit(EXIT_SUCCESS);
}

void
  additionalUsage()
{
  fprintf(stderr, "----- Additional Usage -----\n");
}
