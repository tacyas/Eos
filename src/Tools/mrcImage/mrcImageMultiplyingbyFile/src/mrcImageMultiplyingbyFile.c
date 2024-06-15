/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMultiplyingbyFile ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageMultiplyingbyFile
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMultiplyingbyFile ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageMultiplying.h"


int
main(int argc, char* argv[]) 
{
	mrcImageMultiplyingbyFileInfo info;

/* variables */
	mrcImage in1;
	mrcImage in2;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in1 ,info.In1 ,"in main" ,0);
	mrcFileRead(&in2 ,info.In2 ,"in main" ,0);
	if (in1.HeaderN.x !=in2.HeaderN.x || in1.HeaderN.y !=in2.HeaderN.y){
	  fprintf(stderr,"Warning! Image size is different.\n");
	}
	lmrcImageMultiplyingByFile(&in1 ,&in2);	
	mrcFileWrite(&in1 ,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

