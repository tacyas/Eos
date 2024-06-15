#ifndef LMRC3DTO2D_H
#define LMRC3DTO2D_H
/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmrc3Dto2D.h ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : mrc3Dto2D
#%Z% Attention
#%Z%
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#undef DEBUG
#include "genUtil.h"
#include "Matrix3D.h"
#include "Vector.h"
#include "mrcImage.h"
#include "lmrc3Dto2D.h"
#include "lmrcFFTCentralSection.h"

typedef enum lmrc3Dto2DObjectAreaMode {
	lmrc3D2DObjectAreaModeCubic=0,
	lmrc3D2DObjectAreaModeGlobular=1
} lmrc3Dto2DObjectAreaMode;

typedef struct lmrc3Dto2DInfo {
	/* Rot1 */
	double Rot1Start;
	double Rot1End;
	double Rot1Delta;
	int    nRot1;

	/* Rot2 */
	double Rot2Start;
	double Rot2End;
	double Rot2Delta;
	int    nRot2;

	/* Rot3 */
	double Rot3Start;
	double Rot3End;
	double Rot3Delta;
	int    nRot3;

	/* EulerAngleMode*/
	char   EulerAngleMode[5];

	/* InterpolationMode */
	int InterpolationMode;

	/* */
	lmrc3Dto2DObjectAreaMode AreaMode; 

	/* PVM */
	int flagPVM;	

	/* fileListInformation */
	int flagFileList;
	char* filenamePrefix;
	char* filenameSuffix;
	char* filenameNumberFormat; 
} lmrc3Dto2DInfo;

typedef struct lmrc3Dto2DSingleInfo {
	/* Section */
	int section;
	/* Init */
	int flagInit;

} lmrc3Dto2DSingleInfo;

typedef struct lmrc3Dto2DFFTInfoOut{
    mrcImage out;
    char EulerMode[5];
    double Rot[3];
    double Prior;
}lmrc3Dto2DFFTInfoOut;

typedef struct lmrc3Dto2DFFTInfo{
 
    lmrc3Dto2DFFTInfoOut* Out;
    lmrcFFTCentralSectionsGetInfo llinfo;
}lmrc3Dto2DFFTInfo;



extern void lmrcImage3Dto2D(mrcImage* out, mrcImage* in, lmrc3Dto2DInfo* linfo, int mode);
extern void lmrcImage3Dto2DFollowingTailer(mrcImage* out, mrcImage* in, mrcImage* ref, lmrc3Dto2DInfo* linfo, int mode);
extern void lmrcImage3Dto2DSingle(mrcImage* out, mrcImage* in, 
	char Mat[4], 
	double Rot1, 
	double Rot2,
	double Rot3, 
	lmrc3Dto2DInfo* linfo, 
	lmrc3Dto2DSingleInfo* llinfo, 
	int mode);
/*3DFFT to 2DFFT*/
extern void lmrc3Dto2DFFT(lmrc3Dto2DFFTInfoOut* Out, mrcImage* template, mrcImage* volume, lmrc3Dto2DFFTInfo* linfo, int mode);
extern void lmrc3Dto2DFFTInfoWrite(FILE* fpt, char* filename, char* file3d, lmrc3Dto2DFFTInfoOut* Out, lmrc3Dto2DFFTInfo* linfo,int mode);

#endif /* LMRC2DTO3D_H */
