/*
# lLcalculation.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lLcalculation.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#ifndef SIMULTANEOUS_COMMON_STRUCT
#define SIMULTANEOUS_COMMON_STRUCT

#include "mrcImage.h"
#include "genUtil.h"

typedef struct CommonLineData {
	float angleRef;
	float angleOther;
	float angularweight;
	int num;
	int flag;
} CommonLineData;

double
lLcalculation(mrcImage* refOneLineFT, mrcImage* otherOneLineFT, CommonLineData* commonlinedata, double delU, int Num, int mode);

#endif
