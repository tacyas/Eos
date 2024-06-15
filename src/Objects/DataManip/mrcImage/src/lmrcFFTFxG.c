#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../inc/mrcImage.h"       
#include "genUtil.h"

void 
lmrcFFTFxG(mrcImage* out, mrcImage* in1, mrcImage* in2)
{
    mrcImageParaTypeReal x, y, z;
    double re1, re2, im1, im2, re, im;
    
    if(!(   in1->HeaderN.x==in2->HeaderN.x
          &&in1->HeaderN.y==in2->HeaderN.y
          &&in1->HeaderN.z==in2->HeaderN.z)) {
        fprintf(stderr, "Different size between in1(%d,%d,%d) and in2(%d,%d,%d)\n"
                        ,in1->HeaderN.x, in2->HeaderN.x
                        ,in1->HeaderN.y, in2->HeaderN.y
                        ,in1->HeaderN.z, in2->HeaderN.z);
        exit(EXIT_FAILURE);
    }

    *out = *in1;
    mrcInit(out, NULL);

    for(z=-in1->HeaderN.z/2.0; z<in1->HeaderN.z/2.0; z++) {
    for(y=-in1->HeaderN.y/2.0; y<in1->HeaderN.y/2.0; y++) {
    for(x=0; x<=in1->HeaderN.x/2.0; x++) {
        mrcPixelDataGet(in1, x, y, z, &re1, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in2, x, y, z, &re2, mrcPixelRePart, mrcPixelHowNearest);
        mrcPixelDataGet(in1, x, y, z, &im1, mrcPixelImPart, mrcPixelHowNearest);
        mrcPixelDataGet(in2, x, y, z, &im2, mrcPixelImPart, mrcPixelHowNearest);
        re =  re1*re2 - im1*im2;
        im =  re1*im2 + re2*im1;
        mrcPixelDataSet(out, x, y, z, re, mrcPixelRePart);
        mrcPixelDataSet(out, x, y, z, im, mrcPixelImPart);
    }
    }
    }
}


