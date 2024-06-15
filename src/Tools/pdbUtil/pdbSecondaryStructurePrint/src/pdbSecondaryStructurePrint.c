/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbSecondaryStructurePrint ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbSecondaryStructurePrint
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbSecondaryStructurePrint ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"

int
main(int argc, char* argv[]) 
{
	pdbSecondaryStructurePrintInfo info;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn, &pdb);
	pdbFileWriteSecondaryStructure(info.fptOut, &(pdb.second));
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
