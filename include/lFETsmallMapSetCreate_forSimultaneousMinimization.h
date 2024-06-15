/*
# lFETsmallMapSetCreate_forSimultaneousMinimization.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lFETsmallMapSetCreate_forSimultaneousMinimization.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include<stdio.h>
#include<math.h>
#include "mrcImage.h"
#include<stdlib.h>


typedef struct lFETsmallMapSetCreate_forSimultaneousMinimizationInfo{
	FILE* InML;
	mrcImage* Out;
	int ss;
	int sr;
	int mode;
}lFETsmallMapSetCreate_forSimultaneousMinimizationInfo;

extern void lFETsmallMapSetCreate_forSimultaneousMinimization(lFETsmallMapSetCreate_forSimultaneousMinimizationInfo info, int mode);











