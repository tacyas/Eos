/*
# lmrcImageFeatureCalc.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageFeatureCalc.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef LMRC_IMAGE_FEATURE_CALC 
#define	LMRC_IMAGE_FEATURE_CALC 

#include <stdio.h>
#include "lmrcImageCalcArea.h"
#include "lmrcImageLabeling.h"
#include "lmrcImageEdge.h"

/* constant begin */


/* constant end */

/* struct begin */

// 2D 
typedef struct lmrcImagePerimeterCalcInfo {
	int flagArea;
	mrcImage* Area;
	mrcImage* Label;


	// 
	int Neighbor;
	//
	mrcImage* ChainCode;
} lmrcImagePerimeterCalcInfo; 

// 3D
typedef struct lmrcImageSurfaceAreaCalcInfo {
	int flagArea;
	mrcImage* Area;
	mrcImage* Label;

	//
	int Neighbor;
	int Mode;
	// 
	mrcImage* Surface;
	int       labelNumber;
	int*      surfaceArea; 
	mrcImageParaTypeIntegerCoord* blCoord;
} lmrcImageSurfaceAreaCalcInfo;


typedef struct lmrcImageCircularityCalcInfo {
	int dummy;
} lmrcImageCircularityCalcInfo; 

typedef struct lmrcImageFeatureEach {
	// Basic
	int   label;
	float area;
	mrcImageParaTypeRealCoord gravityCenter;
	mrcImageParaTypeIntegerCoord bottomLeft;
	
	// PerimeterCalc
	int flagPerimeter;
	double perimeter;

	// SurfaceArea
	int flagSurfaceArea;
	double surfaceArea;

	// CircularityCalc
	int flagCircularity;
	double circularity;

	// Complexity 
	int flagComplexity;
	double complexity;

	// Complexity 
	int flagRadius;
	double radius;
	
	// PCA
	float lamda[3];

	// Shape


  // sumDensity
  int flagSumDensity;
  double sumDensity;
  mrcImage* sumDensityImage;

  // maxDensity
  int flagmaxDensity;
  double maxDensity;
  mrcImage* maxDensityImage;

} lmrcImageFeatureEach;

typedef struct lmrcImageFeatureList {
	int flagNumber;
	int Number;

	int flagEachAllocation;
	lmrcImageFeatureEach* each;

    mrcImage* density;
	//

} lmrcImageFeatureList;

/* struct end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */
extern void lmrcImageFeaturePrint(FILE* fpt, lmrcImageFeatureList* linfo, int mode);

extern void lmrcImageBasicFeatureCalc(mrcImage* out, lmrcImageFeatureList* linfo, mrcImage* in, int mode);

extern void lmrcImagePerimeterCalc(mrcImage* out, mrcImage* in, lmrcImagePerimeterCalcInfo* linfo, int mode);
extern void lmrcImagePerimeterCalcPrint(FILE* fpt, lmrcImagePerimeterCalcInfo linfo, int mode);
extern void lmrcImagePerimeterCalcUsage(FILE* fpt);


extern void lmrcImageSurfaceAreaCalc(mrcImage* out, mrcImage* in, lmrcImageSurfaceAreaCalcInfo* linfo, int mode);
extern void lmrcImageSurfaceAreaCalcPrint(FILE* fpt, lmrcImageSurfaceAreaCalcInfo linfo, int mode);
extern void lmrcImageSurfaceAreaCalcUsage(FILE* fpt);

extern void lmrcImageCircularityCalc(lmrcImageFeatureList* linfo, int mode);
extern void lmrcImageComplexityCalc(lmrcImageFeatureList* linfo, int mode);
extern void lmrcImageRadiusCalc(lmrcImageFeatureList* linfo, int mode);
extern void lmrcImageSumOfDensitycCalc(lmrcImageFeatureList* linfo, int mode);

extern int lmrcImageChainCodeSearch(int* chain, mrcImageParaTypeRealCoord* next, double* dL, mrcImage* in, mrcImageParaTypeRealCoord ori, int chainCodeStart, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* LMRC_IMAGE_FEATURE_CALC */ 
