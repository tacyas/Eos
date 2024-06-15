/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataCTFCompensate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataCTFCompensate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataCTFCompensate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "llData.h"
#include "eosString.h"
#include "genUtil.h"
#include "ctfInfo.h"
#define SECTION_MARK " \t,"
#include "lllDataCTFCompensate.h"

int
main(int argc, char* argv[]) 
{
	llDataParaTypeInteger status;
	llDataCTFCompensateInfo info;
	lllDataCTFCompensateInfo linfo;
    llData   llIn;
    llData   llInfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.flagIn = info.flagIn;
	linfo.In = info.In;
	linfo.fptIn = info.fptIn;
	linfo.flagIn1 = info.flagIn1;
	linfo.In1 = info.In1;
	linfo.fptIn1 = info.fptIn1;
	linfo.flagIn2 = info.flagIn2;
	linfo.fptIn2 = info.fptIn2;
	linfo.flagOut = info.flagOut;
	linfo.Out = info.Out;
	linfo.fptOut = info.fptOut;
	linfo.flagtruePitch = info.flagtruePitch;
	linfo.truePitch = info.truePitch;
	linfo.flagmode = info.flagmode;
	linfo.mode = info.mode;
	linfo.flagconfigFile = info.flagconfigFile;
	linfo.fptconfigFile = info.fptconfigFile;

	if(linfo.flagconfigFile) {
		configFileRead(linfo.fptconfigFile, &linfo);
	}

    /* Data In */
		llDataFileRead(linfo.fptIn, &llIn, &status);
    	llIn.truePitch = linfo.truePitch;

    /* llInfo Initialization */
    	llInfo = llIn;
    	llDataInit(&llInfo);
    	lllDataAttributeCopy(&llInfo, &llIn);

    /* CTF Compensation */
		if(linfo.flagIn1) {
    		llDataCTFSet(&llInfo, linfo.fptIn1);
		} else if(linfo.flagIn2) {
			llDataCTFSet2(&llInfo,linfo.fptIn2);
		} else {
			fprintf(stderr, "You must choose either In1 or In2.\n");
			exit(EXIT_FAILURE);
		}
   		lllDataMul(&llIn, &llInfo);

    /* Data Out */
		llDataFileWrite(linfo.fptOut, &llIn, &status);
		exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- CTFInformation file 1 -----\n");
	fprintf(stderr, "RR0 F0 PHI0   : If R.lt.RR0, F0=0; If RR0.le.R.lt.RR1, Linear Interpolation F0, F1\n");
	fprintf(stderr, "RR1 F1 PHI1   : If RR1.le.R <RR2,\n"); 
	fprintf(stderr, ".................................................\n");
	fprintf(stderr, "RRn Fn PHIn   : If RRn<= R     , F*0     PHI = 0\n");
	configFileUsage(stderr);
	fprintf(stderr, "----- CTFInformation file 2 -----\n");
	fprintf(stderr, "dF[A] Cs[mm] Acc[kV] ratioOfAmpToPhase\n");
	fprintf(stderr, "----- How to make file 1 or file 2 -----\n");
	fprintf(stderr, "llExtractCtfinfFileCreate make these files.\n");
}
