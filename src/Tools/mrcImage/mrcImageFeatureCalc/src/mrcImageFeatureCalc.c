/*
# mrcImageFeatureCalc : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageFeatureCalc
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "lmrcImageFeatureCalc.h"

/*
Example:
typedef struct lmrcImageFeatureCalcInfo {
	float a;
	int   b;
} lmrcImageFeatureCalcInfo;

typedef enum lmrcImageFeatureCalcMode {
	a=0,
	b=1
} lmrcImageFeatureCalcMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageFeatureCalcInfo info;
	lmrcImageFeatureList    linfo;
	mrcImage in;
	mrcImage out;
	mrcImage label;
  mrcImage density;
  mrcImage densityWeightedArea;
	lmrcImagePerimeterCalcInfo lperi;
	mrcImage peri;
	lmrcImageSurfaceAreaCalcInfo lsurface;
	mrcImage surfaceArea;
	int i;
	double data;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In, "in main", 0);
  if(info.flagInDensity) {
	  mrcFileRead(&density, info.InDensity, "in main", 0);
    linfo.density = &density;
  }

	DEBUGPRINT("lmrcImageLabeling\n");
	lmrcImageLabeling(&label, &in, info.neighbor, 1);
	
	DEBUGPRINT("lmrcImageBasicFeatureCalc\n");
	linfo.flagNumber = 0;
	lmrcImageBasicFeatureCalc(&out, &linfo, &label, info.mode);

	if(info.flagOutPerimeter || info.flagOutChain) {
		if(in.HeaderN.z<=1) {
			lperi.flagArea=0;
			switch(info.neighbor) {
				case 0:
				case 4: {
					lperi.Neighbor=4;
					lmrcImagePerimeterCalc(&peri, &in, &lperi, 1);
					break;
				}
				case 8: {
					lperi.Neighbor=8;
					lmrcImagePerimeterCalc(&peri, &in, &lperi, 0);
					break;	
				}
				default: {
					fprintf(stderr, "Not supported neighbor: %ld\n", info.neighbor);
					fprintf(stderr, "Use 6-neighbor\n");
					lmrcImagePerimeterCalc(&peri, &in, &lperi, 1);
					break;
				}
			}
			for(i=0; i<=linfo.Number; i++) {
				mrcPixelDataGet(&peri, 
					linfo.each[i].bottomLeft.x,
					linfo.each[i].bottomLeft.y,
					linfo.each[i].bottomLeft.z,
					&linfo.each[i].perimeter,
					mrcPixelRePart,
					mrcPixelHowNearest);
				linfo.each[i].flagPerimeter = 1;			
			}
      if(info.flagOutPerimeter) {
			  mrcFileWrite(&peri, info.OutPerimeter, "in main", 0);
      }
      if(info.flagOutChain) {
			  mrcFileWrite(lperi.ChainCode, info.OutChain, "in main", 0);
      }
		} else {
			fprintf(stderr, "Not supported for 3D image\n");
		}
	}

	if(info.flagOutSurfaceArea) {
		if(1<in.HeaderN.z) {
			lsurface.Neighbor = info.neighbor; 
			if(lsurface.Neighbor==0) {
				lsurface.Neighbor = 6;
			}
			lsurface.Mode = 0;
			lsurface.flagArea = 0;
			DEBUGPRINT("lmrcImageSurfaceAreaCalc Start\n");
			lmrcImageSurfaceAreaCalc(&surfaceArea, &in, &lsurface, 0); 
			DEBUGPRINT("lmrcImageSurfaceAreaCalc End\n");
			for(i=0; i<=linfo.Number; i++) {
				mrcPixelDataGet(&surfaceArea, 
					linfo.each[i].bottomLeft.x,
					linfo.each[i].bottomLeft.y,
					linfo.each[i].bottomLeft.z,
					&linfo.each[i].surfaceArea,
					mrcPixelRePart,
					mrcPixelHowNearest);
				linfo.each[i].flagSurfaceArea = 1;			
			}
			mrcFileWrite(&surfaceArea, info.OutSurfaceArea, "in main", 0);
		} else {
			fprintf(stderr, "Not supported for 2D image\n");
		}

	}
	DEBUGPRINT("lmrcImageFeaturePrint\n");
	lmrcImageFeaturePrint(info.fptOut, &linfo, info.mode);	
	if(info.flagOutGC) {
		mrcFileWrite(&out, info.OutGC, "in main", 0);
	}
	if(info.flagOutLabel) {
		mrcFileWrite(&label, info.OutLabel, "in main", 0);
	}
  if(info.flagOutDensityWeightedArea) {
		mrcFileWrite(&densityWeightedArea, info.OutDensityWeightedArea, "in main", 0);
  }
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Mode\n");
}
