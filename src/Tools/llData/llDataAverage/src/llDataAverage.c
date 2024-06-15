/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataAverage ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataAverage
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataAverage ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "llData.h"
#include "lllDataFitAndAverage.h"
#ifdef PVM
#include "PVM.h"
#include "pvm3.h"
#endif
int
main(int argc, char* argv[]) 
{
	llDataParaTypeInteger i, status;
	llDataAverageInfo info;
	llData  llModel;  /* Input Model Data */
	llData  llRef;    /* Reference Data from Input Model Data */
	llData* llIn;     /* Test Data */
	llData* llOut;    /* Test Data */
	llData  llAve;    /* Averaged Data */
	llDataParaTypeReal W;
	llDataFittedParam* paraFit;
	llDataFittedParam  range;
	lllDataFitAndAverageInfo linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	/* Set Paramgeres */
	memoryClear(&range, sizeof(range), 0);
	range.Para.r.Min   = info.rmin;
	range.Para.r.Max   = info.rmax;
	range.Para.r.Delta = info.dr;
	range.Para.phi.Min = info.phimin*RADIAN;
	range.Para.phi.Max = info.phimax*RADIAN;
	range.Para.phi.Delta = info.dphi*RADIAN;
	range.Para.z.Min   = info.zmin;
	range.Para.z.Max   = info.zmax;
	range.Para.z.Delta = info.dz;
	range.Para.flagCTF = 0;

    /* Input Model File */
	llDataFileRead  (info.fptModel,  &llModel, 0);
	lllDataWeightSet(info.fptllInfo, &llModel, 0.0, 0);

	/* Create Reference Data */
	llRef = llModel;
	llRef.truePitch = info.truePitch;
	llRef.Weight = 1.0;

    /* Input Test llDataFile */
	fprintf(stdout, "---Input Data---\n");
	llIn=(llData*)memoryAllocate(info.flagIn*sizeof(llData), "in Main");
	llOut=(llData*)memoryAllocate(info.flagIn*sizeof(llData), "in Main");
	DEBUGPRINT1("FileNumber: %d\n", info.flagIn);
	for(i=0; i<info.flagIn; i++) {
		DEBUGPRINT2("%d: %s\n", i, info.In[i]);
		llDataFileRead(info.fptIn[i], &(llIn[i]), 0);
		lllDataWeightSet(info.fptllInfo, &(llIn[i]), 0.0, 0);
		llIn[i].truePitch = info.truePitch;
		/*
		llIn[i].Weight    = info.WeightOfFile[i];
		*/
		llIn[i].Weight    = 1.0;
	}

    /* paraF Allocate */
	paraFit=(llDataFittedParam*)memoryAllocate(info.flagIn*sizeof(llDataFittedParam), "in Main");
	for(i=0; i<info.flagIn; i++) {
		paraFit[i].Para = range.Para;
	}

	/* Fit and Average */
	memoryClear(&linfo, sizeof(linfo), 0);
	linfo.nFile         = info.flagIn;
	linfo.times         = 0;
	linfo.flagOutParam2 = info.flagOutParam2;
	linfo.OutParam2     = info.OutParam2;
	linfo.In            = info.In;
	linfo.fptLog        = info.fptLog;
	linfo.mode          = PVALUE_MODE|lllDataFitFitProcessPrint;
	linfo.flagAveragingWithoutAntiPole = info.withoutAntiPole;
	llDataInitWithReference(&llAve, &llRef);
	llOut = (llData*)memoryAllocate(info.flagIn*sizeof(llData), "in Main");
	for(i=0; i<info.flagIn; i++) {
		llDataInitWithReference(&(llOut[i]), &(llIn[i]));
	}
#ifdef PVM
	if(info.flagpvmList) {
		linfo.flagPVM = 1;
		lllDataFitServerStart(&(linfo.vPVM), info.fptpvmList, 0);
	} else if(info.flagpvm) {
		linfo.flagPVM = 1;
		lllDataFitServerStart(&(linfo.vPVM), NULL, info.pvm);
	} else {
		linfo.flagPVM = 0;
	}
#endif
	linfo.flagCTF = 0;

	lllDataFitAndAverage(&llAve, llOut, llIn, llRef, paraFit, linfo);

#ifdef PVM
	if(info.flagpvmList || info.flagpvm) {
		lllDataFitServerEnd(linfo.vPVM);
		linfo.flagPVM = 0;
	}
#endif

    /* Output */
	fprintf(stdout, "---Output---\n");
	for(i=0; i<info.flagOut; i++) {
		llDataFileWrite(info.fptOut[i], &(llOut[i]), &status);
	}
	llDataFileWrite(info.fptAve, &llAve, &status);

	fprintf(info.fptOutParam, "## Fit and Average Step ##\n");
	for(i=0; i<info.flagIn; i++) {
		fprintf(info.fptOutParam, "%s %s %15.6f %15.6f %15.6f %15.6f %5d\n",
			info.Model,
			info.In[i],
			paraFit[i].Para.R*DEGREE,
			paraFit[i].Para.phi.Value*DEGREE,
			paraFit[i].Para.z.Value,
			paraFit[i].Para.r.Value,
			paraFit[i].Para.Pole);
	}

    if(info.flagP2) {
		for(i=0; i<info.flagIn; i++) {
			if(paraFit[i].PPara.R < paraFit[i].PParaInv.R) {
				fprintf(info.fptP2, "%s %s %15.6f %15.6f %d\n",
					info.Model,
					info.In[i],
				 	paraFit[i].PPara.R*DEGREE,
					paraFit[i].PParaInv.R*DEGREE,
					paraFit[i].PPara.Pole);
			} else {
				fprintf(info.fptP2, "%s %s %15.6f %15.6f %d \n",
					info.Model,
					info.In[i],
					paraFit[i].PParaInv.R*DEGREE,
					paraFit[i].PPara.R*DEGREE,
					paraFit[i].PParaInv.Pole);
			}
		}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{

}
