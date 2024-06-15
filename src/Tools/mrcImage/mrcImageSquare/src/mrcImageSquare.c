/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSquare ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSquare
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSquare ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/* prototypes */
void lmrcImageSquare(mrcImage* in);
void lmrcImageRoot(mrcImage* in ,double eps);

/*
Example:
typedef struct lmrcImageSquareInfo {
	float a;
	int   b;
} lmrcImageSquareInfo;

typedef enum lmrcImageSquareMode {
	a=0,
	b=1
} lmrcImageSquareMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageSquareInfo info;

/* variables */
	mrcImage in;
	

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	
/* begin */
	DEBUGPRINT("Program Start\n");
	if (info.mode==0){
	  lmrcImageSquare(&in);
	}else if (info.mode==1){
	  lmrcImageRoot(&in,info.eps);
	}
	mrcFileWrite(&in ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0: Square \n");
	fprintf(stderr, "mode 1: Square Root\n");
}

void lmrcImageSquare(mrcImage* in)
{
/* variables */
  int x,y,z;
  double data,datao;
  
/* begin */
  for (z=0 ;z<in->HeaderN.z ;z++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (x=0 ;x<in->HeaderN.x ;x++){
	mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
	datao = data*data;
	mrcPixelDataSet(in,x,y,z,datao ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in,0);  
}


void lmrcImageRoot(mrcImage* in ,double eps)
{
/* variables */
  int x,y,z;
  double data,datao;
  
/* begin */
  for (z=0 ;z<in->HeaderN.z ;z++){
    for (y=0 ;y<in->HeaderN.y ;y++){
      for (x=0 ;x<in->HeaderN.x ;x++){
	mrcPixelDataGet(in,x,y,z,&data,mrcPixelRePart ,mrcPixelHowNearest); 
       	if (data > eps){
	  datao = sqrt(data);
	}else {
	  datao = 0;
	  if (data < 0){
	    fprintf(stderr,"Data is negative! (x,y,z)=(%d,%d,%d) \n",x,y,z);
	  }
	}
	mrcPixelDataSet(in,x,y,z,datao ,mrcPixelRePart);
      }
    }
  }
  mrcStatDataSet(in,0);  
}
