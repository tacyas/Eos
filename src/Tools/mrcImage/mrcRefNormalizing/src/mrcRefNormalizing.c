/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcRefNormalizing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcRefNormalizing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcRefNormalizing ver%I%; Date:%D% %Z%";
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


void
main(int argc, char* argv[]) 
{
	long status;
	mrcRefNormalizingInfo info;
	double sig;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	switch (info.mode){
	case 0:
	  lmrcRefNormalization(&in);  
	  break;
	case 1:
	  if (in.HeaderMode==mrcShortImage ||
	      in.HeaderMode==mrcCharImage){
	    out.Header=in.Header;
	    out.HeaderMode=mrcFloatImage;
	    mrcInit(&out,NULL);
	    lmrcImageDataStraightCopy(&out, &in);
	    sig=lmrcImageNormalization(&out,0);
	    mrcFileWrite(&out ,info.Out ,"in main" ,0);
	    exit(EXIT_SUCCESS);
	  }
	  sig=lmrcImageNormalization(&in,0);
	  fprintf(stdout,"sigma= %g\n",sig);	  
	}
	mrcFileWrite(&in ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
fprintf(stdout,"---- mode ---- \n");
fprintf(stdout,"0:Ref image \n");
fprintf(stdout,"1:Normal 2D image \n");
}



