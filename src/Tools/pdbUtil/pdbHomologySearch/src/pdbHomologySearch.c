/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbHomologySearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbHomologySearch
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbHomologySearch ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "pdbFile.h"

int
main(int argc, char* argv[]) 
{
	pdbHomologySearchInfo info;
	pdbFile pdbIn;
	pdbFile pdbInCA;
	pdbFile pdbRef;
	pdbFile pdbRefCA;
	mrcImage map;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	pdbFileRead(info.fptIn,  &pdbIn);
	pdbFileRead(info.fptRef, &pdbRef);

	pdbFileCAOnlyCopyAll(&pdbInCA, &pdbIn);
	pdbFileCAOnlyCopyAll(&pdbRefCA, &pdbRef);

	lpdbFileHomologyMapCreate(&map, &pdbInCA, &pdbRefCA, 0);
	lpdbFileHomologySearch(&map, &pdbInCA, &pdbRefCA, 0);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

