/*
# mrcImagesSinogramCorrelation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImagesSinogramCorrelation
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "Memory.h"
#include "Matrix3D.h"
#include "lmrcImageFileListAndEulerAngleDataRead.h"
#include "lmrcImageSinogram.h"
#include "lCommonLineCalculation.h"

#define WORDLEN 1024

typedef struct lmrcImagesSinogramCorrelationInfo {
	int CreateMode;
	
	int    LengthThresholdMode;
	double LengthThresholdRatio;

	char** OutFileListName;
	int    pairNumber;
	int    imagenumber;
	char*  OutHeader;
	char*  directory;

	char*   extensionOfList;
	char*   extensionOfCor;
	char*   resultDirectory;
	char**  CorDirectory;

	int Nmode;
	int D1mode;
	int D2mode;
	int Lmode;

	float* CommonLineAngleIn;
	float* CommonLineAngleRef;
	char** NormalFilename;
	char** Derivation1DFilename;
	char** Derivation2DFilename;
	char** LengthFilename;
} lmrcImagesSinogramCorrelationInfo;

/*
typedef enum lmrcImagesSinogramCorrelationMode {
	a=0,
	b=1
} lmrcImagesSinogramCorrelationMode;
*/

extern void lmrcImagesSinogramCorrelation(mrcImage* in, char** filename, lmrcImagesSinogramCorrelationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, int mode);
extern void lmrcImagesSinogramCorrelation2(mrcImage* in, char** filename, lmrcImagesSinogramCorrelationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, int mode);
extern void lmrcImageFileListAndCommonLinePositionDataWrite(lmrcImagesSinogramCorrelationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, char** filename, int mode);

int
main(int argc, char* argv[]) 
{
	mrcImagesSinogramCorrelationInfo  info;
	lmrcImagesSinogramCorrelationInfo linfo;
	lCommonLineCalculationInfo CommonLineInfo;
	mrcImage In;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.LengthThresholdMode  = info.LengthThresholdMode;
	linfo.LengthThresholdRatio = info.LengthThresholdRatio;

	linfo.OutHeader = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
	strcpy(linfo.OutHeader, info.OutHeader);

	linfo.extensionOfCor  = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
	strcpy(linfo.extensionOfCor,  info.CorrelationExtension);
	
	linfo.extensionOfList = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
	strcpy(linfo.extensionOfList, info.ListExtension);
	
	linfo.resultDirectory = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
	strcpy(linfo.resultDirectory, info.Rd);

	linfo.Nmode  = info.Nmode;
	linfo.D1mode = info.D1mode;
	linfo.D2mode = info.D2mode;
	linfo.Lmode  = info.Lmode;

	linfo.CreateMode = (int)info.CM;

	linfo.CorDirectory = (char **)memoryAllocate(sizeof(char*)*4, "in main");
	if(linfo.Nmode == 0){
		linfo.CorDirectory[0] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
		strcpy(linfo.CorDirectory[0], info.Nd);
	}
	if(linfo.D1mode == 0){
		linfo.CorDirectory[1] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
		strcpy(linfo.CorDirectory[1], info.D1d);
	}
	if(linfo.D2mode == 0){
		linfo.CorDirectory[2] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
		strcpy(linfo.CorDirectory[2], info.D2d);
	}
	if(linfo.Lmode == 0){
		linfo.CorDirectory[3] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in main");
		strcpy(linfo.CorDirectory[3], info.Ld);
	}

	DEBUGPRINT("Program Start\n");

	if(mkdir(linfo.resultDirectory, 00750) != 0){
		DEBUGPRINT("Can't creat directory\n");
		exit(1);
	}

	lmrcImageFileListAndEulerAngleDataRead(&In, info.In, info.flagIn, info.fptInList, 0);
	switch(linfo.CreateMode){
		case 0 :
			lmrcImagesSinogramCorrelation(&In, info.In, &linfo, &CommonLineInfo, 0);
		break;
		case 1 :/* create only list */
			lmrcImagesSinogramCorrelation2(&In, info.In, &linfo, &CommonLineInfo, 0);
		break;
	}
	lmrcImageFileListAndCommonLinePositionDataWrite(&linfo, &CommonLineInfo, info.In, 0);

	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- create mode -----\n");
	fprintf(stderr, "-CM : 0 : image of correlation and list\n");
	fprintf(stderr, "      1 : list only\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, ">>Nmode  : 0 :     creat normal correlation       (-Nd)\n");
	fprintf(stderr, "           1 : not creat normal correlation\n");
	fprintf(stderr, ">>D1mode : 0 :     creat derivation1D correlation (-D1d)\n");
	fprintf(stderr, "           1 : not creat derivation1D correlation\n");
	fprintf(stderr, ">>D2mode : 0 :     creat derivation2D correlation (-D2d)\n");
	fprintf(stderr, "           1 : not creat derivation2D correlation\n");
	fprintf(stderr, ">>Lmode  : 0 :     creat length correlation       (-Ld, -LTM, -LTR)\n");
	fprintf(stderr, "           1 : not creat length correlation\n");
	fprintf(stderr, "\n----- directory and file -----\n");
	fprintf(stderr, ">>create directory : Rd\n");
	fprintf(stderr, "                   : Rd/Nd (D1d, D2d, Ld)\n");
	fprintf(stderr, "\n>>create list file        : Rd/Nd/oH-Nd.LE\n");
	fprintf(stderr, "                           (Result/Normal/test-Normal.list)\n");
	fprintf(stderr, "\n>>create correlation file : Rd/Nd/infile1_infile2.Nd.CE\n");
	fprintf(stderr, "                           (Result/Normal/test1_test2.Normal.cor)\n");
}

void
lmrcImagesSinogramCorrelation(mrcImage* in , char** filename, lmrcImagesSinogramCorrelationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, int mode)
{
	int   					   i, j; 
	int      				   ImageNumber;
	int                        pair;
	lmrcImageSinogramInfo      SinogramInfo;
	mrcImage 				   sino1;
	mrcImage 				   sino2;
	mrcImage                   NormalCorrelationImage;
	mrcImage                   sino1Derivation1D;
	mrcImage                   sino1Derivation2D;
	mrcImage                   sino2Derivation1D;
	mrcImage                   sino2Derivation2D;
	mrcImage                   Derivation1DCorrelationImage;
	mrcImage                   Derivation2DCorrelationImage;
	mrcImage                   LengthCorrelationImage;
	char**                     directoryName;
	char*                      workNormal;
	char*                      workDerivation1D;
	char*                      workDerivation2D;
	char*                      workLength;
	char**                     filenameWithoutExtension;
	char*                      extensionPosition;

	ImageNumber = in->numTailer;
	linfo->imagenumber = ImageNumber;
	linfo->pairNumber  = ImageNumber*(ImageNumber-1)/2;
	CommonLineInfo->num = linfo->pairNumber;

	CommonLineInfo->I1RotationalMode = MemoryAllocate(char*, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2RotationalMode = MemoryAllocate(char*, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	for(i=0; i<CommonLineInfo->num; i++){
		CommonLineInfo->I1RotationalMode[i] = (char *)memoryAllocate(sizeof(char)*5, "in lmrcImageSinogramCorrelation");
		CommonLineInfo->I2RotationalMode[i] = (char *)memoryAllocate(sizeof(char)*5, "in lmrcImageSinogramCorrelation");
	}
	CommonLineInfo->I1Angle1 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I1Angle2 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I1Angle3 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2Angle1 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2Angle2 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2Angle3 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->CLAngleOnI1AgainstI2  = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->CLAngleOnI2AgainstI1  = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->flag     = MemoryAllocate(int  , CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");

	SinogramInfo.LengthCorrelationMode = 0;
	SinogramInfo.LengthThresholdMode   = linfo->LengthThresholdMode;
	SinogramInfo.LengthThresholdRatio  = linfo->LengthThresholdRatio;
	SinogramInfo.dphi                  = in->HeaderLength.y*RADIAN;
	SinogramInfo.correlationMode       = 0;

	filenameWithoutExtension = (char **)memoryAllocate(sizeof(char*)*ImageNumber, "in lmrcImagesSinogramCorrelation");
	for(i=0; i<ImageNumber; i++){
		filenameWithoutExtension[i] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		strcpy(filenameWithoutExtension[i], filename[i]);
	
		extensionPosition = strrchr(filenameWithoutExtension[i], '.');
		strcpy(extensionPosition, "\0");
	}

	directoryName = (char **)memoryAllocate(sizeof(char*)*4, "in lmrcImagesSinogramCorrelation");
	if(linfo->Nmode == 0){
		workNormal = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->NormalFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
		directoryName[0] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[0], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[0]);
	
		if(mkdir(directoryName[0],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[0]);
			exit(1);
		}
	}
	if(linfo->D1mode == 0){
		workDerivation1D = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->Derivation1DFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCprrelation");
		directoryName[1] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[1], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[1]);
	
		if(mkdir(directoryName[1],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[1]);
			exit(1);
		}
	}
	if(linfo->D2mode == 0){ 
		workDerivation2D = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->Derivation2DFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
		directoryName[2] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[2], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[2]);
	
		if(mkdir(directoryName[2],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[2]);
			exit(1);
		}
	}
	if(linfo->Lmode == 0){
		workLength = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->LengthFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
		directoryName[3] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[3], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[3]);
	
		if(mkdir(directoryName[3],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[3]);
			exit(1);
		}
	}
	
	linfo->CommonLineAngleIn    = (float *)memoryAllocate(sizeof(float)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
	linfo->CommonLineAngleRef   = (float *)memoryAllocate(sizeof(float)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
	pair = 0;
	for(i=0; i<ImageNumber-1; i++){
		mrcImageSectionGet(&sino1, in, i, 1);
	for(j=i+1; j<ImageNumber; j++){
		mrcImageSectionGet(&sino2, in, j, 1);

		CommonLineInfo->I1Angle1[pair] = in->Tailer[i].Cont.Rot1;
		CommonLineInfo->I1Angle2[pair] = in->Tailer[i].Cont.Rot2;
		CommonLineInfo->I1Angle3[pair] = in->Tailer[i].Cont.Rot3;
		CommonLineInfo->I2Angle1[pair] = in->Tailer[j].Cont.Rot1;
		CommonLineInfo->I2Angle2[pair] = in->Tailer[j].Cont.Rot2;
		CommonLineInfo->I2Angle3[pair] = in->Tailer[j].Cont.Rot3;
		CommonLineInfo->flag[pair] = 0;
		strcpy(CommonLineInfo->I1RotationalMode[pair], in->Tailer[i].Cont.EulerAngleMode);
		strcpy(CommonLineInfo->I2RotationalMode[pair], in->Tailer[j].Cont.EulerAngleMode);

		lCommonLineCalculation1(CommonLineInfo, pair, 0);
		
		if(linfo->Nmode == 0){
			lmrcImageSinogramCorrelation0(&NormalCorrelationImage, &sino1, &sino2, &SinogramInfo, 0);
			
			linfo->NormalFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->NormalFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                    linfo->CorDirectory[0], linfo->extensionOfCor);
			sprintf(workNormal, "%s/%s", directoryName[0], linfo->NormalFilename[pair]);
			mrcFileWrite(&NormalCorrelationImage, workNormal, "Write NormalCorrelation", 0);
			mrcImageFree(&NormalCorrelationImage, 0);
		}
		if(linfo->D1mode == 0){
			lmrcImageDerivationCalculation(&sino1Derivation1D, &sino1, 1);
			lmrcImageDerivationCalculation(&sino2Derivation1D, &sino2, 1);
			lmrcImageSinogramCorrelation0(&Derivation1DCorrelationImage, &sino1Derivation1D, &sino2Derivation1D, &SinogramInfo, 0);
			
			linfo->Derivation1DFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->Derivation1DFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                          linfo->CorDirectory[1], linfo->extensionOfCor);
			sprintf(workDerivation1D, "%s/%s", directoryName[1], linfo->Derivation1DFilename[pair]);
			mrcFileWrite(&Derivation1DCorrelationImage, workDerivation1D, "Write Derivation1DCorrelation", 0);
			mrcImageFree(&sino1Derivation1D, 0);
			mrcImageFree(&sino2Derivation1D, 0);
			mrcImageFree(&Derivation1DCorrelationImage, 0);
		}
		if(linfo->D2mode == 0){
			lmrcImageDerivationCalculation(&sino1Derivation2D, &sino1, 2);
			lmrcImageDerivationCalculation(&sino2Derivation2D, &sino2, 2);
			lmrcImageSinogramCorrelation0(&Derivation2DCorrelationImage, &sino1Derivation2D, &sino2Derivation2D, &SinogramInfo, 0);
			
			linfo->Derivation2DFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->Derivation2DFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                          linfo->CorDirectory[2], linfo->extensionOfCor);
			sprintf(workDerivation2D, "%s/%s", directoryName[2], linfo->Derivation2DFilename[pair]);
			mrcFileWrite(&Derivation2DCorrelationImage, workDerivation2D, "Write Derivation2DCorrelation", 0);
			mrcImageFree(&sino1Derivation2D, 0);
			mrcImageFree(&sino2Derivation2D, 0);
			mrcImageFree(&Derivation2DCorrelationImage, 0);
		}
		if(linfo->Lmode == 0){
			lmrcImageSinogramLengthCorrelation(&LengthCorrelationImage, &sino1, &sino2, &SinogramInfo, 0);
			
			linfo->LengthFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->LengthFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                    linfo->CorDirectory[3], linfo->extensionOfCor);
			sprintf(workLength, "%s/%s", directoryName[3], linfo->LengthFilename[pair]);
			mrcFileWrite(&LengthCorrelationImage, workLength, "Write LengthCorrelation", 0);
			mrcImageFree(&LengthCorrelationImage, 0);
		}
		pair++;
	}
	}

	if(linfo->Nmode == 0){
		free(workNormal);
		free(directoryName[0]);
	}
	if(linfo->D1mode == 0){
		free(workDerivation1D);
		free(directoryName[1]);
	}
	if(linfo->D2mode == 0){
		free(workDerivation2D);
		free(directoryName[2]);
	}
	if(linfo->Lmode == 0){
		free(workLength);
		free(directoryName[3]);
	}
	free(directoryName);

	for(i=0; i<ImageNumber; i++){
		free(filenameWithoutExtension[i]);
	}
	free(filenameWithoutExtension);

	mrcImageFree(in, 0);
}

void
lmrcImagesSinogramCorrelation2(mrcImage* in , char** filename, lmrcImagesSinogramCorrelationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, int mode)
{
	int   					   i, j; 
	int      				   ImageNumber;
	int                        pair;
	lmrcImageSinogramInfo      SinogramInfo;
	mrcImage 				   sino1;
	mrcImage 				   sino2;
	char**                     directoryName;
	char*                      workNormal;
	char*                      workDerivation1D;
	char*                      workDerivation2D;
	char*                      workLength;
	char**                     filenameWithoutExtension;
	char*                      extensionPosition;

	ImageNumber = in->numTailer;
	linfo->imagenumber = ImageNumber;
	linfo->pairNumber  = ImageNumber*(ImageNumber-1)/2;
	CommonLineInfo->num = linfo->pairNumber;

	CommonLineInfo->I1RotationalMode = MemoryAllocate(char*, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2RotationalMode = MemoryAllocate(char*, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	for(i=0; i<CommonLineInfo->num; i++){
		CommonLineInfo->I1RotationalMode[i] = (char *)memoryAllocate(sizeof(char)*5, "in lmrcImageSinogramCorrelation");
		CommonLineInfo->I2RotationalMode[i] = (char *)memoryAllocate(sizeof(char)*5, "in lmrcImageSinogramCorrelation");
	}
	CommonLineInfo->I1Angle1 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I1Angle2 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I1Angle3 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2Angle1 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2Angle2 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->I2Angle3 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->CLAngleOnI1AgainstI2 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->CLAngleOnI2AgainstI1 = MemoryAllocate(float, CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");
	CommonLineInfo->flag     = MemoryAllocate(int  , CommonLineInfo->num, "in lmrcImagesSinogramCorrelation");

	SinogramInfo.LengthCorrelationMode = 0;
	SinogramInfo.LengthThresholdMode   = linfo->LengthThresholdMode;
	SinogramInfo.LengthThresholdRatio  = linfo->LengthThresholdRatio;
	SinogramInfo.dphi                  = in->HeaderLength.y*RADIAN;
	SinogramInfo.correlationMode       = 0;

	filenameWithoutExtension = (char **)memoryAllocate(sizeof(char*)*ImageNumber, "in lmrcImagesSinogramCorrelation");
	for(i=0; i<ImageNumber; i++){
		filenameWithoutExtension[i] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		strcpy(filenameWithoutExtension[i], filename[i]);
	
		extensionPosition = strrchr(filenameWithoutExtension[i], '.');
		strcpy(extensionPosition, "\0");
	}

	directoryName = (char **)memoryAllocate(sizeof(char*)*4, "in lmrcImagesSinogramCorrelation");
	if(linfo->Nmode == 0){
		workNormal = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->NormalFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
		directoryName[0] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[0], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[0]);
	
		if(mkdir(directoryName[0],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[0]);
			exit(1);
		}
	}
	if(linfo->D1mode == 0){
		workDerivation1D = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->Derivation1DFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCprrelation");
		directoryName[1] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[1], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[1]);
	
		if(mkdir(directoryName[1],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[1]);
			exit(1);
		}
	}
	if(linfo->D2mode == 0){ 
		workDerivation2D = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->Derivation2DFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
		directoryName[2] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[2], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[2]);
	
		if(mkdir(directoryName[2],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[2]);
			exit(1);
		}
	}
	if(linfo->Lmode == 0){
		workLength = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		linfo->LengthFilename = (char **)memoryAllocate(sizeof(char*)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
		directoryName[3] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
		sprintf(directoryName[3], "%s/%s", linfo->resultDirectory, linfo->CorDirectory[3]);
	
		if(mkdir(directoryName[3],00750) != 0){
			DEBUGPRINT1("Can't creat %s\n", directoryName[3]);
			exit(1);
		}
	}
	
	linfo->CommonLineAngleIn    = (float *)memoryAllocate(sizeof(float)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
	linfo->CommonLineAngleRef   = (float *)memoryAllocate(sizeof(float)*linfo->pairNumber, "in lmrcImagesSinogramCorrelation");
	pair = 0;
	for(i=0; i<ImageNumber-1; i++){
		mrcImageSectionGet(&sino1, in, i, 1);
	for(j=i+1; j<ImageNumber; j++){
		mrcImageSectionGet(&sino2, in, j, 1);

		CommonLineInfo->I1Angle1[pair] = in->Tailer[i].Cont.Rot1;
		CommonLineInfo->I1Angle2[pair] = in->Tailer[i].Cont.Rot2;
		CommonLineInfo->I1Angle3[pair] = in->Tailer[i].Cont.Rot3;
		CommonLineInfo->I2Angle1[pair] = in->Tailer[j].Cont.Rot1;
		CommonLineInfo->I2Angle2[pair] = in->Tailer[j].Cont.Rot2;
		CommonLineInfo->I2Angle3[pair] = in->Tailer[j].Cont.Rot3;
		CommonLineInfo->flag[pair] = 0;
		strcpy(CommonLineInfo->I1RotationalMode[pair], in->Tailer[i].Cont.EulerAngleMode);
		strcpy(CommonLineInfo->I2RotationalMode[pair], in->Tailer[j].Cont.EulerAngleMode);

		lCommonLineCalculation1(CommonLineInfo, pair, 0);
		
		if(linfo->Nmode == 0){
			linfo->NormalFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->NormalFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                    linfo->CorDirectory[0], linfo->extensionOfCor);
			sprintf(workNormal, "%s/%s", directoryName[0], linfo->NormalFilename[pair]);
		}
		if(linfo->D1mode == 0){
			linfo->Derivation1DFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->Derivation1DFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                          linfo->CorDirectory[1], linfo->extensionOfCor);
			sprintf(workDerivation1D, "%s/%s", directoryName[1], linfo->Derivation1DFilename[pair]);
		}
		if(linfo->D2mode == 0){
			linfo->Derivation2DFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->Derivation2DFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                          linfo->CorDirectory[2], linfo->extensionOfCor);
			sprintf(workDerivation2D, "%s/%s", directoryName[2], linfo->Derivation2DFilename[pair]);
		}
		if(linfo->Lmode == 0){
			linfo->LengthFilename[pair] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImagesSinogramCorrelation");
			sprintf(linfo->LengthFilename[pair], "%s_%s.%s.%s", filenameWithoutExtension[i], filenameWithoutExtension[j], 
			                                                    linfo->CorDirectory[3], linfo->extensionOfCor);
			sprintf(workLength, "%s/%s", directoryName[3], linfo->LengthFilename[pair]);
		}
		pair++;
	}
	}

	if(linfo->Nmode == 0){
		free(workNormal);
		free(directoryName[0]);
	}
	if(linfo->D1mode == 0){
		free(workDerivation1D);
		free(directoryName[1]);
	}
	if(linfo->D2mode == 0){
		free(workDerivation2D);
		free(directoryName[2]);
	}
	if(linfo->Lmode == 0){
		free(workLength);
		free(directoryName[3]);
	}
	free(directoryName);

	for(i=0; i<ImageNumber; i++){
		free(filenameWithoutExtension[i]);
	}
	free(filenameWithoutExtension);

	mrcImageFree(in, 0);
}

void
lmrcImageFileListAndCommonLinePositionDataWrite(lmrcImagesSinogramCorrelationInfo* linfo, lCommonLineCalculationInfo* CommonLineInfo, char** filename, int mode)
{
	int i, j, pair;
	FILE* fptNormal;
	FILE* fptDerivation1D;
	FILE* fptDerivation2D;
	FILE* fptLength;

	linfo->OutFileListName = (char **)memoryAllocate(sizeof(char*)*4, "in lmrcImageFileListAndCommonLinePositionDataWrite");

	if(linfo->Nmode == 0){
		linfo->OutFileListName[0] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImageFileListAndCommonLinePositionDataWrite");
		sprintf(linfo->OutFileListName[0], "%s/%s/%s-%s.%s", linfo->resultDirectory, linfo->CorDirectory[0], 
		                                                     linfo->OutHeader, linfo->CorDirectory[0], linfo->extensionOfList);
		fptNormal       = fopen(linfo->OutFileListName[0],"w");
		pair = 0;
		for(i=0; i<linfo->imagenumber-1; i++){
		for(j=i+1; j<linfo->imagenumber; j++){
			if(CommonLineInfo->flag[pair] == 0){
				fprintf(fptNormal, "%s %s %s %f %f 1\n", linfo->NormalFilename[pair], filename[i], filename[j], 
			    	                                   CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);
			}
			else{
				fprintf(fptNormal, "%s %s %s %f %f z-rotation\n", linfo->NormalFilename[pair], filename[i], filename[j], 
			    	                                   CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);

			}
			pair++;
		}
		}
		fclose(fptNormal);
	}
	if(linfo->D1mode == 0){
		linfo->OutFileListName[1] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImageFileListAndCommonLinePositionDataWrite");
		sprintf(linfo->OutFileListName[1], "%s/%s/%s-%s.%s", linfo->resultDirectory, linfo->CorDirectory[1], 
		                                                     linfo->OutHeader, linfo->CorDirectory[1], linfo->extensionOfList);
		fptDerivation1D = fopen(linfo->OutFileListName[1],"w");
		pair = 0;
		for(i=0; i<linfo->imagenumber-1; i++){
		for(j=i+1; j<linfo->imagenumber; j++){
			if(CommonLineInfo->flag[pair] == 0){
				fprintf(fptDerivation1D, "%s %s %s %f %f 1\n", linfo->Derivation1DFilename[pair], filename[i], filename[j], 
			    	                                         CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);
			}
			else{
				fprintf(fptDerivation1D, "%s %s %s %f %f z-rotation\n", linfo->Derivation1DFilename[pair], filename[i], filename[j], 
			    	                                         CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);

			}
			pair++;
		}
		}
		fclose(fptDerivation1D);
	}
	if(linfo->D2mode == 0){
		linfo->OutFileListName[2] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImageFileListAndCommonLinePositionDataWrite");
		sprintf(linfo->OutFileListName[2], "%s/%s/%s-%s.%s", linfo->resultDirectory, linfo->CorDirectory[2], 
		                                                     linfo->OutHeader, linfo->CorDirectory[2], linfo->extensionOfList);
		fptDerivation2D = fopen(linfo->OutFileListName[2],"w");
		pair = 0;
		for(i=0; i<linfo->imagenumber-1; i++){
		for(j=i+1; j<linfo->imagenumber; j++){
			if(CommonLineInfo->flag[pair] == 0){
				fprintf(fptDerivation2D, "%s %s %s %f %f 1\n", linfo->Derivation2DFilename[pair], filename[i], filename[j], 
			 	                                            CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);
			}
			else{
				fprintf(fptDerivation2D, "%s %s %s %f %f z-rotation\n", linfo->Derivation2DFilename[pair], filename[i], filename[j], 
			    	                                         CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);

			}
			pair++;
		}
		}
		fclose(fptDerivation2D);
	}
	if(linfo->Lmode == 0){
		linfo->OutFileListName[3] = (char *)memoryAllocate(sizeof(char)*WORDLEN, "in lmrcImageFileListAndCommonLinePositionDataWrite");
		sprintf(linfo->OutFileListName[3], "%s/%s/%s-%s.%s", linfo->resultDirectory, linfo->CorDirectory[3], 
		                                                     linfo->OutHeader, linfo->CorDirectory[3], linfo->extensionOfList);
		fptLength       = fopen(linfo->OutFileListName[3],"w");
		pair = 0;
		for(i=0; i<linfo->imagenumber-1; i++){
		for(j=i+1; j<linfo->imagenumber; j++){
			if(CommonLineInfo->flag[pair] == 0){
				fprintf(fptLength, "%s %s %s %f %f 1\n", linfo->LengthFilename[pair], filename[i], filename[j], 
			        	                               CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);
			}
			else{
				fprintf(fptLength, "%s %s %s %f %f z-rotation\n", linfo->LengthFilename[pair], filename[i], filename[j], 
			            	                           CommonLineInfo->CLAngleOnI1AgainstI2[pair], CommonLineInfo->CLAngleOnI2AgainstI1[pair]);

			}
			pair++;
		}
		}
		fclose(fptLength);
	}
}
