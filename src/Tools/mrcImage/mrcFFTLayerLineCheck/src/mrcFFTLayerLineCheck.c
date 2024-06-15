/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTLayerLineCheck ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTLayerLineCheck
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTLayerLineCheck ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcFFTLayerLineCheckInfo {
	/* In */	
	mrcImageParaTypeInteger L; 
	int flagNoEq;

	/* Out */
	double Fall;
	double Flayer;
	double Residual;
} lmrcFFTLayerLineCheckInfo;

extern void lmrcFFTLayerLineCheck(mrcImage* in, lmrcFFTLayerLineCheckInfo* info, int mode);

int
main(int argc, char* argv[]) 
{
	mrcFFTLayerLineCheckInfo info;
	lmrcFFTLayerLineCheckInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0); 
	linfo.L = info.L;
	linfo.flagNoEq = info.NoEq;

	lmrcFFTLayerLineCheck(&in, &linfo, 0);

	/* Output */
	fprintf(info.fptOut, "Fall:     %g\n", linfo.Fall);	
	fprintf(info.fptOut, "Flayer:   %15.6g  %15.6g \n", linfo.Flayer,   linfo.Flayer/linfo.Fall);	
	fprintf(info.fptOut, "Residual: %15.6g  %15.6g \n", linfo.Residual, linfo.Residual/linfo.Fall);	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmrcFFTLayerLineCheck(mrcImage* in, lmrcFFTLayerLineCheckInfo* info, int mode)
{
	double  mag;
	mrcImageParaTypeInteger x, y, z;

	info->Fall     = 0;	
	info->Flayer   = 0;	
	info->Residual = 0;	
	for(x=0; x<=in->HeaderN.x/2; x++) {
	for(y=-in->HeaderN.y/2; y<in->HeaderN.y/2; y++) {
		mrcPixelDataGet(in, x, y, 0.0, &mag, mrcPixelMag, mrcPixelHowNearest); 
		if(info->flagNoEq && (-info->L<y && y<info->L)) {
		} else {	
			info->Fall += SQR(mag);
			if(0==(y%info->L)) {
				if(x==0) {
					DEBUGPRINT1("l: %d\n", y);
				}
				info->Flayer   += SQR(mag);
			} else {
				info->Residual += SQR(mag);
			}
		}
	}
	}
}

