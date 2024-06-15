/*
# mrcImageShapePCAFit : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageShapePCAFit
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
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageShapePCA.h"

int
main(int argc, char* argv[]) 
{
	mrcImageShapePCAFitInfo info;
	mrcImage in;
	mrcImage ref;
	mrcImage tmp;
	mrcImage fit;
	mrcImage fitIn;
	mrcImage fitRef;
	lmrcImageShapePCAInfo linfoIn;
	lmrcImageShapePCAInfo linfoRef;
	lmrcImageShapePCAInfo linfoFit;
	lmrcImageShapePCAInfo linfoFitIn;
	lmrcImageShapePCAInfo linfoFitRef;
	Matrix3D mat;
	Matrix3D mat1;
	Matrix3D matRef;
	Matrix3D matIn;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in,  info.In,  "in main", 0);
	mrcFileRead(&ref, info.Ref, "in main", 0);

    linfoIn.nLevel  = info.flagContour;
    linfoRef.nLevel = info.flagContour;
    linfoFit.nLevel = info.flagContour;
    linfoFitIn.nLevel  = info.flagContour;
    linfoFitRef.nLevel = info.flagContour;
    if(0<linfoIn.nLevel) {
    	linfoIn.Level  = info.Contour;
    	linfoRef.Level = info.Contour;
    	linfoFit.Level = info.Contour;
    	linfoFitIn.Level  = info.Contour;
    	linfoFitRef.Level = info.Contour;
    } else {
        if(NULL!=(linfoIn.Level=(float*)malloc(sizeof(float)*1))) {
            fprintf(stderr, "Not allocated \n");
            exit(EXIT_FAILURE);
        }
        if(NULL!=(linfoRef.Level=(float*)malloc(sizeof(float)*1))) {
            fprintf(stderr, "Not allocated \n");
            exit(EXIT_FAILURE);
        }
        if(NULL!=(linfoFit.Level=(float*)malloc(sizeof(float)*1))) {
            fprintf(stderr, "Not allocated \n");
            exit(EXIT_FAILURE);
        }
        if(NULL!=(linfoFitIn.Level=(float*)malloc(sizeof(float)*1))) {
            fprintf(stderr, "Not allocated \n");
            exit(EXIT_FAILURE);
        }
        if(NULL!=(linfoFitRef.Level=(float*)malloc(sizeof(float)*1))) {
            fprintf(stderr, "Not allocated \n");
            exit(EXIT_FAILURE);
        }
        linfoIn.Level[0]  = 1;
        linfoRef.Level[0] = 1;
        linfoFit.Level[0] = 1;
        linfoFitIn.Level[0]  = 1;
        linfoFitRef.Level[0] = 1;
    }

	// Calculation PCA 
	lmrcImageShapePCA(&in,  &linfoIn,  info.mode);
	lmrcImageShapePCA(&ref, &linfoRef, info.mode);

	// Output Prams
	fprintf(info.fptOut, "#In");	
	lmrcImageShapePCAResultsPrint(info.fptOut, &linfoIn, info.mode);
	fprintf(info.fptOut, "#Ref");	
	lmrcImageShapePCAResultsPrint(info.fptOut, &linfoRef, info.mode);

	// Matrix3D for fitting
	matrix3DFromRotationMatrix(matIn,  linfoIn.u);
	matrix3DFromRotationMatrix(matRef, linfoRef.u);

#ifdef DEBUG
	fprintf(stderr, "\nUnit(In): matIn \n");
	matrix3DFileWrite(stderr, matIn);
	fprintf(stderr, "\nUnit(Ref): matRef\n");
	matrix3DFileWrite(stderr, matRef);
	fprintf(stderr, "\n\n");
#endif

	if(info.flagFit) {
		/* 
			The UnitVector Array supplys 
			the Rotation Matrix from the Objects to the Reference: 1st (1,0,0), 2nd (0,1,0), 3rd (0,0,1) 
		*/
		matrix3DInverse(matIn);
		matrix3DMultiply(matIn, matRef); // matIn = matIn-1 * matRef, i.e., matRef-1 * matIn
		lmrcImageRotation3DFollowingMatrix3D(&fit, &in, matIn, info.IMode, info.mode);

		lmrcImageShapePCA(&fit, &linfoFit, info.mode);

		fprintf(info.fptOut, "#Fit");	
		lmrcImageShapePCAResultsPrint(info.fptOut, &linfoFit, info.mode);
		mrcFileWrite(&fit, info.Fit, "in main", 0);
	}

	if(info.flagFitMat) {
		matrix3DFileWrite(info.fptFitMat, mat);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
