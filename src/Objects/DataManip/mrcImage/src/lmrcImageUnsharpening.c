/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageUnsharpening ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageUnsharpening 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageUnsharpening ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include "./lmrcImageUnsharpening.h" 

void
lmrcImageUnsharpeningUsage(FILE* fpt)
{
	fprintf(fpt, "--UnsharpeningMode--\n");
	fprintf(fpt, "0: 0 -1  0 \n");
	fprintf(fpt, "  -1  5 -1 \n");
	fprintf(fpt, "   0 -1  0 \n");
	fprintf(fpt, "1:-1 -1 -1 \n");
	fprintf(fpt, "  -1  9 -1 \n");
	fprintf(fpt, "  -1 -1 -1 \n");
	fprintf(fpt, "2: 1 -2  1 \n");
	fprintf(fpt, "  -2  5 -2 \n");
	fprintf(fpt, "   1 -2  1 \n");
}

void
lmrcImageUnsharpening(mrcImage* out, mrcImage* in, int mode)
{
	//*out = *in;
	mrcImageParaTypeInteger x0, y0;
	mrcImageParaTypeInteger x1, y1;
	double data;
	double data20, data21, data22;	
	double data10, data11, data12;	
	double data00, data01, data02;	
	
	out->Header = in->Header;
	mrcInit(out, NULL);

	for(y0=0; y0<out->HeaderN.y; y0++) {
	for(x0=0; x0<out->HeaderN.x; x0++) {
		// data = in->ImageFloatImage[x0+y0*out->HeaderN.x]; 
		// mrcPixelDataGet(&in, x0, y0, 0, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0-1, y0-1, 0, &data00, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0-1, y0,   0, &data01, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0-1, y0+1, 0, &data02, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0  , y0-1, 0, &data10, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0  , y0,   0, &data11, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0  , y0+1, 0, &data12, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0+1, y0-1, 0, &data20, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0+1, y0,   0, &data21, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(in, x0+1, y0+1, 0, &data22, mrcPixelRePart, mrcPixelHowNearest);

		switch(mode) {
			case 0: {
				data =            -1*data12 
				       -1*data01 + 5*data11 -1*data21 
					              -1*data10;
				break;
			} 
			case 1: {
				data = -1*data02 -1*data12 -1*data22
				       -1*data01 +9*data11 -1*data21
					   -1*data00 -1*data10 -1*data20;
				break;
			}
			case 2: {
				data =  1*data02 -2*data12 +1*data22
				       -2*data01 +5*data11 -2*data21
					   +1*data00 -2*data10 +1*data20;
				break;
			}
			default: {
				fprintf(stderr, "Not supported mode: %d\n", mode);
				exit(EXIT_FAILURE);
			}
		}
		mrcPixelDataSet(out, x0, y0, 0, data, mrcPixelRePart);
	}
	}

}
