/*
# mrcImageShapePCA : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShapePCA
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
#include "Array.h"
#include "mrcImage.h"
#include "lmrcImageShapePCA.h"

int
main(int argc, char* argv[]) 
{
	mrcImageShapePCAInfo info;
	lmrcImageShapePCAInfo linfo;
	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.nLevel = info.flagContour;
	if(0<linfo.nLevel) {
		linfo.Level  = info.Contour;
	} else {
		if(NULL==(linfo.Level=(float*)malloc(sizeof(float)*1))) {
			fprintf(stderr, "Not allocated \n");
			exit(EXIT_FAILURE);
		}
		linfo.Level[0] = 0.0; // Cannot get this value from OptionControlFile 
		linfo.nLevel = 1;
	}


	mrcFileRead(&in, info.In, "in main", 0); 

	lmrcImageShapePCA(&in, &linfo, info.mode);	

	lmrcImageShapePCAResultsPrint(info.fptOut, &linfo, info.mode);	

	return 0;	
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "-C : ContourLevels\n");
	fprintf(stderr, "   e.g. -C  20  30  40 \n");
	fprintf(stderr, "           100%% 60%% 40%%\n");
	fprintf(stderr, "----- Objectives -----\n");
	fprintf(stderr, "Determine the orientations/molecular axis by PCA alogrism\n");
	fprintf(stderr, "  $ mrcImageShapePCA -i mrc -o parameter -C C1 C2 C3 ...\n");
	fprintf(stderr, "-m \n");
	fprintf(stderr, "  +1: Sphere (default)\n");
	fprintf(stderr, "  +2: Disk\n");
	fprintf(stderr, "  +4: Cylinder\n");
	fprintf(stderr, "\n");

}

