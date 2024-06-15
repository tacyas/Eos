/*
# mrcImageSectionGet.c  1.2
# The latest update : 08/28/96 at 16:51:03
#
#@(#) mrcImageSectionGet ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageSectionGet 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageSectionGet ver1.2; Date:96/08/28 @(#)";

#include <string.h>
#include <stdlib.h>

#include "../inc/mrcImage.h"

char*
mrcImageSectionGetModeDescription(long mode)
{
	char* s;
	switch(mode) {
		case 0: {
			s = strdup("Copy the selected section into a new area indicated by dst");
			break;
		}
		case 1: {
			s = strdup("Share the selected section between dst and src: replacement of pointers");
			break;
		}
		default: {
			s = strdup("Not supported Mode in mrcImageSectionGet");
			break;
		}
	}
	return s;
}

void
mrcImageSectionGet(mrcImage* dst, mrcImage* src, mrcImageParaTypeReal z, long mode)
{
	mrcImageParaTypeReal x, y;
	double data;

	switch(mode) {
		case 0: {
			dst->Header.Cont = src->Header.Cont;
			dst->HeaderN.z = 1;
			mrcInit(dst, NULL);
			for(y=0; y<dst->HeaderN.y; y++) {
			for(x=0; x<dst->HeaderN.x; x++) {
				mrcPixelDataGet(src, x, y, z,   &data, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataSet(dst, x, y, 0.0, data,  mrcPixelRePart);
			}
			}
			if(0!=src->numTailer) {
				dst->numTailer=1;
				mrcTailerInit(dst, 0);
				dst->Tailer[0].Cont = src->Tailer[(int)(z+0.5)].Cont;
			}
			break;
		}
		case 1: {
			*dst = *src;
			dst->HeaderN.z = 1;
			mrcHiddenDataSet(dst, 0);
			dst->Image          = (char*)src->Image + (dst->BytePerImage*((int)(z+0.5)));
			dst->ImageCharImage = dst->ImageShortImage 
								= dst->ImageLongImage 
								= dst->ImageFloatImage
								= dst->ImageDoubleImage = dst->Image;
			if(0!=src->numTailer) {
				dst->numTailer=1;
				dst->Tailer = &(src->Tailer[((int)(z+0.5))]);
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in mrcImageSectionGet: %ld\n", mode);
			exit(EXIT_FAILURE);
		}
	}
}

