/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% Decartes2Polar ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : Descartes2Polar
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%Descartes2Polar ver%I%; Date:%D% %Z%";
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
	Descartes2PolarInfo info;
	lDescartesIntoPolarInfo linfo;
	DescartesCoord src;
	PolarCoord dst;

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
	src.x = info.x;
	src.y = info.y;
	src.z = info.z;
	dst = lDescartesCoordIntoPolarCoord(src, linfo, 0);
	fprintf(info.fptOut, "%15.6g %15.6g %15.6g\n", 
		dst.r, 
		dst.phi*DEGREE, 
		dst.theta*DEGREE); 	
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
