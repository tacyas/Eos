/*
# mrcImageOrientationSearch : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageOrientationSearch
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
#include "Memory.h"
#include "eosString.h"
#include "lCommonLineCalculation.h"

#define WORDLEN 1024

typedef struct SinogramPositionInfo {
	int     PositionNum;
	char*   filename1;
	char*   filename2;
	/* DEGREE */
	double* CommonLinePosition1;
	double* CommonLinePosition2;
	int*    mode;
} SinogramPositionInfo;

typedef struct EulerAngleInfo {
	char*  filename;
	int    flag;
	/* DEGREE */
	double theta;
	double phi;
	double psi;
} EulerAngleInfo;

typedef struct lmrcImageOrientationSearchInfo {
	char** CorrelationFilename;
	int    Correlationfilenum;
	int    filenum;

	SinogramPositionInfo* position;
	EulerAngleInfo**      angle;
	char*                 rotationalMode;
} lmrcImageOrientationSearchInfo;

/*
typedef enum lmrcImageOrientationSearchMode {
	a=0,
	b=1
} lmrcImageOrientationSearchMode;
*/

void
__FileListReadModeSelect(lmrcImageOrientationSearchInfo* linfo, FILE* fpt, int mode);

void
__FileListAndCommonLinePositionRead(lmrcImageOrientationSearchInfo* linfo, FILE* fpt, int mode);

void
__FileListRead(lmrcImageOrientationSearchInfo* linfo, FILE* fpt, int mode);

void
lmrcImageOrientationSearch(lmrcImageOrientationSearchInfo* linfo, int mode);

int
lmrcImageOrientationSearchOut(FILE* fpt, lmrcImageOrientationSearchInfo* linfo, int mode);

void
lEulerAngleCalculationFromThreeCommonLinePosition(lmrcImageOrientationSearchInfo* linfo, int number, int* flag, int mode);

void
lEulerAngleCalculationFromAdditionlCommonLinePosition(lmrcImageOrientationSearchInfo* linfo, int num, int mode);


int
main(int argc, char* argv[]) 
{
	mrcImageOrientationSearchInfo  info;
	lmrcImageOrientationSearchInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	/* file and correlation file number copy in linfo*/
	linfo.Correlationfilenum = info.flagIn1;
	linfo.filenum            = info.flagIn2;
	//linfo.Correlationfilenum = linfo.filenum*(linfo.filenum-1)/2;

	/* input file2 */
	linfo.angle    = MemoryAllocate(EulerAngleInfo*,            2, "in main");
	linfo.angle[0] = MemoryAllocate(EulerAngleInfo, linfo.filenum, "in main");
	linfo.angle[1] = MemoryAllocate(EulerAngleInfo, linfo.filenum, "in main");
	for(i=0; i<linfo.filenum; i++){
		linfo.angle[0][i].filename = MemoryAllocate(char, WORDLEN, "in main");
		linfo.angle[1][i].filename = MemoryAllocate(char, WORDLEN, "in main");
		stringCopy(linfo.angle[0][i].filename, info.In2[i], WORDLEN-1);
		stringCopy(linfo.angle[1][i].filename, info.In2[i], WORDLEN-1);
		linfo.angle[0][i].flag = 1;
		linfo.angle[1][i].flag = 1;
	}
	
	switch(info.mode){
		case 0 :{
			break;
		}
		case 1 :
		case 2 :{
			linfo.CorrelationFilename = MemoryAllocate(char*, linfo.Correlationfilenum, "in main");
			for(i=0; i<linfo.Correlationfilenum; i++){
				linfo.CorrelationFilename[i] = MemoryAllocate(char, WORDLEN, "in main");
				strcpy(linfo.CorrelationFilename[i], info.In1[i]);
			}
			break;
		}	
	}
	
	/* input file1 */
	__FileListReadModeSelect(&linfo, info.fptIn1List, info.mode);
	
	/* determine Euler angle */
	lmrcImageOrientationSearch(&linfo, info.mode);

	/* Output */
	lmrcImageOrientationSearchOut(info.fptOut, &linfo, info.mode);
	DEBUGPRINT("Program End\n");

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "-m : 0 : There is one common line position in input file (using Test)\n");
	fprintf(stderr, "     1 : There is    correlation file name in input file (common line position is determined Max correlation)\n");
	fprintf(stderr, "     2 : There is    correlation file name in input file (common line position is determined Threshold), -T\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- input file 1 format -----\n");
	fprintf(stderr, "-m : 0 : filename1 filename2 commonlineposition1 commonlineposition2 commonlinepositionMode\n");
	fprintf(stderr, "             .         .             .                   .                     .           \n");
	fprintf(stderr, "             .         .             .                   .                     .           \n");
	fprintf(stderr, "             .         .             .                   .                     .           \n");
	fprintf(stderr, "             .         .             .                   .                     .           \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "     1 : correlationfilename filename1 filename2\n");
	fprintf(stderr, "     2 :         .               .         .    \n");
	fprintf(stderr, "                 .               .         .    \n");
	fprintf(stderr, "                 .               .         .    \n");
	fprintf(stderr, "                 .               .         .    \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- input file 2 format -----\n");
	fprintf(stderr, "-m : 0 : filename \n");
	fprintf(stderr, "     1 :    .     \n");
	fprintf(stderr, "     2 :    .     \n");
	fprintf(stderr, "            .     \n");
	fprintf(stderr, "            .     \n");
	fprintf(stderr, "\n");
}

void
__FileListReadModeSelect(lmrcImageOrientationSearchInfo* linfo, FILE* fpt, int mode)
{
	switch(mode){
		case 0 :{
			__FileListAndCommonLinePositionRead(linfo, fpt, 0);
			break;
		}
		case 1 :
		case 2 :{
			__FileListRead(linfo, fpt, 0);
			break;
		}
	}
}

void
__FileListAndCommonLinePositionRead(lmrcImageOrientationSearchInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;
	char* m;

	s = MemoryAllocate(char, WORDLEN, "in __FileListAndCommonLinePositionRead");
	m = MemoryAllocate(char, WORDLEN, "in __FileListAndCommonLinePositionRead");
	
	linfo->position = MemoryAllocate(SinogramPositionInfo, linfo->Correlationfilenum, "in __FileListAndCommonLinePositionRead");

	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->Correlationfilenum; i++){
		linfo->position[i].PositionNum         = 1;
		linfo->position[i].filename1           = MemoryAllocate(char  , WORDLEN, "in __FileListAndCommonLinePositionRead");
		linfo->position[i].filename2           = MemoryAllocate(char  , WORDLEN, "in __FileListAndCommonLinePositionRead");
		linfo->position[i].CommonLinePosition1 = MemoryAllocate(double, 1      , "in __FileListAndCommonLinePositionRead");
		linfo->position[i].CommonLinePosition2 = MemoryAllocate(double, 1      , "in __FileListAndCommonLinePositionRead");
		linfo->position[i].mode                = MemoryAllocate(int   , 1      , "in __FileListAndCommonLinePositionRead");
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->position[i].filename1, stringGetNthWord(s, 2, " \t,"), WORDLEN-1);
		stringCopy(linfo->position[i].filename2, stringGetNthWord(s, 3, " \t,"), WORDLEN-1);
		linfo->position[i].CommonLinePosition1[0] = stringGetNthRealData(s, 4, " \t,");
		linfo->position[i].CommonLinePosition2[0] = stringGetNthRealData(s, 5, " \t,");
		stringCopy(m, stringGetNthWord(s, 6, " \t,"), WORDLEN-1);
		if(strcoll(m, "1") == 0){
			linfo->position[i].mode = 0;
		}
		else if(strcoll(m, "z-rotation") == 0){
			linfo->position[i].mode[0] = 1;
		}
		else{
			linfo->position[i].mode[0] = 2;
			DEBUGPRINT1("Is not supported Common line position mode : in input file line >> %d\n", i);
		}
	}
	free(m);
	free(s);
}

void
__FileListRead(lmrcImageOrientationSearchInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;

	s = MemoryAllocate(char, WORDLEN, "in __FileListRead");
	
	linfo->position = MemoryAllocate(SinogramPositionInfo, linfo->Correlationfilenum, "in __FileListRead");
	
	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->Correlationfilenum; i++){
		linfo->position[i].filename1 = MemoryAllocate(char, WORDLEN, "in __FileListRead");
		linfo->position[i].filename2 = MemoryAllocate(char, WORDLEN, "in __FileListRead");
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->position[i].filename1, stringGetNthWord(s, 2, " \t,"), WORDLEN-1);
		stringCopy(linfo->position[i].filename2, stringGetNthWord(s, 3, " \t,"), WORDLEN-1);
	}
	free(s);
}


int
lmrcImageOrientationSearchOut(FILE* fpt, lmrcImageOrientationSearchInfo* linfo, int mode)
{
	int i, j;
	int flag;

	flag = 1;
	i    = 2;

	switch(mode){
		case 0 :{
			for(i=0; i<2; i++){
			for(j=0; j<linfo->filenum; j++){
				if(linfo->angle[i][j].flag == 0){
					fprintf(fpt, "%s %s %f %f %f\n", linfo->angle[i][j].filename, linfo->rotationalMode, 
                                                linfo->angle[i][j].psi, linfo->angle[i][j].theta, linfo->angle[i][j].phi);
				}
			}
			}
			break;
		}
		case 1 :{
			break;
		}
		case 2 :{
			break;
		}
		default: {
			break;
		}
	}
}

void
lmrcImageOrientationSearch(lmrcImageOrientationSearchInfo* linfo, int mode)
{
	int i, j;
	int flag;
	
	flag = 1;
	i    = 2;
	switch(mode){
		case 0 :{
			while(flag == 1 && i < linfo->filenum){
				lEulerAngleCalculationFromThreeCommonLinePosition(linfo, i, &flag, 0);
				i++;
			}
			DEBUGPRINT("\n");			
			for(i=0; i<2; i++){
			for(j=0; j<linfo->filenum; j++){
				if(linfo->angle[i][j].flag == 0){
					DEBUGPRINT5("filename : %s >>> %s (%f, %f, %f)\n", linfo->angle[i][j].filename, linfo->rotationalMode, 
                                                linfo->angle[i][j].psi, linfo->angle[i][j].theta, linfo->angle[i][j].phi);
				}
			}
			DEBUGPRINT("\n");
			}
			//DEBUGPRINT("program end\n");
			//exit(1);
			for(j=i; j<linfo->Correlationfilenum; j++){
				lEulerAngleCalculationFromAdditionlCommonLinePosition(linfo, j, 0);
			}
			break;
		}
		case 1 :{
			break;
		}
		case 2 :{
			break;
		}
	}
}

void
lEulerAngleCalculationFromThreeCommonLinePosition(lmrcImageOrientationSearchInfo* linfo, int number, int* flag, int mode)
{
	int*   wnum;
	int    i;
	double* angle;
	double* cosine;
	double* sine;
	double* Xrotation1; 
	double  cosineXr1;
	double* Xrotation2; 
	double  cosineXr2;
	double  ratio;
	
	wnum = MemoryAllocate(int , 3, "lEulerAngleCalculationFromThreeCommonLinePosition");
	for(i=0; i<linfo->Correlationfilenum; i++){
		if(strcoll(linfo->angle[0][0].filename, linfo->position[i].filename1) == 0 && 
		   strcoll(linfo->angle[0][1].filename, linfo->position[i].filename2) == 0)
		{
			wnum[0] = i;
		}
		if(strcoll(linfo->angle[0][0].filename, linfo->position[i].filename1) == 0 && 
		   strcoll(linfo->angle[0][number].filename, linfo->position[i].filename2) == 0)
		{
			wnum[1] = i;
		}
		if(strcoll(linfo->angle[0][1].filename, linfo->position[i].filename1) == 0 && 
		   strcoll(linfo->angle[0][number].filename, linfo->position[i].filename2) == 0)
		{
			wnum[2] = i;
		}
	}
	angle = MemoryAllocate(double, 6, "lEulerAngleCalculationFromThreeCommonLinePosition");
	for(i=0 ;i<3; i++){
		angle[i*2]   = linfo->position[wnum[i]].CommonLinePosition1[0]*RADIAN;
		angle[i*2+1] = linfo->position[wnum[i]].CommonLinePosition2[0]*RADIAN;
	}
	cosine = MemoryAllocate(double, 6, "lEulerAngleCalculationFromThreeCommonLinePosition");
	sine   = MemoryAllocate(double, 6, "lEulerAngleCalculationFromThreeCommonLinePosition");
	for(i=0; i<6; i++){
		cosine[i] = cos(angle[i]);
		sine[i]   = sin(angle[i]);
		DEBUGPRINT4("angle[%d] = %f >> cosine = %f sine = %f\n", i, angle[i], cosine[i], sine[i]);	
	}

	cosineXr1 = 0;
	cosineXr2 = 0;

	cosineXr1 = ((cosine[4]*cosine[5]+sine[4]*sine[5])-((cosine[2]*cosine[3]+sine[2]*sine[3])*(cosine[0]*cosine[1]+sine[0]*sine[1])))
	           /((cosine[2]*sine[3]-sine[2]*cosine[3])*(cosine[0]*sine[1]-sine[0]*cosine[1]));
	
	cosineXr2 = (((cosine[2]*sine[3]-sine[2]*cosine[3])*(cosine[0]*cosine[1]+sine[0]*sine[1])*cosineXr1)
	            +((cosine[2]*cosine[3]+sine[2]*sine[3])*(sine[0]*cosine[1]-cosine[0]*sine[1])))
	           /(cosine[4]*sine[5]-sine[4]*cosine[5]);

	DEBUGPRINT2("cosineXr1 = %f cosineXr2 = %f \n", cosineXr1, cosineXr2);

	ratio = (cosine[4]*sine[5]-sine[4]*cosine[5])/(cosine[2]*sine[3]-sine[2]*cosine[3]);

	DEBUGPRINT1("ratio = %f \n", ratio);
	
	Xrotation1 = MemoryAllocate(double, 2, "in lEulerAngleCalculationFromThreeCommonLinePosition");
	Xrotation2 = MemoryAllocate(double, 2, "in lEulerAngleCalculationFromThreeCommonLinePosition");
	if(ratio < -0.0000001 || ratio > 0.0000001){
		Xrotation1[0] = acos(cosineXr1);
		Xrotation1[1] = 2*M_PI-Xrotation1[0];
		Xrotation2[0] = acos(cosineXr2);
		Xrotation2[1] = 2*M_PI-Xrotation2[0];
		if(ratio*sin(Xrotation1[0] < 0)){
			Xrotation2[0] = 2*M_PI-Xrotation2[0];
			Xrotation2[1] = Xrotation2[0];
		}
		DEBUGPRINT2("Xrotation1 = %f Xrotation2 = %f\n",Xrotation1[0], Xrotation2[0]);		
		linfo->rotationalMode = MemoryAllocate(char, 5, "in lEulerAngleCalculationFromThreeCommonLinePosition");
		stringCopy(linfo->rotationalMode, "ZENR", 4); /* Z->X->Z rotation */
		linfo->angle[0][0].theta   = 0;
		linfo->angle[0][0].phi     = 0;
		linfo->angle[0][0].psi     = 0;
		linfo->angle[0][1].theta   = linfo->position[wnum[0]].CommonLinePosition1[0];
		linfo->angle[0][1].phi     = Xrotation1[0]*DEGREE;
		linfo->angle[0][1].psi     = linfo->position[wnum[0]].CommonLinePosition2[0];
		linfo->angle[0][number].theta = linfo->position[wnum[1]].CommonLinePosition1[0];
		linfo->angle[0][number].phi   = Xrotation2[0]*DEGREE;
		linfo->angle[0][number].psi   = linfo->position[wnum[1]].CommonLinePosition2[0];
	
		linfo->angle[1][0].theta   = 0;
		linfo->angle[1][0].phi     = 0;
		linfo->angle[1][0].psi     = 0;
		linfo->angle[1][1].theta   = linfo->position[wnum[0]].CommonLinePosition1[0];
		linfo->angle[1][1].phi     = Xrotation1[1]*DEGREE;
		linfo->angle[1][1].psi     = linfo->position[wnum[0]].CommonLinePosition2[0];
		linfo->angle[1][number].theta = linfo->position[wnum[1]].CommonLinePosition1[0];
		linfo->angle[1][number].phi   = Xrotation2[1]*DEGREE;
		linfo->angle[1][number].psi   = linfo->position[wnum[1]].CommonLinePosition2[0];
		
		/* angle is determined */
		*flag = 0;
		linfo->angle[0][0].flag = 0;
		linfo->angle[0][1].flag = 0;
		linfo->angle[0][number].flag = 0;
		linfo->angle[1][0].flag = 0;
		linfo->angle[1][1].flag = 0;
		linfo->angle[1][number].flag = 0;
	} else {
		DEBUGPRINT3("Can't determine Euler Angle : %s %s %s\n", linfo->angle[0][0].filename, linfo->angle[0][1].filename, 
		                                                       linfo->angle[0][number].filename);
		/* angle is not determined */
		*flag = 1;
		linfo->angle[0][0].flag = 1;
		linfo->angle[0][1].flag = 1;
		linfo->angle[0][number].flag = 1;
		linfo->angle[1][0].flag = 1;
		linfo->angle[1][1].flag = 1;
		linfo->angle[1][number].flag = 1;
	}
	
	free(wnum);
	free(angle);
	free(cosine);
	free(sine);
	free(Xrotation1);
	free(Xrotation2);
}

void
lEulerAngleCalculationFromAdditionlCommonLinePosition(lmrcImageOrientationSearchInfo* linfo, int num, int mode)
{

}
