/*
# lmrcImageCalcArea : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageCalcArea 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "./lmrcImageDensity.h"
#include "./lmrcImageLabeling.h"
#include "./lmrcImageCalcArea.h"

void
lmrcImageCalcArea(mrcImage* area, mrcImage* label, mrcImage* in, int neighbor, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data, data0, data1;
	int maxLabel, i, inde;
	int* nLabel;
	int total;

	DEBUGPRINT("lmrcImageCalcArea Start\n");
	lmrcImageLabeling(label, in, neighbor, 0);
	mrcStatDataSet(label, 0);

	maxLabel = (int)(label->HeaderAMax+0.5);
	nLabel = (int*)memoryAllocate(sizeof(int)*(maxLabel+1), "in lmrcImageCalcArea");

	for(i=0; i<maxLabel+1; i++) {
		nLabel[i] = 0;
	}
	for(x=0; x<label->HeaderN.x; x++) {
	for(y=0; y<label->HeaderN.y; y++) {
	for(z=0; z<label->HeaderN.z; z++) {
		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		i = (int)(data+0.5);
		nLabel[i]++;
	}
	}
	}

	area->Header = in->Header;
	mrcInit(area, NULL);

	for(x=0; x<area->HeaderN.x; x++) {
	for(y=0; y<area->HeaderN.y; y++) {
	for(z=0; z<area->HeaderN.z; z++) {
		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(fabs(data)<1e-6) {
			mrcPixelDataSet(area,  x, y, z, 0, mrcPixelRePart);
		} else {
			mrcPixelDataSet(area,  x, y, z, nLabel[(int)(data+0.5)], mrcPixelRePart);
		}
	}
	}
	}

	mrcStatDataSet(area, 0);
}


void
lmrcImageCalcDensityWeightedArea(mrcImage* area, mrcImage* label, mrcImage* in, mrcImage* inDensity, int neighbor, int mode)
{
	mrcImageParaTypeReal x, y, z;
	double data, data0, data1;
	int maxLabel, i, inde;
	double* sum;
	int total;
  lmrcImageDensityInfoInfo linfo;

	DEBUGPRINT("lmrcImageCalcArea Start\n");
	lmrcImageLabeling(label, in, neighbor, 0);
	mrcStatDataSet(label, 0);

	maxLabel = (int)(label->HeaderAMax+0.5);
	sum = (double*)memoryAllocate(sizeof(double)*(maxLabel+1), "in lmrcImageCalcArea");

	for(i=0; i<maxLabel+1; i++) {
		sum[i] = 0;
	}
	for(x=0; x<label->HeaderN.x; x++) {
	for(y=0; y<label->HeaderN.y; y++) {
	for(z=0; z<label->HeaderN.z; z++) {
		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(inDensity, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
		i = (int)(data+0.5);
		sum[i]+=data1;
	}
	}
	}

	area->Header = in->Header;
	mrcInit(area, NULL);

	for(x=0; x<area->HeaderN.x; x++) {
	for(y=0; y<area->HeaderN.y; y++) {
	for(z=0; z<area->HeaderN.z; z++) {
		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
		if(fabs(data)<1e-6) {
			mrcPixelDataSet(area,  x, y, z, 0, mrcPixelRePart);
		} else {
			mrcPixelDataSet(area,  x, y, z, sum[(int)(data+0.5)], mrcPixelRePart);
		}
	}
	}
	}

  linfo.deltaVolume = 0.25;
  lmrcImageDensityInfo(&linfo, area, mrcImageDensityInfoPercentageVolume);

  switch(mode) {
    case 0: 
      break;
    case 1: // 75%
    	for(x=0; x<area->HeaderN.x; x++) {
    	for(y=0; y<area->HeaderN.y; y++) {
    	for(z=0; z<area->HeaderN.z; z++) {
    		mrcPixelDataGet(label, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
    		mrcPixelDataGet(area, x, y, z, &data1, mrcPixelRePart, mrcPixelHowNearest);
    		if(fabs(data)<1e-6) {
    			mrcPixelDataSet(area,  x, y, z, 0, mrcPixelRePart);
    		} else {
          data0 = data1/linfo.percentageVolume.data[1]*0.75;
    			mrcPixelDataSet(area,  x, y, z, data0, mrcPixelRePart);
    		}
    	}
    	}
      }
      break;
    default: {
      fprintf(stderr, "Not supported mode in lmrcImageCalcDensityWeightedArea: %d\n", mode);
      exit(EXIT_FAILURE);
      break;
    }
  }
	mrcStatDataSet(area, 0);
}


