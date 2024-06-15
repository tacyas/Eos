/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfFunction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfFunction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfFunction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#undef DEBUG 
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "ctfInfo.h"

#ifdef PVM
#undef DEBUG
#include "PVM.h"
#include "pvm3.h"
#endif

int
main(int argc, char* argv[]) 
{
	long status;
	ctfFunctionInfo info;
	float R;
	ctfInfo CTFInfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	CTFInfo.Cs = info.Cs;
	CTFInfo.defocus = info.Defocus;
	CTFInfo.kV = info.kV;
	CTFInfo.mode = info.ctfMode;
	CTFInfo.ratioOfAmpToPhase = info.AoverP;
	CTFInfo.Ain = info.Ain;
	CTFInfo.flagMagnification  = 0;
	if(!info.flagpvm && !info.flagpvmList) {
		for(R=0; R<info.Rmax; R+=info.dR) {
			fprintf(info.fptOut, "%e %e\n", R, ctfFunction(&CTFInfo, R, 0)); 
		}
	} else {
#ifdef PVM
		int* tids;
		int mytid;
		int  numTask;
		int  i;
		float CTF;
		char* argv[] = { (char*)0 };
		
		/* PVM Start */
		mytid = pvm_mytid();

		numTask = info.pvm;
		if(info.flagpvmList) {
			DEBUGPRINT1("pvmList: %s\n", info.pvmList);
			tids = pvmServerStart("ctfFunctionServer", argv, info.fptpvmList, &numTask, 0);
		} else if(info.flagpvm) {
			DEBUGPRINT1("nTask: %d\n", info.pvm);
			tids = pvmServerStart("ctfFunctionServer", argv, NULL, &numTask, 0);
		} else {
			fprintf(stderr, "Something wrong\n");
			exit(EXIT_FAILURE);
		}
		if(numTask<=0) {
			exit(EXIT_FAILURE);
		}
		for(R=0, i=0; R<info.Rmax; R+=info.dR, i++) {
			ctfFunctionPVMStart(&CTFInfo, R, tids[i%numTask], 0); 
		}

		for(R=0, i=0; R<info.Rmax; R+=info.dR, i++) {
			DEBUGPRINT1("from %x\n", tids[i%numTask]);
			CTF = ctfFunctionPVMEnd(&CTFInfo, R, tids[i%numTask], 0); 
			fprintf(info.fptOut, "%e %e\n", R, CTF); 
		}

		for(i=0; i<numTask; i++) {
			pvm_kill(tids[i]);		
		}

		pvm_exit();
#else
		fprintf(stderr, "Not supported pvm in this host\n");
		exit(EXIT_FAILURE);
#endif
	} 
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, ">>>> ctfMode <<<< \n");
	fprintf(stderr, " 0: Phase CTF \n"); 
	fprintf(stderr, " 1: PhaseCTF + ratio*AmpCTF \n");
	fprintf(stderr, " 32: EnvFromAillumination*()\n");
	fprintf(stderr, ">>>> mode <<<< \n");
	fprintf(stderr, "No action\n");
}

