/*
# lAllCommonLineCalculation.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lAllCommonLineCalculation.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#ifndef SIMULTANEOUS_COMMON_STRUCT
#define SIMULTANEOUS_COMMON_STRUCT

typedef struct CommonLineData {
	float angleRef;
	float angleOther;
	float angularweight;
	int num;
	int flag;
} CommonLineData;

#endif

#ifndef SIMULTANEOUS_OTHER_STRUCT
#define SIMULTANEOUS_OTHER_STRUCT

#include "lCommonLineCalculation.h"

typedef struct EulerAngle {
	char* filename;

	float phi;
	float theta;
	float psi;
} EulerAngle;

typedef struct lmrcImageOrientationSearchBySimultaneousMinimizationInfo {
	int   filenum;
	char* OutFileName;

	float dtheta;
	float dpsi;

	int mode;
	int initialrandomdata;
	int modeinitialdata;
	int ModeStartPoint;
	int ModeAngularArea;

	int   MaxCount;
	char* FileNameHeader;

	EulerAngle* angle;
} lmrcImageOrientationSearchBySimultaneousMinimizationInfo;

typedef struct PlaneRotationAngle {
	float theta;
	float phi;
} PlaneRotationAngle;

int
lAllCommonLineCalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, int* randomNn,
                          PlaneRotationAngle* planerotationAngle, CommonLineData* Workcommonlinedata, int n, int j, int mode);

#endif
