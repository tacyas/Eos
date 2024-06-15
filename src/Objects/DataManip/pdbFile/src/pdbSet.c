/*
# pdbSet.c  1.1
# The latest update : 07/13/96 at 11:39:18
#
#@(#) pdbSet ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : pdbSet 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbSet ver1.1; Date:96/07/13 @(#)";
#include "../inc/pdbFile.h"
#include "genUtil.h"
#include "eosString.h"

void
pdbFileChainIdentifierSetAll(pdbFile* pdb, unsigned char c)
{
	pdbRecord* tmp;

	tmp = pdb->PDB;
	pdbFileTop(pdb);
	do {
		pdbFileChainIdentifierSet(pdb, c);
	} while(NULL!=pdbFileNext(pdb));
	pdb->PDB = tmp;
}

void
pdbFileChainIdentifierSet(pdbFile* pdb, unsigned char c)
{
	if(pdbFileIsAtom(pdb)) {
		pdb->PDB->ChainIdentifier = c;
	}
}

void
pdbFileTemperatureFactorSet(pdbFile* pdb, double data)
{
	if(pdbFileIsAtom(pdb)) {
		pdb->PDB->TemperatureFactor = data;
	}
}

void
pdbFileOccupancySet(pdbFile* pdb, double data)
{
	if(pdbFileIsAtom(pdb)) {
		pdb->PDB->Occupancy = data;
	}
}

long
pdbFileCoordSet(pdbFile* pdb, pdbFileParaTypeReal x, pdbFileParaTypeReal y, pdbFileParaTypeReal z)
{
	if(pdbFileIsAtom(pdb)) {	
		pdb->PDB->Coord.x = x;
		pdb->PDB->Coord.y = y;
		pdb->PDB->Coord.z = z;
	}
	return 0;
}

void
pdbFileResidueSequenceNumberIncrementAll(pdbFile* pdb, int i)
{
	pdbRecord* tmp;

	tmp = pdb->PDB;
	pdbFileTop(pdb);
	do {
		pdbFileResidueSequenceNumberIncrement(pdb, i);
	} while(NULL!=pdbFileNext(pdb));
	pdb->PDB = tmp;
}

void
pdbFileResidueSequenceNumberIncrement(pdbFile* pdb, int i)
{
	if(pdbFileIsAtom(pdb)) {
		pdb->PDB->ResidueSequenceNumber += i;
	}
}
