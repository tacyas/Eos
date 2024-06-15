/*
# pdbFileWrite.c  1.1
# The latest update : 07/13/96 at 11:39:12
#
#@(#) pdbFileWrite ver 1.1
#@(#) Created by 
#@(#)
#@(#) Usage : pdbFileWrite 
#@(#) Attention
#@(#)
*/
static char __sccs_id[] = "@(#)pdbFileWrite ver1.1; Date:96/07/13 @(#)";
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "genUtil.h"
#include "pdbFile.h"

void
pdbFileWrite(FILE* fpt, pdbFile* pdb)
{
  pdbFileTop(pdb);
  while(1) {
    pdbFileRecordPrint(fpt, pdb);
    if(NULL==pdbFileNext(pdb)) {
      break;
    }
  }
}

void
pdbFileWriteCoord(FILE* fpt, pdbFile* pdb)
{
  pdbFileTop(pdb);
  while(1) {
	if(pdbFileIsAtom(pdb)) {
	  fprintf(fpt, "%8.3f, %8.3f, %8.3f\n",  pdb->PDB->Coord.x, pdb->PDB->Coord.y, pdb->PDB->Coord.z);
	}
    if(NULL==pdbFileNext(pdb)) {
      break;
    }
  }
}



/*werewolf presents*/

void
pdbFileTableWrite(FILE* fpt, pdbFile* pdb)
{
  pdbFileTop(pdb);
  while(1) {
    pdbFileRecordTablePrint(fpt, pdb);
    if(NULL==pdbFileNext(pdb)) {
      break;
    }
  }
}


void
pdbFileWriteSecondaryStructure(FILE* fpt, pdbFileSecondaryStructure* second)
{
	int i;

	i = 0;
	second->SecondaryStructure = second->top;
	while(1) {
		if(second->nSecondaryStructure<=i) {
			break;
		}
		pdbFileSecondaryStructureRecordPrint(fpt, second->SecondaryStructure);	
		if(NULL==second->SecondaryStructure->next) {
			break;
		} else {
			second->SecondaryStructure = second->SecondaryStructure->next;
		}
		i++;
	} 
}

