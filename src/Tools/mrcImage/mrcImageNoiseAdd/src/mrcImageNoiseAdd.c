/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNoiseAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNoiseAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNoiseAdd ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#define DEBUG
#include "../inc/config.h"
#include "Random.h"
#include "mrcImage.h"

double lmrcImageStandardDeviationwithLH(mrcImage* in, double H, double L);

int
main(int argc, char* argv[]) 
{
	mrcImageNoiseAddInfo info;
	mrcImage in;
	mrcImageParaTypeReal x, y, z;
	double data,SD, NS;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	
	mrcFileRead(&in, info.In, "in main", 0);
	if (!info.flagSD){
	  if (!info.flagH){
	    info.H = in.HeaderAMax;
	  } 
	  if (!info.flagL){
	    info.L = in.HeaderAMin;
	  } 
	  SD = lmrcImageStandardDeviationwithLH(&in, info.H, info.L);
	} else {
	  SD = info.SD;
	}
	if(info.flagNS) {
		NS = info.NS;
	} else if(info.flagSN){
		if(info.SN!=0) {	
			NS = 1/info.SN;
		} else {
			fprintf(stderr, "Not supported for SN=0\n");
			exit(EXIT_FAILURE);
		}
	} else {
		NS = 1;
	}

	DEBUGPRINT1("SD %f \n",SD); 
	srandomByTime();
	for(x=0; x<in.HeaderN.x; x++) {
	  for(y=0; y<in.HeaderN.y; y++) {
	    for(z=0; z<in.HeaderN.z; z++) {
	      mrcPixelDataGet(&in, x, y, z, &data, mrcPixelRePart,  mrcPixelHowNearest); 
	      data += NS*SD*randomNormalGet(2);
	      mrcPixelDataSet(&in, x, y, z, data, mrcPixelRePart); 
	    }
	  }
	}
	mrcStatDataSet(&in, 0);
	mrcFileWrite(&in, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}
void
additionalUsage()
{
}

double lmrcImageStandardDeviationwithLH(mrcImage* in, double H, double L)
{
/* variables */
	long x,y,z,n;
	double sum2,sum,data;

/* begin */
	sum2 = 0.0;
	sum = 0.0;
	n=0;
	for(z=0 ;z < in->HeaderN.z ;z++) {
	  for(x=0 ;x < in->HeaderN.x ;x++) {
	    for(y=0 ;y < in->HeaderN.y ;y++){
	      mrcPixelDataGet(in ,x ,y ,z ,&data ,mrcPixelRePart ,mrcPixelHowNearest);
	      if (data > L && data < H){
		sum2 += data*data;
		sum += data;
		n++;
	      }
	    }
	  }
	}
	sum /= n;
	sum2 /= n;
	sum2 -= sum*sum;
	sum2 = sqrt(sum2);
	return(sum2);
}

