/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageRadialDistribution ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageRadialDistribution
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageRadialDistribution ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageRadialDistribution.h"
#include "lmrcImageDensityInverse.h"
#include "lmrcImageDensity.h"
#include "Vector.h"


void
main(int argc, char* argv[]) 
{
	mrcImage mrc;
	floatVector dst; 
	mrcImageRadialDistributionInfo info;
	lmrcImageRadialDistributionInfo linfo;
	mrcImageParaTypeRealCoord centre;
	int i;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&mrc, info.In, "in main", 0); 

	if(info.Inv) {
		lmrcImageDensityInverse(&mrc, 0);
	}
	if(info.flagCx) {
		linfo.Cx = info.Cx;
		linfo.Cy = info.Cy;	
	} else if(info.flagCsx) {
		linfo.Cx = info.Csx;
		linfo.Cy = info.Csy;	
		linfo.Cz = info.Csz;	
	} else {
		centre = lmrcImageDensityInfoCentreOfGravity(&mrc, 0); 
		linfo.Cx = centre.x;	
		linfo.Cy = centre.y;	
		linfo.Cz = centre.z;	
	}
	linfo.flagAverage = info.Avg;

	switch(info.mode) {
		case 0: {
			lmrcImageRadialDistribution(&dst, &mrc, &linfo);	
			break;
		}
		case 1: {
			lmrcImageRadialDistributionSphericalCoordinates(&dst, &mrc, &linfo);	
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode: %d\n", info.mode);
			exit(EXIT_FAILURE);
		}
	}	
	DEBUGPRINT1("Size: %d\n", dst.size);
	for(i=0; i<dst.size; i++) {
		fprintf(info.fptOut, "%f\n", dst.data[i]);  
	}

	if(info.flagOut2) {
		out.Header = mrc.Header;
		out.HeaderN.x = dst.size;
		out.HeaderN.y = out.HeaderN.z = 1;
		out.HeaderMode = mrcFloatImage;
		mrcInit(&out, NULL);

		for(i=0; i<out.HeaderN.x; i++) { 
			mrcPixelDataSet(&out, i, 0, 0, dst.data[i], mrcPixelRePart); 
		}
		mrcFileWrite(&out, info.Out2, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> Mode \n");
	fprintf(stderr, " 0: 2D or 3D(Cylindrical Coordinates)\n");
	fprintf(stderr, " 1: 2D or 3D(Spherical Coordinates)\n");
}

