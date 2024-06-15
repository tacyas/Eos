/*
# pdbGet.c  1.2
# The latest update : 05/21/97 at 20:15:35
#
#@(#) pdbGet ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : pdbGet 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbGet ver1.2; Date:97/05/21 @(#)";
#include "string.h"
#include "Memory.h"
#include "../inc/pdbFile.h"

static residueName residue[MAX_RESIDUE_NUMBER] = { 
"ALA","A", "VAL","V", "PHE","F", "PRO","P",
"MET","M", "ILE","I", "LEU","L", "ASP","D",
"GLU","E", "LYS","K", "ARG","R", "SER","S",
"THR","T", "TYR","Y", "HIS","H", "CYS","C",
"ASN","N", "GLN","Q", "TRP","W", "GLY","G"
};

long
pdbFileCoordGet(pdbFile* pdb, pdbFileParaTypeReal* x, pdbFileParaTypeReal* y, pdbFileParaTypeReal* z)
{
	if(pdbFileIsAtom(pdb)) {	
		*x = pdb->PDB->Coord.x;
		*y = pdb->PDB->Coord.y;
		*z = pdb->PDB->Coord.z;
	}
	return 0;
}

long
pdbFileCoordCAArrayGet( pdbFile* pdb, 
					    pdbCoord* coordArray,
					    pdbFileParaTypeInteger start, 
					    pdbFileParaTypeInteger number,
					    char                   Chain,
						int mode						
					   )
{
	pdbRecord* orig;
	pdbRecord* tmp;
	int n=0;

	orig = pdb->PDB;

	tmp = pdbFileTop(pdb);
	while(NULL!=tmp) {
		if(pdbFileIsCA(pdb)) {
		}
		tmp = pdbFileNextCA(pdb);
	}

	pdb->PDB = orig;
	return n;
}

long
pdbFileResidueSequenceNumberGet(pdbFile* pdb)
{
	return pdb->PDB->ResidueSequenceNumber;
}

unsigned char
pdbFileChainIdentifierGet(pdbFile* pdb)
{
	return pdb->PDB->ChainIdentifier;
}

char*
pdbFileResidueNameGet(pdbFile* pdb,int mode)
{
	int i;
	if(mode==RESIDUE_THREECHAR_MODE){
		return pdb->PDB->ResidueName;
	}else{
		for(i=0;i<MAX_RESIDUE_NUMBER;i++){
			if(!strcmp(pdb->PDB->ResidueName,residue[i].residueName3)){
				return residue[i].residueName1;
				break;
			}
		}
	}
	return NULL;
}

pdbFileParaTypeReal 
pdbFileTemperatureFactorGet(pdbFile* pdb)
{
	return pdb->PDB->TemperatureFactor;
}
