/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataMultiCTFCompensation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataMultiCTFCompensation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataMultiCTFCompensation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "eosString.h"
#include "../inc/config.h"
#include "llData.h"
#include "ctfInfo.h"
#include "lllDataLowPassFiltering.h"
#include "lllDataFitAndAverage.h"
#include "lllDataCTFCompensation.h"

int
main(int argc, char* argv[]) 
{
	int status;
	llDataMultiCTFCompensationInfo info;
	lllDataFitAndAverageInfo       linfo;
	llData*  llIn;
	llData*  llOut;
	llData  llAve;
	llData  llRef;
	llDataFittedParam* paraFit;
	llDataParamToFit   range;
	long i, iter;
	char s[1024];

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	memoryClear(&linfo, sizeof(linfo), 0);
	/* Set Fitting Parameter */
	memoryClear(&range, sizeof(range), 0);
    range.r.Min   = info.rmin;
    range.r.Max   = info.rmax;
    range.r.Delta = info.dr;
    range.phi.Min = info.phimin*RADIAN;
    range.phi.Max = info.phimax*RADIAN;
    range.phi.Delta = info.dphi*RADIAN;
    range.z.Min   = info.zmin;
    range.z.Max   = info.zmax;
    range.z.Delta = info.dz;
	linfo.noise = info.Noise;	
	/* Allocate paraFit */	
	paraFit=(llDataFittedParam*)memoryAllocate(info.flagIn*sizeof(llDataFittedParam), "in main");
	for(i=0; i<info.flagIn; i++) {
		paraFit[i].Para = range;
	}
	/* Input reference data */
	DEBUGPRINT("----- Input Ref Data -----\n");
	memoryClear(&llRef, sizeof(llRef), 0);
	llDataFileRead(info.fptRef, &llRef, &status);
	DEBUGPRINT("----- Set Weight -----\n");
	lllDataWeightSet(info.fptllInfo, &llRef, 0.0, 0);
	llRef.truePitch = info.truePitch;
	llRef.Weight    = 1.0;
	if(info.flagRmax) {	
		lllDataLowPassFiltering(&llRef, info.Rmax, 1);
	}

	/* Input test data*/
	DEBUGPRINT("----- Input Data -----\n");
	llIn  = (llData*) memoryAllocate(sizeof(llData)*info.flagIn, "in main");
	llOut = (llData*) memoryAllocate(sizeof(llData)*info.flagIn, "in main");
	linfo.nFile  = info.flagIn;
	linfo.In     = info.In;
	linfo.fptLog = info.fptOutParam;
	linfo.flagCTF = 1;
	linfo.ctfMode = info.mode;
	linfo.CTF = (ctfInfo*)memoryAllocate(sizeof(ctfInfo)*info.flagIn, "in main");
	linfo.flagWeight = 1;
	linfo.weight = (llDataParaTypeReal*)memoryAllocate(sizeof(llDataParaTypeReal)*info.flagIn, "in main");
	linfo.mode   = PVALUE_MODE|lllDataFitFitProcessPrint ;
	fseek(info.fptInList, 0L, SEEK_SET);
	for(i=0; i<info.flagIn; i++) {
		llDataFileReadFollowingllData(info.fptIn[i], &(llIn[i]), &llRef, &status);
		llDataInitWithReference(&(llOut[i]), &(llIn[i]));
		lllDataWeightSet(info.fptllInfo, &(llIn[i]), 0.0, 0);
		
		llIn[i].truePitch = info.truePitch;
		llIn[i].Weight    = 1.0;
		if(info.flagRmax) {	
			lllDataLowPassFiltering(&(llIn[i]), info.Rmax, 1);
		}
		stringGetFromFile(s, "", info.fptInList, stdout, 1);			
		linfo.weight[i]			= stringGetNthRealData(s, 2, " ,");
		linfo.CTF[i].defocus = stringGetNthRealData(s, 3, " ,");
		linfo.CTF[i].Cs 		= stringGetNthRealData(s, 4, " ,");
		linfo.CTF[i].kV 		= stringGetNthRealData(s, 5, " ,");
		linfo.CTF[i].ratioOfAmpToPhase 	= stringGetNthRealData(s, 6, " ,");
		linfo.CTF[i].mode     = ctfInfoModePhaseAndAmpCTF;
		paraFit[i].Para.flagCTF = linfo.flagCTF;
		paraFit[i].Para.ctfCompensationMode = linfo.ctfMode;
		paraFit[i].Para.CTF   = linfo.CTF[i];
	}
	llDataInitWithReference(&llAve, &llRef);

	for(iter=0; iter<info.MaxIter; iter++) {
	    LOGPRINT1(linfo.fptLog, "ITER","FIT","The %ldth Iteration\n", iter);
		lllDataFitAndAverage(&llAve, llOut, llIn, llRef, paraFit, linfo);
		lllDataCopy(&llRef, &llAve);
	  	for(i=0; i<info.flagIn; i++) {
		 	LOGPRINT7(info.fptOutParam, "ITER","FIT",
				"%s %s %15.6f %15.6f %15.6f %15.6f %5d",
				info.Ref,
			   	info.In[i],
				paraFit[i].Para.R*DEGREE,
				paraFit[i].Para.phi.Value*DEGREE,
				paraFit[i].Para.z.Value,
				paraFit[i].Para.r.Value,
				paraFit[i].Para.Pole);
		}
	}
	llDataFileWrite(info.fptAve, &llAve, &status);
	if(info.flagOut) {
		if(info.flagOut!=info.flagIn) {
			fprintf(stderr, "The number of In (%d) is different from that of Out (%d) \n", 
				info.flagIn, info.flagOut);
		}
		for(i=0; i<info.flagOut; i++) {
			llDataFileWrite(info.fptOut[i], &(llOut[i]), &status);
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	ERRORPRINT("---- InputFileFormat ----\n");
	ERRORPRINT("filename weight(NumberOfAveragedFile) deltaF[A] Cs[mm] kV[kV] ratioOfAmpToPhase\n");
	lllDataMultiCTFCompensationModePrint(stderr);
}

