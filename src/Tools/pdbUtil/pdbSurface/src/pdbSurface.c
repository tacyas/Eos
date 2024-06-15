/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbSurface ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbSurface
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbSurface ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "lpdbSurface.h"

/*
Example:
typedef struct lpdbSurfaceInfo {
	float a;
	int   b;
} lpdbSurfaceInfo;

typedef enum lpdbSurfaceMode {
	a=0,
	b=1
} lpdbSurfaceMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbSurfaceInfo info;
	lpdbSurfaceInfo linfo;
	lpdbSurfaceMode lmode;
	pdbFile pdb;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	lmode = info.mode;
	linfo.order  = info.order;
	linfo.refine = info.refine;
	linfo.size   = info.size;
	linfo.mergin = info.mergin;
	linfo.weight = info.weight;
	linfo.thresHold = info.thresHold;
	linfo.DensityMode = info.DensityMode;

	pdbFileRead(info.fptIn, &pdb);

	lpdbSurfaceAsTemperatureFactor(&pdb, &linfo, lmode);

	pdbFileWrite(info.fptOut, &pdb); 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
