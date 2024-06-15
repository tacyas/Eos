/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNoiseCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNoiseCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNoiseCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageNoiseCreate.h"


/* prototype */

int
main(int argc, char* argv[]) 
{
	mrcImageNoiseCreateInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT("Program Start\n");
	lmrcImageNoiseCreate(&out ,&in ,info.Noise, info.mode);
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Output file has the same infomation (Nx Ny Nz Length and so on) as reference file. \n");
}

