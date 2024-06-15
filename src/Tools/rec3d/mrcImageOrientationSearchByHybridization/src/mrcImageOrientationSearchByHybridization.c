/*
# mrcImageOrientationSearchByHybridization : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageOrientationSearchByHybridization
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <time.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG
#define WORDLEN 256
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "Matrix3D.h"

typedef struct EulerAngle{
	char* filename;

	float psi;
	float theta;
	float phi;
}EulerAngle;

typedef struct lmrcImageOrientationSearchByHybridizationInfo {
	int IncreaseRate;
	int HybridizationPointNumber;
	int FileNum;
	int LineNum;
	int ChildrenNum;

	EulerAngle** InputAngle;
	EulerAngle** HybridizationAngle;
} lmrcImageOrientationSearchByHybridizationInfo;

/*
typedef enum lmrcImageOrientationSearchByHybridizationMode {
	a=0,
	b=1
} lmrcImageOrientationSearchByHybridizationMode;
*/

void
__InputDataFileListRead(lmrcImageOrientationSearchByHybridizationInfo* linfo, char** FileNameList, int mode);

void
__RotationAngleMatching(lmrcImageOrientationSearchByHybridizationInfo* linfo, int mode);

void
lmrcImageOrientationSearchByHybridization(lmrcImageOrientationSearchByHybridizationInfo* linfo, int mode);

void
__OutputDataWrite(lmrcImageOrientationSearchByHybridizationInfo* linfo, char* OutHeader, char* OutExtension, int mode);

void
__MatchAngleWrite(lmrcImageOrientationSearchByHybridizationInfo* linfo, char* OutHeader, char* OutExtension, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImageOrientationSearchByHybridizationInfo  info;
	lmrcImageOrientationSearchByHybridizationInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.IncreaseRate             = info.ir;
	linfo.HybridizationPointNumber = info.hpn;
	linfo.FileNum                  = info.flagIn;
	linfo.ChildrenNum              = ((linfo.FileNum*(linfo.FileNum-1))/2)*linfo.IncreaseRate + linfo.FileNum;
	linfo.InputAngle         = MemoryAllocate(EulerAngle*, linfo.FileNum,     "in main");
	linfo.HybridizationAngle = MemoryAllocate(EulerAngle*, linfo.ChildrenNum, "in main");

	DEBUGPRINT("Program Start\n");

	switch(info.ms){
		case 0 :
			srand((unsigned)time(NULL));
		break;
		case 1 :
			srand(info.ird);
		break;
	}
	__InputDataFileListRead(&linfo, info.In, 0);
	__RotationAngleMatching(&linfo, 0);
	switch(info.mode){
		case 0 :
			lmrcImageOrientationSearchByHybridization(&linfo, 0);
			__OutputDataWrite(&linfo, info.Out, info.extension, 0);
		break;
		case 1 :
			__MatchAngleWrite(&linfo, info.Out, info.extension, 0);
		break;
	}
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, ">> This algrithm use results of mrcImageOrientationSearchBySimultaneousMinimization\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- IncreaseRate -----\n");
	fprintf(stderr, "-ir : 1 >> Increase number is 45 (filenum = 10)\n");
	fprintf(stderr, "      2 >> Increase number is 90 (filenum = 10)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- HybridizationPointNumber -----\n");
	fprintf(stderr, "-hpn : The number of hybridization points \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode of selection -----\n");
	fprintf(stderr, "-ms : 0 : random\n");
	fprintf(stderr, "      1 : myself (-ird)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "-m : 0 : create children angle file\n");
	fprintf(stderr, "     1 : do not create children angle file , create match angle file\n");
	fprintf(stderr, "\n");
}

void
__InputDataFileListRead(lmrcImageOrientationSearchByHybridizationInfo* linfo, char** FileNameList, int mode)
{
	int   i, j;
	char* s;
	FILE* fpt;

	s = MemoryAllocate(char, WORDLEN, "in __InputDataFileListRead");	
	if((fpt = fopen(FileNameList[0], "r")) == NULL){
		fprintf(stderr, "file not open !!\n");
		exit(1);
	}
	linfo->LineNum = 0;
	while(fgets(s, WORDLEN-1, fpt) != NULL){
		linfo->LineNum++;
	}
	fclose(fpt);

	for(i=0; i<linfo->FileNum; i++){
		linfo->InputAngle[i] = MemoryAllocate(EulerAngle, linfo->LineNum, "in __InputDataFileListRead");
		for(j=0; j<linfo->LineNum; j++){
			linfo->InputAngle[i][j].filename = MemoryAllocate(char, WORDLEN, "in __InputDataFileListRead");
		}
	}
	
	for(j=0; j<linfo->FileNum; j++){
		if((fpt = fopen(FileNameList[j], "r")) == NULL){
			fprintf(stderr, "file not open !!\n");
			exit(1);
		}
		for(i=0; i<linfo->LineNum; i++){
			stringGetFromFile(s, "", fpt, stdout, 3);
			stringCopy(linfo->InputAngle[j][i].filename, stringGetNthWord(s, 1, " ,\t"), WORDLEN-1);
			linfo->InputAngle[j][i].phi   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
			linfo->InputAngle[j][i].theta = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
			linfo->InputAngle[j][i].psi   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
		}
		fclose(fpt);
	}
	free(s);
}

void
lmrcImageOrientationSearchByHybridization(lmrcImageOrientationSearchByHybridizationInfo* linfo, int mode)
{
	int  i, j, k, l;
	int  ChildrenNumber;
	int* HybridizationPoint;
	int  HybridizationFileNum;

	linfo->HybridizationAngle = MemoryAllocate(EulerAngle*, linfo->ChildrenNum, "lmrcImageOrientationSearchByHybridization");	
	for(i=0; i<linfo->ChildrenNum; i++){
		linfo->HybridizationAngle[i] = MemoryAllocate(EulerAngle, linfo->LineNum, "lmrcImageOrientationSearchByHybridization");	
		for(j=0; j<linfo->LineNum; j++){
			linfo->HybridizationAngle[i][j].filename = MemoryAllocate(char, WORDLEN, "lmrcImageOrientationSearchByHybridization");	
		}
	}
	HybridizationPoint = MemoryAllocate(int, linfo->HybridizationPointNumber, "lmrcImageOrientationSearchByHybridization");
	ChildrenNumber = 0;
	for(i=0; i<linfo->FileNum-1; i++){
		for(j=i+1; j<linfo->FileNum; j++){
			for(k=0; k<linfo->IncreaseRate; k++){
				for(l=0; l<linfo->LineNum; l++){
					strcpy(linfo->HybridizationAngle[ChildrenNumber][l].filename, linfo->InputAngle[0][l].filename);
				}
				/* Hybridization */
				if(linfo->HybridizationPointNumber == 1){
					do{
						HybridizationPoint[0] = (int)((double)random()/RAND_MAX*linfo->LineNum);
					}while(HybridizationPoint[0] == 0 || HybridizationPoint[0] == linfo->LineNum-1);
					HybridizationFileNum  = (int)((double)random()/RAND_MAX*2);
					fprintf(stdout, "HybridizationPoint = %d FileNum = %d\n", HybridizationPoint[0], HybridizationFileNum);
					for(l=0; l<HybridizationPoint[0]; l++){
						strcpy(linfo->HybridizationAngle[ChildrenNumber][l].filename, linfo->InputAngle[HybridizationFileNum][l].filename);
						linfo->HybridizationAngle[ChildrenNumber][l].phi   = linfo->InputAngle[HybridizationFileNum][l].phi;
						linfo->HybridizationAngle[ChildrenNumber][l].theta = linfo->InputAngle[HybridizationFileNum][l].theta;
						linfo->HybridizationAngle[ChildrenNumber][l].psi   = linfo->InputAngle[HybridizationFileNum][l].psi;
					}
					HybridizationFileNum = (HybridizationFileNum + 1 )%2;
					for(l=HybridizationPoint[0]; l<linfo->LineNum; l++){
						strcpy(linfo->HybridizationAngle[ChildrenNumber][l].filename, linfo->InputAngle[HybridizationFileNum][l].filename);
						linfo->HybridizationAngle[ChildrenNumber][l].phi   = linfo->InputAngle[HybridizationFileNum][l].phi;
						linfo->HybridizationAngle[ChildrenNumber][l].theta = linfo->InputAngle[HybridizationFileNum][l].theta;
						linfo->HybridizationAngle[ChildrenNumber][l].psi   = linfo->InputAngle[HybridizationFileNum][l].psi;
					}
				}
				else{
					fprintf(stderr, "This mode do not make : HybridizationPointNumber = %d\n", linfo->HybridizationPointNumber);
					exit(1);
					/*
					for(l=0; l<linfo->HybridizationPointNumber; l++){
						HybridizationPoint[l] = (int)((double)random()/RAND_MAX*linfo->LineNum);
					}
					if(linfo->HybridizationPointNumber > 1){
						qsort();
					}
					*/
				}
				ChildrenNumber++;
			}
		}
	}
	for(i=0; i<linfo->FileNum; i++){
		for(l=0; l<linfo->LineNum; l++){
			strcpy(linfo->HybridizationAngle[ChildrenNumber+i][l].filename, linfo->InputAngle[i][l].filename);
			linfo->HybridizationAngle[ChildrenNumber+i][l].phi   = linfo->InputAngle[i][l].phi;
			linfo->HybridizationAngle[ChildrenNumber+i][l].theta = linfo->InputAngle[i][l].theta;
			linfo->HybridizationAngle[ChildrenNumber+i][l].psi   = linfo->InputAngle[i][l].psi;
		}
	}
}

void
__OutputDataWrite(lmrcImageOrientationSearchByHybridizationInfo* linfo, char* OutHeader, char* OutExtension, int mode)
{
	int   i, j;
	char* OutFileName;
	FILE* fpt;

	OutFileName = MemoryAllocate(char, WORDLEN, "in __OutputDataWrite");

	for(i=0; i<linfo->ChildrenNum; i++){
		sprintf(OutFileName, "%s-%d.%s", OutHeader, i, OutExtension);
		if((fpt = fopen(OutFileName, "w")) == NULL){
			fprintf(stderr, "file not open !!\n");
			exit(1);
		}
		for(j=0; j<linfo->LineNum; j++){
			fprintf(fpt, "%s ZONS %5.1f %5.1f %5.1f\n", linfo->HybridizationAngle[i][j].filename,
														linfo->HybridizationAngle[i][j].phi*DEGREE,
														linfo->HybridizationAngle[i][j].theta*DEGREE,
														linfo->HybridizationAngle[i][j].psi*DEGREE);
		}
		fclose(fpt);
	}
	free(OutFileName);
}

void
__MatchAngleWrite(lmrcImageOrientationSearchByHybridizationInfo* linfo, char* OutHeader, char* OutExtension, int mode)
{
	int   i, j;
	char* OutFileName;
	FILE* fpt;

	OutFileName = MemoryAllocate(char, WORDLEN, "in __OutputDataWrite");

	for(i=0; i<linfo->FileNum; i++){
		sprintf(OutFileName, "%s-%d.%s", OutHeader, i, OutExtension);
		if((fpt = fopen(OutFileName, "w")) == NULL){
			fprintf(stderr, "file not open !!\n");
			exit(1);
		}
		for(j=0; j<linfo->LineNum; j++){
			fprintf(fpt, "%s ZONS %5.1f %5.1f %5.1f\n", linfo->InputAngle[i][j].filename,
														linfo->InputAngle[i][j].phi*DEGREE,
														linfo->InputAngle[i][j].theta*DEGREE,
														linfo->InputAngle[i][j].psi*DEGREE);
		}
		fclose(fpt);
	}
	free(OutFileName);
}

void
__RotationAngleMatching(lmrcImageOrientationSearchByHybridizationInfo* linfo, int mode)
{
	int i, j;
	Matrix3D BasedMatrix;
	Matrix3D Matrix;
	matrix3DParaTypeReal x, y, z;

	for(i=0; i<linfo->FileNum ; i++){
		matrix3DRotationAntiSetFollowingEulerAngle(BasedMatrix,
												   "ZONS",
												   linfo->InputAngle[i][0].phi,
												   linfo->InputAngle[i][0].theta,
												   linfo->InputAngle[i][0].psi,
												   MATRIX_3D_MODE_INITIALIZE);
		for(j=0; j<linfo->LineNum; j++){
			matrix3DRotationSetFollowingEulerAngle(Matrix,
												   "ZONS",
												   linfo->InputAngle[i][j].phi,
												   linfo->InputAngle[i][j].theta,
												   linfo->InputAngle[i][j].psi,
												   MATRIX_3D_MODE_INITIALIZE);
			
			matrix3DMultiplyInv(BasedMatrix, Matrix);
			matrix3DEulerAngleGetFromMatrix3D(Matrix, "ZONS", &x,&y, &z, 0); 
			linfo->InputAngle[i][j].phi   = x; 
			linfo->InputAngle[i][j].theta = y;
			linfo->InputAngle[i][j].psi   = z;
		
			matrix3DFileWrite(stderr, Matrix);
			fprintf(stderr, "\n");	
			DEBUGPRINT3("%15.6f %15.6f %15.6f\n", x*DEGREE, y*DEGREE, z*DEGREE);
			DEBUGPRINT3("%15.6f %15.6f %15.6f\n", linfo->InputAngle[i][j].phi*DEGREE, linfo->InputAngle[i][j].theta*DEGREE, linfo->InputAngle[i][j].psi*DEGREE);	
		}
	}
}

