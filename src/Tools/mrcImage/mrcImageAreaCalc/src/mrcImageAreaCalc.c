/*
# mrcImageAreaCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageAreaCalc
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
typedef struct lmrcImageAreaCalcInfo {
	float a;
	int   b;
} lmrcImageAreaCalcInfo;

typedef enum lmrcImageAreaCalcMode {
	a=0,
	b=1
} lmrcImageAreaCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageAreaCalcInfo info;
	mrcImage in;
	mrcImage label;
	mrcImage out;
	int n, i;
	double dens;
	double* datHist;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "mrcFileRead", 0);
	
	lmrcImageCalcArea(&out, &label, &in, info.Neighbor, 0);

	mrcFileWrite(&out, info.Out, "mrcFileWrite", 0);
	if(info.flagLabel) {
		mrcFileWrite(&label, info.Label, "mrcFileWrite", 0);
	}
	fprintf(info.fptOutInfo, "MaxRegion: %f \n", out.HeaderAMax);

	if(info.flagOutHist) {
		lmrcImageHistgram4(&datHist, info.DelHist, &out);
		n = (unsigned long)((out.HeaderAMax - out.HeaderAMin)/info.DelHist + 1);
		for(i=0; i<n; i++) {
			dens = out.HeaderAMin + i*info.DelHist;
			fprintf(info.fptOutHist, "%15.6g %15.6g \n", dens, datHist[i]);
		}
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
