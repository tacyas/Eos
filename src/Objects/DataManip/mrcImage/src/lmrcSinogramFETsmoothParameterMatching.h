/*
# lmrcSinogramFETsmoothParameterMatching.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcSinogramFETsmoothParameterMatching.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include<stdio.h>
#include<math.h>
#include "mrcImage.h"

typedef struct lmrcSinogramFETsmoothParameterMatchingInfo{
	FILE* InList;
	int listLength;
	mrcImage* InSTD;
	int mode;
}lmrcSinogramFETsmoothParameterMatchingInfo;

extern void lmrcSinogramFETsmoothParameterMatching(lmrcSinogramFETsmoothParameterMatchingInfo info, int mode);






