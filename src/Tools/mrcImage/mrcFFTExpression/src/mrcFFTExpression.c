/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcFFTExpression ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcFFTExpression
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcFFTExpression ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcFFTExpression.h"

void
main(int argc, char* argv[]) 
{
 
	mrcFFTExpressionInfo info;

/* variables */
	mrcImage fft;
	mrcImage img;
/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

/* begin */

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&fft, info.In, "from Main Routine", 0);
	lmrcFFTExpression(&img, &fft, info.Thres ,info.mode);
	mrcFileWrite(&img, info.Out, "from Main Routine", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcFFTExpressionModePrint(stderr);
}

