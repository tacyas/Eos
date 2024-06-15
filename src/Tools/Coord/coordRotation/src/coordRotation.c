/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% coordRotation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : coordRotation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%coordRotation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Matrix3D.h"

int
main(int argc, char* argv[]) 
{
	coordRotationInfo info;
	Matrix3D M;
	floatVector V;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	matrix3DFileRead(info.fptMat, M);
	floatVectorInit(&V, 4);

	V.data[0] = info.x;
	V.data[1] = info.y;
	V.data[2] = info.z;
	V.data[3] = 1;
	
	matrix3DMultiplyVector(&V, M);

	fprintf(info.fptOut, "%15.6g %15.6g %15.6g\n", V.data[0], V.data[1], V.data[2]);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
