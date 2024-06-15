/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbCrystalCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbCrystalCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbCrystalCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "Matrix3D.h"
#include "Crystal.h"

typedef struct lpdbCrystalCreateInfo {
	CrystalInfo crystalInfo;	
} lpdbCrystalCreateInfo;

void lpdbCrystalCreateInfoSet(lpdbCrystalCreateInfo* linfo, pdbCrystalCreateInfo info, int mode);
void lpdbCrystalCreate(pdbFile* pdbOut, pdbFile* pdbIn, lpdbCrystalCreateInfo* linfo, int mode);
void lpdbCrystalCreateP1(pdbFile* pdbOut, pdbFile* pdbIn, lpdbCrystalCreateInfo* linfo, int mode);

int
main(int argc, char* argv[]) 
{
	pdbCrystalCreateInfo info;
	lpdbCrystalCreateInfo linfo;
	static pdbFile pdbIn;
	static pdbFile pdbOut;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	lpdbCrystalCreateInfoSet(&linfo, info, 0); 
	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdbIn);

	lpdbCrystalCreate(&pdbOut, &pdbIn, &linfo, 0);

	pdbFileWrite(info.fptOut, &pdbOut);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- CrystalInfo -----\n");
	crystalInfoFileFormat(stderr, 0);
	fprintf(stderr, "----- CrystalSpaceGroup -----\n");
	crystalSpaceGroupPrint(stderr, 0);
}

void
lpdbCrystalCreateInfoSet(lpdbCrystalCreateInfo* linfo, pdbCrystalCreateInfo info, int mode)
{
	crystalInfoRead(info.fptInfo, &linfo->crystalInfo, mode);
	crystalInfoWrite(stdout, &linfo->crystalInfo, mode);
}

void 
lpdbCrystalCreate(pdbFile* pdbOut, pdbFile* pdbIn, lpdbCrystalCreateInfo* linfo, int mode)
{
	switch(linfo->crystalInfo.SpaceGroup) {
		case CrystalSpaceGroupP1: {
			lpdbCrystalCreateP1(pdbOut, pdbIn, linfo, mode);
			break;
		}
		default: {
			fprintf(stderr, "Not supported Space Group: %5d %s\n", 
				linfo->crystalInfo.SpaceGroup, 
				CrystalSpaceGroupString[linfo->crystalInfo.SpaceGroup]);
			break;
		}
	}
}



void 
lpdbCrystalCreateP1(pdbFile* pdbOut, pdbFile* pdbIn, lpdbCrystalCreateInfo* linfo, int mode)
{
	CrystalInfo crystal;
	int ia, ib, ic;
	matrix3DParaTypeReal x, y, z;
	static pdbFile tmpPDB;
	Matrix3D M;

	crystal = linfo->crystalInfo;
	for(ia=crystal.StartN.a; ia < crystal.N.a + crystal.StartN.a; ia++) {
	for(ib=crystal.StartN.b; ib < crystal.N.b + crystal.StartN.b; ib++) {
	for(ic=crystal.StartN.c; ic < crystal.N.c + crystal.StartN.c; ic++) {
		pdbFileNew(&tmpPDB);
		pdbFileCopyAll(&tmpPDB, pdbIn);
		/* 
			newposition = aAxis*ia + bAxis*ib + cAxis*ic
		*/
		x = crystal.aAxis.x*ia + crystal.bAxis.x*ib +  crystal.cAxis.x*ic;
		y = crystal.aAxis.y*ia + crystal.bAxis.y*ib +  crystal.cAxis.y*ic;
		z = crystal.aAxis.z*ia + crystal.bAxis.z*ib +  crystal.cAxis.z*ic;
		
		x += crystal.Origin.x;
		y += crystal.Origin.y;
		z += crystal.Origin.z;
		DEBUGPRINT3("%d %d %d\n", ia, ib, ic);
		DEBUGPRINT3("%g %g %g\n", x, y, z);
		matrix3DTranslationSet(M, x, y, z, MATRIX_3D_MODE_INITIALIZE);
		pdbTrans(&tmpPDB,  M);
		
		pdbFileAppendAll(pdbOut, &tmpPDB);	
		DEBUGPRINT("pdbFileGoToEnd")
		pdbFileGoToEnd(pdbOut);
		DEBUGPRINT1("PDB: %d\n", *(pdbOut->PDB));
		pdbFileFree(&tmpPDB);
	}
	}
	}
}

