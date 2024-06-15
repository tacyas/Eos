/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc2png ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrc2png 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrc2png ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#include <stdint.h>
#include "../inc/pngFile.h"

void
lmrc2png(pngFile* out, mrcImage* in, lmrc2pngInfo* linfo, int mode)
{
	pngFileInit(out, 0);
	int i;
	int size;
	double width;

	out->pngImage.width  = in->HeaderN.x;
	out->pngImage.height = in->HeaderN.y;
	out->pngImage.format = PNG_FORMAT_GRAY;

	out->stride = PNG_IMAGE_ROW_STRIDE(out->pngImage);	
	out->size   = in->HeaderN.x*in->HeaderN.y; 
	out->flagHanded = -1;
	out->byteImage = memoryAllocate(sizeof(unsigned char)*out->size, "in lmrc2png");

	width = 255.0/(in->HeaderAMax - in->HeaderAMin);

	switch(in->HeaderMode) {
		case mrcCharImage: {
			memcpy(out->byteImage, in->ImageCharImage+in->HeaderN.x*in->HeaderN.z*linfo->z, sizeof(unsigned char)*out->size);	
			break;
		}
		case mrcShortImage: {
			for(i=0; i<out->size; i++) {
				if(in->HeaderAMax<in->ImageShortImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z]) {
					out->byteImage[i] = 255;	
				} else if(in->HeaderAMin>in->ImageShortImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z]) {
					out->byteImage[i] = 0;
				} else {
					out->byteImage[i] = (unsigned char)((in->ImageShortImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z] - in->HeaderAMin)*width); 
				}
			}
			break;	
		}
		case mrcFloatImage: {
			for(i=0; i<out->size; i++) {
				if(in->HeaderAMax<in->ImageFloatImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z]) {
					out->byteImage[i] = 255;	
				} else if(in->HeaderAMin>in->ImageFloatImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z]) {
					out->byteImage[i] = 0;
				} else {
					out->byteImage[i] = (unsigned char)((in->ImageFloatImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z] - in->HeaderAMin)*width); 
				}
			}
			break;
		}
		case mrcUShortImage: {
			for(i=0; i<out->size; i++) {
				if(in->HeaderAMax<(unsigned short)in->ImageShortImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z]) {
					out->byteImage[i] = 255;	
				} else if(in->HeaderAMin>(unsigned short)in->ImageShortImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z]) {
					out->byteImage[i] = 0;
				} else {
					out->byteImage[i] = (unsigned char)(((unsigned short)in->ImageShortImage[i+in->HeaderN.x*in->HeaderN.z*linfo->z] - in->HeaderAMin)*width); 
				}
			}
			break;	
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", in->HeaderMode);
			exit(EXIT_FAILURE);
		}
	}
}

