/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFTMeridianEquatorRedece ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFTMeridianEquatorRedece
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFTMeridianEquatorRedece ver%I%; Date:%D% %Z%";
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
void lmrcFTMeridianEquatorReduce(mrcImage* in, long maxX, long maxY, int mode);

int
main(int argc, char* argv[]) 
{
	mrcFTMeridianEquatorRedeceInfo info;

/* variables */
	mrcImage in;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in ,info.In ,"in main" ,0);
	
/* begin */
	DEBUGPRINT("Program Start\n");
	lmrcFTMeridianEquatorReduce(&in, info.MaxX, info.MaxY, info.mode);
	mrcFileWrite(&in ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode: 0 ; 0 below maxX and/or maxY\n n");
	fprintf(stderr, "mode: 1 ; 0 above maxX and/or maxY\n n");
}

void lmrcFTMeridianEquatorReduce(mrcImage* in, long maxX, long maxY, int mode)
{
/* variables */
  long X,Y;

/* begin */  
  switch(mode) {
    case 0: 
    for(Y = -in->HeaderN.y / 2.0; Y < in->HeaderN.y / 2.0; Y += 1){
    for(X = 0; X <= in->HeaderN.x / 2.0; X += 1){
      if (abs(X) <= maxX || abs(Y) <= maxY){
	    mrcPixelDataSet(in, X, Y, 0, 0, mrcPixelRePart);
	    mrcPixelDataSet(in, X, Y, 0, 0, mrcPixelImPart);
      }
    }
    }
    break;

    case 1:
    for(X = 0; X <= in->HeaderN.x / 2.0; X += 1){
      if (abs(X) >= maxX){
	    mrcPixelDataSet(in, X, 0, 0, 0, mrcPixelRePart);
	    mrcPixelDataSet(in, X, 0, 0, 0, mrcPixelImPart);
      }
    }
    for(Y = -in->HeaderN.y / 2.0; Y < in->HeaderN.y / 2.0; Y += 1){
      if (abs(Y) >= maxY){
	    mrcPixelDataSet(in, 0, Y, 0, 0, mrcPixelRePart);
	    mrcPixelDataSet(in, 0, Y, 0, 0, mrcPixelImPart);
      }
    }
    break;

    case 2: 
    for(X = 0; X <= in->HeaderN.x / 2.0; X += 1){
      if (abs(X) <= maxX){
	    mrcPixelDataSet(in, X, 0, 0, 0, mrcPixelRePart);
	    mrcPixelDataSet(in, X, 0, 0, 0, mrcPixelImPart);
      }
    }
    for(Y = -in->HeaderN.y / 2.0; Y < in->HeaderN.y / 2.0; Y += 1){
      if (abs(Y) <= maxY){
	    mrcPixelDataSet(in, 0, Y, 0, 0, mrcPixelRePart);
	    mrcPixelDataSet(in, 0, Y, 0, 0, mrcPixelImPart);
      }
    }
    break;
  }
  
  mrcStatDataSet(in,0); 
}


