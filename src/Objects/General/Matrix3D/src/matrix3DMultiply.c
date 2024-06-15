/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% matrix3DMultiply ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : matrix3DMultiply 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%matrix3DMultiply ver%I%; Date:%D% %Z%";
#include "../inc/Matrix3D.h"

/*
	A = A*B

	a00 a10 a20 a30     b00 ........ 
	...............     b01 ........
	...............  *  b02 ........
	...............     b03 ........
*/
inline void 
matrix3DMultiply(Matrix3D A, Matrix3D B)
{
    Matrix3D Matrix;
	long i, j, k;

	for(i=0; i<MATRIX_3D_WIDTH; i++) {	
		for(j=0; j<MATRIX_3D_HEIGHT; j++) {	
			Matrix[i][j] = 0.0;
			for(k=0; k<MATRIX_3D_WIDTH; k++) {
				Matrix[i][j] += (A[k][j]*B[i][k]);
			}
		}
	}
			
	for(i=0; i<MATRIX_3D_WIDTH; i++) {
		for(j=0; j<MATRIX_3D_HEIGHT; j++) {	
			A[i][j] = Matrix[i][j];
		}
	}	
}

/*
	B = A*B

	a00 a10 a20 a30     b00 ........ 
	...............     b01 ........
	...............  *  b02 ........
	...............     b03 ........
*/
inline void 
matrix3DMultiplyInv(Matrix3D A, Matrix3D B)
{
    Matrix3D Matrix;
	long i, j, k;

	for(i=0; i<MATRIX_3D_WIDTH; i++) {	
		for(j=0; j<MATRIX_3D_HEIGHT; j++) {	
			Matrix[i][j] = 0.0;
			for(k=0; k<MATRIX_3D_WIDTH; k++) {
				Matrix[i][j] += (A[k][j]*B[i][k]);
			}
		}
	}
			
	for(i=0; i<MATRIX_3D_WIDTH; i++) {
		for(j=0; j<MATRIX_3D_HEIGHT; j++) {	
			B[i][j] = Matrix[i][j];
		}
	}	
}

