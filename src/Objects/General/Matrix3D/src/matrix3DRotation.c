/*
# matrix3DRotation.c  1.11
# The latest update : 09/27/97 at 14:16:28
#
#@(#) matrix3DRotation ver 1.11
#@(#) Created by 
#@(#)
#@(#) Usage : matrix3DRotation 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)matrix3DRotation ver1.11; Date:97/09/27 @(#)";
#include "../inc/Matrix3D.h"
#include <math.h>

/*
	Matrix : x 
	   1    0    0    0 
	   0  cos -sin    0 
       0  sin  cos    0 
	   0    0    0    1 
	Matrix : y 
	 cos    0  sin    0 
	   0    1    0    0 
    -sin    0  cos    0 
	   0    0    0    1 
	Matrix : z
	 cos -sin    0    0 
	 sin  cos    0    0 
       0    0    1    0 
	   0    0    0    1 
*/
inline void
matrix3DRotationSet(Matrix3D Matrix, char mode, matrix3DParaTypeReal rot, long Mode)
{
	if(MATRIX_3D_MODE_INITIALIZE==Mode)	{
		matrix3DInit(Matrix);
	}
	switch(mode) {
		case 'X': 
		case 'x': {
			Matrix[1][1] =  cos(rot); Matrix[2][1] = -sin(rot);
			Matrix[1][2] =  sin(rot); Matrix[2][2] =  cos(rot);
			break;
		}
		case 'Y':
		case 'y': {
			Matrix[2][2] =  cos(rot); Matrix[0][2] = -sin(rot);
			Matrix[2][0] =  sin(rot); Matrix[0][0] =  cos(rot);
			break;
		}
		case 'Z': 
		case 'z': {
			Matrix[0][0] =  cos(rot); Matrix[1][0] = -sin(rot);
			Matrix[0][1] =  sin(rot); Matrix[1][1] =  cos(rot);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in matrix3DRotationSet: %c\n", mode);
			break;
		}
	}
}

/*
	M = X*Y*Z
*/
inline void
matrix3DRotationSetXYZ(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode)
{
	Matrix3D MatrixX;
	Matrix3D MatrixY;
	Matrix3D MatrixZ;

	matrix3DRotationSet(MatrixZ, 'z', rotz, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixY, 'y', roty, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixX, 'x', rotx, MATRIX_3D_MODE_INITIALIZE);

	if(MATRIX_3D_MODE_INITIALIZE==mode) {
		matrix3DInit(Matrix);
	}

	matrix3DMultiply(Matrix, MatrixX);
	matrix3DMultiply(Matrix, MatrixY);
	matrix3DMultiply(Matrix, MatrixZ);
}

/*
	M = Z*Y*X
*/
inline void
matrix3DRotationSetZYX(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode)
{
	Matrix3D MatrixX;
	Matrix3D MatrixY;
	Matrix3D MatrixZ;


	matrix3DRotationSet(MatrixZ, 'z', rotz, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixY, 'y', roty, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixX, 'x', rotx, MATRIX_3D_MODE_INITIALIZE);

	if(MATRIX_3D_MODE_INITIALIZE==mode) {
		matrix3DInit(Matrix);
	}

	matrix3DMultiply(Matrix, MatrixZ);
	matrix3DMultiply(Matrix, MatrixY);
	matrix3DMultiply(Matrix, MatrixX);
}

/*
	M = Z*X*Y
*/
inline void
matrix3DRotationSetZXY(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode)
{
	Matrix3D MatrixX;
	Matrix3D MatrixY;
	Matrix3D MatrixZ;


	matrix3DRotationSet(MatrixZ, 'z', rotz, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixY, 'y', roty, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixX, 'x', rotx, MATRIX_3D_MODE_INITIALIZE);

	if(MATRIX_3D_MODE_INITIALIZE==mode) {
		matrix3DInit(Matrix);
	}

	matrix3DMultiply(Matrix, MatrixZ);
	matrix3DMultiply(Matrix, MatrixX);
	matrix3DMultiply(Matrix, MatrixY);
}


/*
	M = Y*X*Z
*/
inline void
matrix3DRotationSetYXZ(Matrix3D Matrix, matrix3DParaTypeReal rotx, matrix3DParaTypeReal roty, matrix3DParaTypeReal rotz, long mode)
{
	Matrix3D MatrixX;
	Matrix3D MatrixY;
	Matrix3D MatrixZ;


	matrix3DRotationSet(MatrixZ, 'z', rotz, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixY, 'y', roty, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSet(MatrixX, 'x', rotx, MATRIX_3D_MODE_INITIALIZE);

	if(MATRIX_3D_MODE_INITIALIZE==mode) {
		matrix3DInit(Matrix);
	}

	matrix3DMultiply(Matrix, MatrixY);
	matrix3DMultiply(Matrix, MatrixX);
	matrix3DMultiply(Matrix, MatrixZ);
}

