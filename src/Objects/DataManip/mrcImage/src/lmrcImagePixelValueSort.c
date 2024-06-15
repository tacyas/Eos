/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImagePixelValueSort ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImagePixelValueSort 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImagePixelValueSort ver%I%; Date:%D% %Z%";

#include "../inc/mrcImage.h"
#include "Memory.h"


static 
int 
__compareUp(const void* a, const void* b) 
{
    if(*(double*)a > *(double*)b) {
        return 1;
    } else if(*(double*)a < *(double*)b) {
        return -1;
    } else {
        return 0;
    }
}

static 
int 
__compareDown(const void* a, const void* b) 
{
    if(*(double*)a > *(double*)b) {
        return -1;
    } else if(*(double*)a < *(double*)b) {
        return 1;
    } else {
        return 0;
    }
}

void 
lmrcImagePixelValueSort(double* dst, mrcImage* src, int mode)
{
    int N;
    int i;
    mrcImageParaTypeReal x, y, z;
    double data;
    
    N = src->HeaderN.x*src->HeaderN.y*src->HeaderN.z;
    //dst = (double*) memoryAllocate(sizeof(double)*N, "in lmrcImagePixelValueSort");

    i = 0;
    for(z=0; z<src->HeaderN.z; z++) { 
    for(y=0; y<src->HeaderN.y; y++) { 
    for(x=0; x<src->HeaderN.x; x++) { 
        mrcPixelDataGet(src, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);  
        dst[i] = data;
        i++;
    }
    }
    }
    switch(mode) {
        case 0: 
            qsort(dst, N, sizeof(double), __compareUp);  
            break;
        case 1: 
            qsort(dst, N, sizeof(double), __compareDown);
            break;
        default: 
            fprintf(stderr, "Not supported Mode in lmrcImagePixelValueSort: %d\n", mode);
            exit(EXIT_FAILURE);
    }
}
