/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbTwoProteinFit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbTwoProteinFit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbTwoProteinFit ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "Matrix3D.h"
#include "pdbFile.h"
#include "lpdbSelectedAtom.h"

extern void lpdbTwoProteinFit(Matrix3D Matrix, pdbFile* pdbSelect, pdbFile* refSelect);
extern pdbFileParaTypeReal lpdbCalcRMS(pdbFile* pdb1, pdbFile* pdb2);
extern void lpdbCalcAtomDistance(pdbFile* out, pdbFile* pdb, pdbFile* ref, int mode);
extern void lpdbTemperatureFactorPrint(FILE* fpt, pdbFile* pdb, int mode);

int
main(int argc, char* argv[]) 
{
	int status;
	pdbTwoProteinFitInfo info;
	pdbFile pdb;
	pdbFile ref;
	pdbFile pdbSelect;
	pdbFile refSelect;
	Matrix3D Matrix;
	int pdbNum, refNum;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	pdbFileRead(info.fptIn,  &pdb);
	pdbFileRead(info.fptRef, &ref);

	pdbNum = lpdbSelectedCa(&pdbSelect, &pdb, info.fptInResidue);
	refNum = lpdbSelectedCa(&refSelect, &ref, info.fptRefResidue);

	if(info.flagParam)  {
		fprintf(info.fptParam, "RMSBefore: %f\n", lpdbCalcRMS(&pdb, &ref));
		fprintf(info.fptParam, "RMSSelectedBefore: %f\n", lpdbCalcRMS(&pdbSelect, &refSelect));
	}

	if(pdbNum!=refNum) {
		fprintf(stderr, "The number of pdb (%d)is different from that of ref (%d)\n",
			pdbNum, refNum);
		fprintf(stderr, "Please check selection information\n");
		if(info.flagSelectIn) {
			pdbFileWrite(info.fptSelectIn, &pdbSelect);
		}
		if(info.flagSelectRef) {
			pdbFileWrite(info.fptSelectRef, &refSelect);
		}
		exit(EXIT_FAILURE);
	}
	if(pdbNum<6) {
		fprintf(stderr, "Attention!! The number of selected residues is too small: %d < 6 \n", pdbNum);
	}

	lpdbTwoProteinFit(Matrix, &pdbSelect, &refSelect);

	pdbTrans(&pdb,       Matrix);
	pdbTrans(&pdbSelect, Matrix);

	if(info.flagSelectIn) {
		pdbFileWrite(info.fptSelectIn, &pdbSelect);
	}
	if(info.flagSelectRef) {
		pdbFileWrite(info.fptSelectRef, &refSelect);
	}
	if(info.flagParam)  {
		fprintf(info.fptParam, "RMSSelectedAfter: %f\n", lpdbCalcRMS(&pdbSelect, &refSelect));
		fprintf(info.fptParam, "RMSAfter: %f\n", lpdbCalcRMS(&pdb, &ref));
	}

	pdbFileWrite(info.fptOut, &pdb);
	pdbMatrixFileWrite(info.fptMatrix, Matrix);
	
	if(info.flagoutDis) {
		pdbFile p;

		lpdbCalcAtomDistance(&p, &pdb, &ref, 0);
		pdbFileWrite(info.fptoutDis, &p);
		if(info.flagoutDis2) {
			lpdbTemperatureFactorPrint(info.fptoutDis2, &p,  0);
		}
	}
	return 0; 
}

void
additionalUsage()
{
	USAGEPRINT(">>>> Input and Reference File Format<<<<\n");
	USAGEPRINT("ResidueNumberToBeFitted\n");
	USAGEPRINT("...\n");
	USAGEPRINT("If |, all residules are sellected till the residue in the next line\n");
}

void
lpdbTemperatureFactorPrint(FILE* fpt, pdbFile* pdb, int mode)
{
	int num;
	pdbFileTop(pdb);
	num = 0;
	do {
		if(pdbFileIsCA(pdb)) {
			DEBUGPRINT1("num %d\n", num);
			num++;
			fprintf(fpt, "%05d %15.6f\n", pdb->PDB->ResidueSequenceNumber, pdb->PDB->TemperatureFactor);
		}
	} while(NULL!=pdbFileNext(pdb));
	DEBUGPRINT("End: lpdbTemperatureFactorPrint\n");
	return;
}

void
lpdbCalcAtomDistance(pdbFile* out, pdbFile* pdb, pdbFile* ref, int mode)
{
	DEBUGPRINT2("Start lpdbCalcAtomDistance: %x %x\n", pdb, ref);
	int num;
	pdbFileTop(pdb);
	pdbFileTop(ref);
	DEBUGPRINT2("Top: %x %x\n", pdb->PDB, ref->PDB);
	num = 0;
	do {
		if(pdbFileIsAtom(pdb) && pdbFileIsAtom(ref)) {
			DEBUGPRINT1("num %d\n", num);
			if(0==num) {
				pdbFileNew(out);	
			} else {
				pdbFileAppend(out);	
			}
			num++;
			pdbFileOneRecordCopy(out, ref);
			out->PDB->Coord.x = ref->PDB->Coord.x; 
			out->PDB->Coord.y = ref->PDB->Coord.y; 
			out->PDB->Coord.z = ref->PDB->Coord.z; 
			out->PDB->TemperatureFactor = sqrt(
				 SQR(pdb->PDB->Coord.x - ref->PDB->Coord.x)
				+SQR(pdb->PDB->Coord.y - ref->PDB->Coord.y)
				+SQR(pdb->PDB->Coord.z - ref->PDB->Coord.z));
		}
	} while((NULL!=pdbFileNext(pdb)) && (NULL!=pdbFileNext(ref)));
	DEBUGPRINT("End: lpdbCalcAtomDistance\n");
	return;
}

pdbFileParaTypeReal
lpdbCalcRMS(pdbFile* pdb1, pdbFile* pdb2)
{
	pdbFileParaTypeReal    RMS;
	pdbFileParaTypeInteger num;

	RMS = 0.0;
	pdbFileTop(pdb1);
	num = 0;
	pdbFileTop(pdb2);
	do {
		RMS = RMS
			+SQR(pdb1->PDB->Coord.x-pdb2->PDB->Coord.x)
			+SQR(pdb1->PDB->Coord.y-pdb2->PDB->Coord.y)
			+SQR(pdb1->PDB->Coord.z-pdb2->PDB->Coord.z);
		num++;
	} while((NULL!=pdbFileNext(pdb1)) && (NULL!=pdbFileNext(pdb2)));
	RMS = sqrt(RMS/num);
	return RMS;
}

pdbCoord
lpdbCalcCentreOfGravity(pdbFile* pdb)
{
	pdbCoord               centre;
	pdbFileParaTypeInteger num;

	num = 0;
	centre.x = centre.y =  centre.z = 0.0;
	pdbFileTop(pdb);
	do {
		centre.x += pdb->PDB->Coord.x;
		centre.y += pdb->PDB->Coord.y;
		centre.z += pdb->PDB->Coord.z;
		num++;
	} while(NULL!=pdbFileNext(pdb));
	centre.x /= num;
	centre.y /= num;
	centre.z /= num;
	return centre;
}

void 
lpdbTwoProteinFit(Matrix3D Matrix, pdbFile* pdb, pdbFile* ref)
{
	pdbFileParaTypeReal deltaRMS;
	pdbFileParaTypeReal oldRMS, RMS, minRMS;	
	pdbCoord cpdb, cref;
	pdbCoord theta, mintheta, start, end, delta;
	pdbCoord p, minp, s, e, d;
	Matrix3D tmpMatrix, tmpMatrix0, tmpMatrix1, tmpMatrix2, tmpMatrix3, tmpMatrix4, tmpMatrix5;
	Matrix3D firstMat, endMat;
	pdbFile  tmppdb; 
	long flagMin;
	
	DEBUGPRINT("lpdbTwoProteinFit Start\n");
	matrix3DInit(Matrix);
	RMS  = lpdbCalcRMS(pdb, ref);
	cpdb = lpdbCalcCentreOfGravity(pdb);
	cref = lpdbCalcCentreOfGravity(ref);
	matrix3DTranslationSet(firstMat, cref.x - cpdb.x, 
									 cref.y - cpdb.y, 
									 cref.z - cpdb.z, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(endMat,  -cref.x + cpdb.x, 
									-cref.y + cpdb.y, 
									-cref.z + cpdb.z, MATRIX_3D_MODE_INITIALIZE);
#ifdef DEBUG
	DEBUGPRINT("First Trial\n");
	DEBUGPRINT3("centre: %f %f %f\n", cpdb.x, cpdb.y, cpdb.z);	
	DEBUGPRINT3("centre: %f %f %f\n", cref.x, cref.y, cref.z);	
	pdbMatrixFileWrite(stderr, firstMat);
	DEBUGPRINT("\n");
#endif
	pdbTrans(pdb, firstMat);
	matrix3DMultiplyInv(firstMat, Matrix);

	oldRMS = RMS;
	RMS = lpdbCalcRMS(pdb, ref);

	start.x = start.y = start.z = 0.0;
	end.x = end.y = end.z = 2.0*M_PI;
	delta.x = delta.y = delta.z = 2.0*M_PI/6.0;
	mintheta.x = mintheta.y = mintheta.z = 0;

	s.x = s.y = s.z = -10;
	e.x = e.y = e.z =  10;
	d.x = d.y = d.z =   2;
	minp.x = minp.y = minp.z = 0;
	while(1e-6<fabs(RMS-oldRMS) 
	  && (1e-4<delta.x && 1e-4<delta.y && 1e-4<delta.z)
	  && (1e-2<d.x     && 1e-2<d.y     && 1e-2<d.z)) {
	    oldRMS = RMS;	

		/* Rotation Check */
		flagMin = 0;
		minRMS = oldRMS;
		matrix3DTranslationSet(tmpMatrix0, minp.x, minp.y, minp.z, MATRIX_3D_MODE_INITIALIZE);
		matrix3DTranslationSet(tmpMatrix5,-minp.x,-minp.y,-minp.z, MATRIX_3D_MODE_INITIALIZE);
		pdbTrans(pdb, tmpMatrix0);
		cpdb = lpdbCalcCentreOfGravity(pdb);
		matrix3DTranslationSet(tmpMatrix1,-cpdb.x, -cpdb.y, -cpdb.z, MATRIX_3D_MODE_INITIALIZE);
		matrix3DTranslationSet(tmpMatrix4, cpdb.x,  cpdb.y,  cpdb.z, MATRIX_3D_MODE_INITIALIZE);
		for(theta.x=start.x; theta.x<end.x; theta.x+=delta.x) {
			for(theta.y=start.y; theta.y<end.y; theta.y+=delta.y) {
				for(theta.z=start.z; theta.z<end.z; theta.z+=delta.z) {
					matrix3DRotationSetXYZ(tmpMatrix2,  theta.x,  theta.y,  theta.z, MATRIX_3D_MODE_INITIALIZE);
					matrix3DRotationSetZYX(tmpMatrix3, -theta.x, -theta.y, -theta.z, MATRIX_3D_MODE_INITIALIZE);
					matrix3DInit(tmpMatrix);	
					matrix3DMultiplyInv(tmpMatrix1, tmpMatrix);
					matrix3DMultiplyInv(tmpMatrix2, tmpMatrix);
					matrix3DMultiplyInv(tmpMatrix4, tmpMatrix);
					pdbTrans(pdb, tmpMatrix);
					RMS = lpdbCalcRMS(pdb, ref);
					if(RMS<=minRMS) {
#ifdef DEBUG
						cpdb = lpdbCalcCentreOfGravity(pdb);
						DEBUGPRINT3("centre: %f %f %f\n", cpdb.x, cpdb.y, cpdb.z);	
						DEBUGPRINT5("%f %f %f: %f<=%f\n", theta.x, theta.y, theta.z, RMS, oldRMS);
						pdbMatrixFileWrite(stderr, tmpMatrix);
#endif
						mintheta = theta;
						minRMS = RMS;
						flagMin++;
					}
					matrix3DInit(tmpMatrix);	
					matrix3DMultiplyInv(tmpMatrix1, tmpMatrix);
					matrix3DMultiplyInv(tmpMatrix3, tmpMatrix);
					matrix3DMultiplyInv(tmpMatrix4, tmpMatrix);
					pdbTrans(pdb, tmpMatrix);
				}
			}
		}	
		pdbTrans(pdb, tmpMatrix5);
		if(0==flagMin) {
			fprintf(stderr, "No minimum in rotation\n");
		}
		start.x = mintheta.x - delta.x;
		end.x   = mintheta.x + delta.x;
		delta.x = delta.x/6;
		start.y = mintheta.y - delta.y;
		end.y   = mintheta.y + delta.y;
		delta.y = delta.y/6;
		start.z = mintheta.z - delta.z;
		end.z   = mintheta.z + delta.z;
		delta.z = delta.z/6;

		/* Translation Check */
		matrix3DRotationSetXYZ(tmpMatrix1,  mintheta.x,  mintheta.y,  mintheta.z, MATRIX_3D_MODE_INITIALIZE);
		matrix3DRotationSetZYX(tmpMatrix4, -mintheta.x, -mintheta.y, -mintheta.z, MATRIX_3D_MODE_INITIALIZE);

		pdbTrans(pdb, tmpMatrix1);
		flagMin = 0;
		for(p.x=s.x; p.x<e.x; p.x+=d.x) {
			for(p.y=s.y; p.y<e.y; p.y+=d.y) {
				for(p.z=s.z; p.z<e.z; p.z+=d.z) {
					matrix3DTranslationSet(tmpMatrix2, p.x, p.y, p.z, MATRIX_3D_MODE_INITIALIZE);
					matrix3DTranslationSet(tmpMatrix3,-p.x,-p.y,-p.z, MATRIX_3D_MODE_INITIALIZE);

					pdbTrans(pdb, tmpMatrix2);
					RMS = lpdbCalcRMS(pdb, ref);
					if(RMS<=minRMS) {
						DEBUGPRINT5("%f %f %f: %f<=%f\n", theta.x, theta.y, theta.z, RMS, oldRMS);
						minp = p;
						minRMS = RMS;
						flagMin++;
					}
					pdbTrans(pdb, tmpMatrix3);
				}
			}
		}
		pdbTrans(pdb, tmpMatrix4);

		if(0==flagMin) {
			fprintf(stderr, "No minimum in translation\n");
		}
		s.x = minp.x - d.x;
		e.x = minp.x + d.x;
		d.x = d.x/10;
		s.y = minp.y - d.y;
		e.y = minp.y + d.y;
		d.y = d.y/10;
		s.z = minp.z - d.z;
		e.z = minp.z + d.z;
		d.z = d.z/10;

		RMS = minRMS;
	}
	DEBUGPRINT3("minp: %f %f %f\n", minp.x, minp.y, minp.z);
	matrix3DTranslationSet(tmpMatrix1, minp.x, minp.y, minp.z, MATRIX_3D_MODE_INITIALIZE);
	matrix3DMultiplyInv(tmpMatrix1, Matrix);

	DEBUGPRINT3("mintheta: %f %f %f\n", mintheta.x, mintheta.y, mintheta.z);	
	cpdb = lpdbCalcCentreOfGravity(pdb);
	DEBUGPRINT3("centre: %f %f %f\n", cpdb.x, cpdb.y, cpdb.z);	
	matrix3DTranslationSet(tmpMatrix1,-cpdb.x, -cpdb.y, -cpdb.z, MATRIX_3D_MODE_INITIALIZE);
	matrix3DTranslationSet(tmpMatrix3, cpdb.x,  cpdb.y,  cpdb.z, MATRIX_3D_MODE_INITIALIZE);
	matrix3DRotationSetXYZ(tmpMatrix2, mintheta.x,  mintheta.y,  mintheta.z, MATRIX_3D_MODE_INITIALIZE);
	matrix3DMultiplyInv(tmpMatrix1, Matrix);
	matrix3DMultiplyInv(tmpMatrix2, Matrix);
	matrix3DMultiplyInv(tmpMatrix3, Matrix);

	pdbTrans(pdb, endMat);
#ifdef DEBUG
	pdbMatrixFileWrite(stderr, Matrix);
#endif
}
