/*
# marker2Dto3DEstimator : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : marker2Dto3DEstimator
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
#include "Memory.h"
#include "eosString.h"
#include "eosPoint.h"

typedef struct lmarker2Dto3DEstimatorInfo {
	// Input 
	eosPoint*       pList2D;
	EulerAngleInfo* EAListInit;
	Matrix3D*       matListInit; 
	int				flagSigmaIn;
	int				zeroPlane;
	double          initShiftX;
	double          initShiftY;
	// Control

	// Output
	eosPoint*       pList3D;
	EulerAngleInfo* EAListFinal;
	EulerAngleInfo* EAListSigma;
	Matrix3D*       matListFinal;
	int				flagSigmaOut;
} lmarker2Dto3DEstimatorInfo;

/*
typedef enum lmarker2Dto3DEstimatorMode {
	a=0,
	b=1
} lmarker2Dto3DEstimatorMode;
*/

extern void lmarker2Dto3DEstimator(lmarker2Dto3DEstimatorInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	int i;
	char s[STRING_MAX_LENGTH];
	marker2Dto3DEstimatorInfo  info;
	lmarker2Dto3DEstimatorInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");


	// Read init parameters  
	linfo.pList2D = (eosPoint*) memoryAllocate(sizeof(eosPoint)*info.flagIn, "in main");
	linfo.flagSigmaIn = info.InType;
	for(i=0; i<info.flagIn; i++) {
		eosPointRead(info.fptIn[i], &(linfo.pList2D[i]), linfo.flagSigmaIn);
    }
	linfo.matListInit = (Matrix3D*) memoryAllocate(sizeof(Matrix3D)*info.flagIn, "in main");
	linfo.EAListInit  = (EulerAngleInfo*) memoryAllocate(sizeof(EulerAngleInfo)*info.flagIn, "in     main");
	fseek(info.fptInList, 0L, SEEK_SET);
	for(i=0; i<info.flagIn; i++) {
		stringGetFromFile(s, "main", info.fptInList, stderr, 3);
		stringCopy(linfo.EAListInit[i].EAMode, stringGetNthWord(s, 2, " ,\t"), 4);
		linfo.EAListInit[i].Rot1 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		linfo.EAListInit[i].Rot2 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		linfo.EAListInit[i].Rot3 = stringGetNthRealData(s, 5, " ,\t")*RADIAN;
		linfo.initShiftX = stringGetNthRealData(s, 6, " ,\t")*RADIAN;
		linfo.initShiftX = stringGetNthRealData(s, 7, " ,\t")*RADIAN;
		matrix3DRotationSetFollowingEulerAngle(linfo.matListInit[i],
			linfo.EAListInit[i].EAMode,
			linfo.EAListInit[i].Rot1,
			linfo.EAListInit[i].Rot2,
			linfo.EAListInit[i].Rot3, MATRIX_3D_MODE_INITIALIZE);
	}

	lmarker2Dto3DEstimator(&linfo, info.mode);

	// Write final parameters
	if(info.flagOut) {
		for(i=0; i<info.flagOut; i++) {
			eosPointWrite(info.fptOut[i], &(linfo.pList3D[i]), info.OutType);
		}
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- input; -i  -----\n");
	fprintf(stderr, "-i pointListPerEachImage\n");
	fprintf(stderr, "point2d.000 YOYS tiltAngle0 tiltAxisBeta0 tiltAxisAlpha0 axisShiftX0 axisShiftY0\n");
	fprintf(stderr, "point2d.001 YOYS tiltAngle1 tiltAxisBeta1 tiltAxisAlpha1 axisShiftX1 axisShiftY1\n");
	fprintf(stderr, ".....\n");
	fprintf(stderr, "EachFile::eosPoint(type)\n");
	fprintf(stderr, "x0 y0 0 weight0 sigx0 sigy0 0\n");
	fprintf(stderr, "x1 y1 0 weight1 sigx1 sigy1 0\n");
	fprintf(stderr, ".....\n");
}

void
lmarker2Dto3DEstimator(lmarker2Dto3DEstimatorInfo* linfo, int mode)
{

	

}

