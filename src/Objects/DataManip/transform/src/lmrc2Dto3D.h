#ifndef LMRC2DTO3D_H
#define LMRC2DTO3D_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc2Dto3D.h ver %I%
#%Z% Created by tacyas 
#%Z%
#%Z% Usage : mrc2Dto3D
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "mrcImage.h"
#include "Matrix3D.h"
#include "lmrcImageRhoFiltering.h"
#include "lmrcImageMultiplying.h"
#include "lmrc3Dto2D.h"
#include "ctfInfo.h"


typedef enum lmrc2Dto3DMode {
	mrc2Dto3DModeSimpleBackProjection = 0,
	mrc2Dto3DModeFilteredBackProjection = 1,
	mrc2Dto3DModeWeightedBackProjection = 2
} lmrc2Dto3DMode;

typedef struct lmrc2Dto3DInfo {
	// for Many Files 
	int    inFileNum; 
	char** inFileList;
	mrcImageTailer* Tailer;

	// For Control  
	long flagDouble;
	long singleTiltMode;
	lmrcImageRhoFiltering1Mode singleFilterMode;
	long mode;
	int  InterpolationMode;
	long flagPlusXrot;
	double Rmax;
	mrcImage* CounterForWeight;
	lmrcImageRhoFilteringInfo rhoInfo;
	lmrcImageRhoFiltering1Info rhoInfo1;

	// Size
	int flagOutputSize;
	int Nx;
	int Ny;
	int Nz;
} lmrc2Dto3DInfo;


typedef struct lmrc2Dto3DSIRTInfo {
	lmrc3Dto2DInfo l3Dto2DInfo;

	ctfInfo ctfInfo;
	int maxIter;
	double rms;
	double lambda;
} lmrc2Dto3DSIRTInfo;

extern void lmrc2Dto3D(mrcImage* Out, mrcImage* in, lmrc2Dto3DInfo* linfo, long mode);
extern void lmrc2Dto3DSimpleBackProjectionForEach(mrcImage* Out, mrcImage* prj, lmrc2Dto3DInfo* linfo, Matrix3D Matrix, long mode);
extern void lmrc2Dto3DFilteredBackProjectionForEach(mrcImage* Out, mrcImage* prj, lmrc2Dto3DInfo* linfo, Matrix3D Matrix, long mode);
extern void lmrc2Dto3DSIRT(mrcImage* Out, mrcImage* in, lmrc2Dto3DInfo* linfo, lmrc2Dto3DSIRTInfo* llinfo, long mode);
#endif /* LMRC2DTO3D_H */
