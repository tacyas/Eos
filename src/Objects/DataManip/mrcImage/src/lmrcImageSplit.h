/*
# lmrcImageSplit.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageSplit.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"

typedef struct lmrcImageSplitInfo {
	mrcImageParaTypeIntegerCoord Size;
	char* filename;
	char* suffix;
	/* Output */
	char** FileName;
	int    N;
	mrcImage* Out;
} lmrcImageSplitInfo;

extern void lmrcImageSplit(mrcImage* in, lmrcImageSplitInfo* linfo, int mode);
