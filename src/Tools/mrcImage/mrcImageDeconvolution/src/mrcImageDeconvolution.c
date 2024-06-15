/*
# mrcImageDeconvolution : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageDeconvolution
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
#include "lmrcImageDeconvolution.h"

/*
Example:
typedef struct lmrcImageDeconvolutionInfo {
	float a;
	int   b;
} lmrcImageDeconvolutionInfo;

typedef enum lmrcImageDeconvolutionMode {
	a=0,
	b=1
} lmrcImageDeconvolutionMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageDeconvolutionInfo info;
	lmrcImageDeconvolutionInfo linfo;
	mrcImage in;
	mrcImage kernel;
	mrcImage out;
	mrcImage convOut; 

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	mrcFileRead(&kernel, info.Kernel, "in main", 0);

	linfo.thresCTF = info.thresCTF;
	linfo.NSRatio  = info.NSRatio;
	linfo.NSCoeff  = info.NSCoeff;
	linfo.Pad3DMode = info.Pad3DMode;
	linfo.KernelCentreMode = info.KernelCentre;
	if (!info.flagr){
		info.r=MIN((kernel.HeaderN.x-1)/2, (kernel.HeaderN.y-1)/2);
		DEBUGPRINT1("rmax: %f\n", info.r);
	}
   	linfo.Pad3DInfo.rmax = info.r;
	DEBUGPRINT1("rmax: %f\n", linfo.Pad3DInfo.rmax);
    linfo.Pad3DInfo.flagr = 1;
	linfo.Pad3DInfo.w    = info.w;
	linfo.Pad3DInfo.flagv = info.flagv;
	linfo.Pad3DInfo.v     = info.v;
	linfo.Pad3DInfo.flagFloating = info.Floating;

	linfo.maxIter = info.maxIter;
	linfo.minRMSD = info.minRMSD;
	linfo.lambda  = info.lambda;

	lmrcImageIterativeDeconvolution(&out, &convOut, &in, &kernel, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	if(info.flagOutASCII) {
		fprintf(info.fptOutASCII, "rmsd: %f\n", linfo.subInfo.sd);
		fprintf(info.fptOutASCII, "min:  %f\n", linfo.subInfo.min);
		fprintf(info.fptOutASCII, "max:  %f\n", linfo.subInfo.max);
		fprintf(info.fptOutASCII, "iter: %d\n", linfo.Iter);
	}
	if(info.flagOutRMSD) {
		mrcFileWrite(&linfo.rmsd, info.OutRMSD, "in main", 0);
	}
	if(info.flagOutConv) {
		mrcFileWrite(&convOut, info.OutConv, "in main", 0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Deconvolution Mode \n");
	lmrcImageDeconvolutionModePrint(stderr);
}
