/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllExtractdYEstimate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllExtractdYEstimate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllExtractdYEstimate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define GLOBAL_DECLARATION

#define UNDEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lllExtractdYEstimate.h"

int 
lllExtractdYEstimate(mrcImage* in, lllExtractdYEstimateInfo* dYinfo)
{
	float CalculatedY = 0.0;
	float IntCalculatedY = 0.0;
	float finaldY = 0.0;
	float deltadY = 0.0;

		DEBUGPRINT("in lllExtractdYEstimate\n");
		CalculatedY = (in->HeaderN.y * dYinfo->PixelSize) / (dYinfo->truePitch * dYinfo->mag);
		IntCalculatedY = (int)floor( 0.5 + CalculatedY);
		fprintf(stderr, "LengthY %f [A] = LengthY %d [Pixel] x PixelSize %f [A/Pixel] x Mag %f\n",
			(in->HeaderN.y * dYinfo->PixelSize *dYinfo->mag),
			(int)in->HeaderN.y,
			dYinfo->PixelSize,
			dYinfo->mag);
	
		deltadY = fabs(CalculatedY - IntCalculatedY);

		fprintf(stderr, "Final CalculatedY  %15.6f\n",CalculatedY);
		fprintf(stderr, "      CalculatedY  %15.6f\n",IntCalculatedY);
		fprintf(stderr, "      deltadY      %15.6f\n",deltadY);

		if ( deltadY <= dYinfo->deltadY){
			finaldY = IntCalculatedY;
		} else {
			fprintf(stderr, "The deltadY value %f is larger than permitted deltadY range %f\n", deltadY, dYinfo->deltadY);
			fprintf(stderr, "dY could not be determined\n");
			exit(EXIT_FAILURE);
		}
		return finaldY;
}
