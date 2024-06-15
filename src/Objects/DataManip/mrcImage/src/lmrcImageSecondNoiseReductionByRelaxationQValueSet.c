/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrcImageSecondNoiseReductionByRelaxationQValueSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmrcImageSecondNoiseReductionByRelaxationQValueSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmrcImageSecondNoiseReductionByRelaxationQValueSet ver%I%; Date:%D% %Z%";
#include "Memory.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageFirstNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxation.h"
#include "lmrcImageSecondNoiseReductionByRelaxationQValueSet.h"

void lmrcImageSecondNoiseReductionByRelaxationQValueSet(mrcImage* q, double* d, mrcImage* p0, double* r,
							lmrcImageNoiseReductionByRelaxationInfo* info)
{
  double* qtemp;
  double* ptemp;
  double qpix;
  
  int dxmax, dymax, dzmax;
  int dxmin, dymin, dzmin;
  int ix, iy, iz;
  int x,y,z;
  int i,j,k,l,m;
  int pix;
  
  
  qtemp = (double*)memoryAllocate(sizeof(double)*(info->classNumber), "in main");
  ptemp = (double*)memoryAllocate(sizeof(double)*(info->ddimx*info->ddimy*info->ddimz), "in main");
  
  dxmin = -(info->ddimx-1)/2; 
  dxmax = (info->ddimx-1)/2;
  dymin = -(info->ddimy-1)/2; 
  dymax = (info->ddimy-1)/2;
  dzmin = -(info->ddimz-1)/2; 
  dzmax = (info->ddimz-1)/2;		
  
  for (z=0; z<p0[0].HeaderN.z; z++){
    for (y=0; y<p0[0].HeaderN.y; y++){
      DEBUGPRINT1(" y = %d\n", y);
      for (x=0; x<p0[0].HeaderN.x; x++){
	
	for (l=0; l<info->classNumber; l++){
	  
	  qpix = 0.0;
	  for (m=0; m<info->classNumber; m++){
	    
	    qtemp[m] = 0.0;
	    for (ix = dxmin, i=0; ix<=dxmax; ix++, i++){
	      for (iy = dymin, j=0; iy<=dymax; iy++, j++){
		for (iz = dzmin, k=0; iz<=dzmax; iz++, k++){
		  pix = XYZCOORD(i, j, k, info->ddimx, info->ddimy, info->ddimz);
		  mrcPixelDataGet(&(p0[m]), x+ix, y+iy, z+iz, &ptemp[pix], mrcPixelRePart, mrcPixelHowNearest);
		  qtemp[m] += d[pix]*ptemp[pix];
		}
	      }	
	    }
	    
	    qpix += qtemp[m] * r[m+l*info->classNumber];
	  }
	  mrcPixelDataSet(&(q[l]), x, y, z, qpix, mrcPixelRePart);
	}
      
      }
    }
  }
}
