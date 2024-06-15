/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageCTFCompensation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageCTFCompensation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageCTFCompensation ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "ctfInfo.h"

void
lmrcImageCTFCompensation(mrcImage* dstfft, ctfInfo* ctf, long mode)
{
    float X, Y, R, Weight, dX, dY;
	double re, im;

	DEBUGPRINT1("Astigmatism %d\n", ctf->flagAstigmatism);
    switch(mode) {
		case 0: 
		case 1: 
		case 2: 
		case 3: 
		case 4: 
		case 5: 
		case 6: 
		case 7: 
		case 8: 
		case 9: {
			ctf->mode = 1;
			dX = 1.0/(dstfft->HeaderN.x*dstfft->HeaderLength.x);
			dY = 1.0/(dstfft->HeaderN.y*dstfft->HeaderLength.y);
			for(Y=-dstfft->HeaderN.y/2.0; Y<dstfft->HeaderN.y/2.0; Y++) {
				for(X=0; X<=dstfft->HeaderN.x/2.0; X++) {
					R = sqrt(SQR(X*dX) + SQR(Y*dY));
					if(ctf->flagAstigmatism) {
						//DEBUGPRINT("With Astigmatism\n");
						Weight = ctfWeightForCorrection2D(ctf, X*dX, Y*dY, mode);
					} else {
						//DEBUGPRINT("Without Astigmatism\n");
						Weight = ctfWeightForCorrection(ctf, R, mode);
					}
					// DEBUGPRINT4("%f %f %f %f \n ",X,Y,R,Weight);
					if(ctf->flagWin) {
						if(ctf->CutLow< R && R < ctf->CutHigh) {
							Weight = Weight*(cos((R-ctf->CutLow)/(ctf->CutHigh-ctf->CutLow)*M_PI)+1)*0.5;
						} else if(ctf->CutHigh <= R) {
							Weight = 0.0;
						}
					}
					mrcPixelDataGet(dstfft, X, Y, 0.0, &re, mrcPixelRePart, mrcPixelHowNearest);
					mrcPixelDataGet(dstfft, X, Y, 0.0, &im, mrcPixelImPart, mrcPixelHowNearest);
					mrcPixelDataSet(dstfft, X, Y, 0.0, Weight*re, mrcPixelRePart);
					mrcPixelDataSet(dstfft, X, Y, 0.0, Weight*im, mrcPixelImPart);
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode : %ld in lmrcImageCTFCompensation \n", mode);
			exit(EXIT_FAILURE);
		}
	}

}
