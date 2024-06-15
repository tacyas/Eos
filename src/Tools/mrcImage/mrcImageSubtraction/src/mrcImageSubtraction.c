/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSubtraction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSubtraction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSubtraction ver%I%; Date:%D% %Z%";
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


int
main(int argc, char* argv[]) 
{
	mrcImageSubtractionInfo info;

/* variables */
	mrcImage in1;
	mrcImage in2;
	mrcImage out;
	mrcImage tmp;
	mrcImageInformation linfo;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in1 ,info.In1 ,"in main" ,0);
	mrcFileRead(&in2 ,info.In2 ,"in main" ,0);
	if (in1.HeaderN.x !=in2.HeaderN.x || in1.HeaderN.y !=in2.HeaderN.y){
	  fprintf(stderr,"Image size is different!");
	  exit(1);
	}
	if (info.mode){
	  llmrcImageSub(&tmp ,&in1 ,&in2);
	  lmrcImageAbs(&out ,&tmp);
	} else {
	  llmrcImageSub(&out, &in1, &in2);
	}
	mrcFileWrite(&out ,info.Out ,"in main" ,0);

	linfo.mode = RMSofAllPixels;
	lmrcImageInformation(&linfo, &out);
	fprintf(info.fptRMSD, "RMSD: %f\n", linfo.RMS); 

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0:out = in1 - in2 \n");
	fprintf(stderr, "     1:out = abs (in1 - in2) \n");
}

