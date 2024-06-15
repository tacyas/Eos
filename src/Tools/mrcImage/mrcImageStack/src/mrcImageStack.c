/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageStack ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageStack
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageStack ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"

/*
Example:
typedef struct lmrcImageStackInfo {
	float a;
	int   b;
} lmrcImageStackInfo;

typedef enum lmrcImageStackMode {
	a=0,
	b=1
} lmrcImageStackMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageStackInfo info;

/* variables */
	mrcImage in;
	mrcImage out;
	long i;
	int sp;

/* input patameters ,file open */
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	DEBUGPRINT1("file:%ld \n",info.flagIn);

/* begin */
	DEBUGPRINT("Program Start\n");

	mrcFileRead(&in, info.In[0], "in main file", 0);
	lmrcImageStackAlloc(&out, &in, info.flagIn, &sp, info.mode); 
	mrcImageFree(&in,"");

	for(i=1; i<info.flagIn; i++) {
	    mrcFileRead(&in, info.In[i], "in main file", 0);
	    lmrcImageStackPush(&out, &in, &sp, info.mode);
		DEBUGPRINT1("%d\n", sp);
	    mrcImageFree(&in,"");
	}
	mrcFileWrite(&out,info.Out ,"in main" ,0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
