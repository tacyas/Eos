/*
# mrcImage3DWindowing : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DWindowing
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
#include "lmrcImage3DWindowing.h"

int
main(int argc, char* argv[]) 
{
	mrcImage3DWindowingInfo info;
	lmrcImage3DWindowingInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.center.x = info.cx;
	linfo.center.y = info.cy;
	linfo.center.z = info.cz;

	linfo.width.x = info.wx;
	linfo.width.y = info.wy;
	linfo.width.z = info.wz;

	linfo.radius  = info.r;
	linfo.widthofR = info.w;
	linfo.wz       = info.widthz;

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0); 

	lmrcImage3DWindowing(&out, &in, &linfo, info.mode);

	mrcFileWrite(&out, info.Out, "in main", 0); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	 lmrcImage3DWindowingUsage(stderr);
}

