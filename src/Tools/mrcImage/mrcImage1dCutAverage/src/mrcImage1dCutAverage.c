/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImage1dCutAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImage1dCutAverage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImage1dCutAverage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

/* prototype */
void lmrcImage1dCutAverage(mrcImage* out, mrcImage* in ,float length);


void
main(int argc, char* argv[]) 
{
/* variables */
	long status;
	mrcImage1dCutAverageInfo info;
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* initialization */
	mrcFileRead(&in ,info.In ,"in main" ,0);

/* begin */
	lmrcImage1dCutAverage(&out ,&in ,info.Length);
 	mrcFileWrite(&out ,info.Out ,"in main" ,0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

void lmrcImage1dCutAverage(mrcImage* out, mrcImage* in ,float length)
{
/* variables */
  double size,idata,odata,val,avr,dev,x;
  int tx;

/* initialization */
  out->Header = in->Header;
  size = length / in->HeaderLength.x ;
  out->HeaderN.x = floor(size) ;
  mrcInit(out ,0);
  x=0;
  DEBUGPRINT1("%f ",size);
/* begin */
  while ( x < in->HeaderN.x-size){
    DEBUGPRINT1("%f ",x);
    val = 0.0 ;
    avr = 0.0 ;
    for (tx=0 ;tx<out->HeaderN.x ;tx++ ){
      lmrcPixelLiGet(in ,x+tx ,0 ,0 ,&idata,mrcPixelRePart ,mrcPixelHowLinear);
/*      DEBUGPRINT2("%f %f   ",x+tx ,idata);   */
      val += idata*idata ;
      avr += idata;
    }
    avr /= out->HeaderN.x;
    dev = sqrt( val/out->HeaderN.x - SQR( avr ) );
    DEBUGPRINT2("%f %f \n ",avr,dev);
    for (tx=0 ;tx<out->HeaderN.x ;tx++ ){
      lmrcPixelLiGet(in ,x+tx ,0 ,0 ,&idata,mrcPixelRePart ,mrcPixelHowLinear);
      idata = (idata-avr)/dev;
      DEBUGPRINT1("%f ",idata); 
      mrcPixelDataGet(out ,tx ,0 ,0 ,&odata ,mrcPixelRePart ,mrcPixelHowNearest);
      odata += idata;
      mrcPixelDataSet(out ,tx ,0 ,0 ,odata ,mrcPixelRePart);
    }
    x += size;
  }
  mrcStatDataSet(out,0);
}
