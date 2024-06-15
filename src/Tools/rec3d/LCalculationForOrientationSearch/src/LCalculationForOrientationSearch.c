/*
# LCalculationForOrientationSearch : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : LCalculationForOrientationSearch
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
#define WORDLEN 256
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"

typedef struct lLCalculationForOrientationSearchInfo {
	int    num;

	char** filename;
	char** rotation;
	float* phi;
	float* theta;
	float* psi;
} lLCalculationForOrientationSearchInfo;

/*
typedef enum lLCalculationForOrientationSearchMode {
	a=0,
	b=1
} lLCalculationForOrientationSearchMode;
*/

void
__FileRead(lLCalculationForOrientationSearchInfo* linfo, FILE* fpt, int mode);

int
main(int argc, char* argv[]) 
{
	LCalculationForOrientationSearchInfo  info;
	lLCalculationForOrientationSearchInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	__FileRead(&linfo, info.fptIn, 0);
	
	DEBUGPRINT("Program End\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
__FileRead(lLCalculationForOrientationSearchInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;

	s = MemoryAllocate(char, WORDLEN, "in __FileRead");
	linfo->num = 0;
	while(fgets(s, WORDLEN-1, fpt) != NULL){
		linfo->num++;
	}
	linfo->filename = MemoryAllocate(char*, linfo->num, "in __FileRead");
	linfo->rotation = MemoryAllocate(char*, linfo->num, "in __FileRead");
	for(i=0; i<linfo->num; i++){
		linfo->filename[i] = MemoryAllocate(char, WORDLEN, "in __FileRead");
		linfo->rotation[i] = MemoryAllocate(char,       5, "in __FileRead");
	}
	linfo->phi   = MemoryAllocate(float, linfo->num, "in __FileRead");
	linfo->theta = MemoryAllocate(float, linfo->num, "in __FileRead");
	linfo->psi   = MemoryAllocate(float, linfo->num, "in __FileRead");
	for(i=0; i<linfo->num; i++){
		stringGetFromFile(s, "", fpt, stdout, 3);
		linfo->phi[i]   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		linfo->theta[i] = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
		linfo->psi[i]   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
	}
	fclose(fpt);
	free(s);
}
