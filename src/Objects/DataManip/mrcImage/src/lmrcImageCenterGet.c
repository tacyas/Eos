#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "time.h"
#include "Random.h"


void lmrcImageCenterGet(mrcImage* out ,mrcImage* in ,int Nx ,int Ny ,int Nz ,float Cx ,float Cy ,float Cz ,int mode)
{
/* variables */
  double data,ix,iy,iz,x,y,z;

/* initialization */
  out->Header = in->Header;
  out->HeaderN.x = Nx;
  out->HeaderN.y = Ny;
  out->HeaderN.z = Nz;
  mrcInit(out,NULL);

/* begin */
  ix = Cx - (float)(Nx-1)/2.0 ;
  iy = Cy - (float)(Ny-1)/2.0 ;
  iz = Cz - (float)(Nz-1)/2.0 ;
  DEBUGPRINT2("ix,iy %f %f \n",ix,iy);
  for (z = iz ; z < iz+Nz ;z++){
  for (y = iy ;y < iy+Ny ;y++){
  for (x = ix ;x < ix+Nx ;x++){
	DEBUGPRINT3("%f,%f,%f\t ",x,y,z);
	mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mode);
	mrcPixelDataSet(out ,x-ix ,y-iy ,z-iz ,data, mrcPixelRePart);
  }
  }
  }
  mrcStatDataSet(out,0);
}
