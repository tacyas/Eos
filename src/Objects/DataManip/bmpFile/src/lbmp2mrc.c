/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lbmp2mrc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lbmp2mrc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lbmp2mrc ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#include <stdio.h>
#include "../inc/bmpFile.h"
#include "mrcImage.h"

void
lbmp2mrc(mrcImage* mrc, bmpFile* bmp, lbmp2mrcInfo linfo, int mode)
{
	mrcImageParaTypeInteger x, y;	
	int n, nn;
	double data, r, g, b;
	mrcDefaultHeaderValueSet(mrc);
	mrc->HeaderN.x = bmp->Width; 
	mrc->HeaderN.y = bmp->Height; 
	mrc->HeaderN.z = 1;
	mrc->HeaderMode = mrcCharImage;
	mrc->HeaderLength = linfo.Length;
	mrcInit(mrc, NULL);

	for(y=0; y<mrc->HeaderN.y; y++) {
	for(x=0; x<mrc->HeaderN.x; x++) {
		//n  = x+y*bmp->Width; 
		nn = x+y*bmp->Width4; 
		if(bmp->BytesPerPixel==1) {
			b = bmp->Palette[bmp->Image[nn]].rgbBlue;
			g = bmp->Palette[bmp->Image[nn]].rgbGreen;
			r = bmp->Palette[bmp->Image[nn]].rgbRed;
		} else if(bmp->BytesPerPixel==4) {
			b = bmp->ColorImage[4*nn+0];
			g = bmp->ColorImage[4*nn+1];
			r = bmp->ColorImage[4*nn+2];
		} else if(bmp->BytesPerPixel==3) {
			b = bmp->ColorImage[3*nn+0];
			g = bmp->ColorImage[3*nn+1];
			r = bmp->ColorImage[3*nn+2];
		} else {
			fprintf(stderr, "Not supported Mode: BytesPerPixel: %d BitsPerPixel: %d \n", bmp->BytesPerPixel, bmp->BitsPerPixel);
			exit(EXIT_FAILURE);
		}
		switch(linfo.mode) {
			case lbmp2mrcInfoModeY: {
				data = 0.299*r + 0.587*g + 0.114*b; 
				break;
			}
			case lbmp2mrcInfoModeR: {
				data = r;
				break;
			}
			case lbmp2mrcInfoModeG: {
				data = g;
				break;
			}
			case lbmp2mrcInfoModeB: {
				data = b;
				break;
			}
			default: {
				fprintf(stderr, "Not supported mode: %d. Instead, use Y: %d\n", linfo.mode, lbmp2mrcInfoModeY);
				data = 0.299*r + 0.587*g + 0.114*b; 
				break;
			}
		}
		if(0<bmp->Info.biWidth) {
			mrcPixelDataSet(mrc, x, y, 0, data, mrcPixelRePart);
		} else {
			mrcPixelDataSet(mrc, x, bmp->Height - y - 1, 0, data, mrcPixelRePart);
		}	
	}
	}	
}

void
lbmp2mrcUsage(FILE* fpt)
{
	fprintf(fpt, "%d: Y to mono\n", lbmp2mrcInfoModeY);
	fprintf(fpt, "%d: R to mono\n", lbmp2mrcInfoModeR);
	fprintf(fpt, "%d: G to mono\n", lbmp2mrcInfoModeG);
	fprintf(fpt, "%d: B to mono\n", lbmp2mrcInfoModeB);
}
