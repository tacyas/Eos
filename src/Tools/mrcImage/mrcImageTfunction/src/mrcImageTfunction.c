/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageTfunction ver %I%
#%Z% Created by Isao Sakane
#%Z%
#%Z% Usage : mrcImageTfunction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageTfunction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"

void
main(int argc, char* argv[]) 
{
	long status;
	mrcImageTfunctionInfo info;
	lmrcImageTfunctionInfo linfo;
	mrcImage src;
	mrcImage dst;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.sx = info.sx;
	linfo.sy = info.sy;
	linfo.sz = info.sz;

	mrcFileRead(&src, info.In, "in main", 0);
	lmrcImageTfunction(&dst, &src, &linfo, 0);
	mrcStatDataSet(&dst, 0);
	mrcFileWrite(&dst, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
