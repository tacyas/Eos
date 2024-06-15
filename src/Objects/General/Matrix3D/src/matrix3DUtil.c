/*
# matrix3DInverse : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : matrix3DInverse 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/Matrix3D.h"
#include "Array.h"

void
matrix3DFromRotationMatrix(Matrix3D dst, Array a)
{
	int i, j;

	matrix3DInit(dst);
	if(a.dim != 2) {
		fprintf(stderr, "Dim of array(%ld) is not two: in matrix3DFromRotationMatrix\n", a.dim); 
		exit(EXIT_FAILURE);
	}
	for(i=0; i<3; i++) {
	for(j=0; j<3; j++) {
		dst[i][j] = arrayDataGet2(a,i,j); 
	}
	}

}
void
matrix3DCopy(Matrix3D dst, Matrix3D src)
{
	int i, j;

	for(i=0; i<4; i++) {
	for(j=0; j<4; j++) {
		dst[i][j] = src[i][j]; 
	}
	}
}

void
matrix3DScale(Matrix3D mat, double ratio)
{
	int i, j;

	for(i=0; i<4; i++) {
	for(j=0; j<4; j++) {
		mat[i][j] *= ratio; 
	}
	}
}

void
matrix3DInverse(Matrix3D mat)
{
	int i, j;
	Matrix3D tmp;			

	matrix3DCopy(tmp, mat);

	/* Rotation */
	mat[0][1] = tmp[1][0];
	mat[0][2] = tmp[2][0];
	mat[1][0] = tmp[0][1];
	mat[1][2] = tmp[2][1];
	mat[2][0] = tmp[0][2];
	mat[2][1] = tmp[1][2];
	
	/* Translation:              tx                    ty                    tz   */
	mat[3][0] = - ( mat[0][0]*tmp[3][0] + mat[1][0]*tmp[3][1] + mat[2][0]*tmp[3][2] ) ;
	mat[3][1] = - ( mat[0][1]*tmp[3][0] + mat[1][1]*tmp[3][1] + mat[2][1]*tmp[3][2] ) ;
	mat[3][2] = - ( mat[0][2]*tmp[3][0] + mat[1][2]*tmp[3][1] + mat[2][2]*tmp[3][2] ) ;
}
