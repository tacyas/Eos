/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageAsProbability ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageAsProbability 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageAsProbability ver%I%; Date:%D% %Z%";

#include "lmrcImageAsProbability.h"

void
lmrcImageNormalizationAsProbability(mrcImage* mrc, int mode)
{
    mrcImageParaTypeReal x, y, z;
    double sum;
    double data;

    sum = 0;
    for(x=0; x<mrc->HeaderN.x; x++) {
        for(y=0; y<mrc->HeaderN.y; y++) {
            for(z=0; z<mrc->HeaderN.z; z++) {
                mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
                sum += data;
            }
        }
    }

    for(x=0; x<mrc->HeaderN.x; x++) {
        for(y=0; y<mrc->HeaderN.y; y++) {
            for(z=0; z<mrc->HeaderN.z; z++) {
                mrcPixelDataGet(mrc, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
                data /= sum; 
                mrcPixelDataSet(mrc, x, y, z,  data, mrcPixelRePart);
            }
        }
    }
}

