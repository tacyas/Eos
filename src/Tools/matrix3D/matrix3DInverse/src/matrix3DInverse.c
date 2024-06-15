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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Matrix3D.h"
#include "Memory.h"
#include "eosString.h"

/*
Example:
typedef struct lmatrix3DInverseInfo {
	float a;
	int   b;
} lmatrix3DInverseInfo;

typedef enum lmatrix3DInverseMode {
	a=0,
	b=1
} lmatrix3DInverseMode;
*/

extern void lmatrix3DInverse(double** outMatrix, double** inMatrix, int mode);
extern void FileRead(FILE* fpt, double** Matrix);
extern void FileWrite(FILE* fpt, double** Matrix);
extern void inv1(double* a, int n, int nn);

int
main(int argc, char* argv[]) 
{
	matrix3DInverseInfo info;
	double**            inMatrix;
	double**            outMatrix;
	int                 i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	inMatrix = (double **)memoryAllocate(sizeof(double*)*4, "in main");
	for(i=0; i<4; i++){
		inMatrix[i] = (double *)memoryAllocate(sizeof(double)*4, "in main");
	}

	FileRead(info.fptIn, inMatrix);

	outMatrix  = (double **)memoryAllocate(sizeof(double*)*4, "in lmatrix3DInverse");
	for(i=0; i<4; i++){
		outMatrix[i]  = (double *)memoryAllocate(sizeof(double)*4, "in lmatrix3DInverse");
	}
	lmatrix3DInverse(outMatrix, inMatrix, info.mode);
	FileWrite(info.fptOut, outMatrix);
	
	free(inMatrix);
	free(outMatrix);
	DEBUGPRINT("Program end\n");
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lmatrix3DInverse(double** outMatrix, double** inMatrix, int mode)
{
	int    i, j, k;
	double workMatrix[4][4];

/*
	outMatrix  = (double **)memoryAllocate(sizeof(double*)*4, "in lmatrix3DInverse");
	for(i=0; i<4; i++){
		outMatrix[i]  = (double *)memoryAllocate(sizeof(double)*4, "in lmatrix3DInverse");
	}
*/
	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		workMatrix[i][j] = inMatrix[i][j];
		outMatrix[i][j]  = 0;
	}
	}

	inv1(workMatrix, 4, 4);

	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		outMatrix[i][j] = workMatrix[i][j];
	}
	}
		
	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		DEBUGPRINT1("%15.6f ", inMatrix[i][j]);
	}
	DEBUGPRINT("\n");
	}
	DEBUGPRINT("\n");
	DEBUGPRINT("\n");

	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		DEBUGPRINT1("%15.6f ", outMatrix[i][j]);
	}
	DEBUGPRINT("\n");
	}
	DEBUGPRINT("\n");
	DEBUGPRINT("\n");
	
	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		workMatrix[i][j] = 0;
		for(k=0; k<4; k++){
			workMatrix[i][j] += outMatrix[i][k]*inMatrix[k][j];
		}
	}
	}

	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		DEBUGPRINT1("%15.6f ", workMatrix[j][i]);
	}
	DEBUGPRINT("\n");
	}
	DEBUGPRINT("\n");
	DEBUGPRINT("\n");
}

void
inv1(double* a, int n ,int nn)
{
	int i,j,k;
	double p,q;
	double *ak,*ai;

	for(k=0, ak=a; k<n; ++k, ak+=nn){
		p=ak[k];
		ak[k]=1.0;
		for(j=0; j<n; ++j){
			ak[j] /= p;
		}
		for(i=0, ai=a; i<n; ++i, ai+=nn){
			if(i!=k){
				q     = ai[k];
				ai[k] = 0.0;
			for(j=0; j<n; ++j){
				ai[j] -= q*ak[j];
			}
			}
		}
	}
}

void
FileRead(FILE* fpt, double** Matrix)
{
	char s[1024];
	int i, j;

	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<4; i++){
		if(NULL!=stringGetFromFile(s, "", fpt, stdout, 1)){
			for(j=0; j<4; j++){
				Matrix[i][j] = stringGetNthRealData(s, j+1, " \t,");
			}
		}
		else{
			fprintf(stderr, "Matrix File is Wrong!!\n");
			exit(EXIT_FAILURE);
		}
	}
}

void
FileWrite(FILE* fpt, double** Matrix)
{
	int i, j;

	fseek(fpt, 0L, SEEK_SET);
	for(i=0; i<4; i++){
	for(j=0; j<4; j++){
		fprintf(fpt, "%15.6f ",Matrix[i][j]);
	}
		fprintf(fpt, "\n");
	}
}
