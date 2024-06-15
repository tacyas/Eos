/*
# mrcImageGradient : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageGradient
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

typedef struct lmrcImageGradientInfo {
	mrcImage Gradient;
	mrcImage Dx;
	mrcImage Dy;
	mrcImage Dz;
} lmrcImageGradientInfo;

typedef enum lmrcImageGradientMode {
	a=0,
	b=1
} lmrcImageGradientMode;

extern int lmrcImageGradientCalc(lmrcImageGradientInfo* linfo, mrcImage* in, lmrcImageGradientMode);

int
main(int argc, char* argv[]) 
{
	mrcImageGradientInfo  info;
	lmrcImageGradientInfo linfo;
    mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    mrcFileRead(&in, info.In, "in main", 0);

    lmrcImageGradientCalc(&linfo, &in, info.mode);
    
    if(info.flagOut) {
        mrcFileWrite(&linfo.Gradient, info.Out, "in main", 0);
    }
    if(info.flagOutDx) {
        mrcFileWrite(&linfo.Dx, info.OutDx, "in main", 0);
    }
    if(info.flagOutDy) {
        mrcFileWrite(&linfo.Dy, info.OutDy, "in main", 0);
    }
    if(info.flagOutDz) {
        mrcFileWrite(&linfo.Dz, info.OutDz, "in main", 0);
    }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int 
lmrcImageGradientCalc(lmrcImageGradientInfo* linfo, mrcImage* in, lmrcImageGradientMode mode)
{
    mrcImageParaTypeReal x, y, z;
    double d000, dp00, dm00, d0p0, d0m0, d00p, d00m; 
    double dx, dy, dz, grad;

    linfo->Gradient.Header = in->Header;
    linfo->Dx.Header = in->Header;
    linfo->Dy.Header = in->Header;
    linfo->Dz.Header = in->Header;

    mrcInit(&(linfo->Gradient), NULL);
    mrcInit(&(linfo->Dx), NULL);
    mrcInit(&(linfo->Dy), NULL);
    mrcInit(&(linfo->Dz), NULL);

    for(z=0; z<in->HeaderN.z; z++) {
    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        mrcPixelDataGet(in, x, y, z, &d000, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, x-1, y, z, &dm00, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, x+1, y, z, &dp00, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, x, y-1, z, &d0m0, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, x, y+1, z, &d0p0, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, x, y, z-1, &d00m, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in, x, y, z+1, &d00p, mrcPixelRePart, mrcPixelHowNearest);
        dx = (dp00 - dm00)/2.0; 
        dy = (d0p0 - d0m0)/2.0; 
        dz = (d00p - d00m)/2.0; 
        grad = sqrt(dx*dx+ dy*dy + dz*dz);
        mrcPixelDataSet(&(linfo->Gradient), x, y, z, grad,  mrcPixelRePart); 
        mrcPixelDataSet(&(linfo->Dx), x, y, z, dx, mrcPixelRePart); 
        mrcPixelDataSet(&(linfo->Dy), x, y, z, dy, mrcPixelRePart); 
        mrcPixelDataSet(&(linfo->Dz), x, y, z, dz, mrcPixelRePart); 
    }
    }
    }

    return 0;
}

