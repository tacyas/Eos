/*
# matrix3DEulerAngleGet : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : matrix3DEulerAngleGet 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "genUtil.h" 
#include "../inc/Matrix3D.h" 

static int _Safe[4] = {0, 1, 2, 0};
static int _Next[4] = {1, 2, 0, 1};
void
matrix3DEulerAngleGetFromMatrix3D(Matrix3D M, const char* Mode, matrix3DParaTypeReal* Rot1, matrix3DParaTypeReal* Rot2, matrix3DParaTypeReal* Rot3, long mode)
{
	int i, j, k, h, n, s, frame;
	int first;
	
	switch(Mode[3]) {
		case 'S': {
			frame = 0;
			break;
		}
		case 'R': {
			frame = 1;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}

	switch(Mode[2]) {
		case 'Y': {
			s = 0;
			break;
		}
		case 'N': {
			s = 1;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}

	switch(Mode[1]) {
		case 'O': {
			n = 1;
			break;
		}
		case 'E': {
			n = 0;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}


	switch(Mode[0]) {
		case 'X': {
			first = 0;
			break;
		}
		case 'Y': {
			first = 1;
			break;
		}
		case 'Z': {
			first = 2;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	i = _Safe[first&3];
	j = _Next[i+n];
	k = _Next[i+1-n];
	h = s?k:i;

	if(s==1) {
		double sy;
		sy = sqrt(SQR(M[j][i]) + SQR(M[k][i]));
		if(sy>MATRIX_3D_NEGLECT_VALUE) {
			*Rot1 = atan2(M[j][i], M[k][i]);
			*Rot2 = atan2(sy,M[i][i]);
			*Rot3 = atan2(M[i][j], -M[i][k]);
		} else {
			*Rot1 = atan2(-M[k][j], M[j][j]);
			*Rot2 = atan2(sy, M[i][i]);
			*Rot3 = 0;
		}
	} else {
		double cy;
		cy = sqrt(SQR(M[i][i]) + SQR(M[i][j]));
		if(cy>MATRIX_3D_NEGLECT_VALUE) {
			*Rot1 = atan2(M[j][k], M[k][k]);
			*Rot2 = atan2(-M[i][k], cy);
			*Rot3 = atan2(M[i][j], M[i][i]);
		} else {
			*Rot1 = atan2(-M[k][j], M[j][j]);
			*Rot2 = atan2(-M[i][k], cy);
			*Rot3 = 0;
		}
	}
	if(n==1) {
		*Rot1 = -*Rot1;
		*Rot2 = -*Rot2;
		*Rot3 = -*Rot3;
	} 

	if(s==1) {
		if(*Rot2<=-MATRIX_3D_NEGLECT_VALUE) {
			*Rot1 = fmod(*Rot1+M_PI,2*M_PI);  
			*Rot2 *= -1; 
			*Rot3 = fmod(*Rot3+M_PI,2*M_PI);  
		}
	} else {
		if(*Rot1<=-MATRIX_3D_NEGLECT_VALUE) {
			*Rot1 = fmod(*Rot1+M_PI,2*M_PI);
			*Rot2 = M_PI - *Rot2;
			*Rot3 = fmod(*Rot3+M_PI,2*M_PI);
		}
		if(*Rot3<=-MATRIX_3D_NEGLECT_VALUE) {
			*Rot1 = fmod(*Rot1+M_PI,2*M_PI);
			*Rot2 = M_PI - *Rot2;
			*Rot3 = fmod(*Rot3+M_PI,2*M_PI);
		}
	}

	if(fabs(*Rot1)<MATRIX_3D_NEGLECT_VALUE || fabs(*Rot1-2*M_PI)<MATRIX_3D_NEGLECT_VALUE) *Rot1 = 0;
	if(fabs(*Rot2)<MATRIX_3D_NEGLECT_VALUE || fabs(*Rot2-  M_PI)<MATRIX_3D_NEGLECT_VALUE) *Rot2 = 0;
	if(fabs(*Rot3)<MATRIX_3D_NEGLECT_VALUE || fabs(*Rot3-2*M_PI)<MATRIX_3D_NEGLECT_VALUE) *Rot3 = 0;

	if(frame==1) {
		float t = *Rot1;
		*Rot1 = *Rot3;
		*Rot3 = t;
	}
}

