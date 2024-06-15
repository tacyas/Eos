/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate ver%I%; Date:%D% %Z%";

#include <math.h>
#include <stdlib.h>
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate.h"
#undef DEBUG

  
void lmrcImageSecondNoiseReductionByRelaxationDijValueCalculate(double* d, double* dsum,
								lmrcImageNoiseReductionByRelaxationInfo* info,
								lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1* mode1,
								lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2* mode2)
{
  int i,j,k;
  
  static int dSavitzyGolay1[25] = {
    -13, 2, 7, 2, -13,
     2, 17, 22, 17, 2,
     7, 22, 27, 22, 7,
     2, 17, 22, 17, 2,		
    -13, 2, 7, 2, -13,
  };
  static int dSavitzyGolay2[25] = {
     0,  -14, 3, -14,   0,
     -14, 37, 54, 37, -14,
     3,   54, 71, 54,   3,
     -14, 37, 54, 37, -14,		
     0,  -14, 3, -14,   0,
  };
  
  *dsum = 0.0;
  for (i=0; i<info->ddimx; i++){
    for (j=0; j<info->ddimy; j++){
      for (k=0; k<info->ddimz; k++){
	
	switch (*mode1){
	case lmrcImageSecondNoiseReductionByRelaxationDijStyleMode1SavitzyGolay:
	  switch(*mode2) {
	  case lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2Rectangle:
	    d[XYZCOORD(i,j,k,info->ddimx,info->ddimy,info->ddimz)] = 
	      dSavitzyGolay1[XYZCOORD(i,j,k,info->ddimx,info->ddimy,info->ddimz)];
	    break;
	  case lmrcImageSecondNoiseReductionByRelaxationDijStyleMode2Circle:
	    d[XYZCOORD(i,j,k,info->ddimx,info->ddimy,info->ddimz)] = 
	      dSavitzyGolay2[XYZCOORD(i,j,k,info->ddimx,info->ddimy,info->ddimz)];
	    break;
	  }
	  break;
	default:
	  fprintf(stderr,"dij-style not supported !! (ToT)/ ");
	  exit(EXIT_FAILURE);
	}
	*dsum += d[XYZCOORD(i,j,k,info->ddimx,info->ddimy,info->ddimz)];
	
      }
    }
  }
}

