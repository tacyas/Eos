/*
# mrcImageRotation3D : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageRotation3D
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

int
main(int argc, char* argv[]) 
{
	mrcImage in;
	mrcImage out;
	mrcImageRotation3DInfo info;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

    if(info.flagNx&&info.flagNy&&info.flagNz) {
        out.Header = in.Header;
        out.HeaderN.x = info.Nx;
        out.HeaderN.y = info.Ny;
        out.HeaderN.z = info.Nz;
        mrcInit(&out, NULL);
	    lmrcImageRotation3DFollowingEulerAngle2(&out, &in, 
		 	info.EulerAngle, 
		 	info.Rot1*RADIAN, 
			info.Rot2*RADIAN, 
			info.Rot3*RADIAN, 
			info.Mode, info.mode);
        DEBUGPRINT4("%s: %f %f %f\n", info.EulerAngle, info.Rot1, info.Rot2, info.Rot3);
    } else {
	    lmrcImageRotation3DFollowingEulerAngle(&out, &in, 
		 	info.EulerAngle, 
		 	info.Rot1*RADIAN, 
			info.Rot2*RADIAN, 
			info.Rot3*RADIAN, 
			info.Mode, info.mode);
    }
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-m \n");
	fprintf(stderr, " 0: padding 0 \n");
	fprintf(stderr, " 1: padding average \n");
	fprintf(stderr, " +0:  within ellipsoidal area.\n");
	fprintf(stderr, " +16: within square area.\n");

}
