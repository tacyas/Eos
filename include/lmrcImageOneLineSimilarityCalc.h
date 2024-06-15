/*
# lmrcImageOneLineSimilarityCalc.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageOneLineSimilarityCalc.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include "mrcImage.h"

typedef struct lmrcImageOneLineSimilarityCalc {
	int shiftflag;
	int shiftrange;
	int methodmode;
}lmrcImageOneLineSimilarityCalcInfo;

extern double lmrcImageOneLineSimilarityCalc(mrcImage* in1, mrcImage* in2, lmrcImageOneLineSimilarityCalcInfo linfo);

