#include <stdio.h>
#include <stdlib.h>
/*
# mrcImageHighlighting.c  1.2
# The latest update : 05/01/96 at 16:28:12
#
#@(#) mrcImageHighlighting Function ver 1.2
#@(#) Created by Isao Sakane May 1, 1996.
#@(#)
#@(#) Attention
#@(#)
*/
#include <string.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

int
main(int argc, char* argv[]) 
{
	mrcImage dst, src;
	mrcImageHighlightingInfo info;
	lmrcImageHighlightInfo linfo;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	linfo.mode = info.mode;
	linfo.Bias = info.Bias;
	linfo.Grad = info.Grad;
	mrcFileRead(&src, info.In, "in main", 0);
	lmrcImageHighlighting(&dst, &src, &linfo);
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);

	//exit(EXIT_SUCCESS);
	return 0;
}

void
additionalUsage()
{
	//extern lmrcImageHighlightingInfoPrint(FILE*); 

	lmrcImageHighlightingInfoPrint(stderr);
}
