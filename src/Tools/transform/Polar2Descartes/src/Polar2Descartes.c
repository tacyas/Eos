/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% Polar2Descartes ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : Polar2Descartes
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%Polar2Descartes ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#include "genUtil.h"
#include "lDescartesIntoPolar.h"

int
main(int argc, char* argv[]) 
{
	Polar2DescartesInfo info;
	lDescartesIntoPolarInfo linfo;
	DescartesCoord dst;
	PolarCoord src;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.xaxis.x = info.xx;
	linfo.xaxis.y = info.xy;
	linfo.xaxis.z = info.xz;
	linfo.zaxis.x = info.zx;
	linfo.zaxis.y = info.zy;
	linfo.zaxis.z = info.zz;
	linfo.centre.x = info.cx;
	linfo.centre.y = info.cy;
	linfo.centre.z = info.cz;
	lDescartesAxisCalc(&linfo, 0);
	src.r     = info.r;
	src.phi   = info.phi*RADIAN;
	src.theta = info.theta*RADIAN;
	dst = lPolarCoordIntoDescartesCoord(src, linfo, 0);
	fprintf(info.fptOut, "%15.6g %15.6g %15.6g\n", dst.x, dst.y, dst.z); 	

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

