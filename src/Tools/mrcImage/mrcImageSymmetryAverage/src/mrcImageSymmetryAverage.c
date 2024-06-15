/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageSymmetryAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageSymmetryAverage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageSymmetryAverage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "mrcRefUtil.h"
#include "lDescartesIntoPolar.h" 
#include "lmrcImageSymmetryFind.h"
#include "lmrcImageDensity.h"


int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out;
	mrcImageSymmetryAverageInfo info;
	DescartesCoord centre;
	mrcImageParaTypeRealCoord centre2;
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	if(info.flagcx) {
		centre.x = info.cx;	
		centre.y = info.cy;	
		centre.z = info.cz;	
	} else { 
		centre2 = lmrcImageDensityInfoCentreOfGravity(&in, 0);
		centre.x = centre2.x;
		centre.y = centre2.y;
		centre.z = centre2.z;
	}
	lmrcImageSymmetryAverage(&out, &in, info.NSym, centre, 0);

	mrcFileWrite(&out, info.Out, "in main", 0);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-centre : Set a defined centre\n");
	fprintf(stderr, "          otherwise CentreOfGravity  \n");

}
