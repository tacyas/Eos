/*
# mrcImageShape.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShape.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#ifndef MRC_IMAGE_SHAPE_H 
#define MRC_IMAGE_SHAPE_H 

#include <stdio.h>
#include "genUtil.h"
#include "Memory.h"
#include "Matrix3D.h"
#include "Vector.h"
#include "mrcImage.h"
#include "mrcImageShape.h"
#include "avsFile.h"


/* constant begin */
typedef enum lmrcImageShapeMode {
    lmrcImageShapeModeNoShape=-1,
    lmrcImageShapeModeSylinder=0,
    lmrcImageShapeModeDisk=1,
    lmrcImageShapeModeSphere=2,
    lmrcImageShapeModeMax=3
} lmrcImageShapeMode;

typedef enum lmrcImageShapeContactMode {
    lmrcImageShapeContactModeNoShape=-1,
    lmrcImageShapeContactModeSylinderSylinder=0,
    lmrcImageShapeContactModeMax=1
} lmrcImageShapeContactMode;


/* constant end */

/* struct begin */

typedef struct lmrcImageShapeSearchInfo {
    float radius; // Sylinder, half disk, sphere
    float minRadius;
    float maxRadius;
    float delRadius;

    float length; // Sylinder
    float minLength;
    float maxLength;
    float delLength;

    float minTheta;
    float maxTheta;
    float delTheta;

    float minPhi;
    float maxPhi;
    float delPhi;

    float minPsi;
    float maxPsi;
    float delPsi;

    int nCube;

    int flagSmooth;
    int radiusSmooth;
    
    // temporary
    float x;
    float y;
    float z;

    int interpMode;
    int thresZscore;

    // Control
    int flagRefine;

    // Output
    mrcImage average; // Average for all orientations
    mrcImage SD;      // SD for all 
    mrcImage Max;     // Max for all 
    mrcImage Zscore;  // Z-score;
    mrcImage PCA;     // PCA 
    mrcImage PCAaccuracy; 
    int nShapeInfo;
    mrcImage* shapeInfo; // Shape, Orientation, ... 
    mrcImage shape; // Template Structure 

    // Direction
    FILE*   OutVectorBILD;
    float   ZoomVector;
    float   arrowr1;
    float   arrowr2;
    float   arrowrho;
    float   sylinderColor[3];
    float   diskColor[3];

    int     flagOutVectorMRC;
    mrcImage OutVectorMRC[3];

    avsFileField OutVectorFLD;
} lmrcImageShapeSearchInfo;

/* end */

#ifdef __cplusplus
extern "C" {
#endif

/* prototype begin */

extern void lmrcImageShapeModePrint(FILE* fpt);

extern void lmrcImageShapeSearch(mrcImage* out, mrcImage* in, lmrcImageShapeSearchInfo* linfo, int mode);
extern void lmrcImageShapeSearchCalc0(mrcImage* out, mrcImage* in, lmrcImageShapeSearchInfo* linfo, int mode);
extern void lmrcImageShapeSearchSylinder(double* data, mrcImage* in, Matrix3D mat, lmrcImageShapeSearchInfo* linfo, int mode);
extern void lmrcImageShapeSearchDisk(double* data, mrcImage* in, Matrix3D mat, lmrcImageShapeSearchInfo* linfo, int mode);
extern void lmrcImageShapeSearchSphere(double* data, mrcImage* in, Matrix3D mat, lmrcImageShapeSearchInfo* linfo, int mode);
extern void lmrcImageShapeSearchModePrint(FILE* fpt);


extern void lmrcImageShapeContactSearch(mrcImage* contact, lmrcImageShapeSearchInfo* linfo, mrcImage* in, int mode);
extern void lmrcImageShapeContactSearch0(mrcImage* contact, lmrcImageShapeSearchInfo* linfo, mrcImage* in, int mode);

/* prototype end */

#ifdef __cplusplus
};
#endif

#endif  /* XXXX */ 
