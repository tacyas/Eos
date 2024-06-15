/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageNfoldAxisSearch ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageNfoldAxisSearch
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageNfoldAxisSearch ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "mrcImage.h"
#include "lmrcImageTransformDescartesIntoPolar.h"

/*
Example:
typedef struct lmrcImageNfoldAxisSearchInfo {
	float a;
	int   b;
} lmrcImageNfoldAxisSearchInfo;

typedef enum lmrcImageNfoldAxisSearchMode {
	a=0,
	b=1
} lmrcImageNfoldAxisSearchMode;
*/

int
main(int argc, char* argv[]) 
{
	mrcImageNfoldAxisSearchInfo info;
	lmrcImageDeterminationOfPolarAxisByAssumingNfoldInfo linfo;
	mrcImageParaTypeRealCoord centre;
	mrcImage in;
	mrcImage residue;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);

	linfo.minx = info.minx;
	linfo.maxx = info.maxx;
	linfo.delx = info.delx;
	linfo.miny = info.miny;
	linfo.maxy = info.maxy;
	linfo.dely = info.dely;
	linfo.minz = info.minz;
	linfo.maxz = info.maxz;
	linfo.delz = info.delz;
	linfo.nFold = info.nFold;
	linfo.delPHI = info.delPHI*RADIAN;
	lmrcImageDeterminationOfPolarAxisByAssumingNfold(&centre, &residue, &in, linfo, 0);

	fprintf(info.fptOut, "Centre: %g %g %g\n", centre.x, centre.y, centre.z);
	if(info.flagRes) {
		mrcFileWrite(&residue, info.Res, "in main", 0);
	}
	if(info.flagOut2) {
		mrcImage shift;
		mrcImageParaTypeRealCoord offset;
		offset.x = - (centre.x - in.HeaderN.x/2);
		offset.y = - (centre.y - in.HeaderN.y/2);
		offset.z = - (centre.z - in.HeaderN.z/2);
		lmrcImageShift(&shift, &in, offset, mrcPixelHowCubicConv);
		mrcFileWrite(&shift, info.Out2, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
