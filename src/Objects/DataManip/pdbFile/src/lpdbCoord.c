/*
# lpdbCoord : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lpdbCoord 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include "./lpdbCoord.h"

void
lpdbCoordAdd(pdbFile* in1, pdbFile* in2)
{
	pdbFileTop(in1);
	while (!pdbFileEnd(in1)) {
		if(!pdbFileIsAtom(in1)) {
			pdbFileNextAtom(in1);
		}
		if(pdbFileEnd(in1)) {
			break;	
		}
		pdbFileTop(in2);
		while(!pdbFileEnd(in2)) {
			if(!pdbFileIsAtom(in2)) {
				pdbFileNextAtom(in2);
			}
			if(pdbFileEnd(in2)) {
				break;	
			}

			if(in1->PDB->ResidueSequenceNumber == in2->PDB->ResidueSequenceNumber
			&& 0==strcmp(in1->PDB->AtomName, in2->PDB->AtomName)
			&& in1->PDB->ChainIdentifier == in2->PDB->ChainIdentifier) {
				in1->PDB->Coord.x += in2->PDB->Coord.x;
				in1->PDB->Coord.y += in2->PDB->Coord.y;
				in1->PDB->Coord.z += in2->PDB->Coord.z;
				break;
			} else {
				pdbFileNextAtom(in2);
			}
		}
		pdbFileNextAtom(in1);
	} 
}
