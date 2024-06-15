/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefImageCorrelation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefImageCorrelation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefImageCorrelation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"

void lmrcRefImageCorrelation(long* maxn, double* max, long* minn, double* min, mrcImage* in, mrcImage* ref, int mode);

int
main(int argc, char* argv[]) 
{
	mrcRefImageCorrelationInfo info;

/* variables */
        mrcImage in;
        mrcImage ref; 
	mrcImage out;
	
	double max,min;
	long maxn,minn,i;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");
	
/* begin */
	mrcFileRead(&ref ,info.Ref ,"in main",0);
	if (!info.flagInArray){
	  mrcFileRead(&in ,info.In ,"in main" ,0);
	  lmrcRefImageCorrelation(&maxn, &max, &minn, &min, &in, &ref, 0);
	  fprintf(stdout,"min %d %g\n",minn,min);
	  fprintf(stdout,"max %d %g\n",maxn,max);
	} else {
	  for (i=0 ;i<info.flagInArray ;i++){
	    mrcFileRead(&in ,info.InArray[i] ,"in main" ,0);
	    lmrcRefImageCorrelation(&maxn, &max, &minn, &min, &in, &ref, 1);
	    fprintf(stdout,"%s min %d %g max %d %g\n",info.InArray[i],minn,min,maxn,max);
	    mrcImageFree(&in,"");
	  }
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0: To find the images in the reference file of min and max correlation.  Correlation is calclated in the real space.\n");
	fprintf(stderr, "mode 1: To calculate the correlation between one image of the reference file and input file.  The calculation is performed in the fourier space and the output is a mrc image file.  option z is needed.\n");
}

void lmrcRefImageCorrelation(long* maxn, double* max, long* minn, double* min, mrcImage* in, mrcImage* ref, int mode)
{
  int i;
  mrcImage tmp,tmpin;
  double data;
  mrcImageParaTypeRealCoord shift;
  
  if (ref->HeaderN.x != in->HeaderN.x || ref->HeaderN.y != in->HeaderN.y){
      lmrcImageCenterGet(&tmpin ,in , ref->HeaderN.x, ref->HeaderN.y, 1, 
			(in->HeaderN.x - 1.0)/2.0, (in->HeaderN.y - 1.0)/2.0, 0, 2);
      shift.x = shift.y = shift.z =0;
      in->Header=tmpin.Header;
      mrcInit(in,NULL);
      lmrcImageCopy(in,&tmpin,shift);
  }
  for (i=1; i<ref->HeaderN.z; i++){
    lmrc3DZ1ImgGet(&tmp ,ref ,i);
    data=lmrcImageCorrelationinSpace(in, &tmp, 0);
    mrcImageFree(&tmp,"");
    if (i==1){
      *min = *max = data;
      *minn = *maxn = 0;
    } else if (*min > data){
      *min = data;
      *minn = i-1; 
    } else if (*max < data){
      *max = data;
      *maxn = i-1;
    }
    if (mode == 0){
      fprintf(stdout,"%d %g\n",i-1,data);
    }
  }
}
