/*
# eosPointRotation : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : eosPointRotation
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
#include "eosString.h"
#include "Matrix3D.h"
#include "Memory.h"
#include "eosPoint.h"

/*
Example:
typedef struct leosPointRotationInfo {
	float a;
	int   b;
} leosPointRotationInfo;

typedef enum leosPointRotationMode {
	a=0,
	b=1
} leosPointRotationMode;
*/

int
main(int argc, char* argv[]) 
{
	Matrix3D mat;
	Matrix3D* matList;
	EulerAngleInfo* EAList;
	eosPoint p;
	eosPoint* pList;
	eosPointRotationInfo info;
	int i;
	char s[STRING_MAX_LENGTH];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	if(info.flagIn||info.flagInList) { 
		if(info.flagIn) {
			eosPointRead(info.fptIn, &p, info.InType);
		} else {
			if(!info.flagOutList) {
				fprintf(stderr, "Need -O\n");
				usage(argv[0]);
				exit(EXIT_FAILURE);
			}
			pList   = (eosPoint*) memoryAllocate(sizeof(eosPoint)*info.flagInList, "in main");
			for(i=0; i<info.flagInList; i++) {
				eosPointRead(info.fptInList[i], &(pList[i]), info.InType);
			}
		}
	} else {
		fprintf(stderr, "Need -i or -I\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if(info.flagIn) {
		matrix3DRotationSetFollowingEulerAngle(mat, info.EAMode, 
			info.Rot1*RADIAN, 
			info.Rot2*RADIAN, 
			info.Rot3*RADIAN, MATRIX_3D_MODE_INITIALIZE);

		eosPointRotate(&p, mat);
	} else if(info.flagInList) {
		matList = (Matrix3D*) memoryAllocate(sizeof(Matrix3D)*info.flagInList, "in main");
		EAList  = (EulerAngleInfo*) memoryAllocate(sizeof(EulerAngleInfo)*info.flagInList, "in main");
		fseek(info.fptInListList, 0L, SEEK_SET);
		for(i=0; i<info.flagInList; i++) {
			stringGetFromFile(s, "main", info.fptInListList, stderr, 3);
			stringCopy(EAList[i].EAMode, stringGetNthWord(s, 2, " ,\t"), 4);
			EAList[i].Rot1 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
			EAList[i].Rot2 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
			EAList[i].Rot3 = stringGetNthRealData(s, 5, " ,\t")*RADIAN;
			matrix3DRotationSetFollowingEulerAngle(matList[i], 
				EAList[i].EAMode, 
				EAList[i].Rot1, 
				EAList[i].Rot2, 
				EAList[i].Rot3, MATRIX_3D_MODE_INITIALIZE);

			eosPointRotate(&(pList[i]), matList[i]);
		}
	}	

	if(info.flagOut) {
		eosPointWrite(info.fptOut, &p, info.OutType);
	} else if(info.flagOutList) {
		for(i=0; i<info.flagOutList; i++) {
			eosPointWrite(info.fptOutList[i], &(pList[i]), info.OutType);
		}
	} 

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> eosPointFileType\n");
	eosPointFileFormatUsage(stderr);
}
