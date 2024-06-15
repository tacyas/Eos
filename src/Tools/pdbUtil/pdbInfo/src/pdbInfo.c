/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbInfo ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbInfo
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbInfo ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#undef DEBUG
#include "genUtil.h"
#include "pdbFile.h"

void lpdbInfo(FILE* fpt, pdbFile* pdb);
void
main(int argc, char* argv[]) 
{
	long status;
	pdbInfoInfo info;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	pdbFileRead(info.fptIn, &pdb);
	lpdbInfo(info.fptOut, &pdb);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}

#include "pdbInfoGet.h"

void 
lpdbInfo(FILE* fpt, pdbFile* pdb)
{
	pdbInfoData info;

	pdbInfoGet(pdb, &info, 0);

	fprintf(fpt, "Gravity Centre(CA)       : %15.6e %15.6e %15.6e\n", info.cx, info.cy, info.cz);
	fprintf(fpt, "Atom far from Centre(CA) : %15.6e \n", info.distance);
	fprintf(fpt, "Atom far from Centre(CA, Axis) : %10.2f %10.2f %10.2f\n", info.distancex, info.distancey, info.distancez);
}
