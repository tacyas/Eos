/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageEdgeAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageEdgeAverage 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageEdgeAverage ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lmrcImageEdgeAverage.h"

void
lmrcImageEdgeAverage(mrcImage* mrc, lmrcImageEdgeAverageInfo* linfo, long mode)
{
	int edge;
	int devide;
	double data;
	mrcImageParaTypeInteger x, y;

	if(1 < mrc->HeaderN.z) {
		fprintf(stderr, "Not supproted:  1 < z \n");
		exit(EXIT_FAILURE);
	}
	if(linfo->devide<1) {
		linfo->devide = 1;
	} else if(MIN(mrc->HeaderN.x,mrc->HeaderN.y) < linfo->devide) {
		linfo->devide = MIN(mrc->HeaderN.x,mrc->HeaderN.y);
	}
	if(linfo->width<1) {
		linfo->width = 1;
	} else if(MIN(mrc->HeaderN.x,mrc->HeaderN.y)/2.0 < linfo->width) {
		linfo->width =  MIN(mrc->HeaderN.x,mrc->HeaderN.y)/2.0;
	}

	for(edge=0; edge<4; edge++) {
		linfo->avg[edge]   = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*linfo->devide, "in lmrcImageEdgeAverage");			
		linfo->count[edge] = (mrcImageParaTypeReal*)memoryAllocate(sizeof(mrcImageParaTypeReal)*linfo->devide, "in lmrcImageEdgeAverage");			
		memoryClear(linfo->avg[edge],   sizeof(mrcImageParaTypeReal)*linfo->devide, 0);
		memoryClear(linfo->count[edge], sizeof(mrcImageParaTypeReal)*linfo->devide, 0);
	}

	/* 
		    Edge 2
		    -----	
	       |     |
	Edge 3 |     | Edge 1
	       |     |
	        -----
	  	    Edge 0
	*/

	edge = 0;
	for(x=0; x<mrc->HeaderN.x; x++) {
		for(y=0; y<linfo->width; y++) {
			mrcPixelDataGet(mrc, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			linfo->avg[edge][x%linfo->devide] += data; 
			linfo->count[edge][x%linfo->devide] ++;
		}
	}
	for(devide=0; devide<linfo->devide; devide++) {
		if(1<=linfo->count[edge][devide]) {
			linfo->avg[edge][devide] = linfo->avg[edge][devide]/linfo->count[edge][devide];
			DEBUGPRINT3("edge %d devide %d avg %f\n", edge, devide, linfo->avg[edge][devide]);
		} else {
			fprintf(stderr, "Something wrong: count is zero at edge %d, devide %d\n", edge, devide);
			exit(EXIT_FAILURE);
		}
	}

	edge = 1;
	for(y=0; y<mrc->HeaderN.y; y++) {
		for(x=mrc->HeaderN.x-linfo->width-1; x<mrc->HeaderN.x; x++) {
			mrcPixelDataGet(mrc, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			linfo->avg[edge][y%linfo->devide] += data; 
			linfo->count[edge][y%linfo->devide] ++;
		}
	}
	for(devide=0; devide<linfo->devide; devide++) {
		if(1<=linfo->count[edge][devide]) {
			linfo->avg[edge][devide] = linfo->avg[edge][devide]/linfo->count[edge][devide];
			DEBUGPRINT3("edge %d devide %d avg %f\n", edge, devide, linfo->avg[edge][devide]);
		} else {
			fprintf(stderr, "Something wrong: count is zero at edge %d, devide %d\n", edge, devide);
			exit(EXIT_FAILURE);
		}
	}

	edge = 2;
	for(x=0; x<mrc->HeaderN.x; x++) {
		for(y=mrc->HeaderN.y-linfo->width-1; y<mrc->HeaderN.y; y++) {
			mrcPixelDataGet(mrc, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			linfo->avg[edge][x%linfo->devide] += data; 
			linfo->count[edge][x%linfo->devide] ++;
		}
	}
	for(devide=0; devide<linfo->devide; devide++) {
		if(1<=linfo->count[edge][devide]) {
			linfo->avg[edge][devide] = linfo->avg[edge][devide]/linfo->count[edge][devide];
			DEBUGPRINT3("edge %d devide %d avg %f\n", edge, devide, linfo->avg[edge][devide]);
		} else {
			fprintf(stderr, "Something wrong: count is zero at edge %d, devide %d\n", edge, devide);
			exit(EXIT_FAILURE);
		}
	}

	
	/* */
	edge = 3;
	for(y=0; y<mrc->HeaderN.y; y++) {
		for(x=0; x<linfo->width; x++) {
			mrcPixelDataGet(mrc, x, y, 0.0, &data, mrcPixelRePart, mrcPixelHowNearest);
			linfo->avg[edge][y%linfo->devide] += data; 
			linfo->count[edge][y%linfo->devide] ++;
		}
	}
	for(devide=0; devide<linfo->devide; devide++) {
		if(1<=linfo->count[edge][devide]) {
			linfo->avg[edge][devide] = linfo->avg[edge][devide]/linfo->count[edge][devide];
			DEBUGPRINT3("edge %d devide %d avg %f\n", edge, devide, linfo->avg[edge][devide]);
		} else {
			fprintf(stderr, "Something wrong: count is zero at edge %d, devide %d\n", edge, devide);
			exit(EXIT_FAILURE);
		}
	}
}
