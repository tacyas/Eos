/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageAverage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageAverage ver%I%; Date:%D% %Z%";
#define DEBUG
#include "genUtil.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImageAverage.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageAverageInfo info;
	mrcImage* in; 
	mrcImage* inWeight; 
	mrcImage out;
	mrcImage outWeight;
	long i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	/* Input*/
	in = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");
	for(i=0; i<info.flagIn; i++) {
		mrcFileRead(&(in[i]), info.In[i], "in main", 0);
	}
	if(info.flagInWeight) {
		if(info.flagInWeight != info.flagIn) {
			fprintf(stderr, "File Number is different: in %d inWeight %d \n", info.flagIn, info.flagInWeight);
			exit(EXIT_FAILURE);
		}
		inWeight = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagInWeight, "in main");
		for(i=0; i<info.flagInWeight; i++) {
			mrcFileRead(&(inWeight[i]), info.InWeight[i], "in main", 0);
		}
	}

	/* Calcucation */
	if(!info.flagInWeight) {
		lmrcImageAverage(&out, in, info.flagIn, info.mode);
	} else if(info.flagInWeight) {
		lmrcImageAverageWithWeight(&out, &outWeight, in, inWeight, info.flagIn, info.mode);
	}
	DEBUGPRINT("END CALC");
	/* Output */
	mrcFileWrite(&out, info.Out, "in main", 0);
	if(info.flagOutWeight) {
		mrcFileWrite(&outWeight, info.OutWeight, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
