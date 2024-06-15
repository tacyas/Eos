/*
# mrcImageBlurByTemperatureFactor : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageBlurByTemperatureFactor
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

typedef struct atomInfo {   
    int nAtom;
    mrcImageParaTypeRealCoord* coord;
    mrcImageParaTypeReal* Temparature;
} atomInfo;

typedef struct lmrcImageBlurByTemperatureFactorInfo {
    atomInfo
} lmrcImageBlurByTemperatureFactorInfo;

typedef enum lmrcImageBlurByTemperatureFactorMode {
	a=0,
	b=1
} lmrcImageBlurByTemperatureFactorMode;

extern void lmrcImageBlurByTemperatureFactor(mrcImage* out, mrcImage* in, lmrcImageBlurByTemperatureFactorInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageBlurByTemperatureFactorInfo info;
	lmrcImageBlurByTemperatureFactorInfo linfo;
    mrcImage in;
    mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    mrcFileRead(&in, info.In, "in main", 0); 
    lmrcImageBlurByTemperatureFactor(&out, &in, linfo, info.mode);  
    mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void
lmrcImageBlurByTemperatureFactor(mrcImage* out, mrcImage* in, lmrcImageBlurByTemperatureFactorInfo linfo, int mode)
{
    mrcParaTypeReal x, y, z;
    mrcParaTypeReal dstx, dsty, dstz;
    double data;

    out->Header = in->Header;
    mrcInit(out, NULL);

    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
       for(linfo.
       mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest); 


       mrcPixelDataSet(in, x, y, z, &data, mrcPixeRePart, mrcPixelHowNearest); 
    }
    }
    }
}
