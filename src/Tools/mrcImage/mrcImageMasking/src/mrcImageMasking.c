/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageMasking ver %I%
#%Z% Created by tacyas
#%Z% Modified by tacyas 
#%Z%
#%Z% Usage : mrcImageMasking
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageMasking ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "Matrix3D.h"
#include "Vector.h"
#include "mrcImage.h"
#include "lmrcImageNormalizing.h"
#include "lmrcImageMasking.h"
#include "lmrcImageSoftEdge.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageMaskingInfo info;
	mrcImage in;
	mrcImage nor;
    mrcImage tmp;
	mrcImage out;
	lmrcImageMaskingInfo linfo;
	lmrcImageNormalizingInfo lninfo;
	lmrcImageSoftEdgeInfo linfoSoft;
	
	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);
	mrcFileRead(&in, info.In, "from main routine", 0);	
	
	if(info.flagnx) {
		linfo.n.x = info.nx;
	} else {
		linfo.n.x = in.HeaderN.x;
	}
	if(info.flagny) {
		linfo.n.y = info.ny;
	} else {
		linfo.n.y = in.HeaderN.y;
	}
	if(info.flagnz) {
		linfo.n.z = info.nz;
	} else {
		linfo.n.z = in.HeaderN.z;
	}
	if(info.flagcx) {
		linfo.c.x = info.cx;
	} else {
		linfo.c.x = (in.HeaderN.x - 1.0)/2.0;
	}
	if(info.flagny) {
		linfo.c.y = info.cy;
	} else {
		linfo.c.y = (in.HeaderN.y - 1.0)/2.0;
	}
	if(info.flagnz) {
		linfo.c.z = info.cz;
	} else {
		linfo.c.z = (in.HeaderN.z - 1.0)/2.0;
	}

	if(info.flagEuler) {	
		linfo.flagRotation = 1;
		strncpy(linfo.Euler, info.Euler,4);	
		linfo.Rot1 = info.Rot1*RADIAN;
		linfo.Rot2 = info.Rot2*RADIAN;
		linfo.Rot3 = info.Rot3*RADIAN;
	} else {
		linfo.flagRotation = 0;
	}	

	DEBUGPRINT6("%f %f %f %f %f %f\n",linfo.n.x,linfo.n.y,linfo.n.z,linfo.c.x,linfo.c.y,linfo.c.z);
	linfo.shape = info.Shape;
	linfo.mode = info.mode;
	
	if(info.flagNormalize) {
		lninfo.Mode = info.Normalize;	
		lmrcImageNormalizing(&nor, &in, &lninfo, 0);
	} else {
		nor = in;
	}
	lmrcImageMasking(&tmp, &nor, &linfo, 0);
	
    if(info.flagSoft) {
        linfoSoft.envelop = info.Soft;
        linfoSoft.width   = info.SoftWidth;
        lmrcImageSoftEdge(&out, &tmp, linfoSoft, 0);
    } else {
        out = tmp;
    }
	mrcStatDataSet(&out, 0);
	mrcFileWrite(&out, info.Out, "from main routine", 0);	

	return 0;
}

void
additionalUsage()
{
	fprintf(stderr, "----- -Shape Option ----- \n");
	fprintf(stderr, "    -Shape 0 : Sphere: radius(nx, ny, nz)\n");
	fprintf(stderr, "    -Shape 1 : Square : nx x ny x nz\n");
	fprintf(stderr, "    -Shape 2 : Cylinder: radius(nx, ny) x nz\n");
	fprintf(stderr, "----- -m Option----- \n");
	fprintf(stderr, "    -m 0 : masked by avg\n");
	fprintf(stderr, "    -m 1 : masked by 0\n");
	fprintf(stderr, "    -m 2 : masked by 1\n");
}

