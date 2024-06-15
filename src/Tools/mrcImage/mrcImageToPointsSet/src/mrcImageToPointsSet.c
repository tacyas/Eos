/*
# mrcImageToPointsSet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageToPointsSet
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
#include "lmrcImageBinarization.h"

/*
Example:
typedef struct lmrcImageToPointsSetInfo {
	float a;
	int   b;
} lmrcImageToPointsSetInfo;

typedef enum lmrcImageToPointsSetMode {
	a=0,
	b=1
} lmrcImageToPointsSetMode;
*/


extern void	lmrcImageToPoints(FILE* fpt, mrcImage* tmp, long mode);

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage bin;
	mrcImageToPointsSetInfo info;
	lmrcImageBinarizationInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.thresHold = info.Threshold;

	mrcFileRead(&in, info.In, "in main", 0);
	lmrcImageBinarization(&bin, &in, linfo, 0);
	lmrcImageToPoints(info.fptOut, &bin, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void	
lmrcImageToPoints(FILE* fpt, mrcImage* bin, long mode)
{
	float x, y, z;
	double data;

	for(z=0; z<bin->HeaderN.z; z++) {
	for(y=0; y<bin->HeaderN.y; y++) {
	for(x=0; x<bin->HeaderN.x; x++) {
		mrcPixelDataGet(bin, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(0.5<data) {
			fprintf(fpt, "%f, %f, %f\n", 
				(x+bin->HeaderStartN.x)*bin->HeaderLength.x, 
				(y+bin->HeaderStartN.y)*bin->HeaderLength.y, 
				(z+bin->HeaderStartN.z)*bin->HeaderLength.z);
		}
	}
	}
	}
}

