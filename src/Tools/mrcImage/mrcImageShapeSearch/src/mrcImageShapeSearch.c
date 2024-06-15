/*
# mrcImageShapeSearch : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShapeSearch
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

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "Matrix3D.h"
#include "Vector.h"
#include "mrcImage.h"
#include "mrcImageShape.h"
#include "avsFile.h"

int
main(int argc, char* argv[]) 
{
	mrcImageShapeSearchInfo info;
	lmrcImageShapeSearchInfo linfo;
	mrcImage in;
	mrcImage out;
	char filename[1024];
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.minRadius = info.minR;
	linfo.maxRadius = info.maxR;
	linfo.delRadius = info.delR;
	//
	linfo.minLength = info.minL;
	linfo.maxLength = info.maxL;
	linfo.delLength = info.delL;
	//	
	linfo.minPhi   = info.minPhi*RADIAN;
	linfo.maxPhi   = info.maxPhi*RADIAN;
	linfo.delPhi   = info.delPhi*RADIAN;
	//
	linfo.minTheta = info.minTheta*RADIAN;
	linfo.maxTheta = info.maxTheta*RADIAN;
	linfo.delTheta = info.delTheta*RADIAN;
	//
	linfo.minPsi = info.minPsi*RADIAN;
	linfo.maxPsi = info.maxPsi*RADIAN;
	linfo.delPsi = info.delPsi*RADIAN;
	//
	linfo.thresZscore = info.thresZscore;
	linfo.interpMode = info.interpMode;

	// 
	linfo.nCube = info.nCube;
	linfo.flagRefine = info.Refine;
	//
	linfo.OutVectorBILDMode = info.OVMode
	linfo.OutVectorBILD = info.fptOutVectorBILD;
	linfo.arrowr1 = info.ArrowR1;
	linfo.arrowr2 = info.ArrowR2;
	linfo.arrowrho = info.ArrowRho;
	linfo.ZoomVector = info.ZoomVector;
	linfo.sylinderColor[0] = info.ArrowColorSylinder0;
	linfo.sylinderColor[1] = info.ArrowColorSylinder1;
	linfo.sylinderColor[2] = info.ArrowColorSylinder2;
	linfo.diskColor[0] = info.ArrowColorDisk0;
	linfo.diskColor[1] = info.ArrowColorDisk1;
	linfo.diskColor[2] = info.ArrowColorDisk2;
	linfo.flagOutVectorMRC = info.flagOutVector; 



	mrcFileRead(&in, info.In, "in main", 0); 

	lmrcImageShapeSearch(&out, &in, &linfo, info.mode);

	if(info.flagOut) {
		mrcFileWrite(&out, info.Out, "in main", 0);
		sprintf(filename, "%s.PCA", info.Out);	
		mrcFileWrite(&linfo.PCA, filename, "in main", 0);
		sprintf(filename, "%s.PCAaccuracy", info.Out);	
		mrcFileWrite(&linfo.PCAaccuracy, filename, "in main", 0);
	}
	if(info.Refine && info.flagOut) {
		sprintf(filename, "%s.average", info.Out);	
		mrcFileWrite(&linfo.average, filename, "in main", 0);
		sprintf(filename, "%s.sd", info.Out);	
		mrcFileWrite(&linfo.SD, filename, "in main", 0);
		sprintf(filename, "%s.zscore", info.Out);	
		mrcFileWrite(&linfo.Zscore, filename, "in main", 0);
		sprintf(filename, "%s.max", info.Out);	
		mrcFileWrite(&linfo.Max, filename, "in main", 0);
	}

	for(i=0; i<linfo.nShapeInfo; i++) {
		sprintf(filename, "%s.shapeinfo-%02d", info.Out, i);	
		mrcFileWrite(&linfo.shapeInfo[i], filename, "in main", 0);
	}

	if(info.flagShape) {
		mrcFileWrite(&linfo.shape, info.Shape, "in main", 0);
	}
	if(info.flagOutVector) {
		for(i=0; i<3; i++) {
			sprintf(filename, "%s.%1d", info.OutVector, i); 
			mrcFileWrite(&linfo.OutVectorMRC[i], filename, "in main", 0);
		}
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	lmrcImageShapeModePrint(stderr);
}

