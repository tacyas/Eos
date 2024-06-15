/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbOneProteinGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbOneProteinGet
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbOneProteinGet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"

void
main(int argc, char* argv[]) 
{
	long status;
	pdbOneProteinGetInfo info;
	pdbFile in;
	pdbFile out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	pdbFileRead(info.fptIn, &in);
	DEBUGPRINT1("Atom Number : %d\n", in.nAtom);
	pdbFileNew(&out);
	pdbFileOneProteinCopy(&out, &in, info.Num);
	pdbFileWrite(info.fptOut, &out);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
