/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageFTest ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageFTest
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageFTest ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "lmrcImagesStatDataGet.h"

int
main(int argc, char* argv[]) 
{
	mrcImage* in;
	mrcImage* ref;
	mrcImage  Out;
	mrcImage  OutF;
	mrcImageFTestInfo info;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	DEBUGPRINT("Program Start\n");
	in  = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn, "in main");	
	for(i=0; i<info.flagIn; i++) {
		mrcFileRead(&(in[i]), info.In[i], "Read In in main", 0);
	}
	ref = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagRef, "in main");	
	for(i=0; i<info.flagRef; i++) {
		mrcFileRead(&(ref[i]), info.Ref[i], "Read Ref in main", 0);
	}
	lmrcImagesFTest(&Out, &OutF, in, info.flagIn, ref, info.flagRef, info.mode);
	//lmrcImagesFTest(&Out, &OutF, in, info.flagIn, ref, info.flagRef, info.mode);

	mrcFileWrite(&Out, info.Out, "write Out in main", 0);
	if(info.flagOutF) {
		mrcFileWrite(&OutF, info.OutF, "write Out in main", 0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

