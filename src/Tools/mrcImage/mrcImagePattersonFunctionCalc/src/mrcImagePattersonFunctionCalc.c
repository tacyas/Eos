/*
# mrcImagePattersonFunctionCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagePattersonFunctionCalc
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

/*
Example:
typedef struct lmrcImagePattersonFunctionCalcInfo {
	float a;
	int   b;
} lmrcImagePattersonFunctionCalcInfo;

typedef enum lmrcImagePattersonFunctionCalcMode {
	a=0,
	b=1
} lmrcImagePattersonFunctionCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImagePattersonFunctionCalcInfo info;
	mrcImage in;
	mrcImage out;
    mrcImage outfft;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImagePattersonFunctionCalc(&out, &outfft, &in);

	if(info.flagOutPat) {
		lmrcImagePattersonFunctionPrint(info.fptOutPat, &out, info.mode);
	}

	if(info.flagOutGuinierPlot) {
		lmrcImageGuinierFunctionPrint(info.fptOutGuinierPlot, &outfft, info.mode);
	}

	if(info.flagOut) {
        DEBUGPRINT("Write^n");
		mrcFileWrite(&out, info.Out, "in main", 0);
	}

	if(info.flagOutGuinier) {
        DEBUGPRINT("Write^n");
		mrcFileWrite(&outfft, info.OutGuinier, "in main", 0);
	}
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
