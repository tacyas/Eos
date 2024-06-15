/*
# mrcImage2DBackProjection : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage2DBackProjection
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

typedef struct lmrcImage2DBackProjectionInfo {
	mrcImageParaTypeInteger z;
} lmrcImage2DBackProjectionInfo;
/*
typedef enum lmrcImage2DBackProjectionMode {
	a=0,
	b=1
} lmrcImage2DBackProjectionMode;
*/

void
lmrcImage2DBackProjection(mrcImage*out, mrcImage* in,  lmrcImage2DBackProjectionInfo linfo, int mode);


int
main(int argc, char* argv[]) 
{
	mrcImage2DBackProjectionInfo info;
	lmrcImage2DBackProjectionInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	linfo.z = info.NumZ;
	
	lmrcImage2DBackProjection(&out, &in, linfo, 0); 
	
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void
lmrcImage2DBackProjection(mrcImage*out, mrcImage* in,  lmrcImage2DBackProjectionInfo linfo, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;

	out->Header = in->Header;
	out->HeaderN.z = linfo.z;
	mrcInit(out, NULL);

	for(x=0; x<out->HeaderN.x; x++) { 
	for(y=0; y<out->HeaderN.y; y++) { 
		mrcPixelDataGet(in, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);	
		for(z=0; z<out->HeaderN.z; z++) { 
			mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
		}
	}
	}
}
