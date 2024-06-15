/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSymmetryFind ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSymmetryFind 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSymmetryFind ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION

#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageCentre.h"

void lmrcImageCenterOfMassCalculate(lmrcImageCenterOfMass *centerOfMass,mrcImage in1){
  int x,y,z;
  double data;
  double sum=0.0,xsum=0.0,ysum=0.0,zsum=0.0; 
  
  for (z=0; z<in1.HeaderN.z; z++){
  for (y=0; y<in1.HeaderN.y; y++){
  for (x=0; x<in1.HeaderN.x; x++){
	mrcPixelDataGet(&in1,x,y,z, &data, mrcPixelRePart, mrcPixelHowNearest);
	data -= in1.HeaderAMin;
	sum+=data;
	xsum+=x*data;
	ysum+=y*data;
	zsum+=z*data;
  }
  }
  } 
  centerOfMass->x = xsum/sum;
  centerOfMass->y = ysum/sum; 
  centerOfMass->z = zsum/sum; 
}


void lmrcImageShiftCenterOfMassIntoImageCenter(mrcImage* out, mrcImage* in, mrcPixelDataHowToGet mode)
{
	lmrcImageCenterOfMass linfo;
	mrcImageParaTypeRealCoord para;

	lmrcImageCenterOfMassCalculate(&linfo, *in);
	para.x = -linfo.x; 	
	para.y = -linfo.y; 	
	para.z = -linfo.z; 	

	lmrcImageShift(out, in, para, mode);  
}
