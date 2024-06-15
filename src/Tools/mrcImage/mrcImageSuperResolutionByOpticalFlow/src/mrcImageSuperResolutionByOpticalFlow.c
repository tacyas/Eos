/*
# mrcImageSuperResolutionByOpticalFlow : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSuperResolutionByOpticalFlow
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
#include "Memory.h"
#include "mrcImage.h"

typedef struct lmrcImageSuperResolutionByOpticalFlowInfo {
  // In
  mrcImage* Ins;
	mrcImage Vx;
	mrcImage Vy;
	mrcImage Vz;
  double Enlarge;
  mrcImage Avg;
} lmrcImageSuperResolutionByOpticalFlowInfo;

typedef enum lmrcImageSuperResolutionByOpticalFlowMode {
	a=0,
	b=1
} lmrcImageSuperResolutionByOpticalFlowMode;

extern int lmrcImageSuperResolutionByOpticalFlow(mrcImage* out, lmrcImageSuperResolutionByOpticalFlowInfo* linfo, lmrcImageSuperResolutionByOpticalFlowMode mode);

int
main(int argc, char* argv[]) 
{
	mrcImageSuperResolutionByOpticalFlowInfo info;
	lmrcImageSuperResolutionByOpticalFlowInfo linfo;
  mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
  if(info.flagIn3) {
    linfo.Ins = (mrcImage*)memoryAllocate(sizeof(mrcImage)*3, "in main");
    mrcFileRead(&(linfo.Ins[0]), info.In1, "in main", 0);
    mrcFileRead(&(linfo.Ins[1]), info.In2, "in main", 0);
    mrcFileRead(&(linfo.Ins[2]), info.In3, "in main", 0);
  }
  if(info.flagVx) {
    mrcFileRead(&(linfo.Vx), info.Vx, "in main", 0);
    mrcFileRead(&(linfo.Vy), info.Vy, "in main", 0);
    mrcFileRead(&(linfo.Vz), info.Vz, "in main", 0);
  }

  linfo.Enlarge = info.Enlarge;

  lmrcImageSuperResolutionByOpticalFlow(&out, &linfo, info.mode);
  if(info.flagOutAVG) {
    mrcFileWrite(&(linfo.Avg), info.OutAVG, "in main", 0);
  }
  mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

int 
lmrcImageSuperResolutionByOpticalFlow(mrcImage* out, lmrcImageSuperResolutionByOpticalFlowInfo* linfo, lmrcImageSuperResolutionByOpticalFlowMode mode)
{
  mrcImageParaTypeReal x, y, z;
  mrcImageParaTypeReal orgx, orgy, orgz;
  double vx, vy, vz;
  double data;
  double weight;
  double sumData;
  double sumWeight;

  out->Header = linfo->Ins[1].Header;
  out->HeaderN.x *= linfo->Enlarge;
  out->HeaderN.y *= linfo->Enlarge;
  out->HeaderN.z *= linfo->Enlarge;
  out->HeaderLength.x /= linfo->Enlarge;
  out->HeaderLength.y /= linfo->Enlarge;
  out->HeaderLength.z /= linfo->Enlarge;

  mrcInit(out, NULL);

  linfo->Avg.Header = out->Header;
  mrcInit(&(linfo->Avg), NULL);

  for(z=0; z<out->HeaderN.z; z++) {
  for(y=0; y<out->HeaderN.y; y++) {
  for(x=0; x<out->HeaderN.x; x++) {
    orgx = x/linfo->Enlarge;
    orgy = y/linfo->Enlarge;
    orgz = z/linfo->Enlarge;

    mrcPixelDataGet(&(linfo->Vx), orgx, orgy, orgz, &vx, mrcPixelRePart, mrcPixelHowCubicConv);   
    mrcPixelDataGet(&(linfo->Vy), orgx, orgy, orgz, &vy, mrcPixelRePart, mrcPixelHowCubicConv);   
    mrcPixelDataGet(&(linfo->Vz), orgx, orgy, orgz, &vz, mrcPixelRePart, mrcPixelHowCubicConv);   

    sumData = 0;
    sumWeight = 0;
    mrcPixelDataGet(&(linfo->Ins[0]), orgx - vx, orgy - vy, orgz - vz, &data, mrcPixelRePart, mrcPixelHowCubicConv);   
    sumWeight += 0.5;
    sumData   += 0.5*data;
    mrcPixelDataGet(&(linfo->Ins[1]), orgx,      orgy,     orgz, &data, mrcPixelRePart, mrcPixelHowCubicConv);   
    sumWeight += 1.0;
    sumData   += 1.0*data;
    mrcPixelDataGet(&(linfo->Ins[2]), orgx + vx, orgy + vy, orgz + vz, &data, mrcPixelRePart, mrcPixelHowCubicConv);   
    sumWeight += 0.5;
    sumData   += 0.5*data;

    data = data/sumWeight;
    mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
    sumData = 0;
    sumWeight = 0;
    mrcPixelDataGet(&(linfo->Ins[0]), orgx, orgy, orgz, &data, mrcPixelRePart, mrcPixelHowCubicConv);   
    sumWeight += 0.5;
    sumData   += 0.5*data;
    mrcPixelDataGet(&(linfo->Ins[1]), orgx, orgy, orgz, &data, mrcPixelRePart, mrcPixelHowCubicConv);   
    sumWeight += 1.0;
    sumData   += 1.0*data;
    mrcPixelDataGet(&(linfo->Ins[2]), orgx, orgy, orgz, &data, mrcPixelRePart, mrcPixelHowCubicConv);   
    sumWeight += 0.5;
    sumData   += 0.5*data;

    data = data/sumWeight;
    mrcPixelDataSet(&(linfo->Avg), x, y, z, data, mrcPixelRePart);
  }
  }
  }

  return 0;
}
