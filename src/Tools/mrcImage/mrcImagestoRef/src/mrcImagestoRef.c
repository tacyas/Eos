/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImagestoRef ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImagestoRef
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImagestoRef ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#define DEBUG
#include "genUtil.h"
#include "mrcRefUtil.h"


int
main(int argc, char* argv[]) 
{
	mrcImagestoRefInfo info;
	long i;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
       	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In[0], "in main file", 0);
	if (in.HeaderN.z != 1){
	  fprintf(stderr,"The image 0 is a 3D image!\n");
	  exit(EXIT_FAILURE);
	}
	out.Header = in.Header;
	out.HeaderN.z = info.flagIn+1;
	mrcInit(&out,NULL);
	lmrc3DZ1ImgPut(&out ,&in ,1);
	mrcImageFree(&in,"");
	for (i=1 ;i < info.flagIn; i++){
	  mrcFileRead(&in, info.In[i], "in main file", 0);
	  if (in.HeaderN.x != out.HeaderN.x || 
	      in.HeaderN.y != out.HeaderN.y || 
	      in.HeaderN.z != 1) {
	    fprintf(stderr,"The size of the image %d is incorrect!\n",i);
	    exit(EXIT_FAILURE);
	  }
    	  lmrc3DZ1ImgPut(&out ,&in ,i+1);
	  mrcImageFree(&in,"");
	}
	mrcStatDataSet(&out,0);
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "This program packs same size images to no header reference file.");
}
