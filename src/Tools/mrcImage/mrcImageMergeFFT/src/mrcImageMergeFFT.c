/*
# mrcImageMergeFFT : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageMergeFFT
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

typedef struct lmrcImageMergeFFTInfo {
	int nx;
    int ny;
} lmrcImageMergeFFTInfo;

typedef enum lmrcImageMergeFFTMode {
	a=0,
	b=1
} lmrcImageMergeFFTMode;

extern void lmrcImageMergeFFTInfoCalc(mrcImage* out, mrcImage* in, lmrcImageMergeFFTInfo linfo, int mode);

int
main(int argc, char* argv[]) 
{
    mrcImage in;
    mrcImage out;
	mrcImageMergeFFTInfo info;
	lmrcImageMergeFFTInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    linfo.nx = info.nx;
    linfo.ny = info.ny;
    mrcFileRead(&in, info.In, "in main", 0);
    
    lmrcImageMergeFFTInfoCalc(&out, &in, linfo, info.mode); 

    mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImageMergeFFTInfoCalc(mrcImage* out, mrcImage* in, lmrcImageMergeFFTInfo linfo, int mode)
{
    mrcImageParaTypeReal x, y, z;
    mrcImageParaTypeReal srcx, srcy, srcz;
    mrcImageParaTypeReal X, Y, Z;
    mrcImage part;
    mrcImage fft;
    mrcImage pow;
    double data;

    out->Header = in->Header;
    out->HeaderN.x = in->HeaderN.x*2;
    out->HeaderN.y = in->HeaderN.y*2;
    mrcInit(out, NULL);

    part->Header = in->Header;
    part->HeaderN.x = linfo.nx;
    part->HeaderN.y = linfo.ny;
    mrcInit(&part, NULL);

    for(y=0; y<in->HeaderN.y; y++) {
    for(x=0; x<in->HeaderN.x; x++) {
        for(srcy=x-linfo.nx/2; srcy<in->HeaderN.y; srcy++) {
        for(srcx=y-linfo.ny/2; srcx<in->HeaderN.x; srcx++) {
            mrcPixelDataGet(&mrc, srcx, srcy, 0, &data, 
        }
        }
    }
    }
}
