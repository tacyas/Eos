/*
# mrcImageDensityWeightedAreaCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDensityWeightedAreaCalc
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCalcArea.h"

/*
Example:
typedef struct lmrcImageDensityWeightedAreaCalcInfo {
	float a;
	int   b;
} lmrcImageDensityWeightedAreaCalcInfo;

typedef enum lmrcImageDensityWeightedAreaCalcMode {
	a=0,
	b=1
} lmrcImageDensityWeightedAreaCalcMode;
*/

int
main(int argc, char* argv[]) 
{
  mrcImage in;
  mrcImage inDens;
  mrcImage out;
  mrcImage label;
  
	mrcImageDensityWeightedAreaCalcInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

  mrcFileRead(&in, info.In, "in main", 0);
  mrcFileRead(&inDens, info.InDensity, "in main", 0);
  
  lmrcImageCalcDensityWeightedArea(&out, &label, &in, &inDens, info.Neighbor, info.mode);

  if(info.flagOutLabel) {
    mrcFileWrite(&label, info.OutLabel, "in main", 0);
  }
  mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m \n");
	fprintf(stderr, "    0: Sum of density\n");
	fprintf(stderr, "    1: Transform top of 75 pecents of sum of density to 0.75\n");
}
