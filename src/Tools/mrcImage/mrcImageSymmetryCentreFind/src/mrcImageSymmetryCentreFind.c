/*
# mrcImageSymmetryCentreFind : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSymmetryCentreFind
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageSymmetryFind.h"

int
main(int argc, char* argv[]) 
{
	mrcImageSymmetryCentreFindInfo info;
	mrcImage in;
	mrcImage out;
	DescartesCoord centre;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImageSymmetryCentreFind(&in, &centre, 0);

	fprintf(info.fptOut2, "centre: %f %f %f\n", centre.x, centre.y, centre.z);

	if(info.flagOut) {
		mrcImageParaTypeRealCoord shift;

		shift.x = -centre.x+in.HeaderN.x/2; 
		shift.y = -centre.y+in.HeaderN.y/2; 
		shift.z = -centre.z+in.HeaderN.z/2; 
		lmrcImageShift(&out, &in, shift, mrcPixelHowNearest);
		mrcFileWrite(&out, info.Out, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageSymmetryFindModePrint(stderr);
}
