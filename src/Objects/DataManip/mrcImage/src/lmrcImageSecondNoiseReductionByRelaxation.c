/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSecondNoiseReductionByRelaxation ver%I%; Date:%D% %Z%";
#include "mrcImage.h"
#undef DEBUG
#include "genUtil.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"


void lmrcImageSecondNoiseReductionByRelaxation(mrcImage* out, mrcImage* pPrev, mrcImage* q, double* densityLevel,
					       lmrcImageNoiseReductionByRelaxationInfo* info)
{
  double    qpix;
  double    data;
  double    sum;
  int x,y,z;
  int m;
  double p, pmax;
  int maxi;
  
  for (z=0; z<pPrev[0].HeaderN.z; z++){
    DEBUGPRINT1("z: %d\n", z);
    for (y=0; y<pPrev[0].HeaderN.y; y++){
      DEBUGPRINT1("y: %d\n", y);
      for (x=0; x<pPrev[0].HeaderN.x; x++){
	
	/* Calculate the Next Probability ( pNext ) and Set data into Output File */
	/* First : Summation */
	sum = 0.0;
	for (m=0; m<info->classNumber; m++){
	  mrcPixelDataGet(&(pPrev[m]), x, y, z, &p, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(&(q[m]), x, y, z, &qpix, mrcPixelRePart, mrcPixelHowNearest);
	  sum += p*(qpix+1);
	}
	/* Second : Next Probability */
	maxi = 0;
	pmax = 0;
	for (m=0; m<info->classNumber; m++){
	  mrcPixelDataGet(&(pPrev[m]), x, y, z, &p, mrcPixelRePart, mrcPixelHowNearest);
	  mrcPixelDataGet(&(q[m]), x, y, z, &qpix, mrcPixelRePart, mrcPixelHowNearest);
	  p = p*(qpix+1)/sum;
	  mrcPixelDataSet(&(pPrev[m]), x, y, z, p, mrcPixelRePart);
	  if( pmax < p ){
	    pmax  = p;
	    maxi  = m;
	  }
	}
	data = densityLevel[maxi];
	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);
	
      }
    }
  } 
}
