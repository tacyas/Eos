/*
# matrix3DFile.c  1.4
# The latest update : 11/02/96 at 20:19:06
#
#@(#) matrix3DFile ver 1.4
#@(#) Created by 
#@(#)
#@(#) Usage : matrix3DFile 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)matrix3DFile ver1.4; Date:96/11/02 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include "../inc/Matrix3D.h"
#include "genUtil.h"
#include "eosString.h"

void
matrix3DFileFormat(FILE* fpt)
{
	fprintf(fpt, ">>> Matrix3D File Format y = Ax + b<<<\n");
	fprintf(fpt, "a11 a21 a31 : Rotation Array : y=Ax\n");
	fprintf(fpt, "a12 a22 a32 \n");
	fprintf(fpt, "a13 a23 a33 \n");
	fprintf(fpt, "b1  b2  b3  : Translation Array : y = x + b\n");
}

void
matrix3DFileRead(FILE* fpt, Matrix3D Matrix)
{
	char s[GEN_UTIL_MAX_STRING_LENGTH];
	int i, j;
	
	matrix3DInit(Matrix);
	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<MATRIX_3D_HEIGHT-1; i++) {
		if(NULL!=stringGetFromFile(s, "", fpt, stdout, 1)) {
			for(j=0; j<MATRIX_3D_WIDTH-1; j++) {
				Matrix[j][i] = stringGetNthRealData(s, j+1, " \t,");
			}
		} else {
			fprintf(stderr, "Matrix File is Wrong!!\n");
			exit(EXIT_FAILURE);
		}
	}
	if(NULL!=stringGetFromFile(s, "", fpt, stdout, 1)) {
		for(j=0; j<MATRIX_3D_HEIGHT-1; j++) {
			Matrix[3][j] = stringGetNthRealData(s, j+1, " \t,");
		}
	} else {
		fprintf(stderr, "Matrix File is Wrong!!\n");
		exit(EXIT_FAILURE);
	}
}

void
matrix3DFileWrite(FILE* fpt, Matrix3D Matrix)
{
	int i, j;
	
	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<MATRIX_3D_HEIGHT-1; i++) {
		for(j=0; j<MATRIX_3D_WIDTH - 1; j++) {
			fprintf(fpt, "%15.6f ", Matrix[j][i]);
		}
		fprintf(fpt, "\n");
	}
	for(j=0; j<MATRIX_3D_HEIGHT - 1; j++) {
		fprintf(fpt, "%15.6f ", Matrix[3][j]);
	}
}

