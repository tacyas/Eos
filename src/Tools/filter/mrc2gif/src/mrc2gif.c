/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrc2gif ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrc2gif
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrc2gif ver%I%; Date:%D% %Z%";

#undef DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
//#include "gif_lib.h"
#include "gifFile.h"

int
main(int argc, char* argv[]) 
{
	long status, i;
	mrc2gifInfo info;
	float ftmp;
	ColorMapObject* ColorMap;
	mrcImage in;
	mrcImage section;
	int maxColorIndex=256;
	int z;
	char filename[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	mrcFileRead(&in, info.inFile,  "in main", 0);
	if(info.flagLow) {
		in.HeaderAMin = info.Low;
	}
	if(info.flagHigh) {
		in.HeaderAMax = info.High;
	}
	if(info.Inverse) {
		ftmp = in.HeaderAMin;
		in.HeaderAMin = in.HeaderAMax;
		in.HeaderAMax = ftmp;
	}

	ColorMap = gifColorMapInit(maxColorIndex, 0);
	gifColorMapGrey(ColorMap, maxColorIndex);

	if(info.flagZ) {
		if(info.Z<0) {
			for(z=0; z<in.HeaderN.z; z++) {
				sprintf(filename, info.format, info.outFile, z);	
				mrcImageSectionGet(&section, &in, z, 1);
				lmrc2gif(filename, &section, ColorMap, 0);	
			}
		} else {
			mrcImageSectionGet(&section, &in, info.Z, 1);
			lmrc2gif(info.outFile, &section, ColorMap, 0);	
		}
	} else {
		lmrc2gif(info.outFile, &in, ColorMap, 0);	
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "-z\n");
	fprintf(stderr, " -1: Serial Files\n");
	fprintf(stderr, " z(>0): Section at z\n");
}
