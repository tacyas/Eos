/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageBlockMerge ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageBlockMerge
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageBlockMerge ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototype */
void lmrcImageBlockMerge(mrcImage* in1 ,mrcImage* in2);

int
main(int argc, char* argv[]) 
{
	mrcImageBlockMergeInfo info;

/* variables */
	mrcImage in1;
	mrcImage in2;
	int i;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	DEBUGPRINT1("file:%ld \n",info.flagIn);

/* begin */
	if (info.flagIn > 1){
	  mrcFileRead(&in1, info.In[0], "in main file", 0);
	  for(i=1; i<info.flagIn; i++) {
	    DEBUGPRINT1("%d ",i);
	    mrcFileRead(&in2, info.In[i], "in main file", 0);
	    lmrcImageBlockMerge(&in1, &in2 );
	    mrcImageFree(&in2,"");
	  }
	} else {
	  fprintf(stderr,"Too few input files!\n");
	  exit(EXIT_FAILURE);
	}	
	mrcFileWrite(&in1 ,info.Out ,"in main" ,0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageBlockMerge(mrcImage* in1 ,mrcImage* in2)
{
/* variables */
  int x,y,z;
  double data1,data2,datao;
  double eps=1e-8;

/* begin */
  if (in1->HeaderMode == mrcFloatImage || 
      in1->HeaderMode == mrcShortImage ){
    for (z=0 ;z<in1->HeaderN.z ;z++){
      for (y=0 ;y<in1->HeaderN.y ;y++){
	for (x=0 ;x<in1->HeaderN.x ;x++){
	  mrcPixelDataGet(in1,x,y,z,&data1,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataGet(in2,x,y,z,&data2,mrcPixelRePart ,mrcPixelHowNearest); 
	  datao = data1+data2;
	  if (fabs(data1) > eps && fabs(data2) > eps ){
	    datao /= 2.0;
	  }
	  mrcPixelDataSet(in1,x,y,z,datao ,mrcPixelRePart);
	}
      }
    }
  }
  mrcStatDataSet(in1,0);  
}





