/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageFloating ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageFloating 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageFloating ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>

#include "./lmrcImageFloating.h"

void 
lmrcImageFloatingModePrint(FILE* fpt)
{
	fprintf(fpt, ">>> Edge Mode 0xf&mode\n");
	fprintf(fpt, "All Mean:                     %d\n", lmrcImageFloatingModeAllMean);
	fprintf(fpt, "Sphere Surface Mean (rmax):   %d\n", lmrcImageFloatingModeSphereSurfaceMean);
	fprintf(fpt, "Cylinder Surface Mean (rmax): %d\n", lmrcImageFloatingModeCylinderSurfaceMean);
	fprintf(fpt, "Edge Pixels:                  %d\n", lmrcImageFloatingModeEdgePixel);
}

void 
lmrcImageFloating(mrcImage* out, mrcImage* in, lmrcImageFloatingInfo* linfo, int mode)
{
	double data, offset;
	mrcImageParaTypeReal x, y, z;

	out->Header.Cont = in->Header.Cont;
	mrcInit(out, NULL);

	linfo->info.mode = 0xf&mode;
	lmrcImageInformation(&(linfo->info), in);		

	switch(mode) {
		case lmrcImageFloatingModeAllMean:
			offset = linfo->info.mean;
			break;
		case lmrcImageFloatingModeSphereSurfaceMean:
			offset = linfo->info.meanOfSphereSurface;
			break;
		case lmrcImageFloatingModeCylinderSurfaceMean:
			offset = linfo->info.meanOfCylinderSurface;
			break;
		case lmrcImageFloatingModeEdgePixel: 
			offset = linfo->info.meanOfEdge;
			break;
		default: {
			fprintf(stderr, "Not supported mode: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}

	for(z=0; z<in->HeaderN.z; z++) {
	for(y=0; y<in->HeaderN.y; y++) {
	for(x=0; x<in->HeaderN.x; x++) {
		mrcPixelDataGet(in,  x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		data = data - offset + linfo->value;
		mrcPixelDataSet(out, x, y, z,  data, mrcPixelRePart);
	}
	}
	}
}

