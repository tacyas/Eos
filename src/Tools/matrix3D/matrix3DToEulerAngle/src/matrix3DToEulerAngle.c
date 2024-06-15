/*
# matrix3DToEulerAngle : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : matrix3DToEulerAngle
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

/*
Example:
typedef struct lmatrix3DToEulerAngleInfo {
	float a;
	int   b;
} lmatrix3DToEulerAngleInfo;

typedef enum lmatrix3DToEulerAngleMode {
	a=0,
	b=1
} lmatrix3DToEulerAngleMode;
*/

int
main(int argc, char* argv[]) 
{
	matrix3DToEulerAngleInfo info;
	Matrix3D mat;
	Matrix3D mat2;
	matrix3DParaTypeReal r1, r2, r3;
	int i, j;
	double delta;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	matrix3DFileRead(info.fptIn, mat);

	matrix3DEulerAngleGetFromMatrix3D(mat, info.EulerMode, &r1, &r2, &r3, info.mode);


	fprintf(info.fptOut, "%4s %15.6f %15.6f %15.6f\n", info.EulerMode, r1*DEGREE, r2*DEGREE, r3*DEGREE);

	matrix3DRotationSetFollowingEulerAngle(mat2, info.EulerMode, r1, r2, r3,  MATRIX_3D_MODE_INITIALIZE); 
	delta=0;
	for(i=0; i<4; i++) {
	for(j=0; j<4; j++) {
		delta+= SQR(mat[i][j]-mat2[i][j]);	
	}
	}
	delta = sqrt(delta);
	if(delta>info.Threshold) {
		fprintf(stderr, "Something wrong! delta: %15.6g\n", delta);
	}
	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
