/*
# mrcImageFractalFrourierShellCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFractalFrourierShellCorrelation
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

typedef struct lmrcImageFractalFrourierShellCorrelationInfo {
	double Threshold;

} lmrcImageFractalFrourierShellCorrelationInfo;


/*
typedef enum lmrcImageFractalFrourierShellCorrelationMode {
	a=0,
	b=1
} lmrcImageFractalFrourierShellCorrelationMode;
*/


extern void lmrcImageFractralFourierShellCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageFractalFourierCorrelationInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageFractalFrourierShellCorrelationInfo info;
	lmrcImageFractalFrourierShellCorrelationInfo linfo;
	mrcImage in;
	mrcImage ref;
	mrcImage out;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	
	linfo.Threshold = info.Threshold;
	
	mrcFileRead(&in, info.In, "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

	lmrcImageFractalFourierShellCorrelation(&out, &in, &ref, linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmrcImageFractralFourierShellCorrelation(mrcImage* out, mrcImage* in, mrcImage* ref, lmrcImageFractralFourierCorrelationInfo linfo, int mode)
{

}


