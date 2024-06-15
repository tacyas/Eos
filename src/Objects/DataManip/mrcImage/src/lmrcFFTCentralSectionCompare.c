/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcFFTCentralSectionCompare ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcFFTCentralSectionCompare 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcFFTCentralSectionCompare ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./lmrcFFTCentralSection.h"
#include "../inc/mrcImage.h"

void
lmrcFFTCentralSectionCompare(mrcImage* in, mrcImage* volume, lmrcFFTCentralSectionCompareInfo* linfo, int mode){

	mrcImageParaTypeReal x, y;
	mrcImage* vol2d;
	double rein, imin;
	double revol, imvol;
	float likelihood;

	DEBUGPRINT("lmrcFFTCentralSectionCompare start\n");
	
	linfo -> Likelihood = (float*)malloc(sizeof(float));
	
	lmrcFFTCentralSectionGet(&linfo->vol2d, in, volume, &linfo->llinfo, mode);

	DEBUGPRINT("lmrcFFTCentralSectionsGet after\n");
	for(x=0; x < in->HeaderN.x ; x++){
		for(y=0; y < in->HeaderN.y ; y++){
			
			mrcPixelDataGet(in, x, y, 0, &rein, mrcPixelRePart, linfo->llinfo.InterpMode);
			mrcPixelDataGet(in, x, y, 0, &imin, mrcPixelImPart, linfo->llinfo.InterpMode);
		
			mrcPixelDataGet(&linfo->vol2d, x, y, 0, &revol, mrcPixelRePart, linfo->llinfo.InterpMode);
			mrcPixelDataGet(&linfo->vol2d, x, y, 0, &imvol, mrcPixelImPart, linfo->llinfo.InterpMode);

			likelihood = likelihood + ((rein - revol)*(rein - revol)+(imin - imvol)*(imin - imvol))/(-2);
			
		}
	}

	linfo->Likelihood[0] = exp(likelihood)/(2*M_PI);

	DEBUGPRINT("lmrcFFTCentralSectionCompare end\n"); 

}

