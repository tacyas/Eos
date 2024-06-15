/*
# matrix3DMultiplyVector.c  1.5
# The latest update : 11/02/96 at 20:30:52
#
#@(#) matrix3DMultiplyVector ver 1.5
#@(#) Created by 
#@(#)
#@(#) Usage : matrix3DMultiplyVector 
#@(#) Attention
#@(#)   v = Matrix * v
#@(#) 
#@(#)
*/
static char __sccs_id[] = "@(#)matrix3DMultiplyVector ver1.5; Date:96/11/02 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include "Vector.h"
#include "../inc/Matrix3D.h"

/*
	v = M*v

	M00 M10 M20 M30      v0
	..............       v1
	..............    *  v2
	..............       v3
*/

inline void
matrix3DMultiplyVector(floatVector* v, Matrix3D Matrix)
{
	long i, j;
	floatVector tmp;

	if(MATRIX_3D_HEIGHT!=v->size) {
		fprintf(stderr, "Vector size is wrong in matrix3DMutliplyVector: %ld\n", v->size);
		exit(EXIT_FAILURE); 
	}
	floatVectorInit(&tmp, v->size);
	for(j=0; j<v->size; j++) {
		tmp.data[j] = 0.0;
		for(i=0; i<v->size; i++) {
			tmp.data[j] += (Matrix[i][j]*v->data[i]);
		}
	}
	for(i=0; i<v->size; i++) {
		v->data[i] = tmp.data[i];
	}
	floatVectorFree(&tmp);
}



inline void
matrix3DMultiplyVectors(floatVector* vs, int n, Matrix3D Matrix)
{
	long i, j, k;
	floatVector tmp;

	if(MATRIX_3D_HEIGHT!=vs[0].size) {
		fprintf(stderr, "Vector size is wrong in matrix3DMutliplyVector: %ld\n", vs[0].size);
		exit(EXIT_FAILURE); 
	}
	floatVectorInit(&tmp, vs[0].size);

	for(k=0; k<n; k++) {
		for(j=0; j<vs[k].size; j++) {
			tmp.data[j] = 0.0;
			for(i=0; i<vs[k].size; i++) {
				tmp.data[j] += (Matrix[i][j]*vs[k].data[i]);
			}
		}
		for(i=0; i<vs[k].size; i++) {
			vs[k].data[i] = tmp.data[i];
		}
	}
	floatVectorFree(&tmp);
}



