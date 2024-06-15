/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfDeterminationFromPhaseComparison ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfDeterminationFromPhaseComparison 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfDeterminationFromPhaseComparison ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DEBUG
#include "genUtil.h"
#include "../inc/ctfInfo.h"
#include "mrcImage.h"
#include "ctfDeterminationFromPhaseComparison.h"

double
ctfDeterminationFromPhaseComparison(mrcImage* inFFT,
									mrcImage* refFFT,
									ctfInfoDeterminationFromPhaseComparison* DetInfo,
									long mode)
{
	double inMag, inPhase, refMag, refPhase;
	double R;
	double weight, bunbo, bunshi, dPhase, result;
	mrcImageParaTypeReal iX, iY;
	mrcImageParaTypeReal delX, delY;

	inMag    = 0.0;
	inPhase  = 0.0;
	refMag   = 0.0;
	refPhase = 0.0;
	R        = 0.0;
	weight   = 0.0;
	bunbo    = 0.0;
	bunshi   = 0.0;
	dPhase   = 0.0;
	result   = 0.0;
	delX = 1.0/(inFFT->HeaderLength.x*inFFT->HeaderN.x);
	delY = 1.0/(inFFT->HeaderLength.y*inFFT->HeaderN.y);

	for(iY=-inFFT->HeaderN.y/2.0; iY<=inFFT->HeaderN.y/2.0 -1; iY++) {
		for(iX=0.0; iX<inFFT->HeaderN.x/2.0; iX++) {
			R = sqrt(SQR(iX*delX) + SQR(iY*delY));
			if(R<DetInfo->Rmax) {
				mrcPixelDataGet(inFFT , iX, iY, 0.0, &inMag   , mrcPixelMag,   mrcPixelHowNearest);
				mrcPixelDataGet(inFFT , iX, iY, 0.0, &inPhase , mrcPixelPhase, mrcPixelHowNearest);
				mrcPixelDataGet(refFFT, iX, iY, 0.0, &refMag  , mrcPixelMag,   mrcPixelHowNearest);
				mrcPixelDataGet(refFFT, iX, iY, 0.0, &refPhase, mrcPixelPhase, mrcPixelHowNearest);
					
				weight  = (inMag + refMag)/2;	
				dPhase  = inPhase - refPhase;	

				bunbo  += weight;
				bunshi += dPhase*weight;

			}
		}
	}
	DEBUGPRINT2("bunbo =%15.6f bunshi =%15.6f\n", bunbo, bunshi);
	result = bunshi/bunbo; 
	return result;

}
