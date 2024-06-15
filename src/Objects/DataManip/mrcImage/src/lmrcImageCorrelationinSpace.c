#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#undef DEBUG
#include "genUtil.h"
#include "../inc/mrcImage.h"
#include "mrcRefUtil.h"


double lmrcImageCorrelationinSpace(mrcImage* in,mrcImage* ref,int mode)
{
/* valuables */
  int x,y,z;
  double irsum,isum,rsum,datain,dataref,cor;

/* begin */
  irsum=isum=rsum=0;
  if (in->HeaderN.x != ref->HeaderN.x || in->HeaderN.y != ref->HeaderN.y || in->HeaderN.z != ref->HeaderN.z){
    fprintf(stderr,"Size of two files is different!\n");
    exit(1);
  }
  for(x=0 ;x<in->HeaderN.x ;x++){
    for(y=0 ;y<in->HeaderN.y ;y++){
      for(z=0 ;z<in->HeaderN.z ;z++){
	mrcPixelDataGet(in ,x ,y ,z ,&datain ,mrcPixelRePart ,mrcPixelHowNearest);
	mrcPixelDataGet(ref ,x ,y ,z ,&dataref ,mrcPixelRePart ,mrcPixelHowNearest);
	isum += datain*datain;
	rsum += dataref*dataref;
	irsum += datain*dataref;
      }
    }
  }
  cor=irsum/sqrt(rsum*isum);
  return(cor);
}
