/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefNoiseAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefNoiseAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefNoiseAdd ver%I%; Date:%D% %Z%";
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
#include "Random.h"

/* prototype */
void lmrcRefNoiseAdd(mrcImage* image ,double noise ,int mode);
double lmrcImageStandardDeviationwithThreshold(mrcImage* in, double h, double l);

void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefNoiseAddInfo info;

/* variables */
	mrcImage image;
	double sd;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);


/* begin */
	mrcFileRead(&image ,info.In ,"in main" ,0);
	if (info.mode){
	  if (!info.flagH){
	    info.H = image.HeaderAMax;
	  } 
	  if (!info.flagL){
	    info.L = image.HeaderAMin;
	  }
	  sd = lmrcImageStandardDeviationwithThreshold(&image, info.H, info.L);
	  DEBUGPRINT1("3 %f ",sd);
	} else {
	  sd = lmrcRefStandardDeviation(&image);
	  DEBUGPRINT1("%f ",sd);
	}
	lmrcRefNoiseAdd(&image ,info.Noise*sd ,info.mode);
	mrcFileWrite(&image ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout ,"----- mode -----\n");
fprintf(stdout ,"0: for Reffile\n");
fprintf(stdout ,"1: for normal image file\n");
}

void lmrcRefNoiseAdd(mrcImage* image ,double noise ,int mode)
{
/* variables */
  int x,y,z,sz;
  double data;

/* begin */
  lRandShuffle();
  sz = (mode)?0:1;
  for (z=sz ;z<image->HeaderN.z ;z++){
    for (y=0 ;y<image->HeaderN.y ;y++){
      for (x=0 ;x<image->HeaderN.x ;x++){
	mrcPixelDataGet(image ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	data += randomNormalGet(0)*noise;
	mrcPixelDataSet(image ,x ,y ,z ,data  ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(image,NULL);
}

double lmrcImageStandardDeviationwithThreshold(mrcImage* in, double h, double l)
{
/* variables */
	int x,y,z,n;
	double sum2,sum,data;

/* begin */
	sum2 = 0.0;
	sum = 0.0;
	n = 0;
	for (z=0; z < in->HeaderN.z; z++){
	  for(y=0 ;y < in->HeaderN.y ;y++){
	    for(x=0 ;x < in->HeaderN.x ;x++) {
	      mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	      if (data < h && data > l){
		sum2 += data*data;
		sum += data;
		n++;
	      }
	    }
	  }
	}
	DEBUGPRINT3("%f %f %f ",sum2,sum,sum*sum);
	sum /= n;
	sum2 /= n;
	sum2 -= sum*sum;
	if (sum2 != 0){
	  sum2 = sqrt(sum2);
	} 
	return(sum2);
}

 




