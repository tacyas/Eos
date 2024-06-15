/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTSizeChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTSizeChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTSizeChange ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcFFTSizeChangeInfo {
	mrcImageParaTypeReal Nx;
	mrcImageParaTypeReal Ny;
} lmrcFFTSizeChangeInfo;

extern void lmrcFFTSizeChange(mrcImage *out, mrcImage *in, lmrcFFTSizeChangeInfo *linfo);

int
main(int argc, char* argv[]) 
{
	mrcFFTSizeChangeInfo info;
	lmrcFFTSizeChangeInfo linfo; 
	mrcImage in;
	mrcImage out;


	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.Nx = info.Nx;
	linfo.Ny = info.Ny;

	mrcFileRead(&in, info.In, "in main", 0);
	lmrcFFTSizeChange(&out, &in, &linfo);
	mrcFileWrite(&out, info.Out, "in main", 0);


	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmrcFFTSizeChange(mrcImage *out, mrcImage *in, lmrcFFTSizeChangeInfo *linfo)
{
	mrcImageParaTypeReal iX, iY;
	double re, im;

	out->HeaderN.x = linfo->Nx;
	out->HeaderN.y = linfo->Ny;
	out->HeaderN.z = in->HeaderN.z;
	out->HeaderLength.x = in->HeaderLength.x;
	out->HeaderLength.y = in->HeaderLength.y;
	out->HeaderLength.z = in->HeaderLength.z;
	out->HeaderMode = mrcComplexFloatFT;

	mrcInit(out, NULL);

	re = 0.0;
	im = 0.0;

	for(iY=-out->HeaderN.y/2.0; iY<=out->HeaderN.y/2.0 -1; iY++) {
		for(iX=0.0; iX<=out->HeaderN.x/2.0; iX++) {
			mrcPixelDataGet(in , iX, iY, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(in , iX, iY, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
			mrcPixelDataSet(out, iX, iY, 0.0,  re, mrcPixelRePart);
			mrcPixelDataSet(out, iX, iY, 0.0,  im, mrcPixelImPart);
		}
	}

}
