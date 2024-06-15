/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbRotation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbRotation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbRotation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "eosCuda.h"
#include "pdbFile.h"
#include "genUtil.h"

int
main(int argc, char* argv[]) 
{
	long status;
	pdbRotationInfo info;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	if(info.flagcudaDeviceID) {
		eosCudaInit(info.cudaDeviceID);
		eosCudaPropertiesPrint(stderr, info.cudaDeviceID);
	}
	pdbFileRead(info.fptIn, &pdb);
	if(info.flagZXYrotx+info.flagZYXrotx+info.flagXYZrotx+info.flagYXZrotx+info.flagRotMode<=1) {
		if(info.flagZXYrotx) {
			//pdbRotationZXY(&pdb, info.ZXYrotx*RADIAN, info.ZXYroty*RADIAN, info.ZXYrotz*RADIAN);
			pdbRotationFollowingEulerAngle(&pdb, "ZEYS", info.ZXYrotz*RADIAN, info.ZXYrotx*RADIAN, info.ZXYroty*RADIAN);
		}
		if(info.flagZYXrotx) {
			//pdbRotationZYX(&pdb, info.ZYXrotx*RADIAN, info.ZYXroty*RADIAN, info.ZYXrotz*RADIAN);
			pdbRotationFollowingEulerAngle(&pdb, "ZOYS", info.ZYXrotz*RADIAN, info.ZYXroty*RADIAN, info.ZYXrotx*RADIAN);
		}
		if(info.flagXYZrotx) {
			//pdbRotationXYZ(&pdb, info.XYZrotx*RADIAN, info.XYZroty*RADIAN, info.XYZrotz*RADIAN);
			pdbRotationFollowingEulerAngle(&pdb, "XEYS", info.XYZrotx*RADIAN, info.XYZroty*RADIAN, info.XYZrotz*RADIAN);
		}
		if(info.flagYXZrotx) {
			//pdbRotationYXZ(&pdb, info.YXZrotx*RADIAN, info.YXZroty*RADIAN, info.YXZrotz*RADIAN);
			pdbRotationFollowingEulerAngle(&pdb, "YOYS", info.YXZroty*RADIAN, info.YXZrotx*RADIAN, info.YXZrotz*RADIAN);
		}
		if(info.flagRotMode) {
			pdbRotationFollowingEulerAngle(&pdb, info.RotMode, info.Rot1*RADIAN, info.Rot2*RADIAN, info.Rot3*RADIAN);
		}
	} else {
	}
	pdbFileWrite(info.fptOut, &pdb);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "ZXY : y-axis -> x-axis -> z->axis \n");
	fprintf(stderr, "ZYX : x-axis -> y-axis -> z->axis \n");
	fprintf(stderr, "ZXY -> ZYX -> XYZ ->YXZ -> EU\n");
}

