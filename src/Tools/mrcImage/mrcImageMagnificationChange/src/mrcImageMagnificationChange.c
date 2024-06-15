/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMagnificationChange ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMagnificationChange
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMagnificationChange ver%I%; Date:%D% %Z%";
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


/* prototype */


int
main(int argc, char* argv[]) 
{
	mrcImageMagnificationChangeInfo info;
/* variables */
	mrcImage in;
	mrcImage out;
	mrcImage tmpin;
	mrcImage tmpout;
	mrcRefHeader header;
	int z;
  
/* initialization  */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in, info.In, "main routine", 0);

/* begin */
	if (info.mode/16){
	  out.Header=in.Header;
	  out.HeaderN.x=floor( (float)in.HeaderN.x *info.Ratio +0.5) ;
	  out.HeaderN.y=floor( (float)in.HeaderN.y *info.Ratio +0.5) ;
	  mrcInit(&out,NULL);
	  lmrcRefHeaderGet(&header ,&in);
	  lmrcRefHeaderSet(&out ,&header);	
	  for (z=1 ;z<in.HeaderN.z ;z++){
	    lmrc3DZ1ImgGet(&tmpin ,&in ,z);
	    lmrcImageMagnificationChange(&tmpout ,&tmpin ,info.Ratio);
	    lmrc3DZ1ImgPut(&out ,&tmpout ,z);
	    mrcImageFree(&tmpin ,0);
	    mrcImageFree(&tmpout ,0);
	  }
	  info.mode -= 16;
	} else {
	  DEBUGPRINT("start \n");
	  lmrcImageMagnificationChange(&out ,&in ,info.Ratio);
	}
	if (info.mode/2){
	  out.HeaderLength.x /= info.Ratio;
	  out.HeaderLength.y /= info.Ratio;
	  out.HeaderLength.z /= info.Ratio;
	}
	mrcFileWrite(&out, info.Out, "main routine", 0);
       	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---- mode ----\n");
fprintf(stdout,"0:Both axis\n");
fprintf(stdout,"+2:Mrc header is also changed.(Default does not change header.)\n");
fprintf(stdout,"+16:ref image\n");
fprintf(stdout,"---------------\n");
fprintf(stdout,"!!!!!!NOTE!!!!!\n");
fprintf(stdout,"This algorihm is completely different from mrcImageShrink\n");
}


    
  
  
  



