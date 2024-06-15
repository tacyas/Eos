/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractCtfinfFileCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractCtfinfFileCreate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractCtfinfFileCreate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define UNDEBUG
#include "genUtil.h"
#include "lllExtractCtfinfFileCreate.h"

int
main(int argc, char* argv[]) 
{
	llExtractCtfinfFileCreateInfo info;
	infoDataList linfo;
	ctfInfo CTFInfo;
	ctfInfoZeroPoint CTFInfoZeroPoint;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.FirstZero     = info.FirstZero;
	linfo.flagFirstZero = info.flagFirstZero;
	linfo.Out           = info.Out;
	linfo.fptOut        = info.fptOut;

	CTFInfo.Cs = 2.1;
	CTFInfo.defocus = info.Defocus;
	CTFInfo.kV = 200;
	CTFInfo.mode = 1;
	CTFInfo.ratioOfAmpToPhase = info.AoverP;
	CTFInfo.Ain = 0.02;
	
	CTFInfoZeroPoint.RMax = 0.1;
	CTFInfoZeroPoint.dR   = 0.0001;
	CTFInfoZeroPoint.N    = 1;

	switch(info.mode){
		case 0:{
			llExtractCtfinfFileCreateI(&linfo, &CTFInfo, &CTFInfoZeroPoint);
			break;
		}
		case 1:{
			llExtractCtfinfFileCreateII(&linfo, &CTFInfo);
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode : %ld in main", info.mode);
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "----- mode -----\n");
	fprintf(stderr, "0: make CTFInformation file 1\n");
	fprintf(stderr, "   (-df or -FirstZero) and -A\n");
	fprintf(stderr, "1: make CTFInformation file 2\n");
	fprintf(stderr, "   -df and -A\n");
}

