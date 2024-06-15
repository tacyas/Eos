/*
# TestForLcalculationOfOrientationSearchBySimultaneousMinimization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : TestForLcalculationOfOrientationSearchBySimultaneousMinimization
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
#include "lmrcImageOrientationSearchBySimultaneousMinimization.h"

/*
typedef struct lTestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo {
} lTestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo;

typedef enum lTestForLcalculationOfOrientationSearchBySimultaneousMinimizationMode {
	a=0,
	b=1
} lTestForLcalculationOfOrientationSearchBySimultaneousMinimizationMode;
*/

void
__LogFileWrite(mrcImage* ref, mrcImage* other, CommonLineData* commonlinedata, double delU, int Num, int refnum, FILE* fpt, int mode);

void
__RelativeAngleCalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int num, float phi, float theta, float psi, float* Phi, float* Theta, float* Psi, int mode);

void
__mrc3DCreate(mrcImage* mrc3D, lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, double L, float phi, float theta, float psi, int n, int mode);

void
__mrc2DCreate(mrcImage* mrc2D, mrcImage* mrc3D, int mode);

void
lTestForLcalculationOfOrientationSearchBySimultaneousMinimization(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int ErrorPoint, int mode);

void
lTestForLcalculationOfOrientationSearchBySimultaneousMinimization2(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	TestForLcalculationOfOrientationSearchBySimultaneousMinimizationInfo  info;
	lmrcImageOrientationSearchBySimultaneousMinimizationInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.filenum = info.flagIn;
	linfo.angle = MemoryAllocate(EulerAngle, linfo.filenum, "in main");
	for(i=0; i<linfo.filenum; i++){
		linfo.angle[i].filename = MemoryAllocate(char, WORDLEN, "in main");
		strcpy(linfo.angle[i].filename, info.In[i]);
	}
	linfo.dtheta = info.dtheta*RADIAN;
	linfo.dpsi   = info.dpsi*RADIAN;
	linfo.mode   = info.mode;
	linfo.ModeL  = info.modeL;
	linfo.ModeThresholdAngular = info.modeTA;
	linfo.OutFileName = MemoryAllocate(char, WORDLEN, "in main");
	strcpy(linfo.OutFileName, info.Out);
	fclose(info.fptOut);

	linfo.LogFileName   = MemoryAllocate(char, WORDLEN, "in main");
	linfo.mrc2dFileName = MemoryAllocate(char, WORDLEN, "in main");
	linfo.mrc3dFileName = MemoryAllocate(char, WORDLEN, "in main");
	strcpy(linfo.LogFileName,   info.Log);
	fclose(info.fptLog);
	if(strcmp(info.m2, "NULL") == 0){
		strcpy(linfo.mrc2dFileName, info.m2);
		fclose(info.fptm2);
	}
	if(strcmp(info.m3, "NULL") == 0){
		strcpy(linfo.mrc3dFileName, info.m3);
		fclose(info.fptm3);
	}
	linfo.Log2FileName = MemoryAllocate(char, WORDLEN, "in main");
	strcpy(linfo.Log2FileName, info.Log2);
	fclose(info.fptLog2);

	DEBUGPRINT("Program Start\n");

	lInitialDataFileRead(&linfo, info.fptiid, 0);	
	switch(info.mode2){
		case 0 :
			lTestForLcalculationOfOrientationSearchBySimultaneousMinimization(&linfo, info.ep, 0);
		break;
		case 1 :
			lTestForLcalculationOfOrientationSearchBySimultaneousMinimization2(&linfo, 0);
		break;
	}
	
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "-m : 0 : input data --> sinogram\n");
	fprintf(stderr, "     1 : input data --> sinogramFT\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode2 -----\n");
	fprintf(stderr, "-m2 : 0 : normal\n");
	fprintf(stderr, "      1 : about answer\n");
	fprintf(stderr, "\n");
}

void
lTestForLcalculationOfOrientationSearchBySimultaneousMinimization2(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int mode)
{

	int                        J, CommonLineNum, PlaneRotationNum;
	int                        j, i, l, flag, ll;
	int*                       PlaneRotationFileNum;
	float                      RefAngle, OtherAngle;
	float                      phiMin, thetaMin, psiMin;
	float                      Phi, Theta, Psi;
	double                     delU, L, Lmin;	
	PlaneRotationAngle*        planerotationAngle;
	lCommonLineCalculationInfo CommonLineInfo;
	CommonLineData*            Workcommonlinedata;
	CommonLineData*            commonlinedata;
	CommonLineData*            commonlinedataWithPlaneRotation;
	mrcImage                   refOneLineFT, otherOneLineFT;
	FILE*                      fpt;
	FILE*                      fptLog;
	FILE*                      fptLog2;
	FILE*                      fptM2;
	FILE*                      fptM3;
	mrcImage*                  InputImages;
	mrcImage                   mrc3D, mrc2D;
	int                        count, max;
	int*                       num;
	int                        n;

	if((fptLog = fopen(linfo->LogFileName, "w")) == NULL){
		fprintf(stderr, "file not open !! : LogFileName = %s\n", linfo->LogFileName); 
		exit(1);
	}
	if((fptLog2 = fopen(linfo->Log2FileName, "w")) == NULL){
		fprintf(stderr, "file not open !! : LogFileName = %s\n", linfo->LogFileName); 
		exit(1);
	}
	InputImages = MemoryAllocate(mrcImage, linfo->filenum, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
	for(i=0; i<linfo->filenum; i++){
		mrcFileRead(&InputImages[i], linfo->angle[i].filename, "Read InputImages", 0);
	}
	delU = 1/InputImages[0].HeaderLength.x/InputImages[0].HeaderN.x;
	
	Workcommonlinedata = MemoryAllocate(CommonLineData, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
	
    CommonLineInfo.I1RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
    for(i=0; i<linfo->filenum-1; i++){
        CommonLineInfo.I1RotationalMode[i] = MemoryAllocate(char, 5, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
        CommonLineInfo.I2RotationalMode[i] = MemoryAllocate(char, 5, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    }
    CommonLineInfo.I1Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I1Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I1Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");

    CommonLineInfo.I2Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");

    CommonLineInfo.CLAngleOnI1AgainstI2  = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.CLAngleOnI2AgainstI1  = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");

    CommonLineInfo.flag     = MemoryAllocate(int  , linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");

	if((fpt = fopen(linfo->OutFileName, "w")) == NULL){
		fprintf(stderr, "file not open !! : OutFileName = %s\n", linfo->OutFileName); 
		exit(1);
	}

	for(n=0; n<linfo->filenum; n++){
		CommonLineNum    = lAllCommonLineCalculation(linfo, &CommonLineInfo, n, planerotationAngle, Workcommonlinedata, 0, 1);

		commonlinedata   = MemoryAllocate(CommonLineData, CommonLineNum, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
		PlaneRotationNum = lCommonLinesDataSet(linfo, Workcommonlinedata, commonlinedata, 0);

		if(PlaneRotationNum == 0) {
			lAngularWeightCalculation(linfo, commonlinedata, CommonLineNum, 0);
			L = 0;
			fprintf(fpt, "(phi,theta,psi) = (%f,%f,%f) : L = ", linfo->angle[n].phi*DEGREE, linfo->angle[n].theta*DEGREE, linfo->angle[n].psi*DEGREE);
			for(l=0; l<linfo->filenum-1; l++) {
				float LL;
				RefAngle   = commonlinedata[l].angleRef   + linfo->angle[n].psi;
				OtherAngle = commonlinedata[l].angleOther + linfo->angle[commonlinedata[l].num].psi;
				RefAngle   = NORMAL_PHASE(RefAngle);
				OtherAngle = NORMAL_PHASE(OtherAngle);
				lmrcImageOneLineFTCreate(linfo, &InputImages[n], &InputImages[commonlinedata[l].num], 
										 &refOneLineFT, &otherOneLineFT, RefAngle, OtherAngle, 0);
				LL = lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, commonlinedata, delU, l, linfo->ModeL);
				__RelativeAngleCalculation(linfo, commonlinedata[l].num, linfo->angle[n].phi, linfo->angle[n].theta, linfo->angle[n].psi, &Phi, &Theta, &Psi, 0);
				fprintf(fptLog2, "n= %d l= %d LL=%f phi=%f theta=%f psi=%f\n", n, l, LL, Phi*DEGREE, Theta*DEGREE, Psi*DEGREE);
				__LogFileWrite(&refOneLineFT, &otherOneLineFT, commonlinedata, delU, l, n, fptLog, 0);
				mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
				mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
				
				if(linfo->ModeL == 0)      fprintf(fpt, " %7.1f", LL);
				else if(linfo->ModeL == 1) fprintf(fpt, " %7.1f", LL*DEGREE);
				L += LL;
			}
			fprintf(fpt, " %7.1f\n", L);
		} else {
			PlaneRotationFileNum = MemoryAllocate(int, PlaneRotationNum, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
			l = 0;
			for(i=0; i<linfo->filenum-1; i++){
				if(Workcommonlinedata[i].flag == 1){
					PlaneRotationFileNum[l] = Workcommonlinedata[i].num;
					l++;
				}
			}
			commonlinedataWithPlaneRotation = MemoryAllocate(CommonLineData, CommonLineNum+(PlaneRotationNum*InputImages[0].HeaderN.y),
															 "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
		
			lCommonLineDataSetInPlaneRotation(linfo, commonlinedata, commonlinedataWithPlaneRotation, PlaneRotationNum,
			                                  CommonLineNum, i, PlaneRotationFileNum, &InputImages[n], 1);
			lAngularWeightCalculation(linfo, commonlinedataWithPlaneRotation, CommonLineNum+(PlaneRotationNum*InputImages[0].HeaderN.y), 0);
			L = 0;
			fprintf(fpt, "(phi,theta,psi) = (%f,%f,%f) : L = ", linfo->angle[n].phi*DEGREE, linfo->angle[n].theta*DEGREE, linfo->angle[n].psi*DEGREE);
			for(l=0; l<CommonLineNum+(PlaneRotationNum*InputImages[0].HeaderN.y); l++) { /* Loop for Common Line */
				float LL;
				/* I don't know that angleRef and angleOther is answer ?  */
				lmrcImageOneLineFTCreate(linfo, &InputImages[n], &InputImages[commonlinedataWithPlaneRotation[l].num], &refOneLineFT, 
									     &otherOneLineFT, commonlinedataWithPlaneRotation[l].angleRef, commonlinedataWithPlaneRotation[l].angleOther, 0);

				LL = lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, commonlinedataWithPlaneRotation, delU, l, linfo->ModeL);
				__RelativeAngleCalculation(linfo, commonlinedataWithPlaneRotation[l].num, linfo->angle[n].phi, linfo->angle[n].theta, linfo->angle[n].psi, &Phi, &Theta, &Psi, 0);
				fprintf(fptLog2, "n = %d l= %d LL=%f phi=%f theta=%f psi=%f\n", n, l, LL, Phi*DEGREE, Theta*DEGREE, Psi*DEGREE);
				__LogFileWrite(&refOneLineFT, &otherOneLineFT, commonlinedata, delU, l, n, fptLog, 0);
				mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
				mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
				
				if(linfo->ModeL == 0) fprintf(fpt, " %f", LL);
				else if(linfo->ModeL == 1) fprintf(fpt, " %f", LL*DEGREE);
				L += LL;
			}
			fprintf(fpt, " %f\n", L);
			free(commonlinedataWithPlaneRotation);
			free(PlaneRotationFileNum);
		}
		free(commonlinedata);
	}

	fprintf(fpt, "\n(phi, theta, psi) = (%6.2f, %6.2f, %6.2f) : Lmin = %f\n", phiMin*DEGREE, thetaMin*DEGREE, psiMin*DEGREE, Lmin);
	
	fprintf(fpt, "\n");
	for(i=0; i<linfo->filenum; i++){
        fprintf(fpt, "%s ZONS %6.2f %6.2f %6.2f\n", linfo->angle[i].filename, linfo->angle[i].phi*DEGREE,
		                                      		linfo->angle[i].theta*DEGREE, linfo->angle[i].psi*DEGREE);
	}
	fclose(fpt);
	fclose(fptLog);
	fclose(fptLog2);
}

void
lTestForLcalculationOfOrientationSearchBySimultaneousMinimization(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int ErrorPoint, int mode)
{
	int                        J, CommonLineNum, PlaneRotationNum;
	int                        j, i, l, flag, ll;
	int*                       PlaneRotationFileNum;
	float                      RefAngle, OtherAngle;
	float                      phiMin, thetaMin, psiMin;
	float                      Phi, Theta, Psi;
	double                     delU, L, Lmin;	
	PlaneRotationAngle*        planerotationAngle;
	lCommonLineCalculationInfo CommonLineInfo;
	CommonLineData*            Workcommonlinedata;
	CommonLineData*            commonlinedata;
	CommonLineData*            commonlinedataWithPlaneRotation;
	mrcImage                   refOneLineFT, otherOneLineFT;
	FILE*                      fpt;
	FILE*                      fptLog;
	FILE*                      fptLog2;
	FILE*                      fptM2;
	FILE*                      fptM3;
	mrcImage*                  InputImages;
	mrcImage                   mrc3D, mrc2D;
	int                        count, max;
	int*                       num;

	if((fptLog = fopen(linfo->LogFileName, "w")) == NULL){
		fprintf(stderr, "file not open !! : LogFileName = %s\n", linfo->LogFileName); 
		exit(1);
	}
	if((fptLog2 = fopen(linfo->Log2FileName, "w")) == NULL){
		fprintf(stderr, "file not open !! : LogFileName = %s\n", linfo->LogFileName); 
		exit(1);
	}
	InputImages = MemoryAllocate(mrcImage, linfo->filenum, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
	for(i=0; i<linfo->filenum; i++){
		mrcFileRead(&InputImages[i], linfo->angle[i].filename, "Read InputImages", 0);
	}
	delU = 1/InputImages[0].HeaderLength.x/InputImages[0].HeaderN.x;
	
	J = lJcalculation(linfo, 0);
	planerotationAngle = MemoryAllocate(PlaneRotationAngle, J, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
	lPlaneRotationAngleSet(linfo, planerotationAngle, 0);
	
	/* NphiMax count */
	num = MemoryAllocate(int, J, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
	count = 0;
	for(i=0; i<J; i++){
		num[i] = count;
		if(planerotationAngle[i].theta == planerotationAngle[i+1].theta) count++;
		else                                                             count = 0;
		num[i] = count;
	}
	max = 0;
	for(i=0; i<J; i++){
		if(num[i] > max) max = num[i];
	}
	max++;
	
	mrc2D.Header = mrc3D.Header = InputImages[0].Header;
	mrc2D.HeaderMode = mrc3D.HeaderMode = mrcFloatImage;
	mrc2D.HeaderN.x  = mrc3D.HeaderN.x  = max;
	mrc2D.HeaderN.y  = mrc3D.HeaderN.y  = (int)(M_PI/linfo->dtheta + 0.5);
	mrc2D.HeaderN.z  = 1;
	mrc3D.HeaderN.z  = (int)(2*M_PI/linfo->dpsi + 0.5);
	mrc2D.HeaderLength.y = mrc3D.HeaderLength.y = linfo->dtheta*DEGREE;
	mrc3D.HeaderLength.z = linfo->dpsi*DEGREE;
	mrcInit(&mrc2D, NULL);
	mrcInit(&mrc3D, NULL);

	Workcommonlinedata = MemoryAllocate(CommonLineData, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
	
    CommonLineInfo.I1RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lmrcImageOrientationSearchBySimultaneousMinimization");
    for(i=0; i<linfo->filenum-1; i++){
        CommonLineInfo.I1RotationalMode[i] = MemoryAllocate(char, 5, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
        CommonLineInfo.I2RotationalMode[i] = MemoryAllocate(char, 5, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    }
    CommonLineInfo.I1Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I1Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I1Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.I2Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.CLAngleOnI1AgainstI2  = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.CLAngleOnI2AgainstI1  = MemoryAllocate(float, linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
    CommonLineInfo.flag     = MemoryAllocate(int  , linfo->filenum-1, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");

	if((fpt = fopen(linfo->OutFileName, "w")) == NULL){
		fprintf(stderr, "file not open !! : OutFileName = %s\n", linfo->OutFileName); 
		exit(1);
	}

	Lmin     = 1000;
	phiMin   = linfo->angle[ErrorPoint].phi;
	thetaMin = linfo->angle[ErrorPoint].theta;
	psiMin   = linfo->angle[ErrorPoint].psi;
	{
	float weight0=0;
	int count0=0;
	float weight1=1;
	int count1=0;
	for(j=0; j<J; j++){
		CommonLineNum    = lAllCommonLineCalculation(linfo, &CommonLineInfo, ErrorPoint, planerotationAngle, Workcommonlinedata, j, 0);
		commonlinedata   = MemoryAllocate(CommonLineData, CommonLineNum, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
		PlaneRotationNum = lCommonLinesDataSet(linfo, Workcommonlinedata, commonlinedata, 0);

		if(PlaneRotationNum == 0){
			lAngularWeightCalculation(linfo, commonlinedata, CommonLineNum, 0);
			for(i=(int)(PSIMIN/linfo->dpsi+0.5); i*linfo->dpsi<PSIMAX; i++){
				L = 0;
				fprintf(fpt, "(phi,theta,psi) = (%f,%f,%f) : L = ", planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE);
				for(l=0; l<linfo->filenum-1; l++) {
					float LL;
					DEBUGPRINT3("j=%d i=%d l=%d\n", j, i, l);
					RefAngle   = commonlinedata[l].angleRef   + i*linfo->dpsi;
					OtherAngle = commonlinedata[l].angleOther + linfo->angle[commonlinedata[l].num].psi;
					RefAngle   = fmod(RefAngle, 2*M_PI);
					OtherAngle = fmod(OtherAngle, 2*M_PI);
					lmrcImageOneLineFTCreate(linfo, &InputImages[ErrorPoint], &InputImages[commonlinedata[l].num], 
											 &refOneLineFT, &otherOneLineFT, RefAngle, OtherAngle, 0);
					LL = lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, commonlinedata, delU, l, linfo->ModeL);
					__RelativeAngleCalculation(linfo, commonlinedata[l].num, planerotationAngle[j].phi, planerotationAngle[j].theta, i*linfo->dpsi, &Phi, &Theta, &Psi, 0);
					fprintf(fptLog2, "j=%d i= %d l= %d LL=%f phi=%f theta=%f psi=%f\n", j, i, l, LL, Phi*DEGREE, Theta*DEGREE, Psi*DEGREE);
					__LogFileWrite(&refOneLineFT, &otherOneLineFT, commonlinedata, delU, l, ErrorPoint, fptLog, 0);
					mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					
					if(linfo->ModeL == 0)      fprintf(fpt, " %7.1f", LL);
					else if(linfo->ModeL == 1) fprintf(fpt, " %7.1f", LL*DEGREE);
					if(1e8<LL) {
						count0++;
						weight0+=commonlinedata[l].angularweight;	
						if(linfo->ModeL == 0)      fprintf(stderr, "(phi,theta,psi) = (%f,%f,%f) LL: %f AngularWeight: %f\n",  planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE, LL,  commonlinedata[l].angularweight*DEGREE);
						else if(linfo->ModeL == 1) fprintf(stderr, "(phi,theta,psi) = (%f,%f,%f) LL: %f AngularWeight: %f\n",  planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE, LL*DEGREE,  commonlinedata[l].angularweight*DEGREE);
					} else {
						count1++;
						weight1+=commonlinedata[l].angularweight;	
						if(linfo->ModeL == 0)      fprintf(stderr, "small LL: %f AngularWeight: %f\n",  LL,  commonlinedata[l].angularweight*DEGREE);
						else if(linfo->ModeL == 1) fprintf(stderr, "small LL: %f AngularWeight: %f\n",  LL*DEGREE,  commonlinedata[l].angularweight*DEGREE);
						L += LL;
					}
				}
				fprintf(fpt, " %7.1f\n", L);
				if(L < Lmin){
					psiMin   = i*linfo->dpsi;
					thetaMin = planerotationAngle[j].theta;
					phiMin   = planerotationAngle[j].phi;
					Lmin     = L;
				}
				__mrc3DCreate(&mrc3D, linfo, L, planerotationAngle[j].phi, planerotationAngle[j].theta, i*linfo->dpsi, num[j], 0);
			}
		} else {
			PlaneRotationFileNum = MemoryAllocate(int, PlaneRotationNum, "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
			l = 0;
			for(i=0; i<linfo->filenum-1; i++){
				if(Workcommonlinedata[i].flag == 1){
					PlaneRotationFileNum[l] = Workcommonlinedata[i].num;
					l++;
				}
			}
			commonlinedataWithPlaneRotation = MemoryAllocate(CommonLineData, CommonLineNum+(PlaneRotationNum*InputImages[0].HeaderN.y),
															 "in lTestForLcalculationOfOrientationSearchBySimultaneousMinimization");
			
			for(i=(int)(PSIMIN/linfo->dpsi+0.5); i*linfo->dpsi<PSIMAX; i++) {
				lCommonLineDataSetInPlaneRotation(linfo, commonlinedata, commonlinedataWithPlaneRotation, PlaneRotationNum,
				                                  CommonLineNum, i, PlaneRotationFileNum, &InputImages[ErrorPoint], 0);
				lAngularWeightCalculation(linfo, commonlinedataWithPlaneRotation, CommonLineNum+(PlaneRotationNum*InputImages[0].HeaderN.y), 0);
				L = 0;
				fprintf(fpt, "(phi,theta,psi) = (%f,%f,%f) : L = ", planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE);
				for(l=0; l<CommonLineNum+(PlaneRotationNum*InputImages[0].HeaderN.y); l++) { /* Loop for Common Line */
					float LL;
					DEBUGPRINT3("j=%d i=%d l=%d\n", j, i, l);
					/*
					flag = 0;
					for(ll=0; ll<PlaneRotationNum; ll++) { *//* Loop for Plane Rotation *//*
						if(PlaneRotationFileNum[ll] == commonlinedataWithPlaneRotation[l].num) { *//* num: FileNumber FileNum: FileNumber for the ll'th common line of plane rotation*//*
							lmrcImageFTOneLineGet(&refOneLineFT,   &InputImages[ErrorPoint], commonlinedataWithPlaneRotation[l].angleRef,   0);
							lmrcImageFTOneLineGet(&otherOneLineFT, &InputImages[PlaneRotationFileNum[ll]],  commonlinedataWithPlaneRotation[l].angleOther, 0);
							flag = 1;
						}
					}
					if(flag == 0){
						lmrcImageOneLineFTCreate(linfo, &InputImages[ErrorPoint], &InputImages[commonlinedataWithPlaneRotation[l].num], &refOneLineFT, 
											     &otherOneLineFT, commonlinedataWithPlaneRotation[l].angleRef, commonlinedataWithPlaneRotation[l].angleOther, 0);
					}
					*/
					lmrcImageOneLineFTCreate(linfo, &InputImages[ErrorPoint], &InputImages[commonlinedataWithPlaneRotation[l].num], &refOneLineFT, 
										     &otherOneLineFT, commonlinedataWithPlaneRotation[l].angleRef, commonlinedataWithPlaneRotation[l].angleOther, 0);
					
					LL = lLcalculation(linfo, &refOneLineFT, &otherOneLineFT, commonlinedataWithPlaneRotation, delU, l, linfo->ModeL);
					__RelativeAngleCalculation(linfo, commonlinedataWithPlaneRotation[l].num, planerotationAngle[j].phi, planerotationAngle[j].theta, i*linfo->dpsi, &Phi, &Theta, &Psi, 0);
					fprintf(fptLog2, "j=%d i= %d l= %d LL=%f phi=%f theta=%f psi=%f\n", j, i, l, LL, Phi*DEGREE, Theta*DEGREE, Psi*DEGREE);
					__LogFileWrite(&refOneLineFT, &otherOneLineFT, commonlinedata, delU, l, ErrorPoint, fptLog, 0);
					mrcImageFree(&refOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					mrcImageFree(&otherOneLineFT, "in lmrcImageOrientationSearchBySimultaneousMinimization");
					
					if(linfo->ModeL == 0) fprintf(fpt, " %f", LL);
					else if(linfo->ModeL == 1) fprintf(fpt, " %f", LL*DEGREE);
					if(1e8<LL) {
						if(linfo->ModeL == 0) fprintf(stderr, "(phi,theta,psi) = (%f,%f,%f) LL: %f Num: %d AngularWeight: %f\n",  planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE, LL, PlaneRotationNum,  commonlinedataWithPlaneRotation[l].angularweight*DEGREE);
						else if(linfo->ModeL == 1) fprintf(stderr, "(phi,theta,psi) = (%f,%f,%f) LL: %f Num: %d AngularWeight: %f\n",  planerotationAngle[j].phi*DEGREE, planerotationAngle[j].theta*DEGREE, i*linfo->dpsi*DEGREE, LL*DEGREE, PlaneRotationNum,  commonlinedataWithPlaneRotation[l].angularweight*DEGREE);
					} else {
						if(linfo->ModeL == 0) fprintf(stderr, "LL: %f Num: %d AngularWeight: %f\n",  LL, PlaneRotationNum,  commonlinedataWithPlaneRotation[l].angularweight*DEGREE);
						else if(linfo->ModeL == 1) fprintf(stderr, "LL: %f Num: %d AngularWeight: %f\n",  LL*DEGREE, PlaneRotationNum,  commonlinedataWithPlaneRotation[l].angularweight*DEGREE);
						L += LL;
					}
				}
				fprintf(fpt, " %f\n", L);
				if(L < Lmin){
					psiMin   = i*linfo->dpsi;
					thetaMin = planerotationAngle[j].theta;
					phiMin   = planerotationAngle[j].phi;
					Lmin     = L;
				}
				__mrc3DCreate(&mrc3D, linfo, L, planerotationAngle[j].phi, planerotationAngle[j].theta, i*linfo->dpsi, num[j], 0);
			}
			free(commonlinedataWithPlaneRotation);
			free(PlaneRotationFileNum);
		}
		if(count0 != 0) fprintf(stderr, "large: %d %f\n", count0, weight0/count0);	
		if(count1 != 0)fprintf(stderr, "small: %d %f\n", count1, weight1/count1);	
		}
		free(commonlinedata);
	}

	fprintf(fpt, "\n(phi, theta, psi) = (%6.2f, %6.2f, %6.2f) : Lmin = %f\n", phiMin*DEGREE, thetaMin*DEGREE, psiMin*DEGREE, Lmin);
	
	linfo->angle[ErrorPoint].phi   = phiMin;
	linfo->angle[ErrorPoint].theta = thetaMin;
	linfo->angle[ErrorPoint].psi   = psiMin;

	fprintf(fpt, "\n");
	for(i=0; i<linfo->filenum; i++){
        fprintf(fpt, "%s ZONS %6.2f %6.2f %6.2f\n", linfo->angle[i].filename, linfo->angle[i].phi*DEGREE,
		                                      		linfo->angle[i].theta*DEGREE, linfo->angle[i].psi*DEGREE);
	}
	
	__mrc2DCreate(&mrc2D, &mrc3D, 0);
	if(linfo->mrc2dFileName != NULL){	
		mrcFileWrite(&mrc2D, linfo->mrc2dFileName, "2D write", 0);
	}
	if(linfo->mrc3dFileName != NULL){
		mrcFileWrite(&mrc3D, linfo->mrc3dFileName, "3D write", 0);
	}

	fclose(fpt);
	fclose(fptLog);
	fclose(fptLog2);
}

void
__LogFileWrite(mrcImage* ref, mrcImage* other, CommonLineData* commonlinedata, double delU, int Num, int refnum, FILE* fpt, int mode)
{
	int m;
	double* ReRefData;
	double* ReOtherData;
	double* ImRefData;
	double* ImOtherData;
	double RefLength, OtherLength;
	double RefPhase,  OtherPhase;

	ReRefData   = MemoryAllocate(double, ref->HeaderN.x/2 + 1,   "in __LogFileWrite");
	ImRefData   = MemoryAllocate(double, ref->HeaderN.x/2 + 1,   "in __LogFileWrite");
	ReOtherData = MemoryAllocate(double, other->HeaderN.x/2 + 1, "in __LogFileWrite");
	ImOtherData = MemoryAllocate(double, other->HeaderN.x/2 + 1, "in __LogFileWrite");

	for(m=0; m<=ref->HeaderN.x/2; m++){
		mrcPixelDataGet(ref,   m, 0, 0, &ReRefData[m],   mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(other, m, 0, 0, &ReOtherData[m], mrcPixelRePart, mrcPixelHowNearest);
		mrcPixelDataGet(ref,   m, 0, 0, &ImRefData[m],   mrcPixelImPart, mrcPixelHowNearest);
		mrcPixelDataGet(other, m, 0, 0, &ImOtherData[m], mrcPixelImPart, mrcPixelHowNearest);
	}
	
	fprintf(fpt, "%d line: RePart: ", refnum);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		fprintf(fpt, "%f ", ReRefData[m]);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "%d line: ImPart: ", refnum);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		fprintf(fpt, "%f ", ImRefData[m]);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "%d line: Length: ", refnum);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		RefLength   = sqrt(SQR(ReRefData[m])   + SQR(ImRefData[m]));
		fprintf(fpt, "%f ", RefLength);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "%d line: Phase: ", refnum);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		RefPhase = atan2(ImRefData[m], ReRefData[m]);
		if(RefPhase < 0)   RefPhase += 2*M_PI;
		fprintf(fpt, "%f ", RefPhase);
	}
	fprintf(fpt, "\n");

	
	fprintf(fpt, "%d line: RePart: ", commonlinedata[Num].num);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		fprintf(fpt, "%f ", ReOtherData[m]);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "%d line: ImPart: ", commonlinedata[Num].num);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		fprintf(fpt, "%f ", ImOtherData[m]);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "%d line: Length: ", commonlinedata[Num].num);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		OtherLength = sqrt(SQR(ReOtherData[m]) + SQR(ImOtherData[m]));
		fprintf(fpt, "%f ", OtherLength);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "%d line: Phase: ", commonlinedata[Num].num);
	for(m=0; m<=ref->HeaderN.x/2; m++){
		OtherPhase = atan2(ImOtherData[m], ReOtherData[m]);
		if(OtherPhase < 0) OtherPhase += 2*M_PI;
		fprintf(fpt, "%f ", OtherPhase);
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "\n");
	
}

void
__mrc3DCreate(mrcImage* mrc3D, lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, double L, float phi, float theta, float psi, int n, int mode)
{
	int i;
	int Phi, Theta, Psi;

	Phi   = n;
	Theta = (int)((theta/ linfo->dtheta) + 0.5);
	Psi   = (int)((psi  / linfo->dpsi)   + 0.5);

	if(Phi > mrc3D->HeaderN.x-1 || Phi < 0) DEBUGPRINT1("error : phi is wrong !! -> %d\n", Phi);
	if(Theta > mrc3D->HeaderN.y-1 || Theta < 0) DEBUGPRINT1("error : theta is wrong !! -> %d\n", Theta);
	if(Psi > mrc3D->HeaderN.z-1 || Psi < 0) DEBUGPRINT1("error : psi is wrong !! -> %d\n", Psi);

	mrcPixelDataSet(mrc3D, Phi, Theta, Psi, L, mrcPixelRePart);
}

void
__mrc2DCreate(mrcImage* mrc2D, mrcImage* mrc3D, int mode)
{
	int    x, y, z;
	double data;
	double min;

	for(x=0; x<mrc3D->HeaderN.x; x++){
	for(y=0; y<mrc3D->HeaderN.y; y++){
		min = 1000;
		for(z=0; z<mrc3D->HeaderN.z; z++){
			mrcPixelDataGet(mrc3D, x, y, z, &data, mrcPixelRePart, mrcPixelHowNearest);
			if(min > data) min = data;
		}
		mrcPixelDataSet(mrc2D, x, y, 0, min, mrcPixelRePart);
	}
	}
}

void
__RelativeAngleCalculation(lmrcImageOrientationSearchBySimultaneousMinimizationInfo* linfo, int num, float phi, float theta, float psi, float* Phi, float* Theta, float* Psi, int mode)
{
	Matrix3D ref;
	Matrix3D other;
	Matrix3D difference;
	matrix3DRotationSetFollowingEulerAngle(ref, "ZONS", phi, theta, psi, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationAntiSetFollowingEulerAngle(other, "ZONS", 
											   linfo->angle[num].phi,
											   linfo->angle[num].theta,
											   linfo->angle[num].psi,
											   MATRIX_3D_MODE_INITIALIZE);
	matrix3DMultiplyInv(other, ref);
	matrix3DEulerAngleGetFromMatrix3D(ref, "ZONS", Phi, Theta, Psi, 0);
}
