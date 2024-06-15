/*
# CheckCommonLineData : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : CheckCommonLineData
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
#define WORDLEN (1024)
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "eosString.h"
#include "lCommonLineCalculation.h"

typedef struct EulerData{
	char* filename;
	char* RotMode;
	float phi;
	float theta;
	float psi;
} EulerData;

typedef struct lCheckCommonLineDataInfo {
	int        filenum;
	EulerData* InputData;
	mrcImage   outRe;
	mrcImage   outIm;
	mrcImage   outLen;
	mrcImage   outPha;
	mrcImage   outL;
	FILE*      fptLog;
} lCheckCommonLineDataInfo;

/*
typedef enum lCheckCommonLineDataMode {
	a=0,
	b=1
} lCheckCommonLineDataMode;
*/

void
__InputFileRead(lCheckCommonLineDataInfo* linfo, FILE* fpt, int mode);

void
lCheckCommonLineData(lCheckCommonLineDataInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	CheckCommonLineDataInfo  info;
	lCheckCommonLineDataInfo linfo;
	int                      i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.filenum = info.flagIn;
	linfo.InputData = MemoryAllocate(EulerData, linfo.filenum, "in main");
	for(i=0; i<linfo.filenum; i++){
		linfo.InputData[i].filename = MemoryAllocate(char, WORDLEN, "in main");
		strcpy(linfo.InputData[i].filename, info.In[i]);
		linfo.InputData[i].RotMode = MemoryAllocate(char, 5, "in main");
	}
	linfo.fptLog = info.fptLog;

	DEBUGPRINT("Program Start\n");
	
	__InputFileRead(&linfo, info.fptInList, 0);
	lCheckCommonLineData(&linfo, 0);
	if(info.flagOutR == 1){
		mrcFileWrite(&linfo.outRe, info.OutR, "out write", 0);
	}
	if(info.flagOutI == 1){
		mrcFileWrite(&linfo.outIm, info.OutI, "out write", 0);
	}
	if(info.flagOutL == 1){
		mrcFileWrite(&linfo.outLen, info.OutL, "out write", 0);
	}
	if(info.flagOutP == 1){
		mrcFileWrite(&linfo.outPha, info.OutP, "out write", 0);
	}
	if(info.flagOutLL == 1){
		mrcFileWrite(&linfo.outL, info.OutLL, "out write", 0);
	}
	fclose(linfo.fptLog);
	
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
__InputFileRead(lCheckCommonLineDataInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;

	s = MemoryAllocate(char, WORDLEN, "in __InputFileRead");

	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->filenum; i++){
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->InputData[i].RotMode, stringGetNthWord(s, 2, " ,\t"), 4);
		linfo->InputData[i].phi   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		linfo->InputData[i].theta = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		linfo->InputData[i].psi   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
	}
}

void
lCheckCommonLineData(lCheckCommonLineDataInfo* linfo, int mode)
{
	int                        i, p, delta;
	int                        otherCommonPosition;
	int                        tmpOtherY;
	lCommonLineCalculationInfo CommonLineInfo;
	mrcImage ref;
	mrcImage other;
	float  refY, otherY;
	double refRe, refIm;
	double otherRe, otherIm;
	double refLen, refPha;
	double otherLen, otherPha;
	double Re, Im, Len, Pha;
	double ReMin, ImMin, LenMin, PhaMin;
	int    ReDeltaMin, ImDeltaMin, LenDeltaMin, PhaDeltaMin;
	double value;
	double L, LMin; 
	int    LDeltaMin;

    CommonLineInfo.I1RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.I2RotationalMode = MemoryAllocate(char*, linfo->filenum-1, "in lCheckCommonLineData");
	for(i=0; i<linfo->filenum-1; i++){
		CommonLineInfo.I1RotationalMode[i] = MemoryAllocate(char, 5, "in lCheckCommonLineData");
		CommonLineInfo.I2RotationalMode[i] = MemoryAllocate(char, 5, "in lCheckCommonLineData");
	}
	CommonLineInfo.I1Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.I1Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.I1Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.I2Angle1 = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.I2Angle2 = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.I2Angle3 = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.CLAngleOnI1AgainstI2  = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.CLAngleOnI2AgainstI1  = MemoryAllocate(float, linfo->filenum-1, "in lCheckCommonLineData");
	CommonLineInfo.flag     = MemoryAllocate(int  , linfo->filenum-1, "in lCheckCommonLineData");

	for(i=1; i<linfo->filenum; i++){
		strcpy(CommonLineInfo.I1RotationalMode[i-1], linfo->InputData[0].RotMode);
		CommonLineInfo.I1Angle1[i-1] = linfo->InputData[0].phi;
		CommonLineInfo.I1Angle2[i-1] = linfo->InputData[0].theta;
		CommonLineInfo.I1Angle3[i-1] = linfo->InputData[0].psi;
		strcpy(CommonLineInfo.I2RotationalMode[i-1], linfo->InputData[i].RotMode);
		CommonLineInfo.I2Angle1[i-1] = linfo->InputData[i].phi;
		CommonLineInfo.I2Angle2[i-1] = linfo->InputData[i].theta;
		CommonLineInfo.I2Angle3[i-1] = linfo->InputData[i].psi;
	}

	mrcFileRead(&ref, linfo->InputData[0].filename, "Read ref", 0);
	linfo->outRe.Header = ref.Header;
	linfo->outRe.HeaderMode = mrcFloatImage;
	linfo->outRe.HeaderN.x = linfo->filenum-1;
	linfo->outRe.HeaderN.y = ref.HeaderN.y;
	linfo->outRe.HeaderN.z = 1;
	linfo->outRe.HeaderLength.y = ref.HeaderLength.y;
	mrcInit(&linfo->outRe, NULL);
	linfo->outIm.Header = ref.Header;
	linfo->outIm.HeaderMode = mrcFloatImage;
	linfo->outIm.HeaderN.x = linfo->filenum-1;
	linfo->outIm.HeaderN.y = ref.HeaderN.y;
	linfo->outIm.HeaderN.z = 1;
	linfo->outIm.HeaderLength.y = ref.HeaderLength.y;
	mrcInit(&linfo->outIm, NULL);
	linfo->outLen.Header = ref.Header;
	linfo->outLen.HeaderMode = mrcFloatImage;
	linfo->outLen.HeaderN.x = linfo->filenum-1;
	linfo->outLen.HeaderN.y = ref.HeaderN.y;
	linfo->outLen.HeaderN.z = 1;
	linfo->outLen.HeaderLength.y = ref.HeaderLength.y;
	mrcInit(&linfo->outLen, NULL);
	linfo->outPha.Header = ref.Header;
	linfo->outPha.HeaderMode = mrcFloatImage;
	linfo->outPha.HeaderN.x = linfo->filenum-1;
	linfo->outPha.HeaderN.y = ref.HeaderN.y;
	linfo->outPha.HeaderN.z = 1;
	linfo->outPha.HeaderLength.y = ref.HeaderLength.y;
	mrcInit(&linfo->outPha, NULL);
	linfo->outL.Header = ref.Header;
	linfo->outL.HeaderMode = mrcFloatImage;
	linfo->outL.HeaderN.x = linfo->filenum-1;
	linfo->outL.HeaderN.y = ref.HeaderN.y;
	linfo->outL.HeaderN.z = 1;
	linfo->outL.HeaderLength.y = ref.HeaderLength.y;
	mrcInit(&linfo->outL, NULL);

	for(i=1; i<linfo->filenum; i++){
		mrcFileRead(&other, linfo->InputData[i].filename, "Read other", 0);
		value = lCommonLineCalculation1(&CommonLineInfo, i-1, 0);
		
		refY   = CommonLineInfo.CLAngleOnI1AgainstI2[i-1]/(ref.HeaderLength.y*RADIAN);
		otherY = CommonLineInfo.CLAngleOnI2AgainstI1[i-1]/(other.HeaderLength.y*RADIAN);
		fprintf(linfo->fptLog, "Common line position: ref=%5.1f other=%5.1f OuterProduct=%f\n", 
								CommonLineInfo.CLAngleOnI1AgainstI2[i-1]*DEGREE, CommonLineInfo.CLAngleOnI2AgainstI1[i-1]*DEGREE, value);
		otherCommonPosition = (int)(otherY + 0.5);
		for(delta=0; delta<other.HeaderN.y; delta++){
			Re  = 0;
			Im  = 0;
			Len = 0;
			Pha = 0;
			L   = 0;
			for(p=0; p<other.HeaderN.x; p++){
				mrcPixelDataGet(&ref,   p, refY,   0, &refRe,   mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&ref,   p, refY,   0, &refIm,   mrcPixelImPart, mrcPixelHowNearest);
				mrcPixelDataGet(&other, p, delta, 0, &otherRe, mrcPixelRePart, mrcPixelHowNearest);
				mrcPixelDataGet(&other, p, delta, 0, &otherIm, mrcPixelImPart, mrcPixelHowNearest);
				refLen   = SQRT(  SQR(refRe) +   SQR(refIm));
				otherLen = SQRT(SQR(otherRe) + SQR(otherIm));
				refPha   = atan2(  refIm,   refRe);
				if(refPha < 0)   refPha   += 2*M_PI;
				otherPha = atan2(otherIm, otherRe);
				if(otherPha < 0) otherPha += 2*M_PI;
	
				if(refRe > otherRe) Re += fabs(refRe   - otherRe);
				else                Re += fabs(otherRe - refRe);
			
				if(refIm > otherIm) Im += fabs(refIm   - otherIm);
				else                Im += fabs(otherIm - refIm);

				if(refLen > otherLen) Len += refLen   - otherLen;
				else                  Len += otherLen - refLen;

				if(refPha > otherPha) Pha += MIN_NORMAL_PHASE(refPha   - otherPha);
				else                  Pha += MIN_NORMAL_PHASE(otherPha - refPha);
				
				L += SQRT(refRe - otherRe) + SQRT(refIm - otherIm);
			}
			tmpOtherY = delta - otherCommonPosition;
			if(tmpOtherY < 0) tmpOtherY += other.HeaderN.y;

			mrcPixelDataSet(&linfo->outRe,  i-1, tmpOtherY, 0, Re,  mrcPixelRePart);
			mrcPixelDataSet(&linfo->outIm,  i-1, tmpOtherY, 0, Im,  mrcPixelRePart);
			mrcPixelDataSet(&linfo->outLen, i-1, tmpOtherY, 0, Len, mrcPixelRePart);
			mrcPixelDataSet(&linfo->outPha, i-1, tmpOtherY, 0, Pha, mrcPixelRePart);
			mrcPixelDataSet(&linfo->outL,   i-1, tmpOtherY, 0, L,   mrcPixelRePart);
		}
		ReMin  = 1e20;
		ImMin  = 1e20;
		LenMin = 1e20;
		PhaMin = 1e20;
		LMin   = 1e20;
		for(delta=0; delta<other.HeaderN.y; delta++){
			mrcPixelDataGet(&linfo->outRe,  i-1, delta, 0, &Re,  mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outIm,  i-1, delta, 0, &Im,  mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outLen, i-1, delta, 0, &Len, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outPha, i-1, delta, 0, &Pha, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outL,   i-1, delta, 0, &L,   mrcPixelRePart, mrcPixelHowNearest);
			if(Re  < ReMin){
				ReMin  = Re;  
				ReDeltaMin  = delta;
			}
			if(Im  < ImMin){
				ImMin  = Im;  
				ImDeltaMin  = delta;
			}
			if(Len < LenMin){
				LenMin = Len; 
				LenDeltaMin = delta;
			}
			if(Pha < PhaMin){
				PhaMin = Pha; 
				PhaDeltaMin = delta;
			}
			if(L < LMin){
				LMin = L;
				LDeltaMin = delta;
			}
		}
		for(delta=0; delta<other.HeaderN.y; delta++){
			mrcPixelDataGet(&linfo->outRe,  i-1, delta, 0, &Re,  mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outIm,  i-1, delta, 0, &Im,  mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outLen, i-1, delta, 0, &Len, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outPha, i-1, delta, 0, &Pha, mrcPixelRePart, mrcPixelHowNearest);
			mrcPixelDataGet(&linfo->outL,   i-1, delta, 0, &L,   mrcPixelRePart, mrcPixelHowNearest);
			if(ReMin  != 0) Re  /= ReMin;
			if(ImMin  != 0) Im  /= ImMin;
			if(LenMin != 0) Len /= LenMin;
			if(PhaMin != 0) Pha /= PhaMin;
			if(LMin   != 0) L   /= LMin;
			mrcPixelDataSet(&linfo->outRe,  i-1, delta, 0, Re,  mrcPixelRePart);
			mrcPixelDataSet(&linfo->outIm,  i-1, delta, 0, Im,  mrcPixelRePart);
			mrcPixelDataSet(&linfo->outLen, i-1, delta, 0, Len, mrcPixelRePart);
			mrcPixelDataSet(&linfo->outPha, i-1, delta, 0, Pha, mrcPixelRePart);
			mrcPixelDataSet(&linfo->outL,   i-1, delta, 0, L,   mrcPixelRePart);
			if(delta == 0) {
				ReDeltaMin += otherCommonPosition;
				if(ReDeltaMin > 360) ReDeltaMin -= 360;
				ImDeltaMin += otherCommonPosition;
				if(ImDeltaMin > 360) ImDeltaMin -= 360;
				LenDeltaMin += otherCommonPosition;
				if(LenDeltaMin > 360) LenDeltaMin -= 360;
				PhaDeltaMin += otherCommonPosition;
				if(PhaDeltaMin > 360) PhaDeltaMin -= 360;
				LDeltaMin += otherCommonPosition;
				if(LDeltaMin > 360) LDeltaMin -= 360;
				fprintf(linfo->fptLog, "Re:  min=%f data=%f MinDelta=%d\n", ReMin,  Re , ReDeltaMin );
				fprintf(linfo->fptLog, "Im:  min=%f data=%f MinDelta=%d\n", ImMin,  Im , ImDeltaMin );
				fprintf(linfo->fptLog, "Len: min=%f data=%f MinDelta=%d\n", LenMin, Len, LenDeltaMin);
				fprintf(linfo->fptLog, "Pha: min=%f data=%f MinDelta=%d\n", PhaMin, Pha, PhaDeltaMin);
				fprintf(linfo->fptLog, "L:   min=%f data=%f MinDelta=%d\n", LMin,   L  , LDeltaMin  );
				fprintf(linfo->fptLog, "\n");
			}
		}
		mrcImageFree(&other, "in lCheckCommonLineData");
	}
}
