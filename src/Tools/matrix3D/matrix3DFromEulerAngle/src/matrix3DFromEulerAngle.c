/*
# matrix3DFromEulerAngle : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : matrix3DFromEulerAngle
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

/*
Example:
typedef struct lmatrix3DFromEulerAngleInfo {
	float a;
	int   b;
} lmatrix3DFromEulerAngleInfo;

typedef enum lmatrix3DFromEulerAngleMode {
	a=0,
	b=1
} lmatrix3DFromEulerAngleMode;
*/

int
main(int argc, char* argv[]) 
{
	matrix3DFromEulerAngleInfo info;
	Matrix3D  mat;
	char* Mode;
	double r1, r2, r3;	
	
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	Mode = strdup(info.EMode);
	r1 = info.Rot1*RADIAN;
	r2 = info.Rot2*RADIAN;
	r3 = info.Rot3*RADIAN;

	if(info.flagIn) {
		char s[1024];
		stringGetFromFile(s, "Mode", info.fptIn, stdout, 3); 
		Mode = stringGetNthWord(s, 1, " ,\t");
		r1 = stringGetNthRealData(s, 2, " ,\t")*RADIAN;
		r2 = stringGetNthRealData(s, 3, " ,\t")*RADIAN;
		r3 = stringGetNthRealData(s, 4, " ,\t")*RADIAN;
	}
	if(info.flagRot1) {
		Mode = strdup(info.EMode);
		r1 = info.Rot1*RADIAN;
		r2 = info.Rot2*RADIAN;
		r3 = info.Rot3*RADIAN;
	}
	matrix3DInit(mat);
	matrix3DRotationSetFollowingEulerAngle(mat, Mode, r1, r2, r3, MATRIX_3D_MODE_INITIALIZE); 

	matrix3DFileWrite(info.fptOut, mat);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
