/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSphere ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSphere
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSphere ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageSphere.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSphereInfo info;
	mrcImage out;
	lmrcImageSphereInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.r     = info.r;
	linfo.size  = info.size;
	linfo.w     = info.w;
	linfo.mode  = info.mode;

	lmrcImageSphere(&linfo, &out);
	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "mode 0 char \n");
	fprintf(stderr, "mode 2 float \n");
}
