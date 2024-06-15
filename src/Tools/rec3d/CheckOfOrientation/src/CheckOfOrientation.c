/*
# CheckOfOrientation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : CheckOfOrientation
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
#define WORDLEN 1024
#include "genUtil.h"
#include "Memory.h"
#include "Matrix3D.h"
#include "eosString.h"

typedef struct lCheckOfOrientationInfo {
	int        FileNum;
	int        LineNum;
	char**     ResultFileName;

	char**     FileName;
	char***    RotationalMode;
	float**    RotationalAnglePhi;
	float**    RotationalAngleTheta;
	float**    RotationalAnglePsi;

	Matrix3D** DifferentialMatrix;
} lCheckOfOrientationInfo;

/*
typedef enum lCheckOfOrientationMode {
	a=0,
	b=1
} lCheckOfOrientationMode;
*/

void
__InputFileRead(lCheckOfOrientationInfo* linfo, int mode);

void
lCheckOfOrientation(lCheckOfOrientationInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	CheckOfOrientationInfo  info;
	lCheckOfOrientationInfo linfo;
	int                     i, j;
	double                  value;
	double                  valueSum;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.FileNum = (int)info.flagInList;
	linfo.ResultFileName = MemoryAllocate(char*, linfo.FileNum, "in main");
	for(i=0; i<linfo.FileNum; i++){
		linfo.ResultFileName[i] = MemoryAllocate(char, WORDLEN, "in main");
		strcpy(linfo.ResultFileName[i], info.InList[i]);
	}

	DEBUGPRINT("Program Start\n");

	__InputFileRead(&linfo, 0);
	lCheckOfOrientation(&linfo, 0);

	for(i=0; i<linfo.FileNum; i++){
		fprintf(info.fptOut, "%s :\n", linfo.ResultFileName[i]);
		fprintf(info.fptOutV, "%s :\n", linfo.ResultFileName[i]);
		valueSum = 0;
	for(j=0; j<linfo.LineNum; j++){
		fprintf(info.fptOut, ">>%s\n",linfo.FileName[j]);
		fprintf(info.fptOut, "%6.3f %6.3f %6.3f\n", linfo.DifferentialMatrix[i][j][0][0], 
		                                            linfo.DifferentialMatrix[i][j][0][1], 
													linfo.DifferentialMatrix[i][j][0][2]);
		fprintf(info.fptOut, "%6.3f %6.3f %6.3f\n", linfo.DifferentialMatrix[i][j][1][0], 
		                                            linfo.DifferentialMatrix[i][j][1][1], 
													linfo.DifferentialMatrix[i][j][1][2]);
		fprintf(info.fptOut, "%6.3f %6.3f %6.3f\n", linfo.DifferentialMatrix[i][j][2][0], 
		                                            linfo.DifferentialMatrix[i][j][2][1], 
													linfo.DifferentialMatrix[i][j][2][2]);

		value = ((1-linfo.DifferentialMatrix[i][j][0][0])
			    +(1-linfo.DifferentialMatrix[i][j][1][1])
			    +(1-linfo.DifferentialMatrix[i][j][2][2])
				)/3;
		valueSum += value;
		fprintf(info.fptOutV, "%f\n", value);
	}
		fprintf(info.fptOut, "\n");
		fprintf(info.fptOutV, "Sum: %f  Ave: %f\n\n", valueSum, valueSum/linfo.LineNum);
	}
	fclose(info.fptOut);
	DEBUGPRINT("Program Start\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----------- Output file  -------------\n");
	fprintf(stderr, "-o  : output Matrix data\n");
	fprintf(stderr, "-ov : output Value data\n");
	fprintf(stderr, "\n");
}

void
__InputFileRead(lCheckOfOrientationInfo* linfo, int mode)
{
	int   i, j;
	char* s;
	FILE* fpt;
	
	s = MemoryAllocate(char, WORDLEN, "in __InputFileRead");
	linfo->LineNum = 0;
	if((fpt = fopen(linfo->ResultFileName[0], "r")) == NULL){
		fprintf(stderr, "File Not Open !!\n");
		exit(1);
	}
	fseek(fpt, 0L, SEEK_SET);
	while((stringGetFromFile(s, "", fpt, stdout, 3)) != NULL){
		linfo->LineNum++;
	}
	fseek(fpt, 0L, SEEK_SET);
	linfo->FileName = MemoryAllocate(char*, linfo->LineNum, "in __InputFileRead");
	for(i=0; i<linfo->LineNum; i++){
		linfo->FileName[i] = MemoryAllocate(char, WORDLEN, "in __InputFileRead");
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->FileName[i], stringGetNthWord(s, 1, " ,\t"), WORDLEN-1);
	}
	fclose(fpt);
	
	linfo->RotationalMode         = MemoryAllocate(char**, linfo->FileNum, "in __InputFileRead");
	linfo->RotationalAnglePhi     = MemoryAllocate(float*, linfo->FileNum, "in __InputFileRead");
	linfo->RotationalAngleTheta   = MemoryAllocate(float*, linfo->FileNum, "in __InputFileRead");
	linfo->RotationalAnglePsi     = MemoryAllocate(float*, linfo->FileNum, "in __InputFileRead");
	for(i=0; i<linfo->FileNum; i++){
		linfo->RotationalMode[i]       = MemoryAllocate(char*,  linfo->LineNum, "in __InputFileRead");
		linfo->RotationalAnglePhi[i]   = MemoryAllocate(float, linfo->LineNum, "in __InputFileRead");
		linfo->RotationalAngleTheta[i] = MemoryAllocate(float, linfo->LineNum, "in __InputFileRead");
		linfo->RotationalAnglePsi[i]   = MemoryAllocate(float, linfo->LineNum, "in __InputFileRead");
		for(j=0; j<linfo->LineNum; j++){
			linfo->RotationalMode[i][j] = MemoryAllocate(char, 5, "in __InputFileRead");
		}
	}

	for(i=0; i<linfo->FileNum; i++){
		if((fpt = fopen(linfo->ResultFileName[i], "r")) == NULL){
			fprintf(stderr, "File Not Open !!\n");
			exit(1);
		}
		fseek(fpt, 0L, SEEK_SET);
		for(j=0; j<linfo->LineNum; j++){
			stringGetFromFile(s, "", fpt, stdout, 3);
			stringCopy(linfo->RotationalMode[i][j], stringGetNthWord(s, 2, " ,\t"), 4);
			linfo->RotationalAnglePhi[i][j]   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
			linfo->RotationalAngleTheta[i][j] = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
			linfo->RotationalAnglePsi[i][j]   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
		}
		fclose(fpt);
	}
	free(s);
}

void
lCheckOfOrientation(lCheckOfOrientationInfo* linfo, int mode)
{
	int       i, j;
	Matrix3D* BasedMatrix;
	Matrix3D* RotationalMatrix;

	linfo->DifferentialMatrix = MemoryAllocate(Matrix3D*, linfo->FileNum, "in lCheckOfOrientation");
	for(i=0; i<linfo->FileNum; i++){
		linfo->DifferentialMatrix[i] = MemoryAllocate(Matrix3D, linfo->LineNum, "in lCheckOfOrientation");
	}
	
	BasedMatrix      = MemoryAllocate(Matrix3D, 2, "in lCheckOfOrientation");
	RotationalMatrix = MemoryAllocate(Matrix3D, 2, "in lCheckOfOrientation");
	
	matrix3DRotationAntiSetFollowingEulerAngle(BasedMatrix[0],
											   linfo->RotationalMode[0][0],
											   linfo->RotationalAnglePhi[0][0],
											   linfo->RotationalAngleTheta[0][0],
											   linfo->RotationalAnglePsi[0][0],
											   MATRIX_3D_MODE_INITIALIZE);
	for(i=0; i<linfo->FileNum; i++){
		matrix3DRotationSetFollowingEulerAngle(RotationalMatrix[0],
											   linfo->RotationalMode[i][0],
											   linfo->RotationalAnglePhi[i][0],
											   linfo->RotationalAngleTheta[i][0],
											   linfo->RotationalAnglePsi[i][0],
											   MATRIX_3D_MODE_INITIALIZE);
	for(j=0; j<linfo->LineNum; j++){
		matrix3DRotationSetFollowingEulerAngle(BasedMatrix[1],
											   linfo->RotationalMode[0][j],
											   linfo->RotationalAnglePhi[0][j],
											   linfo->RotationalAngleTheta[0][j],
											   linfo->RotationalAnglePsi[0][j],
											   MATRIX_3D_MODE_INITIALIZE);

		matrix3DRotationAntiSetFollowingEulerAngle(RotationalMatrix[1],
												   linfo->RotationalMode[i][j],
												   linfo->RotationalAnglePhi[i][j],
												   linfo->RotationalAngleTheta[i][j],
												   linfo->RotationalAnglePsi[i][j],
												   MATRIX_3D_MODE_INITIALIZE);

		matrix3DInit(linfo->DifferentialMatrix[i][j]);
		matrix3DMultiplyInv(RotationalMatrix[1], linfo->DifferentialMatrix[i][j]);
		matrix3DMultiplyInv(RotationalMatrix[0], linfo->DifferentialMatrix[i][j]);
		matrix3DMultiplyInv(BasedMatrix[0],      linfo->DifferentialMatrix[i][j]);
		matrix3DMultiplyInv(BasedMatrix[1],      linfo->DifferentialMatrix[i][j]);
	}
	}
	free(BasedMatrix);
	free(RotationalMatrix);
}
