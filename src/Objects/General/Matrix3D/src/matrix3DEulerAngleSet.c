/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% matrix3DEulerAngleSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : matrix3DEulerAngleSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%matrix3DEulerAngleSet ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include "../inc/Matrix3D.h"
#undef DEBUG
#include "genUtil.h"


void
matrix3DRotationSetFollowingEulerAngle(Matrix3D m, const char* Mode, float Rot1, float Rot2, float Rot3, long mode)
{
	Matrix3D m1, m2, m3;
	int      EorO;
	char     rot1Eu;
	char     rot2Eu;
	char     rot3Eu;

	switch(mode) {
		case MATRIX_3D_MODE_INITIALIZE: {
			matrix3DInit(m);
			break;
		}
		default: {
			break;
		}
	}
	
	rot1Eu = Mode[0];

	switch(Mode[1]) {
		case 'O': {
			EorO = 2;
			break;
		}
		case 'E': {
			EorO = 1;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	rot2Eu = (unsigned char)(((int)rot1Eu - (int)'X' + EorO)%3) + 'X';

	switch(Mode[2]) {
		case 'Y': {
			EorO = EorO;
			break;
		}
		case 'N': {
			EorO = (2 - EorO) + 1;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	rot3Eu = (unsigned char)(((int)rot2Eu - (int)'X' + EorO)%3) + 'X';

	DEBUGPRINT3("Rotation %x -> %x -> %x\n", rot1Eu, rot2Eu, rot3Eu);
	DEBUGPRINT3("Rotation %c -> %c -> %c\n", rot1Eu, rot2Eu, rot3Eu);

	switch(Mode[3]) {
		case 'S': {
			matrix3DRotationSet(m1, rot1Eu, Rot1, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m2, rot2Eu, Rot2, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m3, rot3Eu, Rot3, MATRIX_3D_MODE_INITIALIZE); 
			break;
		}
		case 'R': {
			matrix3DRotationSet(m1, rot1Eu, Rot3, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m2, rot2Eu, Rot2, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m3, rot3Eu, Rot1, MATRIX_3D_MODE_INITIALIZE); 
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	matrix3DMultiplyInv(m1, m);
	matrix3DMultiplyInv(m2, m);
	matrix3DMultiplyInv(m3, m);
}

void
matrix3DRotationAntiSetFollowingEulerAngle(Matrix3D m, const char* Mode, float Rot1, float Rot2, float Rot3, long mode)
{
	Matrix3D m1, m2, m3;
	int      EorO;
	char     rot1Eu;
	char     rot2Eu;
	char     rot3Eu;

	switch(mode) {
		case MATRIX_3D_MODE_INITIALIZE: {
			matrix3DInit(m);
			break;
		}
		default: {
			break;
		}
	}
	
	rot1Eu = Mode[0];

	switch(Mode[1]) {
		case 'O': {
			EorO = 2;
			break;
		}
		case 'E': {
			EorO = 1;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	rot2Eu = (unsigned char)(((int)rot1Eu - (int)'X' + EorO)%3) + 'X';

	switch(Mode[2]) {
		case 'Y': {
			EorO = EorO;
			break;
		}
		case 'N': {
			EorO = (2 - EorO) + 1;
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	rot3Eu = (unsigned char)(((int)rot2Eu - (int)'X' + EorO)%3) + 'X';

	switch(Mode[3]) {
		case 'S': {
			matrix3DRotationSet(m1, rot1Eu, -Rot1, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m2, rot2Eu, -Rot2, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m3, rot3Eu, -Rot3, MATRIX_3D_MODE_INITIALIZE); 
			break;
		}
		case 'R': {
			matrix3DRotationSet(m1, rot1Eu, -Rot3, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m2, rot2Eu, -Rot2, MATRIX_3D_MODE_INITIALIZE); 
			matrix3DRotationSet(m3, rot3Eu, -Rot1, MATRIX_3D_MODE_INITIALIZE); 
			break;
		}
		default: {
			fprintf(stderr, "Not suppoted : %s in matrix3DRotationSetFollowingEulerAngle\n", Mode);
			exit(EXIT_FAILURE);
		}
	}
	matrix3DMultiplyInv(m3, m);
	matrix3DMultiplyInv(m2, m);
	matrix3DMultiplyInv(m1, m);
}

