/*
# mrcImage2FFT : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage2FFT
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
#include "lmrcImageToFFT.h"

/*
Example:
typedef struct lmrcImage2FFTInfo {
	float a;
	int   b;
} lmrcImage2FFTInfo;

typedef enum lmrcImage2FFTMode {
	a=0,
	b=1
} lmrcImage2FFTMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out;
	mrcImage2FFTInfo info;
	mrcImageParaTypeRealCoord centre;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);


	if(info.flagCentreX) {
		centre.x = info.CentreX;
		centre.y = info.CentreY;
		centre.z = info.CentreZ;
	} else {
		centre.x = in.HeaderN.x/2; 
		centre.y = in.HeaderN.y/2;
		centre.z = in.HeaderN.z/2; 
	}

	DEBUGPRINT("lmrcImageToFFT\n");
	lmrcImageToFFT(&out, &in, centre, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
