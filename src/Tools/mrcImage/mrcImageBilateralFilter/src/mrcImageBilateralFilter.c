/*
# mrcImageBilateralFilter : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageBilateralFilter
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
#include "lmrcImageBilateralFilter.h"

/*
Example:
typedef struct lmrcImageBilateralFilterInfo {
	float a;
	int   b;
} lmrcImageBilateralFilterInfo;

typedef enum lmrcImageBilateralFilterMode {
	a=0,
	b=1
} lmrcImageBilateralFilterMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageBilateralFilterInfo info;
	lmrcImageBilateralFilterInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	// Set Kernel Size
	if(info.flagKernelSizeX) {
		linfo.kernelSize.x = info.KernelSizeX; 
		linfo.kernelSize.y = info.KernelSizeY; 
		linfo.kernelSize.z = info.KernelSizeZ; 
		linfo.flagKernelSize = 1;
	} else if(info.flagKernelSize) {
		linfo.kernelSize.x = info.KernelSize;
		linfo.kernelSize.y = info.KernelSize;
		linfo.kernelSize.z = info.KernelSize;
		linfo.flagKernelSize = 1;
	} else {
		fprintf(stderr, "Use default kernelSIze %ld %ld %ld\n", info.KernelSizeX, info.KernelSizeY, info.KernelSizeZ);
		linfo.kernelSize.x = info.KernelSizeX; 
		linfo.kernelSize.y = info.KernelSizeY; 
		linfo.kernelSize.z = info.KernelSizeZ; 
		linfo.flagKernelSize = 1;
	}

	linfo.sigmaDensity = info.SigmaDensity;
	linfo.sigmaDensityMode = info.KernelTypeDensity;

	if(info.flagSigmaSpaceX) {
		linfo.sigmaSpace.x = info.SigmaSpaceX;
		linfo.sigmaSpace.y = info.SigmaSpaceY;
		linfo.sigmaSpace.z = info.SigmaSpaceZ;
	} else if(info.flagSigmaSpace) {
		linfo.sigmaSpace.x = info.SigmaSpace;
		linfo.sigmaSpace.y = info.SigmaSpace;
		linfo.sigmaSpace.z = info.SigmaSpace;
	} else {
		linfo.sigmaSpace.x = info.SigmaSpaceX;
		linfo.sigmaSpace.y = info.SigmaSpaceY;
		linfo.sigmaSpace.z = info.SigmaSpaceZ;
	}

	linfo.sigmaSpaceMode = info.KernelTypeSpace;

	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageBilateralFilter(&out, &in, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageBilateralFilterUsage(stderr);
}
