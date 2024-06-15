/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbSecondaryStructure ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbSecondaryStructure 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbSecondaryStructure ver%I%; Date:%D% %Z%";
#undef DEBUG
#include <string.h>
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "../inc/pdbFile.h"


int
pdbSecondaryStructureSetFromPDB(pdbFile* pdb, pdbFileSecondaryStructure* second)
{
	second->nSecondaryStructure = 0;	
	pdbFileTop(pdb);
	do {
		if(pdbFileIsSecondaryStructure(pdb)) {
			pdbSecondaryStructureAppend(second);
			if(pdbFileIsHelix(pdb)) {
				second->SecondaryStructure->mode = pdbFileSecondaryStructureModeHelix;
				second->SecondaryStructure->helix = (pdbSecondaryStructureHelix*)memoryAllocate(sizeof(pdbSecondaryStructureHelix),
							"in pdbSecondaryStructureSetFromPDB");
				second->SecondaryStructure->helix->serNum        =  stringGetIntegerDataFromField(pdb->PDB->FullRecord,  8, 10);
				second->SecondaryStructure->helix->helixID       =  stringGetWordFromField       (pdb->PDB->FullRecord, 12, 14);
				second->SecondaryStructure->helix->initResName   =  stringGetWordFromField       (pdb->PDB->FullRecord, 16, 18);
				second->SecondaryStructure->helix->initChainID   = *stringGetWordFromField       (pdb->PDB->FullRecord, 20, 20);
				second->SecondaryStructure->helix->initSeqNum    =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 22, 25);
				second->SecondaryStructure->helix->initICode     = *stringGetWordFromField       (pdb->PDB->FullRecord, 26, 26);
				second->SecondaryStructure->helix->endResName    =  stringGetWordFromField       (pdb->PDB->FullRecord, 28, 30);
				second->SecondaryStructure->helix->endChainID    = *stringGetWordFromField       (pdb->PDB->FullRecord, 32, 32);
				second->SecondaryStructure->helix->endSeqNum     =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 34, 37);
				second->SecondaryStructure->helix->endICode      = *stringGetWordFromField       (pdb->PDB->FullRecord, 38, 38);
				second->SecondaryStructure->helix->helixClass    =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 39, 40);
				second->SecondaryStructure->helix->comment       =  stringGetWordFromField       (pdb->PDB->FullRecord, 41, 70);
				second->SecondaryStructure->helix->length        =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 72, 76);
			} else if(pdbFileIsSheet(pdb)) {
				second->SecondaryStructure->mode  = pdbFileSecondaryStructureModeSheet;
				second->SecondaryStructure->sheet = (pdbSecondaryStructureSheet*)memoryAllocate(sizeof(pdbSecondaryStructureSheet),
							"in pdbSecondaryStructureSetFromPDB");
				second->SecondaryStructure->sheet->strand        =  stringGetIntegerDataFromField(pdb->PDB->FullRecord,  8, 10);
				second->SecondaryStructure->sheet->sheetID       =  stringGetWordFromField       (pdb->PDB->FullRecord, 12, 14);
				second->SecondaryStructure->sheet->numStrands    =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 15, 16);
				second->SecondaryStructure->sheet->initResName   =  stringGetWordFromField       (pdb->PDB->FullRecord, 18, 20);
				second->SecondaryStructure->sheet->initChainID   = *stringGetWordFromField       (pdb->PDB->FullRecord, 22, 22);
				second->SecondaryStructure->sheet->initSeqNum    =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 23, 26);
				second->SecondaryStructure->sheet->initICode     = *stringGetWordFromField       (pdb->PDB->FullRecord, 27, 27);
				second->SecondaryStructure->sheet->endResName    =  stringGetWordFromField       (pdb->PDB->FullRecord, 29, 31);
				second->SecondaryStructure->sheet->endChainID    = *stringGetWordFromField       (pdb->PDB->FullRecord, 33, 33);
				second->SecondaryStructure->sheet->endSeqNum     =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 34, 37);
				second->SecondaryStructure->sheet->endICode      = *stringGetWordFromField       (pdb->PDB->FullRecord, 38, 38);
				second->SecondaryStructure->sheet->sense         =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 39, 40);
				second->SecondaryStructure->sheet->curAtom       =  stringGetWordFromField       (pdb->PDB->FullRecord, 42, 45);
				second->SecondaryStructure->sheet->curResName    =  stringGetWordFromField       (pdb->PDB->FullRecord, 46, 48);
				second->SecondaryStructure->sheet->curChainID    = *stringGetWordFromField       (pdb->PDB->FullRecord, 50, 50);
				second->SecondaryStructure->sheet->curResSeq     =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 51, 54);
				second->SecondaryStructure->sheet->curICode      = *stringGetWordFromField       (pdb->PDB->FullRecord, 55, 55);
				second->SecondaryStructure->sheet->prevAtom      =  stringGetWordFromField       (pdb->PDB->FullRecord, 57, 60);
				second->SecondaryStructure->sheet->prevResName   =  stringGetWordFromField       (pdb->PDB->FullRecord, 61, 63);
				second->SecondaryStructure->sheet->prevChainID   = *stringGetWordFromField       (pdb->PDB->FullRecord, 65, 65);
				second->SecondaryStructure->sheet->prevResSeq    =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 66, 69);
				second->SecondaryStructure->sheet->prevICode     = *stringGetWordFromField       (pdb->PDB->FullRecord, 70, 70);
			} else if(pdbFileIsTurn(pdb)) {
				second->SecondaryStructure->mode = pdbFileSecondaryStructureModeTurn;
				second->SecondaryStructure->turn = (pdbSecondaryStructureTurn*)memoryAllocate(sizeof(pdbSecondaryStructureTurn),
							"in pdbSecondaryStructureSetFromPDB");
				second->SecondaryStructure->turn->serNum        =  stringGetIntegerDataFromField(pdb->PDB->FullRecord,  8, 10);
				second->SecondaryStructure->turn->turnID        =  stringGetWordFromField       (pdb->PDB->FullRecord, 12, 14);
				second->SecondaryStructure->turn->initResName   =  stringGetWordFromField       (pdb->PDB->FullRecord, 16, 18);
				second->SecondaryStructure->turn->initChainID   = *stringGetWordFromField       (pdb->PDB->FullRecord, 20, 20);
				second->SecondaryStructure->turn->initSeqNum    =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 21, 24);
				second->SecondaryStructure->turn->initICode     = *stringGetWordFromField       (pdb->PDB->FullRecord, 25, 25);
				second->SecondaryStructure->turn->endResName    =  stringGetWordFromField       (pdb->PDB->FullRecord, 27, 29);
				second->SecondaryStructure->turn->endChainID    = *stringGetWordFromField       (pdb->PDB->FullRecord, 31, 31);
				second->SecondaryStructure->turn->endSeqNum     =  stringGetIntegerDataFromField(pdb->PDB->FullRecord, 32, 35);
				second->SecondaryStructure->turn->endICode      = *stringGetWordFromField       (pdb->PDB->FullRecord, 36, 36);
				second->SecondaryStructure->turn->comment       =  stringGetWordFromField       (pdb->PDB->FullRecord, 41, 70);
			} else {
				fprintf(stderr, "Not supported: Something wrong\n");
			}	
			DEBUGPRINT1("SECONDARY: %d \n", second->SecondaryStructure->mode);
		}
	} while(NULL!=pdbFileNext(pdb));

	return second->nSecondaryStructure;
}

int
pdbNoSecondaryStructureSetFromPDB(pdbFile* pdb, pdbFileSecondaryStructure* second)
{
	int flagStart;
	pdbFileSecondaryStructureRecord* tmpRecord;
	int count;
	char s[4];
	flagStart = 0;
	count     = 0;
	tmpRecord = NULL;
	pdbFileTop(pdb);
	do {
		if(pdbFileIsCA(pdb)) {
			if(pdbFileSecondaryStructureModeNo==pdbFileWithSecondaryStructure(pdb, second)) {
				if(flagStart==0) { /* Start */
					count++;
					pdbSecondaryStructureAppend(second);
					second->SecondaryStructure->mode = pdbFileSecondaryStructureModeNo;  
					second->SecondaryStructure->no = (pdbSecondaryStructureNo*)memoryAllocate(sizeof(pdbSecondaryStructureNo),
													"in pdbSecondaryStructureSetFromPDB");
					second->SecondaryStructure->no->serNum = count;
					sprintf(s, "%3d", count); 
					second->SecondaryStructure->no->noID   = strdup(s);

					second->SecondaryStructure->no->initResName = strdup(pdb->PDB->ResidueName);
					second->SecondaryStructure->no->initChainID = pdb->PDB->ChainIdentifier;
					second->SecondaryStructure->no->initSeqNum  = pdb->PDB->ResidueSequenceNumber;
					second->SecondaryStructure->no->initICode   = ' ';
					tmpRecord = second->SecondaryStructure;
					flagStart = 1;
				}
			} else {
				if(flagStart==1) {
					pdbFilePrevCA(pdb);
					second->SecondaryStructure = tmpRecord;
					second->SecondaryStructure->no->endResName = strdup(pdb->PDB->ResidueName);
					second->SecondaryStructure->no->endChainID = pdb->PDB->ChainIdentifier;
					second->SecondaryStructure->no->endSeqNum  = pdb->PDB->ResidueSequenceNumber;
					second->SecondaryStructure->no->endICode   = ' ';
					pdbFileNextCA(pdb);
					flagStart = 0;
				}
			}
		}
	} while(NULL!=pdbFileNextCA(pdb));
	return second->nSecondaryStructure; 
}

int
pdbSecondaryStructureAppend(pdbFileSecondaryStructure* second) 
{
	if(second->nSecondaryStructure==0) {
		second->nSecondaryStructure=1;
		second->SecondaryStructure = (pdbFileSecondaryStructureRecord*)memoryAllocate(sizeof(pdbFileSecondaryStructureRecord), 
					"in pdbSecondaryStructureSetFromPDB");
		second->top  = second->SecondaryStructure;
		second->SecondaryStructure->prev = NULL;
		second->SecondaryStructure->next = NULL;
	} else {
		second->nSecondaryStructure++;
		second->SecondaryStructure->next = (pdbFileSecondaryStructureRecord*)
		memoryAllocate(sizeof(pdbFileSecondaryStructureRecord), "in pdbSecondaryStructureSetFromPDB");
		second->SecondaryStructure->next->prev = second->SecondaryStructure;
		second->SecondaryStructure->next->next = NULL;
		second->SecondaryStructure             = second->SecondaryStructure->next;
	}
	return 1;
}


pdbFileSecondaryStructureMode
pdbFileWithSecondaryStructure(pdbFile* pdb, pdbFileSecondaryStructure* second)
{
	if(0==second->nSecondaryStructure) {
		return pdbFileSecondaryStructureModeNo;
	}
	second->SecondaryStructure = second->top;
	while(1) {
		if(second->SecondaryStructure->mode == pdbFileSecondaryStructureModeHelix) {
			if(second->SecondaryStructure->helix->initChainID==pdb->PDB->ChainIdentifier) {	
				if(second->SecondaryStructure->helix->initSeqNum<pdb->PDB->ResidueSequenceNumber
				 &&second->SecondaryStructure->helix->endSeqNum >pdb->PDB->ResidueSequenceNumber) {
					return pdbFileSecondaryStructureModeHelix;
				}
			} 
		}
		if(second->SecondaryStructure->mode == pdbFileSecondaryStructureModeSheet) {
			if(second->SecondaryStructure->sheet->initChainID==pdb->PDB->ChainIdentifier) {	
				if(second->SecondaryStructure->sheet->initSeqNum<pdb->PDB->ResidueSequenceNumber
				 &&second->SecondaryStructure->sheet->endSeqNum >pdb->PDB->ResidueSequenceNumber) {
					return pdbFileSecondaryStructureModeSheet;
				}
			} 
		}
		if(second->SecondaryStructure->mode == pdbFileSecondaryStructureModeTurn) {
			if(second->SecondaryStructure->turn->initChainID==pdb->PDB->ChainIdentifier) {	
				if(second->SecondaryStructure->turn->initSeqNum<pdb->PDB->ResidueSequenceNumber
				 &&second->SecondaryStructure->turn->endSeqNum >pdb->PDB->ResidueSequenceNumber) {
					return pdbFileSecondaryStructureModeTurn;
				}
			} 
		}
		if(NULL==second->SecondaryStructure->next) {
			break;
		} else {
			second->SecondaryStructure = second->SecondaryStructure->next;
		}
	}
	return pdbFileSecondaryStructureModeNo;
}

