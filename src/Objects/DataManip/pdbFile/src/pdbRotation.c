/*
# pdbRotation.c  1.3
# The latest update : 01/23/97 at 11:05:58
#
#@(#) pdbRotation ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : pdbRotation 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbRotation ver1.3; Date:97/01/23 @(#)";
#include "../inc/pdbFile.h"
#include "Matrix3D.h"

void
pdbRotationFollowingEulerAngle(pdbFile* pdb, char Mode[4], matrix3DParaTypeReal rot1,  matrix3DParaTypeReal rot2, matrix3DParaTypeReal rot3)
{
	Matrix3D Matrix;

	matrix3DRotationSetFollowingEulerAngle(Matrix, Mode, rot1, rot2, rot3,  MATRIX_3D_MODE_INITIALIZE); 
	pdbTrans(pdb, Matrix);
}

void
pdbRotationFollowingEulerAngleInverse(pdbFile* pdb, char Mode[4], matrix3DParaTypeReal rot1,  matrix3DParaTypeReal rot2, matrix3DParaTypeReal rot3)
{
	Matrix3D Matrix;

	matrix3DRotationAntiSetFollowingEulerAngle(Matrix, Mode, rot1, rot2, rot3,  MATRIX_3D_MODE_INITIALIZE); 
	pdbTrans(pdb, Matrix);
}

void
pdbRotationZXY(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz)
{
	Matrix3D Matrix;

	matrix3DRotationSetZXY(Matrix, rotx, roty, rotz, MATRIX_3D_MODE_INITIALIZE);
	pdbTrans(pdb, Matrix);
}

void
pdbRotationYXZ(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz)
{
	Matrix3D Matrix;

	matrix3DRotationSetYXZ(Matrix, rotx, roty, rotz, MATRIX_3D_MODE_INITIALIZE);
	pdbTrans(pdb, Matrix);
}

void
pdbRotationXYZ(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz)
{
	Matrix3D Matrix;

	matrix3DRotationSetXYZ(Matrix, rotx, roty, rotz, MATRIX_3D_MODE_INITIALIZE);
	pdbTrans(pdb, Matrix);
}


void
pdbRotationZYX(pdbFile* pdb, pdbFileParaTypeReal rotx, pdbFileParaTypeReal roty, pdbFileParaTypeReal rotz)
{
	Matrix3D Matrix;

	matrix3DRotationSetZYX(Matrix, rotx, roty, rotz, MATRIX_3D_MODE_INITIALIZE);
	pdbTrans(pdb, Matrix);
}
