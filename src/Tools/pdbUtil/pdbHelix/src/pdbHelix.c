/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbHelix ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbHelix
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbHelix ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
       
#include "../inc/config.h"
#include "Random.h"
#include "Matrix3D.h"
#include "pdbFile.h"
#include "lpdb2mrcInfo.h"
#define DEBUG
#include "genUtil.h"

extern void pdbHelixMatrixCreateForHelix(Matrix3D Matrix, pdbFileParaTypeReal dz, pdbFileParaTypeReal dphi);
extern void pdbHelixMatrixCreateForHelix2(Matrix3D Matrix, pdbFileParaTypeReal dz, pdbFileParaTypeReal dphi, pdbFileParaTypeReal ddphi);

#include "pdbInfoGet.h"

void
main(int argc, char* argv[])
{
    pdbHelixInfo info;
    pdbFile pdb;
	Matrix3D Matrix;
	Matrix3D MatrixInv;
	mrcImage mrc3d;
	mrcImage mrc2d;
	lpdb2mrc2dInfo lpdbinfo;
 	lpdb2mrc3dInfo lpdbinfo3;
	pdbInfoData pdbinfo;
    int i;
	time_t t;
	float x, y, z;
	double data;
   	char ID;

    init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	srand(time(&t));
    pdbHelixMatrixCreateForHelix(Matrix,     info.delz,  info.delphi*RADIAN);
    pdbHelixMatrixCreateForHelix(MatrixInv, -info.delz, -info.delphi*RADIAN);
    pdbFileRead(info.fptIn, &pdb);
	ID = info.startID;
	pdbFileChainIdentifierSetAll(&pdb, ID);

	if(info.flagstartn) {
		if(0<info.startn) {
			for(i=0; i<info.startn; i++) {
				pdbTrans(&pdb, Matrix);
			}
		} else {
			fprintf(stderr, "startn is negative\n");
			for(i=0; info.startn<i; i--) {
				DEBUGPRINT1("%d\n", i);
				pdbTrans(&pdb, MatrixInv);
			}
		}
	}
    pdbFileWrite(info.fptOut, &pdb);

	pdbInfoGet(&pdb, &pdbinfo, 0);
	DEBUGPRINT4("%f %f %f: %f\n", pdbinfo.cx, pdbinfo.cy, pdbinfo.cz, pdbinfo.distance);
	if(info.flagOut3D) {
	  DEBUGPRINT("mrc3d \n");
		if(info.flagStartx) {
			lpdbinfo3.sx = info.Startx;
		} else {
			lpdbinfo3.sx = -(MAX(fabs(pdbinfo.cx), fabs(pdbinfo.cy)) + pdbinfo.distance)*1.5;
		}
		if(info.flagStarty) {
			lpdbinfo3.sy = info.Starty;
		} else {
			lpdbinfo3.sy = -(MAX(fabs(pdbinfo.cx), fabs(pdbinfo.cy)) + pdbinfo.distance)*1.5;
		}
		if(info.flagStartz) {
			lpdbinfo3.sz = info.Startz;
		} else {
			lpdbinfo3.sz = pdbinfo.cz;
		}
		if(info.flagnx) {
			lpdbinfo3.nx = info.nx;
		} else {
			lpdbinfo3.nx = 2.0*fabs(lpdbinfo3.sx)/info.dx;
		}
		if(info.flagny) {
			lpdbinfo3.ny = info.ny;
		} else {
			lpdbinfo3.ny = 2.0*fabs(lpdbinfo3.sy)/info.dy;
		}
		if(info.flagnz) {
			lpdbinfo3.nz = info.nz;
		} else {
			lpdbinfo3.nz = (info.nMolecule-1)*info.delz/info.dz;
		}
		lpdbinfo3.dx = info.dx;
		lpdbinfo3.dy = info.dy;
		lpdbinfo3.dz = info.dz;
		lpdbinfo3.Weight = info.Weight;
		DEBUGPRINT("pdb2mrc3d ");
		lpdb2mrc3d(&mrc3d, &pdb, &lpdbinfo3, 0);
		DEBUGPRINT("done\n");
	}
	if(info.flagOut2D) {
		if(info.flagStarty) {
			lpdbinfo.sx = info.Starty; 
		} else {
			lpdbinfo.sx = -(fabs(pdbinfo.cy) + pdbinfo.distance)*1.5;
		}
		if(info.flagStartz) {
			lpdbinfo.sy = info.Startz;
		} else {
			lpdbinfo.sy = pdbinfo.cz;
		}
		lpdbinfo.dx = info.dy;
		lpdbinfo.dy = info.dz;
		if(info.flagny) {
			lpdbinfo.nx = info.ny;
		} else {
			lpdbinfo.nx = fabs(lpdbinfo.sx)*2.0/info.dy;
		}
		if(info.flagnz) {
			lpdbinfo.ny = info.nz;
		} else {
			lpdbinfo.ny = (info.nMolecule-1)*info.delz/info.dz;
		}
		lpdbinfo.Weight = info.Weight;
		DEBUGPRINT5("s: %f %f, n; %d %d, W: %f\n", lpdbinfo.sx, lpdbinfo.sy, lpdbinfo.nx, lpdbinfo.ny, lpdbinfo.Weight);
		lpdb2mrc2d(&mrc2d, &pdb, &lpdbinfo, 'x', 0); 
	}
    for(i=1; i<info.nMolecule; i++) {
        fprintf(stderr, "%d \n", i+1);
        pdbTrans(&pdb, Matrix);
		ID++;
		DEBUGPRINT1("Current Chain: %c\n", ID);
		pdbFileChainIdentifierSetAll(&pdb, ID);
		if(info.flagdeltaSeq) {
			/* info.deltaSeq : 1000 */
			pdbFileResidueSequenceNumberIncrementAll(&pdb, info.deltaSeq);
		}
		if(info.flagdeldelphi) {
    		pdbHelixMatrixCreateForHelix2(Matrix, info.delz, info.delphi*RADIAN, info.deldelphi*RADIAN);
		}
	  	if(info.flagOut) {		
    	    pdbFileWrite(info.fptOut, &pdb);
		}
		if(info.flagOut3D) {
			lpdb2mrc3d(&mrc3d, &pdb, &lpdbinfo3, 1);
		}
		if(info.flagOut2D) {
			DEBUGPRINT1("Out2D: %d\n", i);
			lpdb2mrc2d(&mrc2d, &pdb, &lpdbinfo, 'x', 1); 
		}
    }

	if(info.flagOut3D) {
		mrcFileWrite(&mrc3d, info.Out3D, "in main", 0);	
	}
	if(info.flagOut2D) {
		mrcFileWrite(&mrc2d, info.Out2D, "in main", 0);	
	}
}

void
additionalUsage(void)
{

}

void
pdbHelixMatrixCreateForHelix(Matrix3D Matrix, pdbFileParaTypeReal dz, pdbFileParaTypeReal dphi)
{
	matrix3DRotationSet(Matrix, 'z', dphi, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(Matrix, 0.0, 0.0, dz, MATRIX_3D_MODE_NOT_INITIALIZE);
}

void
pdbHelixMatrixCreateForHelix2(Matrix3D Matrix, pdbFileParaTypeReal dz, pdbFileParaTypeReal dphi, pdbFileParaTypeReal ddphi)
{
	dphi = dphi+ddphi*randomNormalGet(2);
	matrix3DRotationSet(Matrix, 'z', dphi, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(Matrix, 0.0, 0.0, dz, MATRIX_3D_MODE_NOT_INITIALIZE);
}
