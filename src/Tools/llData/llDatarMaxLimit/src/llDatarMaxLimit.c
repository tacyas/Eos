/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDatarMaxLimit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDatarMaxLimit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDatarMaxLimit ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "llData.h"
#include "lllDatarMaxLimit.h"
#include "genUtil.h"

void
main(int argc, char* argv[]) 
{
	llDataParaTypeInteger status;
	llDatarMaxLimitInfo info;
	lllDatarMaxLimitInfo linfo;
    llData   llIn;
    llData   llInfo;
	int l;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

    /* Data In */
	llDataFileRead(info.fptIn, &llIn, &status);
    /* rMax Limitation */
	linfo.flagrMaxMin = info.flagrMaxMin;
	linfo.rMax    = info.rMax;
	linfo.rMaxMin = info.rMaxMin;
    lllDatarMaxLimit(&llIn, linfo, 0);

    /* Data Out */
	llDataFileWrite(info.fptOut, &llIn, &status);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "\n\n");
	fprintf(stderr, "----- rMax Limit Algorithm----- \n");
	fprintf(stderr, "Default \n");
	fprintf(stderr, "     R < (|n|-2)/(2*PI*rMax): Intensity = 0; \n");
	fprintf(stderr, "If -rMin option\n");
	fprintf(stderr, "     R < RR:    (|n|-2)/(2*PI*rMax)   : Intensity = 0.0; \n");
	fprintf(stderr, "     R < RRMin: (|n|-2)/(2*PI*rMaxMin): Intensity = (R - RR)/(RRMin - RR)*Intensity; \n");
	fprintf(stderr, "\n");
}

