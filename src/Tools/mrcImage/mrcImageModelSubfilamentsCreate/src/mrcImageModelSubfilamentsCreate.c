/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageModelSubfilamentsCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageModelSubfilamentsCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageModelSubfilamentsCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"

typedef struct lmrcImageModelSubfilamentsCreateInfo {
	float position;
	float nHelix;
	float deltaPhi;
	float startPhi;
} lmrcImageModelSubfilamentsCreateInfo;

extern void _lmrcImageModelSubfilamentsCreate(mrcImage* out, mrcImage* in,
											 lmrcImageModelSubfilamentsCreateInfo info);

int
main(int argc, char* argv[]) 
{
	mrcImageModelSubfilamentsCreateInfo info;
	lmrcImageModelSubfilamentsCreateInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	linfo.position     = info.position;
	linfo.nHelix       = info.nHelix;
	linfo.deltaPhi     = info.deltaPhi*RADIAN;
	linfo.startPhi     = info.startPhi*RADIAN;

	out.HeaderN.x = info.nx;
	out.HeaderN.y = info.ny;
	out.HeaderN.z = info.nz;
	out.HeaderLength.x = info.lx;
	out.HeaderLength.y = info.ly;
	out.HeaderLength.z = info.lz;
	out.HeaderMode = mrcFloatImage;
	mrcInit(&out, NULL);

	_lmrcImageModelSubfilamentsCreate(&out, &in, linfo);

	mrcFileWrite(&out, info.Out, "in main", 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void 
_lmrcImageModelSubfilamentsCreate(mrcImage* out, mrcImage* in, lmrcImageModelSubfilamentsCreateInfo info)
{
	mrcImageParaTypeInteger i1=0, i2=0;
	mrcImageParaTypeReal x=0, y=0, z=0;
	float Phi=0, nPhi=0;
	mrcImageParaTypeReal dstx=0, dsty=0, dstz=0;

	if(0==out->HeaderN.x%2 || 0==out->HeaderN.y%2) {
		fprintf(stderr, "Even size is not supported\n");
		exit(EXIT_FAILURE);
	}

	nPhi = (360/info.nHelix)*RADIAN;
	
	for ( i2 = 0; i2 <= out->HeaderN.z; i2++){
		for ( i1 = 0; i1 < info.nHelix; i1++){
			Phi = info.startPhi + i2*info.deltaPhi + i1*nPhi;

			x = info.position * cos(Phi); /* A */
			y = info.position * sin(Phi); /* A */
			z = out->HeaderLength.z * i2;  /* A */  

			dstx = x/out->HeaderLength.x + (out->HeaderN.x-1.0)/2.0; /* pixel */
			dsty = y/out->HeaderLength.y + (out->HeaderN.y-1.0)/2.0; /* pixel */
			dstz = z/out->HeaderLength.z;                            /* pixel */

			mrcImageDataSet(out, in, dstx, dsty, dstz, Phi, mrcImageDataSetModeCentre);
		}
	}


}



