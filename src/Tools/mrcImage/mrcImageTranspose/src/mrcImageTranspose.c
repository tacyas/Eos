/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageTranspose ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageTranspose
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageTranspose ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageTranspose.h"
#include "mrcRefUtil.h"



int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageTransposeInfo info;

/* variables */
	mrcImage in;
	mrcImage out;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */
	DEBUGPRINT("start ");
	mrcFileRead(&in ,info.In ,"in main" ,0);
	DEBUGPRINT("read ");
	lmrcImageTranspose(&out ,&in ,info.mode ,info.Mode);
	DEBUGPRINT("trans ");
	mrcFileWrite(&out ,info.Out ,"in main" ,0);
	DEBUGPRINT("write ");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	lmrcImageTransposeUsage(stderr);
}


