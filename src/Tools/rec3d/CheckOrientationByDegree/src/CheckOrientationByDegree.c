/*
# CheckOrientationByDegree : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : CheckOrientationByDegree
# Attention
#   $Loccker$
#  	$State$ 
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#define WORDLEN 1024
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "Matrix3D.h"

typedef struct EulerAngleInfo {
	char** filename;
	char** rotationalMode;
	int    filenum;
	float* phi;
	float* theta;
	float* psi;
} EulerAngleInfo;

typedef struct lCheckOrientationByDegreeInfo {
	EulerAngleInfo InputBase;
	EulerAngleInfo Input;
	EulerAngleInfo Output;
	float DifferentialAve;
} lCheckOrientationByDegreeInfo;

/*
typedef enum lCheckOrientationByDegreeMode {
	a=0,
	b=1
} lCheckOrientationByDegreeMode;
*/

void
__InputFileRead(lCheckOrientationByDegreeInfo* linfo, FILE* fpt, int mode);

void
lCheckOrientationByDegree(lCheckOrientationByDegreeInfo* linfo, int mode);

void
__ChangeRotationalMode(lCheckOrientationByDegreeInfo* linfo, int mode);

void
__OutputFileWrite(lCheckOrientationByDegreeInfo* linfo, FILE* fpt, int mode);

int
main(int argc, char* argv[]) 
{
	CheckOrientationByDegreeInfo  info;
	lCheckOrientationByDegreeInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	
	__InputFileRead(&linfo, info.fptInbase, 0);
	__InputFileRead(&linfo,     info.fptIn, 1);
	if(linfo.InputBase.filenum != linfo.Input.filenum){
		fprintf(stderr, "These files do not apply to this program !!\n");
		exit(1);
	}
	switch(info.modechanging){
		case 0 :
			fprintf(stdout, "Do not chang rotational mode of -i\n");
		break;
		case 1 :
			fprintf(stdout, "Chang rotational mode of -i\n");
			__ChangeRotationalMode(&linfo, 0);	
		break;
	}
	lCheckOrientationByDegree(&linfo, 0);
	__OutputFileWrite(&linfo, info.fptOut, 0);
	DEBUGPRINT("Program Start\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "----- mode changing -----\n");
	fprintf(stderr, "-mc : 0 : do not chang rotational mode of -i\n");
	fprintf(stderr, "      1 :        chang rotational mode of -i\n");
	fprintf(stderr, "\n");
}

void
__InputFileRead(lCheckOrientationByDegreeInfo* linfo, FILE* fpt, int mode)
{
	int   i;
	char* s;

	s = MemoryAllocate(char, WORDLEN, "in __InputFileRead");
	switch(mode){
		case 0 :
			linfo->InputBase.filenum = 0;
			fseek(fpt, 0L, SEEK_SET);
			while(fgets(s, WORDLEN-1, fpt) != NULL){
				linfo->InputBase.filenum++;
			}
			fseek(fpt, 0L, SEEK_SET);
			linfo->InputBase.filename         = MemoryAllocate(char*, linfo->InputBase.filenum, "in __InputFileRead");
			linfo->InputBase.rotationalMode   = MemoryAllocate(char*, linfo->InputBase.filenum, "in __InputFileRead");
			linfo->InputBase.phi              = MemoryAllocate(float, linfo->InputBase.filenum, "in __InputFileRead");
			linfo->InputBase.theta            = MemoryAllocate(float, linfo->InputBase.filenum, "in __InputFileRead");
			linfo->InputBase.psi              = MemoryAllocate(float, linfo->InputBase.filenum, "in __InputFileRead");
			for(i=0; i<linfo->InputBase.filenum; i++){
				linfo->InputBase.filename[i]       = MemoryAllocate(char, WORDLEN, "in __InputFileRead");
				linfo->InputBase.rotationalMode[i] = MemoryAllocate(char,       5, "in __InputFileRead");
			}
			for(i=0; i<linfo->InputBase.filenum; i++){
				stringGetFromFile(s, "", fpt, stdout, 3);
				stringCopy(linfo->InputBase.filename[i],       stringGetNthWord(s, 1, " ,\t"), WORDLEN-1);
				stringCopy(linfo->InputBase.rotationalMode[i], stringGetNthWord(s, 2, " ,\t"),         4);
				linfo->InputBase.phi[i]   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
				linfo->InputBase.theta[i] = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
				linfo->InputBase.psi[i]   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
			}
		break;
		case 1 :
			linfo->Input.filenum = 0;
			fseek(fpt, 0L, SEEK_SET);
			while(fgets(s, WORDLEN-1, fpt) != NULL){
				linfo->Input.filenum++;
			}
			fseek(fpt, 0L, SEEK_SET);
			linfo->Input.filename         = MemoryAllocate(char*, linfo->Input.filenum, "in __InputFileRead");
			linfo->Input.rotationalMode   = MemoryAllocate(char*, linfo->Input.filenum, "in __InputFileRead");
			linfo->Input.phi              = MemoryAllocate(float, linfo->Input.filenum, "in __InputFileRead");
			linfo->Input.theta            = MemoryAllocate(float, linfo->Input.filenum, "in __InputFileRead");
			linfo->Input.psi              = MemoryAllocate(float, linfo->Input.filenum, "in __InputFileRead");
			for(i=0; i<linfo->Input.filenum; i++){
				linfo->Input.filename[i]       = MemoryAllocate(char, WORDLEN, "in __InputFileRead");
				linfo->Input.rotationalMode[i] = MemoryAllocate(char,       5, "in __InputFileRead");
			}
			for(i=0; i<linfo->Input.filenum; i++){
				stringGetFromFile(s, "", fpt, stdout, 3);
				stringCopy(linfo->Input.filename[i],       stringGetNthWord(s, 1, " ,\t"), WORDLEN-1);
				stringCopy(linfo->Input.rotationalMode[i], stringGetNthWord(s, 2, " ,\t"),         4);
				linfo->Input.phi[i]   = (float)stringGetNthRealData(s, 3, " ,\t")*RADIAN;
				linfo->Input.theta[i] = (float)stringGetNthRealData(s, 4, " ,\t")*RADIAN;
				linfo->Input.psi[i]   = (float)stringGetNthRealData(s, 5, " ,\t")*RADIAN;
			}
		break;
	}
	fclose(fpt);
	free(s);
}

void
__ChangeRotationalMode(lCheckOrientationByDegreeInfo* linfo, int mode)
{
	int      i;
	Matrix3D Matrix;
	float Phi, Theta, Psi;

	for(i=0; i<linfo->Input.filenum; i++){
		matrix3DRotationSetFollowingEulerAngle(Matrix,
											   linfo->Input.rotationalMode[i],
											   linfo->Input.phi[i],
											   linfo->Input.theta[i],
											   linfo->Input.psi[i],
											   MATRIX_3D_MODE_INITIALIZE);
		
		matrix3DEulerAngleGetFromMatrix3D(Matrix, linfo->InputBase.rotationalMode[i], 
		                                  &linfo->Input.phi[i], &linfo->Input.theta[i], &linfo->Input.psi[i], 0);
		stringCopy(linfo->Input.rotationalMode[i], linfo->InputBase.rotationalMode[i], 4);
	}
}

void
lCheckOrientationByDegree(lCheckOrientationByDegreeInfo* linfo, int mode)
{
	int i;
	Matrix3D* BasedMatrix;
	Matrix3D** Matrix;
	float Sum;
	
	BasedMatrix = MemoryAllocate(Matrix3D, 2, "in lCheckOrientationByDegree");
	Matrix      = MemoryAllocate(Matrix3D*, 2, "in lCheckOrientationByDegree");
	Matrix[0]   = MemoryAllocate(Matrix3D, linfo->InputBase.filenum, "in lCheckOrientationByDegree");
	Matrix[1]   = MemoryAllocate(Matrix3D, linfo->Input.filenum,     "in lCheckOrientationByDegree");

	matrix3DRotationAntiSetFollowingEulerAngle(BasedMatrix[0], 
	                                           linfo->InputBase.rotationalMode[0],
											   linfo->InputBase.phi[0],
											   linfo->InputBase.theta[0],
											   linfo->InputBase.psi[0],
											   MATRIX_3D_MODE_INITIALIZE);

	matrix3DRotationAntiSetFollowingEulerAngle(BasedMatrix[1], 
	                                           linfo->Input.rotationalMode[0],
											   linfo->Input.phi[0],
											   linfo->Input.theta[0],
											   linfo->Input.psi[0],
											   MATRIX_3D_MODE_INITIALIZE);

	for(i=0; i<linfo->InputBase.filenum; i++){
		matrix3DRotationSetFollowingEulerAngle(Matrix[0][i],
											   linfo->InputBase.rotationalMode[i],
									           linfo->InputBase.phi[i],
									           linfo->InputBase.theta[i],
									           linfo->InputBase.psi[i],
									           MATRIX_3D_MODE_INITIALIZE);
	}
	for(i=0; i<linfo->Input.filenum; i++){
		matrix3DRotationSetFollowingEulerAngle(Matrix[1][i],
											   linfo->Input.rotationalMode[i],
									           linfo->Input.phi[i],
									           linfo->Input.theta[i],
									           linfo->Input.psi[i],
									           MATRIX_3D_MODE_INITIALIZE);
	}
	for(i=0; i<linfo->InputBase.filenum; i++){
		matrix3DMultiplyInv(BasedMatrix[0], Matrix[0][i]);
		matrix3DEulerAngleGetFromMatrix3D(Matrix[0][i], linfo->InputBase.rotationalMode[i], &linfo->InputBase.phi[i], &linfo->InputBase.theta[i], &linfo->InputBase.psi[i], 0);
	}
	for(i=0; i<linfo->Input.filenum; i++){
		matrix3DMultiplyInv(BasedMatrix[1], Matrix[1][i]);
		matrix3DEulerAngleGetFromMatrix3D(Matrix[1][i], linfo->Input.rotationalMode[i], &linfo->Input.phi[i], &linfo->Input.theta[i], &linfo->Input.psi[i], 0);
	}

	linfo->Output.filenum = linfo->Input.filenum;
	linfo->Output.rotationalMode = MemoryAllocate(char*, linfo->Input.filenum, "in lCheckOrientationByDegree");
	for(i=0; i<linfo->Output.filenum; i++){
		linfo->Output.rotationalMode[i] = MemoryAllocate(char, 5, "in lCheckOrientationByDegree");
	}
	linfo->Output.phi   = MemoryAllocate(float, linfo->Input.filenum, "in lCheckOrientationByDegree");
	linfo->Output.theta = MemoryAllocate(float, linfo->Input.filenum, "in lCheckOrientationByDegree");
	linfo->Output.psi   = MemoryAllocate(float, linfo->Input.filenum, "in lCheckOrientationByDegree");
	
	Sum = 0;
	for(i=0; i<linfo->Output.filenum; i++){
		stringCopy(linfo->Output.rotationalMode[i], linfo->Input.rotationalMode[i], 4);
		if(linfo->InputBase.phi[i] > linfo->Input.phi[i]){
			linfo->Output.phi[i] = linfo->InputBase.phi[i] - linfo->Input.phi[i];
		}
		else{
			linfo->Output.phi[i] = linfo->Input.phi[i] - linfo->InputBase.phi[i];
		}
		if(linfo->Output.phi[i] > M_PI){
			linfo->Output.phi[i] = 2*M_PI - linfo->Output.phi[i];
		}
		
		if(linfo->InputBase.theta[i] > linfo->Input.theta[i]){
			linfo->Output.theta[i] = linfo->InputBase.theta[i] - linfo->Input.theta[i];
		}
		else{
			linfo->Output.theta[i] = linfo->Input.theta[i] - linfo->InputBase.theta[i];
		}
		if(linfo->Output.theta[i] > M_PI){
			fprintf(stderr, "Something wrong!! Delta Theta is over PI!! %15.6f = %15.6f - %15.6f\n",  
				linfo->Output.theta[i]*DEGREE, linfo->Input.theta[i]*DEGREE, linfo->InputBase.theta[i]*DEGREE);
			exit(EXIT_FAILURE);	
		}
		
		if(linfo->InputBase.psi[i] > linfo->Input.psi[i]){
			linfo->Output.psi[i] = linfo->InputBase.psi[i] - linfo->Input.psi[i];
		}
		else{
			linfo->Output.psi[i] = linfo->Input.psi[i] - linfo->InputBase.psi[i];
		}
		if(linfo->Output.psi[i] > M_PI){
			linfo->Output.psi[i] = 2*M_PI - linfo->Output.psi[i];
		}
		
		Sum += linfo->Output.phi[i] +linfo->Output.theta[i] + linfo->Output.psi[i];
	}
	linfo->DifferentialAve = Sum/(3*linfo->Output.filenum);
}

void
__OutputFileWrite(lCheckOrientationByDegreeInfo* linfo, FILE* fpt, int mode)
{
	int i;

	for(i=0; i<linfo->Output.filenum; i++){
		fprintf(fpt, "%25s %5s %7.2f %7.2f %7.2f\n", linfo->InputBase.filename[i], linfo->Output.rotationalMode[i], 
		                                 linfo->Output.phi[i]*DEGREE, linfo->Output.theta[i]*DEGREE, linfo->Output.psi[i]*DEGREE); 
	}
	fprintf(fpt, "\n");
	fprintf(fpt, "DifferentialAve = %5.2f\n", linfo->DifferentialAve*DEGREE);
}
