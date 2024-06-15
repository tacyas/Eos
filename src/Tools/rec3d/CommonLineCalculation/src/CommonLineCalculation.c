/*
# CommonLineCalculation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : CommonLineCalculation
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
#include "Matrix3D.h"
#include "Memory.h"
#include "eosString.h"
#include "lCommonLineCalculation.h"

#define WORDLEN 1024

/*
typedef enum lCommonLineCalculationMode {
	a=0,
	b=1
} lCommonLineCalculationMode;
*/

//void lCommonLineCalculation0(lCommonLineCalculationInfo* linfo, int i, int mode);

void
__ModeSelection(lCommonLineCalculationInfo* linfo, int mode);

void
__DataRead(lCommonLineCalculationInfo* linfo, FILE* fpt, int mode);

void
__DataListRead(lCommonLineCalculationInfo* linfo, FILE* fpt, int num ,int mode);

int
main(int argc, char* argv[]) 
{
	CommonLineCalculationInfo info;
	lCommonLineCalculationInfo linfo;
	int i, j, pair;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	if(info.Inputmode == 0){
		__DataRead(&linfo, info.fptIn, 0);
	}
	else if(info.Inputmode == 1){
		__DataListRead(&linfo, info.fptInListList, info.flagInList, 0);
	}
	else{
		DEBUGPRINT("There is not Inputmode\n");
		exit(1);
	}
	//DEBUGPRINT("Data Read\n");
	__ModeSelection(&linfo, info.mode);
	//DEBUGPRINT("Calclated\n");

	pair = 0;
	for(i=0; i<info.flagInList-1; i++){
	for(j=i+1; j<info.flagInList; j++){
		//DEBUGPRINT("in Write-loop  ");
		
		if(linfo.flag[pair] ==0){
			if(info.Inputmode == 0){
				fprintf(info.fptOut,"%11.2f %11.2f 1\n",linfo.CLAngleOnI1AgainstI2[pair]*DEGREE, linfo.CLAngleOnI2AgainstI1[pair]*DEGREE);
			}
			else if(info.Inputmode == 1){
				fprintf(info.fptOut,"%s %s %11.2f %11.2f 1\n", info.InList[i], info.InList[j], linfo.CLAngleOnI1AgainstI2[pair]*DEGREE, linfo.CLAngleOnI2AgainstI1[pair]*DEGREE);
			}
		}
		else if(linfo.flag[pair] == 1){
			if(info.Inputmode == 0){
				fprintf(info.fptOut,"%11.2f %11.2f z-rotation\n",linfo.CLAngleOnI1AgainstI2[pair]*DEGREE, linfo.CLAngleOnI2AgainstI1[pair]*DEGREE);
			}
			else if(info.Inputmode == 1){
				fprintf(info.fptOut,"%s %s %11.2f %11.2f z-rotation\n", info.InList[i], info.InList[j], linfo.CLAngleOnI1AgainstI2[pair]*DEGREE, linfo.CLAngleOnI2AgainstI1[pair]*DEGREE);
			}
		}
		else{
			fprintf(info.fptOut,"flag error\n");
			
		}
		pair++;
	}
	}
	
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "-m : 0 : in 2004/07/22 \n");
	fprintf(stderr, "     1 : in 2004/09/23 (vector product)\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "----- input file format -----\n");
	fprintf(stderr, "-Im : 0\n");
	fprintf(stderr, "RotationalMode1 angle1 angle2 angle3 RotationalMode2 angle1 angle2 angle3\n");
	fprintf(stderr, "RotationalMode1 angle1 angle2 angle3 RotationalMode2 angle1 angle2 angle3\n");
	fprintf(stderr, "      .           .      .      .          .           .      .      .   \n");
	fprintf(stderr, "      .           .      .      .          .           .      .      .   \n");
	fprintf(stderr, "      .           .      .      .          .           .      .      .   \n");
	fprintf(stderr, "      .           .      .      .          .           .      .      .   \n");
	fprintf(stderr, "      .           .      .      .          .           .      .      .   \n");
	fprintf(stderr, "\n");
	fprintf(stderr, "-Im : 1\n");
	fprintf(stderr, "filename RotationalMode angle1 angle2 angle3\n");
	fprintf(stderr, "   .           .           .      .      .  \n");
	fprintf(stderr, "   .           .           .      .      .  \n");
	fprintf(stderr, "   .           .           .      .      .  \n");
	fprintf(stderr, "   .           .           .      .      .  \n");
	fprintf(stderr, "   .           .           .      .      .  \n");
	fprintf(stderr, "\n");
}

void
__DataRead(lCommonLineCalculationInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;

	fseek(fpt, 0L, SEEK_SET);
	linfo->num = 0;
	s = MemoryAllocate(char, WORDLEN, "in __DataRead");
	while((stringGetFromFile(s, "", fpt, stdout, 3))!=NULL){
		linfo->num++;
	}

	linfo->I1RotationalMode = MemoryAllocate(char*, linfo->num, "in __DataRead");
	linfo->I2RotationalMode = MemoryAllocate(char*, linfo->num, "in __DataRead");
	for(i=0; i<linfo->num; i++){
		linfo->I1RotationalMode[i] = MemoryAllocate(char, WORDLEN, "in __DataRead");
		linfo->I2RotationalMode[i] = MemoryAllocate(char, WORDLEN, "in __DataRead");
	}
	linfo->I1Angle1 = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->I1Angle2 = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->I1Angle3 = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->I2Angle1 = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->I2Angle2 = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->I2Angle3 = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->CLAngleOnI1AgainstI2  = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->CLAngleOnI2AgainstI1  = MemoryAllocate(float, linfo->num, "in __DataRead");
	linfo->flag     = MemoryAllocate(int  , linfo->num, "in __DataRead");

	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<linfo->num; i++){
		stringGetFromFile(s, "", fpt, stdout, 3);
		stringCopy(linfo->I1RotationalMode[i], stringGetNthWord(s, 1, " ,\t"), 4);
		linfo->I1Angle1[i] = (float)stringGetNthRealData(s, 2, " ,\t")*RADIAN;
		linfo->I1Angle2[i] = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		linfo->I1Angle3[i] = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		stringCopy(linfo->I2RotationalMode[i], stringGetNthWord(s, 5, " ,\t"), 4);
		linfo->I2Angle1[i] = (float)stringGetNthRealData(s, 6, " ,\t")*RADIAN;
		linfo->I2Angle2[i] = (float)stringGetNthRealData(s, 7, " ,\t")*RADIAN;
		linfo->I2Angle3[i] = (float)stringGetNthRealData(s, 8, " ,\t")*RADIAN;
	}
	free(s);
}

void
__DataListRead(lCommonLineCalculationInfo* linfo, FILE* fpt, int num, int mode)
{
	int    pair;
	int    i, j, k;
	char** s;

	linfo->num = (num*(num-1))/2;
	s    = MemoryAllocate(char*,      2, "in __DataListRead");
	s[0] = MemoryAllocate(char, WORDLEN, "in __DataListRead");
	s[1] = MemoryAllocate(char, WORDLEN, "in __DataListRead");
	linfo->I1RotationalMode = MemoryAllocate(char*, linfo->num, "in __DataListRead");
	linfo->I2RotationalMode = MemoryAllocate(char*, linfo->num, "in __DataListRead");
	for(i=0; i<linfo->num; i++){
		linfo->I1RotationalMode[i] = MemoryAllocate(char, WORDLEN, "in __DataListRead");
		linfo->I2RotationalMode[i] = MemoryAllocate(char, WORDLEN, "in __DataListRead");
	}
	linfo->I1Angle1 = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->I1Angle2 = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->I1Angle3 = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->I2Angle1 = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->I2Angle2 = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->I2Angle3 = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->CLAngleOnI1AgainstI2  = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->CLAngleOnI2AgainstI1  = MemoryAllocate(float, linfo->num, "in __DataListRead");
	linfo->flag     = MemoryAllocate(int  , linfo->num, "in __DataListRead");
	
	pair = 0;
	for(i=0; i<num-1; i++){
		fseek(fpt, 0L, SEEK_SET);
		for(k=0; k<=i; k++){
			stringGetFromFile(s[0], "", fpt, stdout, 3);
		}
	for(j=i+1; j<num;   j++){
		stringCopy(linfo->I1RotationalMode[pair], stringGetNthWord(s[0], 2, " ,\t"), 4);
		linfo->I1Angle1[pair] = (float)stringGetNthRealData(s[0], 3, " ,\t")*RADIAN;
		linfo->I1Angle2[pair] = (float)stringGetNthRealData(s[0], 4, " ,\t")*RADIAN;
		linfo->I1Angle3[pair] = (float)stringGetNthRealData(s[0], 5, " ,\t")*RADIAN;
		stringGetFromFile(s[1], "", fpt, stdout, 3);
		stringCopy(linfo->I2RotationalMode[pair], stringGetNthWord(s[1], 2, " ,\t"), 4);
		linfo->I2Angle1[pair] = (float)stringGetNthRealData(s[1], 3, " ,\t")*RADIAN;
		linfo->I2Angle2[pair] = (float)stringGetNthRealData(s[1], 4, " ,\t")*RADIAN;
		linfo->I2Angle3[pair] = (float)stringGetNthRealData(s[1], 5, " ,\t")*RADIAN;
		pair++;
	}
	}
	free(s[0]);
	free(s[1]);
	free(s);
}

void
__ModeSelection(lCommonLineCalculationInfo* linfo, int mode)
{
	int i;
	
	switch(mode){
		case 0 :{ /* Result is between 0 and PI */
			for(i=0; i<linfo->num; i++){
				lCommonLineCalculation(linfo, i, 0);
			}
			break;
		}
		case 1 :{ /* Result is between 0 and 2PI */
			for(i=0; i<linfo->num; i++){
				lCommonLineCalculation1(linfo, i, 0);
			}
			break;
		}
	}
}
