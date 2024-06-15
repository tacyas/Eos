/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbUtil ver%I%; Date:%D% %Z%";
#undef DEBUG 
#include "genUtil.h"
#include "string.h"
#include "Memory.h"
#include "../inc/pdbFile.h"

pdbRecord* 
pdbFileFree(pdbFile* pdb)
{
	pdbRecord* tmp;

	tmp = pdbFileTop(pdb);
	while(tmp!=NULL) {
		if(pdbFileEnd(pdb)) {
			free(pdb->PDB);
			pdb->PDB = NULL;
		} else {
			pdbFileNext(pdb);
			free(pdb->PDB->prev);
		}
		tmp = pdb->PDB;
	}
	pdb->top = NULL;
	return pdb->PDB;
}

pdbRecord*
pdbFileTop(pdbFile* pdb)
{
	pdb->PDB = pdb->top;
	return pdb->PDB;
}

pdbRecord*
pdbFileTopPointer(pdbFile* pdb)
{
	return pdb->top;
}


pdbRecord*
pdbFileNext(pdbFile* pdb)
{
	if(pdbFileEnd(pdb)) {
		return NULL;
	} else {
		pdb->PDB = pdb->PDB->next;
	}
	return pdb->PDB;
}

pdbRecord*
pdbFileNextAtom(pdbFile* pdb)
{
	if(NULL==pdbFileNext(pdb)){
		return NULL;
	}
	while(!pdbFileIsAtom(pdb)){
		if(NULL==pdbFileNext(pdb)){
			return NULL;
		}
	}
	return pdb->PDB;
}

pdbRecord*
pdbFileNextCA(pdbFile* pdb)
{
	if(NULL==pdbFileNext(pdb)){
		return NULL;
	}
	while(!pdbFileIsCA(pdb)){
		if(NULL==pdbFileNext(pdb)){
			return NULL;
		}
	}
	return pdb->PDB;
}

pdbRecord*
pdbFileNextProtein(pdbFile* pdb)
{
	if(NULL==pdbFileNext(pdb)){
		return NULL;
	}
	while(!pdbFileIsEndLine(pdb)){
		if(NULL==pdbFileNext(pdb)){
			return NULL;
		}
	}
	pdbFileNext(pdb);
	return pdb->PDB;
}

long
pdbFileEnd(pdbFile* pdb)
{
	if(NULL==pdb->PDB->next) {
		return 1;
	}
	return 0;
}

long
pdbFileGoToEnd(pdbFile* pdb)
{
	while(!pdbFileEnd(pdb)) {	
		pdbFileNext(pdb);	
	}
	return 0;
}

pdbRecord*
pdbFilePrev(pdbFile* pdb)
{
	pdb->PDB = pdb->PDB->prev;
	return pdb->PDB;
}

pdbRecord*
pdbFilePrevAtom(pdbFile* pdb)
{
	if(NULL==pdbFilePrev(pdb)){
		return NULL;
	}
	while(!pdbFileIsAtom(pdb)){
		if(NULL==pdbFilePrev(pdb)){
			return NULL;
		}
	}
	return pdb->PDB;
}

pdbRecord*
pdbFilePrevCA(pdbFile* pdb)
{
	if(NULL==pdbFilePrev(pdb)){
		return NULL;
	}
	while(!pdbFileIsCA(pdb)){
		if(NULL==pdbFilePrev(pdb)){
			return NULL;
		}
	}
	return pdb->PDB;
}

long 
pdbFileIsEndLine(pdbFile* pdb) 
{
	if(0==strncmp(pdb->PDB->Record, pdbRecordEnd, PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsAtom(pdbFile* pdb)
{
	if(   0==strncmp(pdb->PDB->Record, pdbRecordAtom, PDB_FILE_RECORD_LENGTH)
	    ||0==strncmp(pdb->PDB->Record, pdbRecordHeteroAtom, PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsANISOU(pdbFile* pdb)
{
	if(0==strncmp(pdb->PDB->Record, pdbRecordANISOU, PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsSecondaryStructure(pdbFile* pdb)
{
	if(   0==strncmp(pdb->PDB->Record, pdbRecordHelix, PDB_FILE_RECORD_LENGTH)
	    ||0==strncmp(pdb->PDB->Record, pdbRecordSheet, PDB_FILE_RECORD_LENGTH)
	    ||0==strncmp(pdb->PDB->Record, pdbRecordTurn,  PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsHelix(pdbFile* pdb)
{
	if(0==strncmp(pdb->PDB->Record, pdbRecordHelix, PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsSheet(pdbFile* pdb)
{
	if(0==strncmp(pdb->PDB->Record, pdbRecordSheet, PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsTurn(pdbFile* pdb)
{
	if(0==strncmp(pdb->PDB->Record, pdbRecordTurn, PDB_FILE_RECORD_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsCA(pdbFile* pdb)
{
	if(0==strncmp(pdb->PDB->AtomName, " CA ", PDB_FILE_ATOM_NAME_LENGTH)) {
		return 1;
	}
	return 0;
}

long
pdbFileIsNegative(pdbFile* pdb)
{
	char *tmpName;
	tmpName=pdbFileResidueNameGet(pdb,RESIDUE_ONECHAR_MODE);

	if((0==strncmp(tmpName,"D",1))||(0==strncmp(tmpName,"E",1))) {
		return 1;
	}
	return 0;
}

long
pdbFileIsPositive(pdbFile* pdb)
{
	char *tmpName;
	tmpName=pdbFileResidueNameGet(pdb,RESIDUE_ONECHAR_MODE);

	if((0==strncmp(tmpName,"K",1))||(0==strncmp(tmpName,"R",1))) {
		return 1;
	}
	return 0;
}

long
pdbFileIsCharge(pdbFile* pdb)
{
	char *tmpName;
	tmpName=pdbFileResidueNameGet(pdb,RESIDUE_ONECHAR_MODE);

	if((0==strncmp(tmpName,"K",1))||(0==strncmp(tmpName,"R",1))
||	(0==strncmp(tmpName,"D",1))||(0==strncmp(tmpName,"E",1))) {
		return 1;
	}
	return 0;
}

pdbRecord* 
pdbFileNew(pdbFile* pdb)
{
	pdb->PDB = (pdbRecord*)memoryAllocate(sizeof(pdbRecord), "in pdbFileNew");
	memset(pdb->PDB, 0, sizeof(pdbRecord));
	pdb->top = pdb->PDB;
	DEBUGPRINT1("pdbFileNew: %d\n", pdb->top);
	pdb->PDB->next = pdb->PDB->prev = NULL;
	return pdb->PDB;
}

pdbRecord*
pdbFileAppend(pdbFile* pdb)
{
	pdbRecord* tmprecord;
	tmprecord = (pdbRecord*)memoryAllocate(sizeof(pdbRecord), "in pdbFileAppend");
	memset(tmprecord, 0, sizeof(pdbRecord));
	tmprecord->prev = pdb->PDB;
	tmprecord->next = pdb->PDB->next;
	pdb->PDB->next  = tmprecord;
	pdb->PDB        = pdb->PDB->next;

	return pdb->PDB;
}

pdbRecord*
pdbFileRecordPrint(FILE* fpt, pdbFile* pdb)
{
  	if(pdbFileIsAtom(pdb)) {
   		fprintf(fpt, "%6s%5ld %4s%c%3s %c%4ld%c   %8.3f%8.3f%8.3f%6.2f%6.2f %3ld%10s\n",
	      pdb->PDB->Record,
	      pdb->PDB->AtomSerialNumber,
	      pdb->PDB->AtomName,
	      pdb->PDB->LocationIndicator, 
	      pdb->PDB->ResidueName,
	      pdb->PDB->ChainIdentifier,
	      pdb->PDB->ResidueSequenceNumber,
	      pdb->PDB->InsertionCode,
	      pdb->PDB->Coord.x,
      	      pdb->PDB->Coord.y,
      	      pdb->PDB->Coord.z,
	      pdb->PDB->Occupancy,
	      pdb->PDB->TemperatureFactor,
	      pdb->PDB->FootnoteNumber,
	      pdb->PDB->Footnote);
  	} else if(pdbFileIsANISOU(pdb)) {
        fprintf(fpt, "%6s%5ld %4s%c%3s %c%4ld%c %6ld%6ld%6ld%6ld%6ld%6ld  %4s%2s%2s\n",
	      pdb->PDB->Record,
	      pdb->PDB->AtomSerialNumber,
	      pdb->PDB->AtomName,
	      pdb->PDB->LocationIndicator, 
	      pdb->PDB->ResidueName,
	      pdb->PDB->ChainIdentifier,
	      pdb->PDB->ResidueSequenceNumber,
	      pdb->PDB->InsertionCode,
	      lround(pdb->PDB->U11*1e4),
	      lround(pdb->PDB->U22*1e4),
      	  lround(pdb->PDB->U33*1e4),
	      lround(pdb->PDB->U12*1e4),
	      lround(pdb->PDB->U13*1e4),
      	  lround(pdb->PDB->U23*1e4),
	      pdb->PDB->SegID,
	      pdb->PDB->Element,
	      pdb->PDB->Charge);
 	} else {	
		if(pdb->PDB->FullRecord[0]!=' ' || pdb->PDB->FullRecord[0]!='\n' || pdb->PDB->FullRecord[0]!='\r') {
    		fprintf(fpt, "%-80s\n", pdb->PDB->FullRecord);
		}
  	}
	return pdb->PDB;
}


/*werewolf presents*/

pdbRecord*
pdbFileRecordTablePrint(FILE* fpt, pdbFile* pdb)
{
        if(pdbFileIsAtom(pdb)) {
                fprintf(fpt, "%s\t%ld\t%s\t%c\t%s\t%c\t%ld\t%c\t%f\t%f\t%f\t%f\t%f\t%ld\t%s\n",
              pdb->PDB->Record,
              pdb->PDB->AtomSerialNumber,
              pdb->PDB->AtomName,
              pdb->PDB->LocationIndicator,
              pdb->PDB->ResidueName,
              pdb->PDB->ChainIdentifier,
              pdb->PDB->ResidueSequenceNumber,
              pdb->PDB->InsertionCode,
              pdb->PDB->Coord.x,
              pdb->PDB->Coord.y,
              pdb->PDB->Coord.z,
              pdb->PDB->Occupancy,
              pdb->PDB->TemperatureFactor,
              pdb->PDB->FootnoteNumber,
              pdb->PDB->Footnote);
        }
        return pdb->PDB;
}



pdbFileSecondaryStructureRecord*
pdbFileSecondaryStructureRecordPrint(FILE* fpt, pdbFileSecondaryStructureRecord* second) {
	switch(second->mode) {
		case pdbFileSecondaryStructureModeHelix: {
			fprintf(fpt,"%6s %3d %3s %3s %c %4d%c %3s %c %4d%c%2d%30s%5d\n",
				"HELIX ",
				second->helix->serNum,
				second->helix->helixID,
				second->helix->initResName,
				second->helix->initChainID,
				second->helix->initSeqNum,
				second->helix->initICode,
				second->helix->endResName,
				second->helix->endChainID,
				second->helix->endSeqNum,
				second->helix->endICode,
				second->helix->helixClass,
				second->helix->comment,
				second->helix->length);
			break;
		}
		case pdbFileSecondaryStructureModeSheet: {
			fprintf(fpt,"%6s %3d %3s%2d %3s %c%4d%c %3s %c%4d%c%2d ",
				"SHEET ",
				second->sheet->strand,
				second->sheet->sheetID,
				second->sheet->numStrands,
				second->sheet->initResName,
				second->sheet->initChainID,
				second->sheet->initSeqNum,
				second->sheet->initICode,
				second->sheet->endResName,
				second->sheet->endChainID,
				second->sheet->endSeqNum,
				second->sheet->endICode,
				second->sheet->sense);
			if(second->sheet->sense==0) {
				fprintf(fpt, "%28s\n", "");
			} else {
				fprintf(fpt,"%4s%3s %c%4d%c %4s%3s %c%4d%c\n",
				second->sheet->curAtom,
				second->sheet->curResName,
				second->sheet->curChainID,
				second->sheet->curResSeq,
				second->sheet->curICode,
				second->sheet->prevAtom,
				second->sheet->prevResName,
				second->sheet->prevChainID,
				second->sheet->prevResSeq,
				second->sheet->prevICode);
			}
			break;
		}
		case pdbFileSecondaryStructureModeTurn: {
			fprintf(fpt,"%6s %3d %3s %3s %c%4d%c %3s %c%4d%c    %30s\n",
				"TURN  ",
				second->turn->serNum,
				second->turn->turnID,
				second->turn->initResName,
				second->turn->initChainID,
				second->turn->initSeqNum,
				second->turn->initICode,
				second->turn->endResName,
				second->turn->endChainID,
				second->turn->endSeqNum,
				second->turn->endICode,
				second->turn->comment);
			break;
		}
		case pdbFileSecondaryStructureModeNo: {
			break;
		}
		default: {
			fprintf(stderr, "Not supported in pdbFileSecondaryStructureRecordPrint: %d\n", second->mode);
			break;
		}
 	}
	return second;
}

pdbRecord*
pdbFileOneRecordCopy(pdbFile* dst, pdbFile* src)
{
	pdbRecord* tmpprev;
	pdbRecord* tmpnext;

	tmpprev = dst->PDB->prev;
	tmpnext = dst->PDB->next;

	*(dst->PDB) = *(src->PDB);
	
	dst->PDB->prev       = tmpprev;
	dst->PDB->next       = tmpnext;
#ifdef DEBUG
	pdbFileRecordPrint(stderr, src);
	pdbFileRecordPrint(stderr, dst);
#endif
	return dst->PDB;
}

pdbRecord*
pdbFileCAOnlyCopy(pdbFile* dst, pdbFile* src)
{
	pdbRecord* tmpprev;
	pdbRecord* tmpnext;

	
	if(pdbFileIsCA(src)) { 
		tmpprev = dst->PDB->prev;
		tmpnext = dst->PDB->next;

		*(dst->PDB) = *(src->PDB);
	
		dst->PDB->prev       = tmpprev;
		dst->PDB->next       = tmpnext;

		return dst->PDB;
	}
	return NULL;
}

void
pdbFileCAOnlyCopyAll(pdbFile* dst, pdbFile* src)
{
	pdbRecord* tmp;
	long flag;

	flag=0;
	tmp = src->PDB;
	dst->nAtom = 0;
	pdbFileTop(src);
	do {
		if(pdbFileIsCA(src)) {	
			if(0==flag) {
				pdbFileNew(dst);	
				flag++;
			} else {
				pdbFileAppend(dst);		
				flag++;
			}
			pdbFileOneRecordCopy(dst, src);
			dst->nAtom++;
			DEBUGPRINT1("%ld\n", flag);
		}
	} while(NULL!=pdbFileNext(src));
	src->PDB = tmp;
}

void
pdbFileCopyAll(pdbFile* dst, pdbFile* src)
{
	pdbRecord* tmpsrc;
	pdbRecord* tmpdst;
	long flag;

	flag=0;
	tmpsrc = src->PDB;
	pdbFileTop(src);
	tmpdst=pdbFileTop(dst);
	do {
		if(NULL==tmpdst) {
			if(0==flag) {
				pdbFileNew(dst);	
			} else {
				pdbFileAppend(dst);		
			}
			pdbFileOneRecordCopy(dst, src);
		} else {
			pdbFileOneRecordCopy(dst, src);
			tmpdst=pdbFileNext(dst);
		}

		flag++;
#ifdef DEBUG
		fprintf(stderr, "%ld\n", flag);
#endif
	} while(NULL!=pdbFileNext(src));
	src->PDB = tmpsrc;
	dst->nAtom=flag;
}


void
pdbFileAppendAll(pdbFile* dst, pdbFile* src)
{
	pdbRecord* tmpsrc;
	pdbRecord* tmpdst;
	long flag;

	flag=0;
	tmpsrc = src->PDB;
	pdbFileTop(src);
	tmpdst=pdbFileTopPointer(dst);
	do {
		if(NULL==tmpdst) {
			if(0==flag) {
				pdbFileNew(dst);
			} else {
				pdbFileAppend(dst);		
			}
		} else {
			pdbFileAppend(dst);		
		}
		pdbFileOneRecordCopy(dst, src);
		tmpdst=pdbFileNext(dst);
		flag++;
#ifdef DEBUG
		fprintf(stderr, "%ld\n", flag);
#endif
	} while(NULL!=pdbFileNext(src));
	src->PDB = tmpsrc;
	dst->nAtom=flag;
}


void
pdbFileOneProteinCopy(pdbFile* dst, pdbFile* src, long num)
{
	pdbRecord* tmpsrc;
	pdbRecord* tmpdst;
	long flag;

	flag=0;
	tmpsrc = src->PDB;
	tmpdst = dst->PDB;
	pdbFileTop(src);
	pdbFileTop(dst);
	while(flag<num) {
		if(NULL==pdbFileNextProtein(src)) {
			fprintf(stderr, "This file has no %ld th protein \n", num);
			exit(EXIT_FAILURE);
		}
		flag++;
	}
	while(!pdbFileIsEndLine(src)) {
		pdbFileOneRecordCopy(dst, src);
		if(NULL==pdbFileNext(src)) {
			fprintf(stderr, "This file has no %ld th protein \n", num);
			exit(EXIT_FAILURE);
		}
		pdbFileAppend(dst);
	} 
	pdbFileOneRecordCopy(dst, src);
	src->PDB = src->PDB;
	dst->nAtom=flag;
}

/*
 *
 *
 */
long
pdbRecordIsNearby(pdbRecord record1,pdbRecord record2)
{
	if(  ( record1.ChainIdentifier==record2.ChainIdentifier)
	    && (labs(record1.ResidueSequenceNumber-record2.ResidueSequenceNumber)==1)) {
		return 1;
	}
	return 0;
}


/*
 *
 */
pdbFileParaTypeInteger
pdbZValueGet(pdbFile* pdb)
{
    if(       pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'H') {
        return 1;
    } else if(pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'C') {
        return 6;
    } else if(pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'N') {
        return 7;
    } else if(pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'O') {
        return 8;
    } else if(pdb->PDB->Footnote[6] == 'N' && pdb->PDB->Footnote[7] == 'A') {
        return 11;
    } else if(pdb->PDB->Footnote[6] == 'M' && pdb->PDB->Footnote[7] == 'G') {
        return 12;
    } else if(pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'P') {
        return 15;
    } else if(pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'S') {
        return 16;
    } else if(pdb->PDB->Footnote[6] == 'C' && pdb->PDB->Footnote[7] == 'L') {
        return 17;
    } else if(pdb->PDB->Footnote[6] == ' ' && pdb->PDB->Footnote[7] == 'K') {
        return 19;
    } else if(pdb->PDB->Footnote[6] == 'C' && pdb->PDB->Footnote[7] == 'A') {
        return 20;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'H') {
        return 1;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'C') {
        return 6;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'N') {
        return 7;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'O') {
        return 8;
    } else if(pdb->PDB->AtomName[0] == 'N' && pdb->PDB->AtomName[1] == 'A') {
        return 11;
    } else if(pdb->PDB->AtomName[0] == 'M' && pdb->PDB->AtomName[1] == 'G') {
        return 12;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'P') {
        return 15;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'S') {
        return 16;
	} else if(pdb->PDB->AtomName[0] == 'C' && pdb->PDB->AtomName[1] == 'L') {
		return 17;
    } else if(pdb->PDB->AtomName[0] == ' ' && pdb->PDB->AtomName[1] == 'K') {
        return 19;
    } else if(pdb->PDB->AtomName[0] == 'C' && pdb->PDB->AtomName[1] == 'A') {
        return 20;
	} else if(pdb->PDB->AtomName[0] == 'F' && pdb->PDB->AtomName[1] == 'E') {
		return 26;
    } else {
        fprintf(stderr, "Not supported element: %c%c\n", pdb->PDB->Footnote[6], pdb->PDB->Footnote[7]);
        fprintf(stderr, "Not supported element: %c%c\n", pdb->PDB->AtomName[0], pdb->PDB->AtomName[1]);
        return 6;
    }
    return 6;
}

