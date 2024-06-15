/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbProteinIDSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbProteinIDSet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbProteinIDSet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "pdbFile.h"

int
main(int argc, char* argv[]) 
{
	long status;
	pdbProteinIDSetInfo info;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	pdbFileRead(info.fptIn, &pdb);

	pdbFileTop(&pdb);
	pdbFileChainIdentifierSetAll(&pdb, info.ID);
	pdbFileWrite(info.fptOut, &pdb);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
}
