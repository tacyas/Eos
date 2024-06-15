/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageExpression ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageExpression
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageExpression ver%I%; Date:%D% %Z%";
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
void lmrcImageExpression(mrcImage* out, mrcImage* in, double th ,int mode);


int
main(int argc, char* argv[]) 
{
	mrcImageExpressionInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "from Main Routine", 0);
	lmrcImageExpression(&out, &in, info.Thres ,info.mode);
	mrcFileWrite(&out, info.Out, "from Main Routine", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0:Absolute value\n");
	fprintf(stderr, "1:Log absolute value\n");
	fprintf(stderr, "2:Root absolute value\n");
	fprintf(stderr, "3:Square absolute value\n");
}



void
lmrcImageExpression(mrcImage* out, mrcImage* in ,double th ,int mode) 
{
  long x,y,z;
  double data;

  out->Header = in->Header;
  mrcInit(out, NULL);
  for (x=0 ;x < in->HeaderN.x; x++){
    for (y=0 ;y < in->HeaderN.y; y++){
      for (z=0 ;z < in->HeaderN.z; z++){
	mrcPixelDataGet(in, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);	
	switch(mode) {
        case 0: 
	  data = fabs(data);
	  break;
	case 1:
	  data = fabs(data);
	  if (data < th){
	    data = th;
	  }
	  data = log10(data);
	  break;
	case 2:
	  data = fabs(data);
	  if (data < th){
	    data = th;
	  }
	  data=sqrt(data);
	  break;
	case 3:
	  data=data*data;
	  break;
	}
	mrcPixelDataSet(out, x, y, z, data, mrcPixelRePart);	
      }
    }
  }
  mrcStatDataSet(out, 0);
}
 
