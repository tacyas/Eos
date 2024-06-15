/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageROI3D ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageROI3D
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageROI3D ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#include "lmrcImageROI3D.h"

int
main(int argc, char* argv[]) 
{
	mrcImageROI3DInfo info;
	mrcImage in;
	mrcImage out;
	lmrcImageROI3DInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.flagx = 1;
	linfo.x1 = info.x1; 
	linfo.x2 = info.x2; 
	
	linfo.flagy = 1;
	linfo.y1 = info.y1; 
	linfo.y2 = info.y2; 
	
	linfo.flagz = 1;
	linfo.z1 = info.z1; 
	linfo.z2 = info.z2; 

	mrcFileRead(&in, info.In, "from Main Routine", 0);
	lmrcImageROI3D(&out, &in, &linfo);
	mrcFileWrite(&out, info.Out, "in Main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "from z1 to z2\n");
}
