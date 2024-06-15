/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageAdd ver%I%; Date:%D% %Z%";
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
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageMultiplying.h"

/* prototype */
void llmrcImageAdd2(mrcImage* in1 ,mrcImage* in2);


int
main(int argc, char* argv[]) 
{
	mrcImageAddInfo info;

/* variables */
	mrcImage in1;
	mrcImage in2;
	mrcImage out;
	long i;
	float value;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	DEBUGPRINT1("file:%ld \n",info.flagIn);
/* begin */
	if (!info.flagIn && info.flagIn1 && info.flagIn2){
	  mrcFileRead(&in1 ,info.In1 ,"in main" ,0);
	  mrcFileRead(&in2 ,info.In2 ,"in main" ,0);
	  if (in1.HeaderN.x !=in2.HeaderN.x || in1.HeaderN.y !=in2.HeaderN.y){
	    fprintf(stderr,"Warning! Image size is different.\n");
	  }
	  llmrcImageAdd2(&in1 ,&in2);
	} else if (info.flagIn) {
	  mrcFileRead(&in1, info.In[0], "in main file", 0);
	  for(i=1; i<info.flagIn; i++) {
	    mrcFileRead(&in2, info.In[i], "in main file", 0);
	    llmrcImageAdd2(&in1, &in2 );
	    mrcImageFree(&in2,"");
	  }
	} else {
	  fprintf(stderr,"Too few input files!\n");
	  exit(EXIT_FAILURE);
	}
	switch(info.mode) {
		case 0:{
			mrcFileWrite(&in1 ,info.Out ,"in main" ,0);
			break;
		}
		case 1:{
			if (info.flagIn==0){
				value = 2;
			} else {
				value = info.flagIn; 
			}
			lmrcImageMultiplying(&out, &in1, 1/value, 2);
			DEBUGPRINT1("Add * %15.6f \n", 1/value);
			mrcFileWrite(&out ,info.Out ,"in main" ,0);
			break;
		}
		default:{
			fprintf(stderr, "Not supported Mode: %ld\n", info.mode);
			exit(EXIT_FAILURE);
		}
	}
	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	 fprintf(stderr, "----- Additional Usage -----\n");
	 fprintf(stderr, "mode 0:Add \n");
	 fprintf(stderr, "mode 1:Add / (Number of Pictures)\n");
}

void llmrcImageAdd2(mrcImage* in1 ,mrcImage* in2)
{
/* variables */
  int x,y,z,X,Y,Z,Zmax;
  double data1,data2,datao;
  double data1r,data2r,data1i,data2i,dataor,dataoi;
  

/* begin */
  if (IsImage(in1, "llmrcImageAdd2", 0)) {
    for (z=0 ;z<in1->HeaderN.z ;z++){
      for (y=0 ;y<in1->HeaderN.y ;y++){
	for (x=0 ;x<in1->HeaderN.x ;x++){
	  mrcPixelDataGet(in1,x,y,z,&data1,mrcPixelRePart ,mrcPixelHowNearest); 
	  mrcPixelDataGet(in2,x,y,z,&data2,mrcPixelRePart ,mrcPixelHowNearest); 
	  datao = data1+data2;
	  mrcPixelDataSet(in1,x,y,z,datao ,mrcPixelRePart);
	}
      }
    }
  } else if (IsFT(in1, "llmrcImageAdd2", 0)) {
    (in1->HeaderN.z == 1)?(Zmax=1):(Zmax=in1->HeaderN.z /2);
    for (Z = - in1->HeaderN.z / 2; Z < Zmax  ;Z++){
      for (Y = - in1->HeaderN.y / 2; Y < in1->HeaderN.y/ 2 ;Y++){
	for (X = 0; X <= in1->HeaderN.x / 2 ;X++){
	  mrcPixelDataGet(in1 ,X ,Y ,Z ,&data1r ,mrcPixelRePart ,mrcPixelHowNearest);
	  mrcPixelDataGet(in2 ,X ,Y ,Z ,&data2r ,mrcPixelRePart ,mrcPixelHowNearest);
	  mrcPixelDataGet(in1 ,X ,Y ,Z ,&data1i ,mrcPixelImPart ,mrcPixelHowNearest);
	  mrcPixelDataGet(in2 ,X ,Y ,Z ,&data2i ,mrcPixelImPart ,mrcPixelHowNearest);
	  dataor = data1r + data2r;
	  dataoi = data1i + data2i;
	  mrcPixelDataSet(in1 ,X ,Y ,Z ,dataor ,mrcPixelRePart);
	  mrcPixelDataSet(in1 ,X ,Y ,Z ,dataoi ,mrcPixelImPart);      
	}
      }
    }
  }
  mrcStatDataSet(in1,0);  
}
