/*
# lmolviePDBRead : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : lmolviePDBRead 
# Attention
#   $Loccker$
#  	$State$ 
#
*/
/* $Log$ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdbFile.h"

static pdbFile* pdbIn;

void lmolviePDBread(FILE* fptIn)
{
	pdbIn= (pdbFile*)malloc(sizeof(pdbFile));
	pdbFileRead(fptIn, pdbIn);

	putpdbCenter(pdbIn);

	fprintf(stdout, "atom:%ld\n", pdbIn->nAtom);
}

pdbFile* get_pdb(void)
{
	return pdbIn;
}
