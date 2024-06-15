/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbPCA ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbPCA
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbPCA ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Array.h"
#include "Matrix3D.h"
#include "pdbFile.h"

int
main(int argc, char* argv[]) 
{
	pdbPCAInfo info;
	pdbFile pdb;
	Array C;
	Array u;
	Array lambda;
	Array X;
	Array average;
	int n;
	pdbFileParaTypeReal x, y, z;
	Matrix3D mat;
	int i, j;
	double sum;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdb);

	pdbFileTop(&pdb);
	n = 0;
	while(!pdbFileEnd(&pdb)) {
		if(pdbFileIsAtom(&pdb)) {
			n++;
		}
		pdbFileNext(&pdb);
	}
	X.dim = 2;	
	X.n[0] = 3;
	X.n[1] = n;
	arrayInit(&X, "X in main");
	
	pdbFileTop(&pdb);
	n = 0;
	while(!pdbFileEnd(&pdb)) {
		if(pdbFileIsAtom(&pdb)) {
			pdbFileCoordGet(&pdb, &x, &y, &z);
			arrayDataSet2(X, 0, n, x);	
			arrayDataSet2(X, 1, n, y);	
			arrayDataSet2(X, 2, n, z);	
			n++;
		}
		pdbFileNext(&pdb);
	}
	arrayPCA(&u, &C, &lambda, &X, &average, 0);

	/* Output */
	fprintf(info.fptOut, "Result\n");
	fprintf(info.fptOut, "C: covariance matrix\n");
	arrayWriteToFile(info.fptOut, &C, "in main");
	fprintf(info.fptOut, "u: unit vector\n");
	arrayWriteToFile(info.fptOut, &u, "in main");
	fprintf(info.fptOut, "lambda^2: lambda^2\n");
	arrayWriteToFile(info.fptOut, &lambda, "in main");
	fprintf(info.fptOut, "Averege: Center Position\n");
	arrayWriteToFile(info.fptOut, &average, "in main");
	fprintf(info.fptOut, "Normalized lambda^2: lambda^2\n");
	sum  = arrayDataGet1(lambda, 0);
	sum += arrayDataGet1(lambda, 1);
	sum += arrayDataGet1(lambda, 2);
	fprintf(info.fptOut, "%15.6f ", arrayDataGet1(lambda, 0)/sum);
	fprintf(info.fptOut, "%15.6f ", arrayDataGet1(lambda, 1)/sum);
	fprintf(info.fptOut, "%15.6f \n", arrayDataGet1(lambda, 2)/sum);

	if(info.flagOutUnit) {
		arrayWriteToFile(info.fptOutUnit, &u, "in main");
	}

	if(info.flagOutMat3D || info.flagOutPDB) {
		matrix3DInit(mat);
		for(i=0; i<u.n[0]; i++) {
		for(j=0; j<u.n[1]; j++) {
			mat[i][j] = arrayDataGet2(u, i, j);
		}
		}
	}

	if(info.flagOutMat3D) {
		matrix3DFileWrite(info.fptOutMat3D, mat);
	}

	if(info.flagOutPDB) {
		pdbTrans(&pdb, mat);
		pdbFileWrite(info.fptOutPDB, &pdb);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


