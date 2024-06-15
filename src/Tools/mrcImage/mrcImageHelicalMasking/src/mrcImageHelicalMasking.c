/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageHelicalMasking ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageHelicalMasking
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageHelicalMasking ver%I%; Date:%D% %Z%";
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

/* prototypes */
void lmrcImageHelicalMasking(mrcImage* in, double dp, long sz, long ez, double sphi, double ephi, double value, int mode);

int
main(int argc, char* argv[]) 
{
  mrcImageHelicalMaskingInfo info;

/* variables */
        mrcImage in;
	double dp;
  
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
        mrcFileRead(&in ,info.In ,"in main" ,0);

/* begin */
	DEBUGPRINT("Program Start\n");
	DEBUGPRINT2("%g,%g\n",info.dz,in.HeaderLength.z);
	dp=info.dphi/(info.dz / in.HeaderLength.z);
	if (!info.flagez){
	  info.ez=in.HeaderN.z-1;
	}
	lmrcImageHelicalMasking(&in, dp, info.sz, info.ez, info.sphi, info.ephi, info.value, info.mode);
	mrcFileWrite(&in ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void lmrcImageHelicalMasking(mrcImage* in, double dp, long sz, long ez, double sphi, double ephi, double value ,int mode)
{
/* variables */
  int x,y,z,flag;
  double sp,ep,p,cx,cy;

/* begin */
  cx=(in->HeaderN.x-1)/2;
  cy=(in->HeaderN.y-1)/2;
  for (z=sz ;z <= ez ;z++){
    sp=(z-sz)*dp+sphi;
    ep=(z-sz)*dp+ephi;
    sp=(NormalDegree(sp));
    ep=(NormalDegree(ep));
    sp*=RADIAN;
    ep*=RADIAN; 
    for (x=0 ;x < in->HeaderN.x ;x++){
      for (y=0 ;y< in->HeaderN.y ;y++){
	p=atan2(y-cy,x-cx);
	if (mode==0){
	  if (sp<=ep){
	    if (p>sp && p<ep){
	      mrcPixelDataSet(in ,x ,y ,z ,value  ,mrcPixelRePart);
	    }
	  } else if (p>sp || p<ep){
	      mrcPixelDataSet(in ,x ,y ,z ,value  ,mrcPixelRePart);
	  }
	} else {
	  if (sp>=ep){
	    if (p>ep && p<sp){
	      mrcPixelDataSet(in ,x ,y ,z ,value  ,mrcPixelRePart);
	    }
	  } else if (p>ep || p<sp){
	      mrcPixelDataSet(in ,x ,y ,z ,value  ,mrcPixelRePart);
	  }	
	}      
      }
    }
  }
  mrcStatDataSet(in,0);
}


