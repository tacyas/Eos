/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageStack ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageStack 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageStack ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include "../inc/mrcImage.h"


void
lmrcImageStackAlloc(mrcImage* dst, mrcImage* src, int N, int* sp, int mode)
{
	mrcImageParaTypeReal x, y;
	double data;

	dst->Header = src->Header;
	if(1!=dst->HeaderN.z) {
		fprintf(stderr, "lmrcImageStackAlloc: not supported 3D stack, just 2D stack\n");
		exit(EXIT_FAILURE);
	}
	dst->HeaderN.z = N;
	mrcInit(dst, NULL);
	
	*sp = 0;

	for(x=0; x<dst->HeaderN.x; x++) {
	for(y=0; y<dst->HeaderN.y; y++) {
		mrcPixelDataGet(src, x, y,   0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(dst, x, y, *sp,  data, mrcPixelRePart);  
	}
	}
}

void
lmrcImageStackPush(mrcImage* dst, mrcImage* src, int* sp, int mode)
{
	mrcImageParaTypeReal x, y;
	double data;

	if(dst->HeaderN.x!=src->HeaderN.x
	 ||dst->HeaderN.y!=src->HeaderN.y) {
	 	fprintf(stderr, "Size not different: dst %d %d src %d %d\n",
			dst->HeaderN.x, dst->HeaderN.y,
			src->HeaderN.x, src->HeaderN.y);
		exit(EXIT_FAILURE); 	
	}

	*sp += 1;
	if(dst->HeaderN.z<=*sp) {
		fprintf(stderr, "Stack Overflow: %d : max %d\n", *sp, dst->HeaderN.z); 
		exit(EXIT_FAILURE);
	}

	for(x=0; x<dst->HeaderN.x; x++) {
	for(y=0; y<dst->HeaderN.y; y++) {
		mrcPixelDataGet(src, x, y,   0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(dst, x, y, *sp,  data, mrcPixelRePart);  
	}
	}
}
