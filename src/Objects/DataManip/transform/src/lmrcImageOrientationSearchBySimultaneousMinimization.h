/*
# lmrcImageOrientationSearchBySimultaneousMinimization.h : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmrcImageOrientationSearchBySimultaneousMinimization.h 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include "mrcImage.h"
#include "Memory.h"
#include "eosString.h"
#include "genUtil.h"
#include "lCommonLineCalculation.h"

#define WORDLEN  (1024)
#define PHIMIN   (0)
#define PHIMAX   (2*M_PI-(M_PI/180/2))
#define THETAMIN (0)
#define THETAMAX (M_PI)
#define PSIMIN   (0)
#define PSIMAX   (2*M_PI-(M_PI/180/2))



typedef struct EulerAngle {
	char* filename;

	float phi;
	float theta;
	float psi;
} EulerAngle;

typedef struct lmrcImageOrientationSearchBySimultaneousMinimizationInfo {
	int    filenum;
	char*  OutFileName;

	float  dtheta;
	float  dpsi;

	int    mode;
	int    initialrandomdata;
	int    modeinitialdata;
	int    ModeStartPoint;
	int    ModeAngularArea;
	int    ModeL;
	int    ModeThresholdAngular;
	int    ModeCalculationArea;
	int    ModeFix;
	double ThresholdCalculationArea;

	char*  LogFileName;
	char*  Log2FileName;
	char*  mrc2dFileName;
	char*  mrc3dFileName;

	int    MaxCount;
	char*  FileNameHeader;

	EulerAngle* angle;
} lmrcImageOrientationSearchBySimultaneousMinimizationInfo;

typedef struct PlaneRotationAngle {
	float theta;
	float phi;
} PlaneRotationAngle;

typedef struct CommonLineData {
	float angleRef;
	float angleOther;
	float angularweight;
	int   num;
	int   flag;
} CommonLineData;

double
lLcalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, mrcImage* refOneLineFT, mrcImage* otherOneLineFT, 
			  mrcImage* refOneLineSino, mrcImage* otherOneLineSino, CommonLineData* commonlinedata, double delU, int Num, int mode);

int
lAllCommonLineCalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, int N,
                          PlaneRotationAngle* planerotationAngle, CommonLineData* Workcommonlinedata, int j, int mode);

int
lJcalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode);

void
lPlaneRotationAngleSet(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, PlaneRotationAngle* planerotationAngle, int mode);

void
lAngularWeightCalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, CommonLineData* commonlinedata, int CommonLineNum, int mode);

void
lCommonLineDataSetInPlaneRotation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, CommonLineData* commonlinedata,
                                  CommonLineData* commonlinedataWithPlaneRotation, int PlaneRotationNum, int CommonLineNum, int i,
                                  int* PlaneRotationFileNum, mrcImage* ref, int mode);

int
lCommonLinesDataSet(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, CommonLineData* Workcommonlinedata, CommonLineData* commonlinedata, int mode);

void
lInitialDataFileRead(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, FILE* fpt, int mode);

void
lmrcImageOneLineGet(mrcImage* out, mrcImage* in, float angle, int mode);

void
lmrcImageFTOneLineGet(mrcImage* out, mrcImage* in, float angle, int mode);

void
lmrcImageOneLineFTCreate(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, mrcImage* ref, mrcImage* other,
                         mrcImage* refOneLineFT, mrcImage* otherOneLineFT, float RefAngle, float OtherAngle, int mode);

double 
lmrcImageOneLineSinogramCorrelationAdditionalWeight(mrcImage* in, mrcImage* ref, int mode);						  
