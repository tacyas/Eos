#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#undef DEBUG       
#include "../inc/config.h"
#include "pdbFile.h"
#include "genUtil.h"
#include "nr2.h"

void lpdbMatrixCreate(Matrix3D Matrix, pdbFile* ref, pdbFile* pdb, long mode);

int
main(int argc, char* argv[])
{
    pdbMatrixCreateInfo info;
    pdbFile pdb;
    pdbFile ref;
	Matrix3D Matrix;
    int i;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
    pdbFileRead(info.fptIn, &pdb);
    pdbFileRead(info.fptRef, &ref);
	lpdbMatrixCreate(Matrix, &ref, &pdb, 0);
	pdbTrans(&pdb, Matrix);
	pdbFileWrite(info.fptOut, &pdb);
	pdbMatrixFileWrite(info.fptMatrix, Matrix);

	return 0;
}

void
additionalUsage(void)
{

}

#define NN (4)
void
lpdbMatrixCreate(Matrix3D Matrix, pdbFile* ref, pdbFile* pdb, long mode)
{

	pdbFileParaTypeInteger rnum, pnum;
	pdbCoord p[NN], r[NN];
	int i, j;
	int* indx;
	float** a;
	float** y;
	float d;
	float* col;

	pdbFileTop(pdb);
	pdbFileTop(ref);
	for(i=0; i<NN; i++) {
		while(!pdbFileEnd(ref)) {
			if(pdbFileIsCA(ref)) {
				pdbFileNext(ref);
				break;
			} else {
				pdbFileNext(ref);
			}
		}
		pdbFileCoordGet(ref, &(r[i].x), &(r[i].y), &(r[i].z));
		DEBUGPRINT4("r[%d]=(%f,%f,%f)\n",i,r[i].x,r[i].y,r[i].z);
		rnum = pdbFileResidueSequenceNumberGet(ref);

		pdbFileTop(pdb);
		while(!pdbFileEnd(pdb)) {
			while(!pdbFileEnd(pdb)) {
				if(pdbFileIsCA(pdb)) {
					break;
				} else {
					pdbFileNext(pdb);
				}
			}
			pnum=pdbFileResidueSequenceNumberGet(pdb);
			if(rnum==pnum) {
				break;
			} else {
				pdbFileNext(pdb);
			}
		}
		if(pdbFileEnd(ref)||pdbFileEnd(pdb)) {
			exit(EXIT_FAILURE);
		}
		pdbFileCoordGet(pdb, &(p[i].x), &(p[i].y), &(p[i].z));
		DEBUGPRINT4("p[%d]=(%f,%f,%f)\n",i,p[i].x,p[i].y,p[i].z);
	}
	
	a = matrix(1, NN, 1, NN);
	y = matrix(1, NN, 1, NN);
	col = vector(1, NN);
	indx = ivector(1, NN);
	for(i=1; i<=NN; i++) {
		a[1][i] = p[i-1].x;
		a[2][i] = p[i-1].y;
		a[3][i] = p[i-1].z;
		a[4][i] = 1.0;
/*
		for(j=1;j<=NN; j++) a[j][i] = 0.0;
		a[i][i] = i;
*/
	}
	ludcmp(a, NN, indx, &d);
	for(j=1; j<=NN; j++) {
		for(i=1; i<=NN; i++) col[i] = 0.0;
		col[j] = 1.0;
		lubksb(a, NN, indx, col);
		for(i=1; i<=NN; i++) y[i][j] = col[i];
	}
	matrix3DInit(Matrix);
	Matrix[0][0] = r[0].x*y[1][1] + r[1].x*y[2][1] + r[2].x*y[3][1] + r[3].x*y[4][1];
	Matrix[1][0] = r[0].x*y[1][2] + r[1].x*y[2][2] + r[2].x*y[3][2] + r[3].x*y[4][2];
	Matrix[2][0] = r[0].x*y[1][3] + r[1].x*y[2][3] + r[2].x*y[3][3] + r[3].x*y[4][3];
	Matrix[0][3] = r[0].x*y[1][4] + r[1].x*y[2][4] + r[2].x*y[3][4] + r[3].x*y[4][4];

	Matrix[0][1] = r[0].y*y[1][1] + r[1].y*y[2][1] + r[2].y*y[3][1] + r[3].y*y[4][1];
	Matrix[1][1] = r[0].y*y[1][2] + r[1].y*y[2][2] + r[2].y*y[3][2] + r[3].y*y[4][2];
	Matrix[2][1] = r[0].y*y[1][3] + r[1].y*y[2][3] + r[2].y*y[3][3] + r[3].y*y[4][3];
	Matrix[1][3] = r[0].y*y[1][4] + r[1].y*y[2][4] + r[2].y*y[3][4] + r[3].y*y[4][4];

	Matrix[0][2] = r[0].z*y[1][1] + r[1].z*y[2][1] + r[2].z*y[3][1] + r[3].z*y[4][1];
	Matrix[1][2] = r[0].z*y[1][2] + r[1].z*y[2][2] + r[2].z*y[3][2] + r[3].z*y[4][2];
	Matrix[2][2] = r[0].z*y[1][3] + r[1].z*y[2][3] + r[2].z*y[3][3] + r[3].z*y[4][3];
	Matrix[2][3] = r[0].z*y[1][4] + r[1].z*y[2][4] + r[2].z*y[3][4] + r[3].z*y[4][4];

}

