/*
# mrcImageConvolution : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageConvolution
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
#include "Array.h"
#include "larray2mrc.h"

/*
Example:
typedef struct lmrcImageConvolutionInfo {
	float a;
	int   b;
} lmrcImageConvolutionInfo;

typedef enum lmrcImageConvolutionMode {
	a=0,
	b=1
} lmrcImageConvolutionMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageConvolutionInfo info;
	larray2mrcInfo llinfo;
	mrcImage in;
	mrcImage out;
	mrcImage kernel;
	Array kernelArray;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	if(info.flagInKernelArray) {
		arrayReadFromFile(info.fptInKernelArray, &kernelArray, "in main");
		llinfo.mrcMode   = in.HeaderMode;
		llinfo.mrcLength = in.HeaderLength.x;
		larray2mrc(&kernel, kernelArray, &llinfo, 0); 
	} 
	if(info.flagInKernelMRC) {
		mrcFileRead(&kernel, info.InKernelMRC, "in main", 0);
	} 

	lmrcImageConvolution(&out, &in, &kernel, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	arrayFormatInfoPrint(stderr, 0);	
}
