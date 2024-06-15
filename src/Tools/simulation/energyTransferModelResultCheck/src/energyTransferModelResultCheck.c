/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% energyTransferModelResultCheck ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : energyTransferModelResultCheck
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%energyTransferModelResultCheck ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lFRET.h"

int
main(int argc, char* argv[]) 
{
	static energyTransferData etData; /* Energy Transfer Data */
	mrcImage* unfix;           /* Unfixed point distribution estimated from unfixed points.   */
	char s[1024];
	static energyTransferModelResultCheckInfo info;
	static lenergyTransferModelCheckInfo linfo;
	int i;
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
    /* Energy Transfer Data Read */
	energyTransferDataRead(&etData, info.fptIn, 0);
	energyTransferDataWrite(&etData, info.fptOut, 0);

	linfo.neglect = info.Neg;
    /* Data Allocation */
	unfix = (mrcImage*)memoryAllocate(sizeof(mrcImage)*etData.numUnfix, "in main");
	for(i=0; i<etData.numUnfix; i++) {
		if(info.flagInResHead) {
			sprintf(s, "%s", info.InResHead);
		}
		sprintf(s, "%s.%s",  s, etData.unfix[i].ID);
		if(info.flagInResTail) {
			sprintf(s, "%s.%02ld", s, info.InResTail);
		}
		mrcFileRead(&(unfix[i]), s, "in main", 0); /* Final Data */
	}
	/* Comparison with FRET data */
	if(info.flagInResTail) {
		linfo.iter = info.InResTail;
	}
	lenergyTransferModelExpectedFRET(info.fptOut, &etData, unfix, linfo, info.mode);
	lenergyTransferModelExpectedFRET2(info.fptOut, &etData, unfix, linfo, info.mode);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

