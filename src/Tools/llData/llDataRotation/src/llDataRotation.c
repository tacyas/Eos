/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataRotation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataRotation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataRotation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "llData.h"

void
main(int argc, char* argv[]) 
{
	long status;
	llDataRotationInfo info;
	llData llIn;
	llData llOut;
	llDataFittedParam p;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);
	llDataFileRead(info.fptIn, &llIn, 0);
	llIn.truePitch = info.truePitch;

	p.Para.r.Value = 1.0;
	p.Para.z.Value = info.z;
	p.Para.phi.Value = info.phi;
	p.Para.Pole    = info.Pole;
	lllDataPhaseShiftInter(&llOut, &llIn, &p);

	llDataFileWrite(info.fptOut, &llOut, &status);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
}
