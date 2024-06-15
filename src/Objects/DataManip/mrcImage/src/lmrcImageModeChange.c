/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageModeChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageModeChange 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageModeChange ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageModeChange.h"

void 
lmrcImageModeChange(mrcImage* out, mrcImage* in, long mode)
{
	mrcImageParaTypeReal x, y, z;
	double datain;
	double dataout;

	out->Header = in->Header;
	out->HeaderMode = mode;
	mrcInit(out, NULL);
	for(x=0; x<in->HeaderN.x; x++) {
		for(y=0; y<in->HeaderN.y; y++) {
			for(z=0; z<in->HeaderN.z; z++) {
				mrcPixelDataGet(in, x, y, z, &datain,  mrcPixelRePart, mrcPixelHowNearest);
				
				if(datain<in->HeaderAMin) {
					datain = in->HeaderAMin;
				}
				if(in->HeaderAMax<datain) {
					datain = in->HeaderAMax;
				}
				switch(out->HeaderMode) {
					case mrcCharImage: {
						dataout = (datain - in->HeaderAMin)/(in->HeaderAMax - in->HeaderAMin)*255.0;
						break;
					}
					case mrcShortImage: {
						dataout = (signed short)datain;
						break;
					}
					case mrcUShortImage: {
						dataout = (unsigned short)datain;
						break;
					}
					case mrcFloatImage: {
						dataout = datain;
						break;
					}
					case mrcDoubleImage: {
						dataout = datain;
						break;
					}
					default: {
						fprintf(stderr, "Not supported mode chanage\n");
						exit(EXIT_FAILURE);
					}
				}	
				mrcPixelDataSet(out, x, y, z, dataout, mrcPixelRePart);
				DEBUGPRINT5("(%f %f %f): %f -> %f\n", x, y, z, datain, dataout);
			}
		}
	}
	mrcStatDataSet(out, 0);
}

