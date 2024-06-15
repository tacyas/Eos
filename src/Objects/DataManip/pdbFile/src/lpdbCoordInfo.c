/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdbCoordInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lpdbCoordInfo 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lpdbCoordInfo ver%I%; Date:%D% %Z%";
#undef DEBUG
#include "genUtil.h"

#include "./lpdbCoordInfo.h"

int 
lpdbDistanceCheck(pdbFile* pdb, pdbCoord p, pdbFileParaTypeReal distance, int mode)
{
	pdbFileParaTypeReal x, y, z;	
	int returnValue;
	pdbFileParaTypeReal dis;

	if(pdbFileIsAtom(pdb)) {
		pdbFileCoordGet(pdb, &x, &y, &z);
		returnValue = 0;
	} else {
		return 0;
	}
	switch(mode) {
		case 0: /* Near */ {
			dis = SQR(x-p.x)+SQR(y-p.y)+SQR(z-p.z);
			DEBUGPRINT2("%f - %f\n", sqrt(dis), distance);
			if(dis < SQR(distance)) {
				DEBUGPRINT7("%f %f %f - %f %f %f: %f\n", x, y, z, p.x, p.y, p.z, distance);
				returnValue = 1;
			}
			break;
		}
		case 1: /* Far */  {
			if(SQR(distance) < SQR(x-p.x)+SQR(y-p.y)+SQR(z-p.z)) {
				returnValue = 1;
			}
			break;
		}
	}
	return returnValue;
}

int 
lpdbDistanceNear(pdbFile* pdb, pdbCoord p, pdbFileParaTypeReal distance, int mode)
{
	return lpdbDistanceCheck(pdb, p, distance, 0);
}

int 
lpdbDistanceFar(pdbFile* pdb, pdbCoord p, pdbFileParaTypeReal distance, int mode)
{
	return lpdbDistanceCheck(pdb, p, distance, 1);
}

