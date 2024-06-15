/*
# matrix3DTranslation.c  1.3
# The latest update : 11/02/96 at 20:32:16
#
#@(#) matrix3DTranslation ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : matrix3DTranslation 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)matrix3DTranslation ver1.3; Date:96/11/02 @(#)";
#include "../inc/Matrix3D.h"

/*
	1 0 0 x
M =	0 1 0 y
	0 0 1 z
	0 0 0 1
*/
inline void
matrix3DTranslationSet(Matrix3D Matrix, matrix3DParaTypeReal x, matrix3DParaTypeReal y, matrix3DParaTypeReal z, long mode)
{
	if(MATRIX_3D_MODE_INITIALIZE==mode) {
		matrix3DInit(Matrix);
	}
	Matrix[3][0] = x;
	Matrix[3][1] = y;
	Matrix[3][2] = z;
}
