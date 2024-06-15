/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageTwoImageTest ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageTwoImageTest
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%mrcImageTwoImageTest ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "Memory.h"
#include "genUtil.h"
#include "lmrcImagesStatDataGet.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImage* in1;
	mrcImage* in2;
	mrcImage FTest;
	mrcImage tTest;
	mrcImageTwoImageTestInfo info;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	in1 = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn1, "In1");
	for(i=0; i<info.flagIn1; i++) {
		mrcFileRead(&(in1[i]), info.In1[i], "in main", 0);
	}
	in2 = (mrcImage*)memoryAllocate(sizeof(mrcImage)*info.flagIn2, "In2");
	for(i=0; i<info.flagIn2; i++) {
		mrcFileRead(&(in2[i]), info.In2[i], "in main", 0);
	}

	if(info.flagtTest) {
		lmrcImagesTTest(&tTest, in1, info.flagIn1, in2, info.flagIn2, 0);
		mrcStatDataSet(&tTest, 0);
		mrcFileWrite(&tTest, info.tTest, "in main", 0);
	}

	if(info.flagFTest) {
		lmrcImagesFTest(&FTest, in1, info.flagIn1, in2, info.flagIn2, 0);
		mrcStatDataSet(&FTest, 0);
		mrcFileWrite(&FTest, info.FTest, "in main", 0);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{

}
