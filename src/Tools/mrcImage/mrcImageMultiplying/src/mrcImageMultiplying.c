/*
# mrcImageMultiplying.c  1.1
# The latest update : 06/12/96 at 13:03:03
#
#@(#) mrcImageMultiplying ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : mrcImageMultiplying
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)mrcImageMultiplying ver1.1; Date:96/06/12 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "lmrcImageMultiplying.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMultiplyingInfo info;
	mrcImage in;
	mrcImage out;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&in,   info.In,  "in main", 0); 
	lmrcImageMultiplying(&out, &in, info.Value, in.HeaderMode);		
	mrcFileWrite(&out, info.Out, "in main", 0); 

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "---- Additional Usage ----\n");
}

