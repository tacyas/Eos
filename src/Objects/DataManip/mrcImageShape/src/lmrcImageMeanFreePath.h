/*
# lmrcImageMeanFreePath.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageMeanFreePath.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRCIMAGE_MEAN_FREE_PATH_H 
#define LMRCIMAGE_MEAN_FREE_PATH_H 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "Array.h"

/* constant begin */

typedef enum lmrcImageMeanFreePathCalcLineMode {
	lmrcImageMeanFreePathCalcLineModeAnd = 0,
	lmrcImageMeanFreePathCalcLineModeOr  = 1, 
	lmrcImageMeanFreePathCalcLineModeGE  = 2  
} lmrcImageMeanFreePathCalcLineMode; 

typedef enum lmrcImageMeanFreePathCalcLineShape {
	lmrcImageMeanFreePathCalcLineShapeRectangle=0,
	lmrcImageMeanFreePathCalcLineShapeDisk=1
} lmrcImageMeanFreePathCalcLineShape; 

typedef enum lmrcImageMeanFreePathCalcMode {
	MeanFreePathCalcModeAlongZaxis=0,
	MeanFreePathCalcModeAlongXaxis=1,
	MeanFreePathCalcModeAlongYaxis=2,
	MeanFreePathCalcModeAnyDirection=3,
	MeanFreePathCalcModeCalcMode=0x0f,
	MeanFreePathCalcModeRealLength=0x10
} lmrcImageMeanFreePathCalcMode;

/* constant end */

/* struct begin */

typedef struct lmrcImageMeanFreePathCalcInfo {
	int  N;
	int* countWhite;
	int* countBlack;
	int* countWhiteEdge;
	int* countBlackEdge;
	double averageWhite;
	double averageBlack;
	double averageWhiteEdge;
	double averageBlackEdge;
	int sumWhite;
	int sumBlack;
	int sumWhiteEdge;
	int sumBlackEdge;

	//
	mrcImage  white;
	mrcImage  black;
	mrcImage  whiteEdge;
	mrcImage  blackEdge;
	//
	mrcImage direction[3];


	// Control: Input
	mrcImageParaTypeRealCoord Length;
	mrcImageParaTypeRealCoord LineThickness;   
	lmrcImageMeanFreePathCalcLineMode  LineMode;
	lmrcImageMeanFreePathCalcLineShape LineShape;
	mrcImageParaTypeReal deltaPhi;
	mrcImageParaTypeReal deltaTheta;

	// TemporalVariables
	mrcImageParaTypeRealCoord min; 
	mrcImageParaTypeRealCoord max; 
	mrcImageParaTypeRealCoord cur; 
} lmrcImageMeanFreePathCalcInfo;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageMeanFreePathCalcPrint(FILE* fpt, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode mode);
extern void lmrcImageMeanFreePathCalc(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode mode);
extern void lmrcImageMeanFreePathCalcAlongZaxis(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode);
extern void lmrcImageMeanFreePathCalcAnyDirection(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode);
extern double lmrcImageMeanFreePathCalcBWEvaluation(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode);
extern void lmrcImageMeanFreePathCalcMeanCalc(mrcImage* in, lmrcImageMeanFreePathCalcInfo* linfo, lmrcImageMeanFreePathCalcMode  mode);

extern void lmrcImageMeanFreePathCalcModePrint(FILE* fpt);


/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRCIMAGE_MEAN_FREE_PATH_H */ 
