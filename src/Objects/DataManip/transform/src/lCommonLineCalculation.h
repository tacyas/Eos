/*
# lCommonLineCalculation.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lCommonLineCalculation.h 
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

#define DEBUG
#include "genUtil.h"
#include "Matrix3D.h"

typedef struct lCommonLineCalculationInfo {
	char** I1RotationalMode;
	char** I2RotationalMode;
	float* I1Angle1;
	float* I1Angle2;
	float* I1Angle3;
	float* I2Angle1;
	float* I2Angle2;
	float* I2Angle3;
	float* CLAngleOnI1AgainstI2;
	float* CLAngleOnI2AgainstI1;
	int    num;
	int*   flag;
} lCommonLineCalculationInfo;

void
lCommonLineCalculation(lCommonLineCalculationInfo* linfo, int i, int mode);

double
lCommonLineCalculation1(lCommonLineCalculationInfo* linfo, int i, int mode);
