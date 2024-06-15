/*
# pdbFileRead.c  1.2
# The latest update : 07/23/96 at 14:28:35
#
#@(#) pdbFileRead ver 1.2
#@(#) Created by 
#@(#)
#@(#) Usage : pdbFileRead 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbFileRead ver1.2; Date:96/07/23 @(#)";
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "../inc/pdbFile.h"

void
pdbFileRead(FILE* fpt, pdbFile* pdb)
{
	pdbFileParaTypeCharacter s[PDB_FILE_RECORD_FULL_LENGTH+3];
	pdbFileParaTypeCharacter* p;
	pdbFileParaTypeCharacter stmp[PDB_FILE_RECORD_FULL_LENGTH+3];
  	pdbFileParaTypeInteger   flag, nAtom;
  
  	flag = 0;
  	nAtom = 0;
  	fseek(fpt, 0L, SEEK_SET);  
  	while(NULL!=fgets(s, PDB_FILE_RECORD_FULL_LENGTH+3, fpt)) {
   		p = s;
    	while('\0'!=*p) {
      		if(*p=='\n') {
				*p = '\0';
				break;
      		}
      		p++;
    	}
    	s[PDB_FILE_RECORD_FULL_LENGTH] = '\0';
	    if(0==flag) {
			pdbFileNew(pdb);
   		   	flag++;
   		 } else {
			pdbFileAppend(pdb);
			flag++;
   		 }
#ifdef DEBUG
		 fprintf(stderr, "%ld\n", flag);
#endif
    	s[PDB_FILE_RECORD_FULL_LENGTH] = '\0';
    	strncpy(pdb->PDB->Record,     s, PDB_FILE_RECORD_LENGTH);
		if(pdbFileIsAtom(pdb)) {
      		strncpy(stmp, s+PDB_FILE_ATOM_NUMBER_START, PDB_FILE_ATOM_NUMBER_LENGTH);
        	*(stmp+PDB_FILE_ATOM_NUMBER_LENGTH) = '\0';
        	pdb->PDB->AtomSerialNumber = atoi(stmp); *stmp = '\0';
      		strncpy(pdb->PDB->AtomName, s+PDB_FILE_ATOM_NAME_START,   PDB_FILE_ATOM_NAME_LENGTH);
      		pdb->PDB->LocationIndicator = *(s+PDB_FILE_LOCATION_START);
      		strncpy(pdb->PDB->ResidueName, s+PDB_FILE_RESIDUE_START,   PDB_FILE_RESIDUE_LENGTH);
      		pdb->PDB->ChainIdentifier = *(s+PDB_FILE_CHAIN_IDENT_START);
      		strncpy(stmp, s+PDB_FILE_RESNUM_START, PDB_FILE_RESNUM_LENGTH);
        	*(stmp+PDB_FILE_RESNUM_LENGTH) = '\0';      
        	pdb->PDB->ResidueSequenceNumber = atoi(stmp); *stmp = '\0';
      		pdb->PDB->InsertionCode = *(s+PDB_FILE_INSERTION_START);
      		strncpy(stmp, s+PDB_FILE_X_START, PDB_FILE_X_LENGTH);
        	*(stmp+PDB_FILE_X_LENGTH) = '\0';      
        	pdb->PDB->Coord.x = atof(stmp); *stmp = '\0';
      		strncpy(stmp, s+PDB_FILE_Y_START, PDB_FILE_Y_LENGTH);
       		*(stmp+PDB_FILE_Y_LENGTH) = '\0';            
        	pdb->PDB->Coord.y = atof(stmp); *stmp = '\0';
      		strncpy(stmp, s+PDB_FILE_Z_START, PDB_FILE_Z_LENGTH);
        	*(stmp+PDB_FILE_Z_LENGTH) = '\0';            
        	pdb->PDB->Coord.z = atof(stmp); *stmp = '\0';
      		strncpy(stmp, s+PDB_FILE_OCCUPANCY_START, PDB_FILE_OCCUPANCY_LENGTH);
        	*(stmp+PDB_FILE_OCCUPANCY_LENGTH) = '\0';            
        	pdb->PDB->Occupancy = atof(stmp); *stmp = '\0';
      		strncpy(stmp, s+PDB_FILE_TEMPERATURE_START, PDB_FILE_TEMPERATURE_LENGTH);
        	*(stmp+PDB_FILE_TEMPERATURE_LENGTH) = '\0';            
        	pdb->PDB->TemperatureFactor = atof(stmp); *stmp = '\0';
      		strncpy(stmp, s+PDB_FILE_FOOT_START, PDB_FILE_FOOT_LENGTH);
        	*(stmp+PDB_FILE_FOOT_LENGTH) = '\0';            
        	pdb->PDB->FootnoteNumber    = atol(stmp); *stmp = '\0';
      		strncpy(pdb->PDB->Footnote, s+PDB_FILE_FOOTNOTE_START, PDB_FILE_FOOTNOTE_LENGTH);
      		strncpy(pdb->PDB->SegID, s+PDB_FILE_SEGID_START, PDB_FILE_SEGID_LENGTH);
      		strncpy(pdb->PDB->Element, s+PDB_FILE_ELEMENT_START, PDB_FILE_ELEMENT_LENGTH);
      		strncpy(pdb->PDB->Charge, s+PDB_FILE_CHARGE_START, PDB_FILE_CHARGE_LENGTH);
      		if(nAtom<pdb->PDB->AtomSerialNumber) {
        		nAtom = pdb->PDB->AtomSerialNumber;
			} else {
				nAtom++;
			}
            pdb->PDB->flagANISOU = 0;
        } else if(pdbFileIsANISOU(pdb)) {
            pdb->PDB->flagANISOU = 1;
            // Same as AtomRecord
      		strncpy(stmp, s+PDB_FILE_ATOM_NUMBER_START, PDB_FILE_ATOM_NUMBER_LENGTH);
        	*(stmp+PDB_FILE_ATOM_NUMBER_LENGTH) = '\0';
        	pdb->PDB->AtomSerialNumber = atoi(stmp); *stmp = '\0';
      		strncpy(pdb->PDB->AtomName, s+PDB_FILE_ATOM_NAME_START,   PDB_FILE_ATOM_NAME_LENGTH);
      		pdb->PDB->LocationIndicator = *(s+PDB_FILE_LOCATION_START);
      		strncpy(pdb->PDB->ResidueName, s+PDB_FILE_RESIDUE_START,   PDB_FILE_RESIDUE_LENGTH);
      		pdb->PDB->ChainIdentifier = *(s+PDB_FILE_CHAIN_IDENT_START);
      		strncpy(stmp, s+PDB_FILE_RESNUM_START, PDB_FILE_RESNUM_LENGTH);
        	*(stmp+PDB_FILE_RESNUM_LENGTH) = '\0';      
        	pdb->PDB->ResidueSequenceNumber = atoi(stmp); *stmp = '\0';
      		pdb->PDB->InsertionCode = *(s+PDB_FILE_INSERTION_START);
            // Different
      		strncpy(stmp, s+PDB_FILE_ANISOU_U11_START, PDB_FILE_ANISOU_U11_LENGTH);
        	*(stmp+PDB_FILE_ANISOU_U11_LENGTH) = '\0';            
            pdb->PDB->U11 = atoi(stmp)*1e-4;
      		strncpy(stmp, s+PDB_FILE_ANISOU_U22_START, PDB_FILE_ANISOU_U22_LENGTH);
        	*(stmp+PDB_FILE_ANISOU_U22_LENGTH) = '\0';            
            pdb->PDB->U22 = atoi(stmp)*1e-4;
      		strncpy(stmp, s+PDB_FILE_ANISOU_U33_START, PDB_FILE_ANISOU_U33_LENGTH);
        	*(stmp+PDB_FILE_ANISOU_U33_LENGTH) = '\0';            
            pdb->PDB->U33 = atoi(stmp)*1e-4;
      		strncpy(stmp, s+PDB_FILE_ANISOU_U12_START, PDB_FILE_ANISOU_U12_LENGTH);
        	*(stmp+PDB_FILE_ANISOU_U12_LENGTH) = '\0';            
            pdb->PDB->U12 = atoi(stmp)*1e-4;
      		strncpy(stmp, s+PDB_FILE_ANISOU_U13_START, PDB_FILE_ANISOU_U13_LENGTH);
        	*(stmp+PDB_FILE_ANISOU_U13_LENGTH) = '\0';            
            pdb->PDB->U13 = atoi(stmp)*1e-4;
      		strncpy(stmp, s+PDB_FILE_ANISOU_U23_START, PDB_FILE_ANISOU_U23_LENGTH);
        	*(stmp+PDB_FILE_ANISOU_U23_LENGTH) = '\0';            
            pdb->PDB->U23 = atoi(stmp)*1e-4;
            // Same as AtomRecord
      		strncpy(stmp, s+PDB_FILE_FOOT_START, PDB_FILE_FOOT_LENGTH);
        	*(stmp+PDB_FILE_FOOT_LENGTH) = '\0';            
        	pdb->PDB->FootnoteNumber    = atol(stmp); *stmp = '\0';
      		strncpy(pdb->PDB->Footnote, s+PDB_FILE_FOOTNOTE_START, PDB_FILE_FOOTNOTE_LENGTH);
            // Connect
            if(pdb->PDB->prev->AtomSerialNumber == pdb->PDB->AtomSerialNumber) {
                pdb->PDB->pAtomforANISOU = pdb->PDB->prev;
            } else {
                pdb->PDB->pAtomforANISOU = NULL;
            }
    	} else {
        	strncpy(pdb->PDB->FullRecord, s, PDB_FILE_RECORD_FULL_LENGTH);
    	}
    	s[0] = '\0';
  	}
  	pdb->nAtom = nAtom;
    pdbSecondaryStructureSetFromPDB(pdb, &(pdb->second));	
}
