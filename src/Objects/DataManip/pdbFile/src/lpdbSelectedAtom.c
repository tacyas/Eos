/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lpdbSelectedAtom ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lpdbSelectedAtom 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%lpdbSelectedAtom ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include "genUtil.h"
#include "eosString.h"
#include "../inc/pdbFile.h"
#include "./lpdbSelectedAtom.h"

/*
	lpdbSelected

FileFormat::
# This is a comment line.
ResidueNumber0
ResidueNumber2
|
ResidueNumber4
*/

pdbFileParaTypeInteger
lpdbSelectedCa(pdbFile* pdbSelect, pdbFile* pdb, FILE* fpt)
{
	pdbRecord* tmptop;
	pdbRecord* tmpprev;
	pdbRecord* tmpnext;
	char s[STRING_MAX_LENGTH];
	pdbFileParaTypeInteger start;
	pdbFileParaTypeInteger end;
	pdbFileParaTypeInteger residue;
	char* stmp;
	long  current;
	pdbFileParaTypeInteger flag;
	int lineNum;

	flag = 0;
	fseek(fpt, 0L, SEEK_SET);
	lineNum = 0;
	while(NULL!=stringGetFromFile(s, "", fpt, stdout, 3)) {
		lineNum++;
		if(s[0] == '#') {
			DEBUGPRINT1("This line (%d) is a comment line\n", lineNum);
		} else {
			start = stringGetNthIntegerData(s, 1, " ,\t");
			current = ftell(fpt);

			if(NULL==stringGetFromFile(s, "", fpt, stdout, 3)) { /* Read the next line */
				end = start;                                     /*   No next line */
			} else {            								 /* The next line exists */
				stmp = stringGetNthWord(s, 1, " ,\t");           /*   Get First Word */
				if('|'==stmp[0]) {                               /*   */
					if(NULL==stringGetFromFile(s, "", fpt, stdout, 3)) { /* No next line */
						fprintf(stderr, "Selected Residue File Format is wrong\n");
						exit(EXIT_FAILURE);
					} else { 									 /* The next line exists. */
						end = stringGetNthIntegerData(s, 1, " ,#");
					}
				} else {										/* No Next residue */	
					end = start;
					fseek(fpt, current, SEEK_SET);
				}
			}

			pdbFileTop(pdb);
			do {
				if(pdbFileIsCA(pdb) && (   start<=pdb->PDB->ResidueSequenceNumber
									    && pdb->PDB->ResidueSequenceNumber<=end)) {
					if(0==flag) {
						pdbFileNew(pdbSelect);
						flag++;
					} else {
						pdbFileAppend(pdbSelect);
						flag++;
					}
					pdbFileOneRecordCopy(pdbSelect, pdb);	
				}
			} while(NULL!=pdbFileNext(pdb));
		}
	}
	return flag;
}

