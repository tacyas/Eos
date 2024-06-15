/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFourierShellCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFourierShellCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFourierShellCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "lmrcImageFourierShellCorrelation.h"
/* prototype */


int
main(int argc, char* argv[]) 
{
	mrcImageFourierShellCorrelationInfo info;
	lmrcImageFourierShellCorrelationInfo linfo;
	lmrcImageFourierShellCorrelationResult res;

/* variables */
	mrcImage in1;
	mrcImage in2;
	mrcImage tmp;
	double* data, DX, DY, DZ;
	int max, i;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	if (info.mode2) {
	  mrcFileRead(&tmp ,info.In2 ,"in main" ,0);
	  lmrc3DZ1ImgGet(&in2 ,&tmp ,info.z);
	  mrcImageFree(&tmp, "");
	} else {
	  mrcFileRead(&in2, info.In2, "in main" ,0);
	}
	DX = 1/ (in2.HeaderLength.x * in2.HeaderN.x);
	DY = 1/ (in2.HeaderLength.y * in2.HeaderN.y);
	DZ = 1/ (in2.HeaderLength.z * in2.HeaderN.z);
	if (!info.flagdelta){
	  info.delta = 1 / (in2.HeaderLength.x * in2.HeaderN.x);
	}

/* begin */
	DEBUGPRINT("Program Start\n");
	/*
	max  =  floor(sqrt(SQR(1/in2.HeaderLength.x)+SQR(1/in2.HeaderLength.y)+SQR(1/in2.HeaderLength.z) ) /info.delta /2  +0.5)+1;
	data = (double *)memoryAllocate(sizeof(double)*max, "in main");
	*/

	linfo.High = info.H;
	linfo.Low  = info.L;
	linfo.Delta  = info.delta;
	res.flagSNR = info.SNR;
	res.flagFSCfull = info.FSCfull;
	res.flagCref = info.Cref;
	res.flagNoiseWeighted = info.flagBrestore;
	res.Brestore= info.Brestore;

	if (info.flagIn1Array==0){
		mrcFileRead(&in1 ,info.In1 ,"in main" ,0);
		lmrcImageFourierShellCorrelation(&res, &in1, &in2, linfo, info.mode, info.mode2);
		lmrcImageFourierShellCorrelationPrint(info.fptOut, &res, linfo, info.mode, info.mode2);
	} else {
		for (i=0 ;i<info.flagIn1Array ;i++){
	    	mrcFileRead(&in1 ,info.In1Array[i] ,"in main" ,0);
	    	fprintf(stdout,"%s ",info.In1Array[i]);
	    	lmrcImageFourierShellCorrelation(&res, &in1, &in2, linfo, info.mode, info.mode2);
			lmrcImageFourierShellCorrelationPrint(info.fptOut, &res, linfo, info.mode, info.mode2);
	    	mrcImageFree(&in1,"in main");
		} 
	}
	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0: Fourier shell correlation.\n");
	fprintf(stderr, "1: Fourier shell phase residual.\n");
	fprintf(stderr, "+2: Correlation between L and H\n");
	fprintf(stderr, "+4: Without equator.\n");
	fprintf(stderr, "----- mode 2 -----\n");
	fprintf(stderr, "0: Correlation between same size images\n");
	fprintf(stderr, "1: Correlation between 2D image and image extracted from 3D image.\n");
	fprintf(stderr, "+2: Correlation between 2D different size images. In1 is compared with center of In2.\n");
}

