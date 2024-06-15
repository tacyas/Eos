/*
# lmrc2contour.c  1.2
# The latest update : 06/15/96 at 14:59:12
#
#@(#) lmrc2contour ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : lmrc2contour 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)lmrc2contour ver1.2; Date:96/06/15 @(#)";
#include <stdio.h>
#include <stdlib.h>

#include "mrcImage.h"
#include "../inc/Contour.h"

void
lmrc2contour(contourLinesSet* lsset, mrcImage* mrc, contourParaTypeReal level, contourFlag flag, long mode)
{
    contourImage ci;
    long ix, iy, iz;
    double tmp;

	fprintf(stderr, "%f %d\n", level , flag);
    ci.x.n = mrc->HeaderN.x;
    ci.y.n = mrc->HeaderN.y;
    ci.z.n = mrc->HeaderN.z;
    if(0!=0x01&mode) {
        ci.x.d = mrc->HeaderLength.x;
        ci.y.d = mrc->HeaderLength.y;
        ci.z.d = mrc->HeaderLength.z;
    } else {
        ci.x.d = 1;
        ci.y.d = 1;
        ci.z.d = 1;
    }
    ci.x.Min = ci.y.Min = ci.z.Min = 0.0;
    ci.x.Max = (ci.x.n - 1)*ci.x.d + ci.x.Min;
    ci.y.Max = (ci.y.n - 1)*ci.y.d + ci.y.Min;
    ci.z.Max = (ci.z.n - 1)*ci.z.d + ci.z.Min;
    
    if(NULL==(ci.image=(contourParaTypeReal*)malloc(sizeof(contourParaTypeReal)*(ci.x.n+1)*(ci.y.n+1)*(ci.z.n+1)))) {
        fprintf(stderr, "Memory Not Allocate in lmrc2contour\n");
        exit(EXIT_FAILURE); 
    }

    for(ix=0; ix<ci.x.n; ix++) {
        for(iy=0; iy<ci.y.n; iy++) {
            for(iz=0; iz<ci.z.n; iz++) {
                 mrcPixelDataGet(mrc, (float)ix, (float)iy, (float)iz, &tmp, mrcPixelRePart, mrcPixelHowNearest);
                 ci.image[ix+iy*ci.x.n+iz*ci.x.n*ci.y.n] = tmp;
            }
        }
    }
	fprintf(stderr, "%f %d\n", level , flag);
    createContour(lsset, ci, level, flag);

}
