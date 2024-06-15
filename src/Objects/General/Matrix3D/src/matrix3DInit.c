/*
# matrix3DInit.c  1.3
# The latest update : 11/02/96 at 20:21:13
#
#@(#) matrix3DInit ver 1.3
#@(#) Created by 
#@(#)
#@(#) Usage : matrix3DInit 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)matrix3DInit ver1.3; Date:96/11/02 @(#)";
#include "../inc/Matrix3D.h"
/*
	i->
  j	1 0 0 0
  | 0 1 0 0
  / 0 0 1 0 
	0 0 0 1
*/
inline void
matrix3DInit(Matrix3D Matrix)
{
	long i, j;

	for(i=0; i<MATRIX_3D_WIDTH; i++) {
		for(j=0; j<MATRIX_3D_HEIGHT; j++) {
			if(i==j) {
				Matrix[i][j] = 1.0;
			} else {
				Matrix[i][j] = 0.0;
			}
		}
	}
}

