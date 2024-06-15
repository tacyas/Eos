/*
# mrcImageTailer.c  1.2
# The latest update : 08/13/96 at 11:42:55
#
#@(#) mrcImageTailer ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageTailer 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageTailer ver1.2; Date:96/08/13 @(#)";

#include "Memory.h"
#include "../inc/mrcImage.h"


void
mrcTailerInit(mrcImage* mrc, long mode)
{
	if(0<mrc->numTailer) {
		mrc->Tailer = (mrcImageTailer*)memoryAllocate(sizeof(mrcImageTailer)*mrc->numTailer, "in mrctailerInit");
	} else {
	}
}

void
mrcTailerCopy(mrcImage* dst, mrcImage* src, long mode)
{
	int i;

	if(mode&0x1) {
		dst->numTailer = src->numTailer;
		mrcTailerInit(dst, 0);
	} else if(dst->numTailer!=src->numTailer) {
		fprintf(stderr, "Tailer size is different between dst %d and src %d\n", dst->numTailer, src->numTailer);
		exit(EXIT_FAILURE);
	}

	for(i=0; i<dst->numTailer; i++) {
		dst->Tailer[i] = src->Tailer[i];
	}
}
