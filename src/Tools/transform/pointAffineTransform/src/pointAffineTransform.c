/*
# pointAffineTransform : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : pointAffineTransform
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
#include "Vector.h"
#include "Matrix3D.h"

/*
typedef struct lpointAffineTransformInfo {
	floatVector v;
} lpointAffineTransformInfo;

typedef enum lpointAffineTransformMode {
	a=0,
	b=1
} lpointAffineTransformMode;
*/

int
main(int argc, char* argv[]) 
{
	pointAffineTransformInfo info;
	Matrix3D m;
	floatVector v;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	floatVectorInit(&v, 4);
	v.data[0] = info.X;
	v.data[1] = info.Y;
	v.data[2] = info.Z;
	v.data[3] = 1;

	matrix3DRotationSetFollowingEulerAngle(m, info.Euler, 
			info.Rot1*RADIAN, 
			info.Rot2*RADIAN, 
			info.Rot3*RADIAN, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(m, info.dX, info.dY, info.dZ, MATRIX_3D_MODE_NOT_INITIALIZE);
	matrix3DMultiplyVector(&v, m);

	fprintf(info.fptOut, "%g %g %g\n", v.data[0], v.data[1], v.data[2]);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
