/*
# mrcImage3DSymmetryFind : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImage3DSymmetryFind
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
#include "Matrix3D.h"



typedef enum SpaceGroupNumber {
	SpaceGrouNumberP1  =1,
	SpaceGrouNumberP_1 =2,
	SpaceGrouNumberP2  =3,
	SpaceGrouNumberP21 =4,
	SpaceGrouNumberC2  =5
} SpaceGroupNumber;

typedef struct lmrcImage3DSymmetryFindInfo {
	int    InterpolationMode;	/* IntepolationMode: refer to mrcImageROI */ 
	int    OffsetMode;	
	int    dCos;
	FILE*  fptOut;
	SpaceGroupNumber ISGN;
	double dRot1;
	double minRot1;
	double maxRot1;
	double dRot2;
	double minRot2;
	double maxRot2;
	char*  RotMode;

	int    corMode; /* Correlation mode */

	double corMaxRot1;
	double corMaxRot2;
	double corMaxX;
	double corMaxY;
	double corMaxZ;
	double corMaxCor;

	mrcImage avg;
} lmrcImage3DSymmetryFindInfo;

extern void lmrcImage3DSymmetryFind(mrcImage* in, lmrcImage3DSymmetryFindInfo* linfo, int mode);  
extern void lmrcImage3DSymmetryFindC2(mrcImage* in, lmrcImage3DSymmetryFindInfo* linfo, int mode);  


int
main(int argc, char* argv[]) 
{
	mrcImage3DSymmetryFindInfo info;
	lmrcImage3DSymmetryFindInfo linfo;

	mrcImage in;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.fptOut = info.fptOut;
	linfo.corMode = info.corMode;
	linfo.dRot1   = info.dRot1*RADIAN;	
	linfo.dRot2   = info.dRot2*RADIAN;	
	linfo.minRot1 = info.minRot1*RADIAN;	
	linfo.minRot2 = info.minRot2*RADIAN;	
	linfo.maxRot1 = info.maxRot1*RADIAN;	
	linfo.maxRot2 = info.maxRot2*RADIAN;	
	linfo.RotMode = info.RotMode;
	linfo.OffsetMode = info.OffsetMode;
	linfo.InterpolationMode = info.InterpolationMode;
	linfo.ISGN    = info.ISGN;
	linfo.dCos    = info.dCos;
	mrcFileRead(&in, info.In, "in main", 0);

	lmrcImage3DSymmetryFind(&in, &linfo, info.mode);

	if(info.flagAvg) {
		mrcFileWrite(&linfo.avg, info.Avg, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


void 
lmrcImage3DSymmetryFind(mrcImage* in, lmrcImage3DSymmetryFindInfo* linfo, int mode)
{
	switch(linfo->ISGN) {
		case SpaceGrouNumberC2: {
			lmrcImage3DSymmetryFindC2(in, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Space Group Number: %d\n", linfo->ISGN);
			exit(EXIT_FAILURE);
			break;
		}		
	}
}


void 
lmrcImage3DSymmetryFindC2(mrcImage* in, lmrcImage3DSymmetryFindInfo* linfo, int mode)
{
	FILE* log;
	log = linfo->fptOut;

	int iRot1, iRot2;
	int nRot1, nRot2;
	double dRot1, dRot2;
	double minRot1, minRot2;
	double maxRot1, maxRot2;
	double Rot1, Rot2;
	double cosVal;
	double cor;
	mrcImage	tmpRot;
	mrcImage	tmp;
	Matrix3D    mat, mat0, mat1, mat2;
	mrcImage	corMap;
	mrcImageInformation corInfo;
	mrcImageParaTypeRealCoord shift;
	long n;

	corInfo.mode = meanOfAll;
	log = linfo->fptOut;
	tmpRot.Header.Cont = in->Header.Cont;

	minRot1 = linfo->minRot1;	
	minRot2 = linfo->minRot2;	
	maxRot1 = linfo->maxRot1;	
	maxRot2 = linfo->maxRot2;	

	linfo->corMaxCor = 0;
	dRot2   = linfo->dRot2;	
	nRot2 = (int)(fabs(maxRot2-minRot2)/dRot2)+1;
	for(iRot2=0; iRot2<nRot2; iRot2++) {
		Rot2 = minRot2 + iRot2*dRot2;
		
		if(linfo->dCos==1) {	
		cosVal = cos(Rot2); 
			if(0<fabs(cosVal)) {
				dRot1 = linfo->dRot1/cosVal; 
			} else {
				dRot1 = fabs(maxRot1-minRot1)+1;	
			}
		} else {
			dRot1 = linfo->dRot1;
		}
		nRot1 = (int)(fabs(maxRot1-minRot1)/dRot1)+1;
	for(iRot1=0; iRot1<nRot1; iRot1++) {
		Rot1 = minRot1 + iRot1*dRot1;
		
		matrix3DInit(mat);
		matrix3DRotationSetFollowingEulerAngle    (mat0, linfo->RotMode, Rot1, Rot2, 0,    MATRIX_3D_MODE_INITIALIZE); 
		matrix3DRotationSetFollowingEulerAngle    (mat1, linfo->RotMode, 0,       0, M_PI, MATRIX_3D_MODE_INITIALIZE); 
		matrix3DRotationAntiSetFollowingEulerAngle(mat2, linfo->RotMode, Rot1, Rot2, 0,    MATRIX_3D_MODE_INITIALIZE); 
		matrix3DMultiplyInv(mat2, mat);
		matrix3DMultiplyInv(mat1, mat);
		matrix3DMultiplyInv(mat0, mat);

	/*
		DEBUGPRINT2("START: %f %f\n", Rot1*DEGREE, Rot2*DEGREE);		
		DEBUGPRINT4("MAT: %+8.4f %+8.4f %+8.4f %+8.4f\n", mat[0][0], mat[0][1], mat[0][2], mat[0][3]);		
		DEBUGPRINT4("MAT: %+8.4f %+8.4f %+8.4f %+8.4f\n", mat[1][0], mat[1][1], mat[1][2], mat[1][3]);		
		DEBUGPRINT4("MAT: %+8.4f %+8.4f %+8.4f %+8.4f\n", mat[2][0], mat[2][1], mat[2][2], mat[2][3]);		
		DEBUGPRINT4("MAT: %+8.4f %+8.4f %+8.4f %+8.4f\n", mat[3][0], mat[3][1], mat[3][2], mat[3][3]);		
	*/
		lmrcImageRotation3DFollowingMatrix3D(&tmpRot, in, mat, linfo->InterpolationMode, 1);
		lmrcImageCorrelation(&corMap, in, &tmpRot, linfo->corMode);

		lmrcImageInformation(&corInfo, &corMap);
		fprintf(log, "COR: %f %f %f %f %f %f\n", Rot1*DEGREE, Rot2*DEGREE, corInfo.max, corInfo.maxCoord.x, corInfo.maxCoord.y, corInfo.maxCoord.z);		
		DEBUGPRINT6("COR: %f %f %f %f %f %f\n", Rot1*DEGREE, Rot2*DEGREE, corInfo.max, corInfo.maxCoord.x, corInfo.maxCoord.y, corInfo.maxCoord.z);		
		if(linfo->corMaxCor<corInfo.max) {
			linfo->corMaxCor  = corInfo.max;
			linfo->corMaxRot1 = Rot1;
			linfo->corMaxRot2 = Rot2;
			linfo->corMaxX    = corInfo.maxCoord.x;
			linfo->corMaxY    = corInfo.maxCoord.y;
			linfo->corMaxZ    = corInfo.maxCoord.z;
			DEBUGPRINT6("CORMAX: %f %f %f %f %f %f\n", Rot1*DEGREE, Rot2*DEGREE, corInfo.max, corInfo.maxCoord.x, corInfo.maxCoord.y, corInfo.maxCoord.z);		
		}
		mrcImageFree(&tmpRot, "in lmrcImage3DSymmmetryFindC2");	
	}
	}

	
	matrix3DInit(mat);
	matrix3DRotationSetFollowingEulerAngle    (mat0, linfo->RotMode, linfo->corMaxRot1, linfo->corMaxRot2, 0,    MATRIX_3D_MODE_INITIALIZE); 
	matrix3DRotationSetFollowingEulerAngle    (mat1, linfo->RotMode, 0,                 0,                 M_PI, MATRIX_3D_MODE_INITIALIZE); 
	matrix3DRotationAntiSetFollowingEulerAngle(mat2, linfo->RotMode, linfo->corMaxRot1, linfo->corMaxRot2, 0,    MATRIX_3D_MODE_INITIALIZE); 
	matrix3DMultiplyInv(mat2, mat);
	matrix3DMultiplyInv(mat1, mat);
	matrix3DMultiplyInv(mat0, mat);
	lmrcImageRotation3DFollowingMatrix3D(&tmpRot, in, mat, linfo->InterpolationMode, 1);
	shift.x = -linfo->corMaxX;
	shift.y = -linfo->corMaxY;
	shift.z = -linfo->corMaxZ;
	lmrcImageShift(&tmp, &tmpRot, shift, linfo->InterpolationMode); 
	linfo->avg.Header.Cont = in->Header.Cont;
	mrcInit(&linfo->avg, NULL);
	n=0;
	lmrcImageAdd(&linfo->avg, in, &n);
	lmrcImageAdd(&linfo->avg, &tmp, &n);
	lmrcImageDividedByReal(&linfo->avg, n);
	mrcImageFree(&tmpRot, "in lmrcImage3DSymmmetryFindC2");	
	fprintf(log, "CORMAX: %f %f %f %f %f %f\n", linfo->corMaxRot1*DEGREE, linfo->corMaxRot2*DEGREE, linfo->corMaxCor, linfo->corMaxX, linfo->corMaxY, linfo->corMaxZ);		
}

