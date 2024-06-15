/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageMove ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageMove 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageMove ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>

#include "lmrcImageMove.h"

extern void __lmrcImageMovePixelUnit(mrcImage* out, mrcImage* in, double dx, double dy, double dz, int mode);

void
lmrcImageMoveModePrint(FILE* fpt)
{
	fprintf(fpt, "Mode for lmrcImageMove\n");
	fprintf(fpt, "%d: Move following Pixel Unit\n", lmrcImageMoveModePixelUnit);
}

void
lmrcImageMove(mrcImage* out, mrcImage* in, double x, double y, double z, lmrcImageMoveMode mode)
{
	switch(mode) {
		case lmrcImageMoveModePixelUnit: {
			__lmrcImageMovePixelUnit(out, in, x, y, z, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
}

void
__lmrcImageMovePixelUnit(mrcImage* out, mrcImage* in, double dx, double dy, double dz, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data;

	out->Header = in->Header;
	mrcInit(out, NULL);
	for(x=0; x<out->HeaderN.x; x++) {
	for(y=0; y<out->HeaderN.y; y++) {
	for(z=0; z<out->HeaderN.z; z++) {
		mrcPixelDataGet(in, x-dx, y-dy, z-dz, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
	}
	}
	}
}
