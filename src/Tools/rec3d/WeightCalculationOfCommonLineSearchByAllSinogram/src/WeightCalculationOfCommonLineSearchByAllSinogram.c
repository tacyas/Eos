/*
# WeightCalculationOfCommonLineSearchByAllSinogram : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : WeightCalculationOfCommonLineSearchByAllSinogram
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
#include "Memory.h"
#include "mrcImage.h"
#include "eosString.h"

#define WORDLEN 1024

typedef struct lFileListAndCommonLinePositionInfo{
	double* CommonLinePositionIn;
	double* CommonLinePositionRef;

	int filenum;

	char** CorrelationFile;
	char** OriginalFileIn;
	char** OriginalFileRef;

	int* mode;
}lFileListAndCommonLinePositionDataInfo;

typedef struct lWeightCalculationOfCommonLineSearchByAllSinogramInfo {
	int Mode;
	int listnum;
	double variance;
	char** FileListName;

	double* weight;

	lFileListAndCommonLinePositionDataInfo* InFileData;
} lWeightCalculationOfCommonLineSearchByAllSinogramInfo;

typedef enum  lWeightCalculationOfCommonLineSearchByAllSinogramModeMask {
	WithN  = 0x01,
	WithD1 = 0x02,
	WithD2 = 0x04,
	WithL  = 0x08
}  lWeightCalculationOfCommonLineSearchByAllSinogramModeMask;

typedef enum lWeightCalculationOfCommonLineSearchByAllSinogramMode {
	WithND1    = WithN|WithD1, 
	WithND2    = WithN|       WithD2, 
	WithD1D2   =       WithD1|WithD2, 
	WithND1D2  = WithN|WithD1|WithD2, 
	WithNL     = WithN|              WithL, 
	WithD1L    =       WithD1|       WithL, 
	WithND1L   = WithN|WithD1|       WithL, 
	WithD2L    =              WithD2|WithL, 
	WithND2L   = WithN|       WithD2|WithL, 
	WithD1D2L  =       WithD1|WithD2|WithL, 
	WithND1D2L = WithN|WithD1|WithD2|WithL 
} lWeightCalculationOfCommonLineSearchByAllSinogramMode;

void
lmrcImageReadFileListCounter(lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode);

void
lmrcImageFileListDataGet(mrcImage** in, lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode);

void
lmrcImageFileListAndCommonLinePositionDataRead(mrcImage* in, char* ListFile, lFileListAndCommonLinePositionDataInfo* llinfo, int mode);

void
lWeightCalculationOfCommonLineSearchByAllSinogram0(mrcImage** in, lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode);

void
lWeightCalculationOfCommonLineSearchByAllSinogram1(lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	WeightCalculationOfCommonLineSearchByAllSinogramInfo info;
	lWeightCalculationOfCommonLineSearchByAllSinogramInfo linfo;
	int i, j;
	mrcImage** In;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.Mode = info.Mode;
	linfo.variance = info.variance;

	DEBUGPRINT("Program Start\n");

	lmrcImageReadFileListCounter(&linfo, linfo.Mode);
	
	linfo.FileListName = MemoryAllocate(char*,linfo.listnum,"in main");
	for(i=0; i<linfo.listnum; i++){
		linfo.FileListName[i] = MemoryAllocate(char,WORDLEN,"in main");
	}
	
	linfo.InFileData = MemoryAllocate(lFileListAndCommonLinePositionDataInfo,linfo.listnum,"in main");
	
	switch(info.mode){
		case 0 :{
			In = MemoryAllocate(mrcImage*,linfo.listnum,"in main");
			break;
		}
		case 1 :{
			break;
		}
	}
	
	i = 0;
	switch(info.Mode & WithN){
		case 0 :{
			break;
		}
		case WithN :{
			linfo.InFileData[i].filenum = info.flagIn1;
			strcpy(linfo.FileListName[i], info.In1List);
			
			switch(info.mode){
				case 0 :{
					In[i] = MemoryAllocate(mrcImage, linfo.InFileData[i].filenum, "in main");
					break;
				}
				case 1 :{
					break;
				}
			}
			
			linfo.InFileData[i].CorrelationFile = MemoryAllocate(char*, linfo.InFileData[i].filenum, "in main");
			for(j=0; j<linfo.InFileData[i].filenum; j++){
				linfo.InFileData[i].CorrelationFile[j] = MemoryAllocate(char, WORDLEN, "in main");
				strcpy(linfo.InFileData[i].CorrelationFile[j], info.In1[j]);
			}
			i++;
			break;
		}
	}
	switch(info.Mode & WithD1){
		case 0 :{
			break;
		}
		case WithD1 :{
			linfo.InFileData[i].filenum = info.flagIn2;
			strcpy(linfo.FileListName[i], info.In2List);
			
			switch(info.mode){
				case 0 :{
					In[i] = MemoryAllocate(mrcImage, linfo.InFileData[i].filenum, "in main");
					break;
				}
				case 1 :{
					break;
				}
			}
			
			linfo.InFileData[i].CorrelationFile = MemoryAllocate(char*, linfo.InFileData[i].filenum, "in main");
			for(j=0; j<linfo.InFileData[i].filenum; j++){
				linfo.InFileData[i].CorrelationFile[j] = MemoryAllocate(char, WORDLEN, "in main");
				strcpy(linfo.InFileData[i].CorrelationFile[j], info.In2[j]);
			}
			i++;
			break;
		}
	}
	switch(info.Mode & WithD2){
		case 0 :{
			break;
		}
		case WithD2 :{
			linfo.InFileData[i].filenum = info.flagIn3;
			strcpy(linfo.FileListName[i], info.In3List);
			
			switch(info.mode){
				case 0 :{
					In[i] = MemoryAllocate(mrcImage, linfo.InFileData[i].filenum, "in main");
					break;
				}
				case 1 :{
					break;
				}
			}
			
			linfo.InFileData[i].CorrelationFile = MemoryAllocate(char*, linfo.InFileData[i].filenum, "in main");
			for(j=0; j<linfo.InFileData[i].filenum; j++){
				linfo.InFileData[i].CorrelationFile[j] = MemoryAllocate(char, WORDLEN, "in main");
				strncpy(linfo.InFileData[i].CorrelationFile[j], info.In3[j], WORDLEN-2);
			}
			i++;
			break;
		}
	}
	switch(info.Mode & WithL){
		case 0 :{
			break;
		}
		case WithL :{
			linfo.InFileData[i].filenum = info.flagIn4;
			strcpy(linfo.FileListName[i], info.In4List);
			
			switch(info.mode){
				case 0 :{
					In[i] = MemoryAllocate(mrcImage, linfo.InFileData[i].filenum, "in main");
					break;
				}
				case 1 :{
					break;
				}
			}
			
			linfo.InFileData[i].CorrelationFile = MemoryAllocate(char*, linfo.InFileData[i].filenum, "in main");
			for(j=0; j<linfo.InFileData[i].filenum; j++){
				linfo.InFileData[i].CorrelationFile[j] = MemoryAllocate(char, WORDLEN, "in main");
				strcpy(linfo.InFileData[i].CorrelationFile[j], info.In4[j]);
			}
			i++;
			break;
		}
	}
	
	lmrcImageFileListDataGet(In, &linfo, info.mode);

	switch(info.mode){
		case 0 :{
			DEBUGPRINT("weight calculation start\n");
			lWeightCalculationOfCommonLineSearchByAllSinogram0(In, &linfo, 0);
			break;
		}
		case 1 :{
			DEBUGPRINT("weight calculation start\n");
			lWeightCalculationOfCommonLineSearchByAllSinogram1(&linfo, 0);
			break;
		}
	}
	for(i=0; i<linfo.listnum; i++){
		fprintf(info.fptOut, "Weight of I%d is %f\n", i+1, linfo.weight[i]);
	}

	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- Mode -----\n");
	fprintf(stderr, "-M : 1 : ued to Normal Correlation\n");
	fprintf(stderr, "     2 : ued to Derivation1D Correlation\n");
	fprintf(stderr, "     4 : ued to Derivation2D Correlation\n");
	fprintf(stderr, "     8 : ued to Length Correlation\n");
	fprintf(stderr, "    15 : ued to All Correlation\n");
	fprintf(stderr, "     (* inupt sum)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "-m : 0 :       get memory of mrcImage \n");
	fprintf(stderr, "     1 : don't get memory of mrcImage \n");
	fprintf(stderr, "\n");
}

void
lmrcImageReadFileListCounter(lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode)
{
	int count = 0;

	switch(mode & WithN){
		case 0 :{
			break;
		}
		case WithN :{
			count++;
			break;
		}
	}
	switch(mode & WithD1){
		case 0 :{
			break;
		}
		case WithD1 :{
			count++;
			break;
		}
	}
	switch(mode & WithD2){
		case 0 :{
			break;
		}
		case WithD2 :{
			count++;
			break;
		}
	}
	switch(mode & WithL){
		case 0 :{
			break;
		}
		case WithL :{
			count++;
			break;
		}
	}
	linfo->listnum = count;	
}

void
lmrcImageFileListDataGet(mrcImage** in, lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode)
{
	int      i = 0;
	mrcImage work;

	switch(linfo->Mode & WithN){
		case 0 :{
			break;
		}
		case WithN :{
			switch(mode){
				case 0 :{
					lmrcImageFileListAndCommonLinePositionDataRead(in[i], linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;		
				}
				case 1 :{
					lmrcImageFileListAndCommonLinePositionDataRead(&work, linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;
				}
			}	
			i++;
			break;
		}
	}
	switch(linfo->Mode & WithD1){
		case 0 :{
			break;
		}
		case WithD1 :{
			switch(mode){
				case 0 :{
					lmrcImageFileListAndCommonLinePositionDataRead(in[i], linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;		
				}
				case 1 :{
					lmrcImageFileListAndCommonLinePositionDataRead(&work, linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;
				}
			}	
			i++;
			break;
		}
	}
	switch(linfo->Mode & WithD2){
		case 0 :{
			break;
		}
		case WithD2 :{
			switch(mode){	
				case 0 :{
					lmrcImageFileListAndCommonLinePositionDataRead(in[i], linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;		
				}
				case 1 :{
					lmrcImageFileListAndCommonLinePositionDataRead(&work, linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;
				}
			}	
			i++;
			break;
		}
	}
	switch(linfo->Mode & WithL){
		case 0 :{
			break;
		}
		case WithL :{
			switch(mode){
				case 0 :{
					lmrcImageFileListAndCommonLinePositionDataRead(in[i], linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;		
				}
				case 1 :{
					lmrcImageFileListAndCommonLinePositionDataRead(&work, linfo->FileListName[i], &(linfo->InFileData[i]), mode); 
					break;
				}
			}	
			i++;
			break;
		}
	}
}


void
lmrcImageFileListAndCommonLinePositionDataRead(mrcImage* in, char* ListFile, lFileListAndCommonLinePositionDataInfo* llinfo, int mode)
{
	int i;
	FILE* fpt;
	char s[WORDLEN];
	char workname[WORDLEN];
	char pathway[WORDLEN];
	char *workposition;
	char workMode[WORDLEN];
	
	switch(mode){
		case 0 :{
			strcpy(workname, ListFile);
			workposition = strrchr(workname, '/');
			if(workposition == NULL){
				DEBUGPRINT("Can't find '/' from FileListName\n");
				exit(1);
			}
			*workposition = '\0';
			for(i=0; i<llinfo->filenum; i++){
				sprintf(pathway, "%s/%s", workname, llinfo->CorrelationFile[i]);
				mrcFileRead(&(in[i]), pathway, "in lmrcImageFileListAndCommonLinePositionDataRead", 0);
			}
			break;
		}
		case 1 :{
			break;
		}
	}

	fpt = fopen(ListFile, "r");

	llinfo->OriginalFileIn  = MemoryAllocate(char*, llinfo->filenum, "in lmrcImageFileListAndCommonLinePositionDataRead");
	llinfo->OriginalFileRef = MemoryAllocate(char*, llinfo->filenum, "in lmrcImageFileListAndCommonLinePositionDataRead");
	llinfo->CommonLinePositionIn  = MemoryAllocate(double, llinfo->filenum, "in lmrcImageFileListAndCommonLinePositionDataRead");
	llinfo->CommonLinePositionRef = MemoryAllocate(double, llinfo->filenum, "in lmrcImageFileListAndCommonLinePositionDataRead");
	llinfo->mode = MemoryAllocate(int, llinfo->filenum, "in lmrcImageFileListAndCommonLinePositionDataRead");

	for(i=0; i<llinfo->filenum; i++){
		llinfo->OriginalFileIn[i]  = MemoryAllocate(char, WORDLEN, "in lmrcImageFileListAndCommonLinePositionDataRead");
		llinfo->OriginalFileRef[i] = MemoryAllocate(char, WORDLEN, "in lmrcImageFileListAndCommonLinePositionDataRead");
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(llinfo->OriginalFileIn[i],  stringGetNthWord(s, 2, " ,\t"), WORDLEN-1);
		stringCopy(llinfo->OriginalFileRef[i], stringGetNthWord(s, 3, " ,\t"), WORDLEN-1);
		llinfo->CommonLinePositionIn[i]  = stringGetNthRealData(s, 4, " ,\t");
		if(llinfo->CommonLinePositionIn[i] < 0){
			llinfo->CommonLinePositionIn[i] += 360;
		}
		llinfo->CommonLinePositionRef[i] = stringGetNthRealData(s, 5, " ,\t");
		if(llinfo->CommonLinePositionRef[i] < 0){
			llinfo->CommonLinePositionRef[i] += 360;
		}
		stringCopy(workMode, stringGetNthWord(s, 6, " ,\t"), WORDLEN-1);
		if(workMode == "z-rotation"){
			llinfo->mode[i] = 1;
		}
		else if(workMode == "1"){
			llinfo->mode[i] = 0;
		}
		else{
			llinfo->mode[i] = -1;
		}
	}
	DEBUGPRINT("Input data get end : CommonLinePositionData\n");

	fclose(fpt);
}

void
lWeightCalculationOfCommonLineSearchByAllSinogram0(mrcImage** in, lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode)
{
	int     i, j;
	int     x, y;
	double  degreeX, degreeY;
	double* weightMax;
	double* weightMin;
	double* weightMinOfFinalCorrelation;
	double* weight;
	double  deltaweight;
	double  FinalCorrelationMin;
	double  FinalCorrelation;
	double  sinoWeight;
	double  sinoWeightSum;
	double* sinoWeightCorrelation;
	double* sinoWeightCorrelationSum;
	double* sinoWeightCorrelationAve;
	double* pixelData;
	double* power;
	double  workpowerFinal;
	double  powerFinal;
	double  weightSum;
	double  powerX;
	double  powerY;
	double  powerV;
	double  powerXYV;
	

	FinalCorrelationMin = 10;
	deltaweight         = pow(2, 0.5);

	linfo->weight = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");

	switch(linfo->Mode){
		case WithND1  :
		case WithND2  :
		case WithNL   :
		case WithD1D2 :
		case WithD1L  :
		case WithD2L  :
			weightMax                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weightMin                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weight                      = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weightMinOfFinalCorrelation = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelationSum    = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelationAve    = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelation       = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			pixelData                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			power                       = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");

			for(i=0; i<linfo->listnum; i++){
				weightMax[i] = 4.0;
				weightMin[i] = pow(2, 0.5);
			}

			while(deltaweight > 1.0){
				for(weight[0] = weightMin[0]; weight[0] <= weightMax[0]; weight[0] += deltaweight){
				for(weight[1] = weightMin[1]; weight[1] <= weightMax[1]; weight[1] += deltaweight){
					FinalCorrelation = 0;
					for(i = 0; i < linfo->InFileData[0].filenum; i++){
						sinoWeightSum = 0;
						for(j = 0; j < linfo->listnum; j++){
							sinoWeightCorrelationSum[j] = 0;
						}
						for(x = 0; x < in[0][0].HeaderN.x; x++){
						for(y = 0; y < in[0][0].HeaderN.y; y++){
							degreeX = (double)x*in[0][0].HeaderLength.x;
							degreeY = (double)y*in[0][0].HeaderLength.y;
							powerX = pow(degreeX-linfo->InFileData[0].CommonLinePositionIn[i],  2);
							powerY = pow(degreeY-linfo->InFileData[0].CommonLinePositionRef[i], 2);
							powerV = pow(linfo->variance, 2);
							sinoWeight = exp(-(powerX+powerY)/2*powerV);
							sinoWeightSum += sinoWeight;
							for(j = 0; j < linfo->listnum; j++){
								mrcPixelDataGet(&(in[j][i]), x, y, 0, &pixelData[j], mrcPixelRePart, mrcPixelHowNearest);
								sinoWeightCorrelation[j] = sinoWeight*pixelData[j];
								sinoWeightCorrelationSum[j] += sinoWeightCorrelation[j];
							}
						}
						}
						workpowerFinal = 1;
						weightSum      = 0;
						for(j = 0; j < linfo->listnum; j++){
							sinoWeightCorrelationAve[j] = sinoWeightCorrelationSum[j]/sinoWeightSum;
							power[j] = pow(1-sinoWeightCorrelationAve[j], weight[j]);
							workpowerFinal *= power[j];
							weightSum      += weight[j];
						}
						powerFinal = pow(workpowerFinal, 1/weightSum);
						FinalCorrelation += powerFinal;
					}
					if(FinalCorrelation < FinalCorrelationMin){
						FinalCorrelationMin = FinalCorrelation;
						for(j = 0; j < linfo->listnum; j++){
							weightMinOfFinalCorrelation[j] = weight[j];
						}
					}
				}
				}
				deltaweight = pow(deltaweight, 0.5);
				for(j = 0; j < linfo->listnum; j++){
					weightMin[j] = weightMinOfFinalCorrelation[j]/pow(deltaweight, 2);
					weightMax[j] = weightMinOfFinalCorrelation[j]*pow(deltaweight, 2);
				}
			}
		break;

		case WithND1D2 :
		case WithND1L  :
		case WithND2L  :
		case WithD1D2L :
			weightMax                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weightMin                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weight                      = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weightMinOfFinalCorrelation = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelationSum    = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelationAve    = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelation       = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			pixelData                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			power                       = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");

			for(i=0; i<linfo->listnum; i++){
				weightMax[i] = 8.0;
				weightMin[i] = pow(2, 0.5);
			}

			while(deltaweight > 1.0){
				for(weight[0] = weightMin[0]; weight[0] <= weightMax[0]; weight[0] += deltaweight){
				for(weight[1] = weightMin[1]; weight[1] <= weightMax[1]; weight[1] += deltaweight){
				for(weight[2] = weightMin[2]; weight[2] <= weightMax[2]; weight[2] += deltaweight){
					FinalCorrelation = 0;
					for(i = 0; i < linfo->InFileData[0].filenum; i++){
						sinoWeightSum = 0;
						for(j = 0; j < linfo->listnum; j++){
							sinoWeightCorrelationSum[j] = 0;
						}
						for(x = 0; x < in[0][0].HeaderN.x; x++){
						for(y = 0; y < in[0][0].HeaderN.y; y++){
							degreeX = (double)x*in[0][0].HeaderLength.x;
							degreeY = (double)y*in[0][0].HeaderLength.y;
							powerX = pow(degreeX-linfo->InFileData[0].CommonLinePositionIn[i],  2);
							powerY = pow(degreeY-linfo->InFileData[0].CommonLinePositionRef[i], 2);
							powerV = pow(linfo->variance, 2);
							sinoWeight = exp(-(powerX+powerY)/2*powerV);
							sinoWeightSum += sinoWeight;
							for(j = 0; j < linfo->listnum; j++){
								mrcPixelDataGet(&(in[j][i]), x, y, 0, &pixelData[j], mrcPixelRePart, mrcPixelHowNearest);
								sinoWeightCorrelation[j] = sinoWeight*pixelData[j];
								sinoWeightCorrelationSum[j] += sinoWeightCorrelation[j];
							}
						}
						}
						workpowerFinal = 1;
						weightSum      = 0;
						for(j = 0; j < linfo->listnum; j++){
							sinoWeightCorrelationAve[j] = sinoWeightCorrelationSum[j]/sinoWeightSum;
							power[j] = pow(1-sinoWeightCorrelationAve[j], weight[j]);
							workpowerFinal *= power[j];
							weightSum      += weight[j];
						}
						powerFinal = pow(workpowerFinal, 1/weightSum);
						FinalCorrelation += powerFinal;
					}
					if(FinalCorrelation < FinalCorrelationMin){
						FinalCorrelationMin = FinalCorrelation;
						for(j = 0; j < linfo->listnum; j++){
							weightMinOfFinalCorrelation[j] = weight[j];
						}
					}
				}
				}
				}
				deltaweight = pow(deltaweight, 0.5);
				for(j = 0; j < linfo->listnum; j++){
					weightMin[j] = weightMinOfFinalCorrelation[j]/pow(deltaweight, 2);
					weightMax[j] = weightMinOfFinalCorrelation[j]*pow(deltaweight, 2);
				}
			}
		break;

		case WithND1D2L :
			weightMax                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weightMin                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weight                      = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			weightMinOfFinalCorrelation = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelationSum    = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelationAve    = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			sinoWeightCorrelation       = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			pixelData                   = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
			power                       = MemoryAllocate(double, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram");

			for(i=0; i<linfo->listnum; i++){
				weightMax[i] = 8.0;
				weightMin[i] = pow(2, 0.5);
			}

			while(deltaweight > 1.0){
				for(weight[0] = weightMin[0]; weight[0] <= weightMax[0]; weight[0] += deltaweight){
				for(weight[1] = weightMin[1]; weight[1] <= weightMax[1]; weight[1] += deltaweight){
				for(weight[2] = weightMin[2]; weight[2] <= weightMax[2]; weight[2] += deltaweight){
				for(weight[3] = weightMin[3]; weight[3] <= weightMax[3]; weight[3] += deltaweight){
					FinalCorrelation = 0;
					for(i = 0; i < linfo->InFileData[0].filenum; i++){
						sinoWeightSum = 0;
						for(j = 0; j < linfo->listnum; j++){
							sinoWeightCorrelationSum[j] = 0;
						}
						for(x = 0; x < in[0][0].HeaderN.x; x++){
						for(y = 0; y < in[0][0].HeaderN.y; y++){
							degreeX = (double)x*in[0][0].HeaderLength.x;
							degreeY = (double)y*in[0][0].HeaderLength.y;
							powerX = pow(degreeX-linfo->InFileData[0].CommonLinePositionIn[i],  2);
							powerY = pow(degreeY-linfo->InFileData[0].CommonLinePositionRef[i], 2);
							powerV = pow(linfo->variance, 2);
							powerXYV = -(powerX+powerY)/(2*powerV);
							sinoWeight = exp(powerXYV);
							sinoWeightSum += sinoWeight;
							for(j = 0; j < linfo->listnum; j++){
								mrcPixelDataGet(&(in[j][i]), x, y, 0, &pixelData[j], mrcPixelRePart, mrcPixelHowNearest);
								sinoWeightCorrelation[j] = sinoWeight*pixelData[j];
								sinoWeightCorrelationSum[j] += sinoWeightCorrelation[j];
							}
						}
						}
						workpowerFinal = 1;
						weightSum      = 0;
						for(j = 0; j < linfo->listnum; j++){
							sinoWeightCorrelationAve[j] = sinoWeightCorrelationSum[j]/sinoWeightSum;
							power[j] = pow(1-sinoWeightCorrelationAve[j], weight[j]);
							workpowerFinal *= power[j];
							weightSum      += weight[j];
						}
						powerFinal = pow(workpowerFinal, 1/weightSum);
						FinalCorrelation += powerFinal;
					}
					if(FinalCorrelation < FinalCorrelationMin){
						FinalCorrelationMin = FinalCorrelation;
						for(j = 0; j < linfo->listnum; j++){
							weightMinOfFinalCorrelation[j] = weight[j];
						}
					}
				}
				}
				}
				}

				DEBUGPRINT("\n");
				DEBUGPRINT1("deltaweight = %f\n", deltaweight);
				DEBUGPRINT1("FinalCorrelationMin = %f \n", FinalCorrelationMin);
				for(j=0; j<linfo->listnum; j++){
					DEBUGPRINT4("weight[%d][%f, %f] >>>> weightMinOfCorrelation = %f\n", j, weightMin[j], weightMax[j], weightMinOfFinalCorrelation[j]);
				}
				
				deltaweight = pow(deltaweight, 0.5);
				for(j = 0; j < linfo->listnum; j++){
					weightMin[j] = weightMinOfFinalCorrelation[j]/pow(deltaweight, 2);
					weightMax[j] = weightMinOfFinalCorrelation[j]*pow(deltaweight, 2);
				}
			}
		break;
	}

	for(i = 0; i < linfo->listnum; i++){
		linfo->weight[i] = weightMinOfFinalCorrelation[i];
	}
}

void
lWeightCalculationOfCommonLineSearchByAllSinogram1(lWeightCalculationOfCommonLineSearchByAllSinogramInfo* linfo, int mode)
{
	mrcImage* correlation;

    int     i, j;
    int     x, y;
    double  degreeX, degreeY;
    double* weightMax;
    double* weightMin;
    double* weightMinOfFinalCorrelation;
    double* weight;
    double  deltaweight;
    double  FinalCorrelationMin;
    double* FinalCorrelation;
    double  sinoWeight;
    double  sinoWeightSum;
    double* sinoWeightCorrelation;
    double* sinoWeightCorrelationSum;
    double* sinoWeightCorrelationAve;
    double  pixelData;
    double* power;
    double  workpowerFinal;
    double  powerFinal;
    double  weightSum;
    double  powerX;
    double  powerY;
    double  powerV;
    double  powerXYV;
	char    path[WORDLEN];
	char**  directory;
	char*   workPosition;
	int     counter;

	correlation                 = MemoryAllocate(mrcImage, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
	linfo->weight               = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    weightMax                   = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    weightMin                   = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    weight                      = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    weightMinOfFinalCorrelation = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    sinoWeightCorrelationSum    = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    sinoWeightCorrelationAve    = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    sinoWeightCorrelation       = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
    power                       = MemoryAllocate(double,   linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
	
	directory    = MemoryAllocate(char*, linfo->listnum, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
	for(i=0; i<linfo->listnum; i++){
		directory[i] = MemoryAllocate(char, WORDLEN, "in lWeightCalculationOfCommonLineSearchByAllSinogram1");
		strncpy(directory[i], linfo->FileListName[i], WORDLEN-2);
		workPosition  = strrchr(directory[i], '/');
		if(workPosition == NULL){
			DEBUGPRINT("Can't find '/' from FileListName\n");
			exit(1);
		}
		*workPosition = '\0';
	}	

	for(i=0; i<linfo->listnum; i++){
		weightMin[i] = pow(2, 0.5);
		weightMax[i] = 8;
	}
	deltaweight = pow(2, 0.5);
	
	FinalCorrelationMin = 100000;

	switch(linfo->Mode){
		case WithND1  :
		case WithND2  :
		case WithNL   :
		case WithD1D2 :
		case WithD1L  :
		case WithD2L  :

			while(deltaweight > 1.0){
				counter = ((int)((weightMax[0] - weightMin[0]) /deltaweight)+1)
						* ((int)((weightMax[1] - weightMin[1]) /deltaweight)+1);
				
				FinalCorrelation = MemoryAllocate(double, counter, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
				
				for(i=0; i<linfo->InFileData[0].filenum; i++){
					for(j=0; j<linfo->listnum; j++){
						sprintf(path, "%s/%s", directory[j], linfo->InFileData[j].CorrelationFile[i]);
						mrcFileRead(&(correlation[j]), path, "in lWeightCalculationOfCommonLineSearchByAllSinogram", 0);
					}
					
					for(j=0; j<linfo->listnum; j++){
						sinoWeightCorrelationSum[j] = 0;
					}
			
					sinoWeightSum = 0;
					for(x=0; x<correlation[0].HeaderN.x; x++){
					for(y=0; y<correlation[0].HeaderN.y; y++){
						degreeX        = (double)x*correlation[0].HeaderLength.x;
						degreeY        = (double)y*correlation[0].HeaderLength.y;
						powerX         = pow(degreeX-linfo->InFileData[0].CommonLinePositionIn[i], 2);
						powerY         = pow(degreeY-linfo->InFileData[0].CommonLinePositionRef[i], 2);
						powerV         = pow(linfo->variance, 2);
						powerXYV       = -(powerX+powerY)/(2*powerV);
						sinoWeight     = exp(powerXYV); 
						sinoWeightSum += sinoWeight;

						for(j=0; j<linfo->listnum; j++){
							mrcPixelDataGet(&(correlation[j]), x, y, 0, &pixelData, mrcPixelRePart, mrcPixelHowNearest);
							sinoWeightCorrelationSum[j] += sinoWeight*pixelData;
						}
					}
					}
					
					for(j=0; j<linfo->listnum; j++){
						sinoWeightCorrelationAve[j] = sinoWeightCorrelationSum[j]/sinoWeightSum;
					}
					
					counter = 0;
					for(weight[0]=weightMin[0]; weight[0]<=weightMax[0]; weight[0] += deltaweight){
					for(weight[1]=weightMin[1]; weight[1]<=weightMax[1]; weight[1] += deltaweight){
						workpowerFinal = 1;
						weightSum      = 0;
						for(j=0; j<linfo->listnum; j++){
							power[j]        = pow(1-sinoWeightCorrelationAve[j], weight[j]);
							workpowerFinal *= power[j];
							weightSum      += weight[j];
						}
						powerFinal = pow(workpowerFinal, 1/weightSum);
						FinalCorrelation[counter] += powerFinal;
						counter++;
					}
					}
					for(j=0; j<linfo->listnum; j++){
						mrcImageFree(&(correlation[j]), 0);
					}
				}
				counter = 0;
				for(weight[0]=weightMin[0]; weight[0]<=weightMax[0]; weight[0] += deltaweight){
				for(weight[1]=weightMin[1]; weight[1]<=weightMax[1]; weight[1] += deltaweight){
					if(FinalCorrelation[counter] < FinalCorrelationMin){
						FinalCorrelationMin = FinalCorrelation[counter];
						for(j=0; j<linfo->listnum; j++){
							weightMinOfFinalCorrelation[j] = weight[j];
						}
					}
					counter++;
				}
				}
			
                DEBUGPRINT("\n");
                DEBUGPRINT1("deltaweight = %f\n", deltaweight);
                DEBUGPRINT1("FinalCorrelationMin = %f \n", FinalCorrelationMin);
                for(j=0; j<linfo->listnum; j++){
                    DEBUGPRINT4("weight[%d][%f, %f] >>>> weightMinOfCorrelation = %f\n", j, weightMin[j], weightMax[j], weightMinOfFinalCorrelation[j]);
                }
			
				deltaweight = pow(deltaweight, 0.5);
				for(j=0; j<linfo->listnum; j++){
					weightMin[j] = weightMinOfFinalCorrelation[j]/pow(deltaweight, 2);
					weightMax[j] = weightMinOfFinalCorrelation[j]*pow(deltaweight, 2);
				}
				
				free(FinalCorrelation);
			}
		break;

		case WithND1D2 :
		case WithND1L  :
		case WithND2L  :
		case WithD1D2L :
			while(deltaweight > 1.0){
				counter = ((int)((weightMax[0] - weightMin[0]) /deltaweight)+1)
						* ((int)((weightMax[1] - weightMin[1]) /deltaweight)+1)
						* ((int)((weightMax[2] - weightMin[2]) /deltaweight)+1);
				
				FinalCorrelation = MemoryAllocate(double, counter, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
				
				for(i=0; i<linfo->InFileData[0].filenum; i++){
					for(j=0; j<linfo->listnum; j++){
						sprintf(path, "%s/%s", directory[j], linfo->InFileData[j].CorrelationFile[i]);
						mrcFileRead(&(correlation[j]), path, "in lWeightCalculationOfCommonLineSearchByAllSinogram", 0);
					}
					
					for(j=0; j<linfo->listnum; j++){
						sinoWeightCorrelationSum[j] = 0;
					}
			
					sinoWeightSum = 0;
					for(x=0; x<correlation[0].HeaderN.x; x++){
					for(y=0; y<correlation[0].HeaderN.y; y++){
						degreeX        = (double)x*correlation[0].HeaderLength.x;
						degreeY        = (double)y*correlation[0].HeaderLength.y;
						powerX         = pow(degreeX-linfo->InFileData[0].CommonLinePositionIn[i], 2);
						powerY         = pow(degreeY-linfo->InFileData[0].CommonLinePositionRef[i], 2);
						powerV         = pow(linfo->variance, 2);
						powerXYV       = -(powerX+powerY)/(2*powerV);
						sinoWeight     = exp(powerXYV); 
						sinoWeightSum += sinoWeight;

						for(j=0; j<linfo->listnum; j++){
							mrcPixelDataGet(&(correlation[j]), x, y, 0, &pixelData, mrcPixelRePart, mrcPixelHowNearest);
							sinoWeightCorrelationSum[j] += sinoWeight*pixelData;
						}
					}
					}
					
					for(j=0; j<linfo->listnum; j++){
						sinoWeightCorrelationAve[j] = sinoWeightCorrelationSum[j]/sinoWeightSum;
					}
					
					counter = 0;
					for(weight[0]=weightMin[0]; weight[0]<=weightMax[0]; weight[0] += deltaweight){
					for(weight[1]=weightMin[1]; weight[1]<=weightMax[1]; weight[1] += deltaweight){
					for(weight[2]=weightMin[2]; weight[2]<=weightMax[2]; weight[2] += deltaweight){
						workpowerFinal = 1;
						weightSum      = 0;
						for(j=0; j<linfo->listnum; j++){
							power[j]        = pow(1-sinoWeightCorrelationAve[j], weight[j]);
							workpowerFinal *= power[j];
							weightSum      += weight[j];
						}
						powerFinal = pow(workpowerFinal, 1/weightSum);
						FinalCorrelation[counter] += powerFinal;
						counter++;
					}
					}
					}
					for(j=0; j<linfo->listnum; j++){
						mrcImageFree(&(correlation[j]), 0);
					}
				}
				counter = 0;
				for(weight[0]=weightMin[0]; weight[0]<=weightMax[0]; weight[0] += deltaweight){
				for(weight[1]=weightMin[1]; weight[1]<=weightMax[1]; weight[1] += deltaweight){
				for(weight[2]=weightMin[2]; weight[2]<=weightMax[2]; weight[2] += deltaweight){
					if(FinalCorrelation[counter] < FinalCorrelationMin){
						FinalCorrelationMin = FinalCorrelation[counter];
						for(j=0; j<linfo->listnum; j++){
							weightMinOfFinalCorrelation[j] = weight[j];
						}
					}
					counter++;
				}
				}
				}
			
                DEBUGPRINT("\n");
                DEBUGPRINT1("deltaweight = %f\n", deltaweight);
                DEBUGPRINT1("FinalCorrelationMin = %f \n", FinalCorrelationMin);
                for(j=0; j<linfo->listnum; j++){
                    DEBUGPRINT4("weight[%d][%f, %f] >>>> weightMinOfCorrelation = %f\n", j, weightMin[j], weightMax[j], weightMinOfFinalCorrelation[j]);
                }
			
				deltaweight = pow(deltaweight, 0.5);
				for(j=0; j<linfo->listnum; j++){
					weightMin[j] = weightMinOfFinalCorrelation[j]/pow(deltaweight, 2);
					weightMax[j] = weightMinOfFinalCorrelation[j]*pow(deltaweight, 2);
				}
				
				free(FinalCorrelation);
			}
		break;

		case WithND1D2L :
			while(deltaweight > 1.001){
				counter = ((int)((weightMax[0] - weightMin[0]) /deltaweight)+1)
						* ((int)((weightMax[1] - weightMin[1]) /deltaweight)+1)
						* ((int)((weightMax[2] - weightMin[2]) /deltaweight)+1)
						* ((int)((weightMax[3] - weightMin[3]) /deltaweight)+1);
				
				FinalCorrelation = MemoryAllocate(double, counter, "in lWeightCalculationOfCommonLineSearchByAllSinogram");
				
				for(i=0; i<linfo->InFileData[0].filenum; i++){
//DEBUGPRINT2("deltaweight = %f >>>>>>>>>>>>>> filenum = %d\n", deltaweight, i);					
					for(j=0; j<linfo->listnum; j++){
						sprintf(path, "%s/%s", directory[j], linfo->InFileData[j].CorrelationFile[i]);
						mrcFileRead(&(correlation[j]), path, "in lWeightCalculationOfCommonLineSearchByAllSinogram", 0);
					}
					
					for(j=0; j<linfo->listnum; j++){
						sinoWeightCorrelationSum[j] = 0;
					}
			
					sinoWeightSum = 0;
					for(x=0; x<correlation[0].HeaderN.x; x++){
					for(y=0; y<correlation[0].HeaderN.y; y++){
						degreeX        = (double)x*correlation[0].HeaderLength.x;
						degreeY        = (double)y*correlation[0].HeaderLength.y;
						powerX         = pow(degreeX-linfo->InFileData[0].CommonLinePositionIn[i], 2);
						powerY         = pow(degreeY-linfo->InFileData[0].CommonLinePositionRef[i], 2);
						powerV         = pow(linfo->variance, 2);
						powerXYV       = -(powerX+powerY)/(2*powerV);
						sinoWeight     = exp(powerXYV); 
						sinoWeightSum += sinoWeight;

						for(j=0; j<linfo->listnum; j++){
							mrcPixelDataGet(&(correlation[j]), x, y, 0, &pixelData, mrcPixelRePart, mrcPixelHowNearest);
							sinoWeightCorrelationSum[j] += sinoWeight*pixelData;
						}
					}
					}
					
					for(j=0; j<linfo->listnum; j++){
						sinoWeightCorrelationAve[j] = sinoWeightCorrelationSum[j]/sinoWeightSum;
					}
					
					counter = 0;
					for(weight[0]=weightMin[0]; weight[0]<=weightMax[0]; weight[0] += deltaweight){
					for(weight[1]=weightMin[1]; weight[1]<=weightMax[1]; weight[1] += deltaweight){
					for(weight[2]=weightMin[2]; weight[2]<=weightMax[2]; weight[2] += deltaweight){
					for(weight[3]=weightMin[3]; weight[3]<=weightMax[3]; weight[3] += deltaweight){
						workpowerFinal = 1;
						weightSum      = 0;
						for(j=0; j<linfo->listnum; j++){
							power[j]        = pow(1-sinoWeightCorrelationAve[j], weight[j]);
							workpowerFinal *= power[j];
							weightSum      += weight[j];
						}
						powerFinal = pow(workpowerFinal, 1/weightSum);
						FinalCorrelation[counter] += powerFinal;
						counter++;
					}
					}
					}
					}
					for(j=0; j<linfo->listnum; j++){
						mrcImageFree(&(correlation[j]), 0);
					}
				}
				counter = 0;
				for(weight[0]=weightMin[0]; weight[0]<=weightMax[0]; weight[0] += deltaweight){
				for(weight[1]=weightMin[1]; weight[1]<=weightMax[1]; weight[1] += deltaweight){
				for(weight[2]=weightMin[2]; weight[2]<=weightMax[2]; weight[2] += deltaweight){
				for(weight[3]=weightMin[3]; weight[3]<=weightMax[3]; weight[3] += deltaweight){
					if(FinalCorrelation[counter] < FinalCorrelationMin){
						FinalCorrelationMin = FinalCorrelation[counter];
						for(j=0; j<linfo->listnum; j++){
							weightMinOfFinalCorrelation[j] = weight[j];
						}
					}
					counter++;
				}
				}
				}
				}
			
                DEBUGPRINT("\n");
                DEBUGPRINT1("deltaweight = %f\n", deltaweight);
                DEBUGPRINT1("FinalCorrelationMin = %f \n", FinalCorrelationMin);
                for(j=0; j<linfo->listnum; j++){
                    DEBUGPRINT4("weight[%d][%f, %f] >>>> weightMinOfCorrelation = %f\n", j, weightMin[j], weightMax[j], weightMinOfFinalCorrelation[j]);
                }
			
				deltaweight = pow(deltaweight, 0.5);
				for(j=0; j<linfo->listnum; j++){
					weightMin[j] = weightMinOfFinalCorrelation[j]/pow(deltaweight, 2);
					weightMax[j] = weightMinOfFinalCorrelation[j]*pow(deltaweight, 2);
				}
				
				free(FinalCorrelation);
			}
		break;
	}

	for(i=0; i<linfo->listnum; i++){
		linfo->weight[i] = weightMinOfFinalCorrelation[i];
	}
}
