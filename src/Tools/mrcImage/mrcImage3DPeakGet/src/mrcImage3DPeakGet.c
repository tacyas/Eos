/*
# mrcImage3DPeakGet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DPeakGet
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
#include "lmrcImageROI2D.h"

typedef struct lmrcImage3DPeakGetInfo {
	lmrcImageROIsInfo     roiInfo;
} lmrcImage3DPeakGetInfo;

/*
typedef enum lmrcImage3DPeakGetMode {
	a=0,
	b=1
} lmrcImage3DPeakGetMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImage3DPeakGetInfo info;
	lmrcImage3DPeakGetInfo linfo;
	mrcImage in;
	mrcImage* out;
	int i;
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	lmrcImageROIsInformationGet(info.fptInfo, &linfo.roiInfo);

	out = (mrcImage*)memoryAllocate(sizeof(mrcImage)*linfo.numROI, "in main (out)");

	for(i=0; i<llinfo.numROI; i++) {
	}

	for(i=0; i<linfo.numROI; i++) {
		mrcFileWrite(&(out[i]), linfo.ROI[i].FileName, "main", 0);
	}
	   
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


