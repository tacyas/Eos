/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSurfaceAreaCalc ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSurfaceAreaCalc 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSurfaceAreaCalc ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "Memory.h"
#include "./lmrcImageFeatureCalc.h"


void 
lmrcImageSurfaceAreaCalcUsage(FILE* fpt)
{
	fprintf(fpt, "mode:\n");
	fprintf(fpt, "   default: 0\n");
	fprintf(fpt, "neighbor: 6|18|26\n");
	fprintf(fpt, "   6(default:0)|18|26\n");

}

void
lmrcImageSurfaceAreaCalcPrint(FILE* fpt, lmrcImageSurfaceAreaCalcInfo linfo, int mode)
{
	int i;
	fprintf(fpt, "%6s %10s %10s %10s %10s\n", "label", "surfaceArea", "startx", "starty", "startz");
	for(i=0; i<=linfo.labelNumber; i++) {
		fprintf(fpt, "%06d %10.4f %10d %10d %10d\n", i, (double)linfo.surfaceArea[i], linfo.blCoord[i].x, linfo.blCoord[i].y, linfo.blCoord[i].z);
	}
}

void 
lmrcImageSurfaceAreaCalc(mrcImage* out, mrcImage* bin, lmrcImageSurfaceAreaCalcInfo* linfo, int mode)
{
	mrcImage* area;
	mrcImage* label;
	mrcImage* surface;
	mrcImageParaTypeReal x, y, z;
	double data, labelIndex;
	double max;
	int index;

	DEBUGPRINT("lmrcImageSurfaceAreaCalc Start\n");
	if(linfo->flagArea) {
		area = linfo->Area;	
		label = linfo->Label;
	} else {
		area  = linfo->Area  = memoryAllocate(sizeof(mrcImage), "in lmrcImageSurfaceAreaCalc");	
		label = linfo->Label = memoryAllocate(sizeof(mrcImage), "in lmrcImageSurfaceAreaCalc");	
		lmrcImageCalcArea(area, label, bin, linfo->Neighbor, 0);
		DEBUGPRINT("lmrcImageLabelingOrder Start\n");
		lmrcImageLabelingOrder(label, 0);
	}

	DEBUGPRINT("lmrcImageSurfaceCal Start\n");
	surface = linfo->Surface = memoryAllocate(sizeof(mrcImage), "in lmrcImageSurfaceAreaCalc");
	lmrcImageSurfaceCalc(surface, bin, linfo->Neighbor, linfo->Mode);

	out->Header = bin->Header;
	mrcInit(out, NULL);

	max = 0;
	for(z=0; z<out->HeaderN.z; z++) {	
	for(y=0; y<out->HeaderN.y; y++) {	
	for(x=0; x<out->HeaderN.x; x++) {	
		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(max<data) {
			max = data;
		}
		mrcPixelDataSet(out, x, y, z, 0, mrcPixelRePart);
	}
	}
	}
	linfo->labelNumber = max;

	linfo->surfaceArea = memoryAllocate(sizeof(int)*(max+1), "in lmrcImageSurfaceAreaCalc");
	linfo->blCoord     = memoryAllocate(sizeof(mrcImageParaTypeIntegerCoord)*(max+1), "in lmrcImageSurfaceAreaCalc");
	for(z=0; z<out->HeaderN.z; z++) {	
	for(y=0; y<out->HeaderN.y; y++) {	
	for(x=0; x<out->HeaderN.x; x++) {	
		mrcPixelDataGet(label,   x, y, z, &labelIndex, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(surface, x, y, z, &data,       mrcPixelRePart, mrcPixelHowNearest);
		if(1e-6<data) {
			index = (int)(labelIndex+0.5);
			linfo->surfaceArea[index]++;
			if(linfo->surfaceArea[index]==1) {
				linfo->blCoord[index].x = x;
				linfo->blCoord[index].y = y;
				linfo->blCoord[index].z = z;
			}
		}
	}
	}
	}

	for(index=0; index<=max; index++) {
		mrcPixelDataSet(out, 
			linfo->blCoord[index].x, 
			linfo->blCoord[index].y,
			linfo->blCoord[index].z,
			linfo->surfaceArea[index], 
			mrcPixelRePart);
	}
}
