/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% pdbMove ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : pdbMove
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%pdbMove ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "pdbFile.h"
#include "pdbInfoGet.h"
#include "Matrix3D.h"

/*
Example:
typedef struct lpdbMoveInfo {
	float a;
	int   b;
} lpdbMoveInfo;

typedef enum lpdbMoveMode {
	a=0,
	b=1
} lpdbMoveMode;
*/

int
main(int argc, char* argv[]) 
{
	pdbMoveInfo info;
	Matrix3D    m;
	pdbFile     pdb;
	pdbInfoData linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	/* Input */
	pdbFileRead(info.fptIn, &pdb);

	/* Set */
	if(info.GCtoOrigin) {
		pdbInfoGet(&pdb, &linfo, 0);
		info.X = -linfo.cx;
        info.Y = -linfo.cy;
        info.Z = -linfo.cz;
    }
    if(info.flagtoX) {
    	info.X = info.toX;
        info.Y = info.toY;
        info.Z = info.toZ;
    }
    if(info.flagfromX) {
    	info.X = -info.fromX;
        info.Y = -info.fromY;
        info.Z = -info.fromZ;
    }

    /* Translation */
    matrix3DTranslationSet(m, info.X, info.Y, info.Z, MATRIX_3D_MODE_INITIALIZE);
    pdbTrans(&pdb, m);

    /* Output */
    pdbFileWrite(info.fptOut, &pdb);

	return EXIT_SUCCESS;
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
