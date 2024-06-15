/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataSeparate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataSeparate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataSeparate ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "mrcImage.h"
#include "llData.h"
#include "lllExtract.h"
#include "lllDatarMaxLimit.h"
#include "lllDataLowPassFiltering.h"

void
main(int argc, char* argv[]) 
{
	mrcImage mrcIn;     /* Fourier Space */
	llData   llMixNea;  /* Mixed Layer Line */
	llData   llMixFar;
	llData   llSepNea;  /* Separated Layer Line */
	llData   llSepFar;
	llDataSeparateInfo  info;
	lllExtractInfo      leInfo;
	llDataParaTypeInteger mode;	
	FILE* fpt;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	fpt = info.fptLog;
	
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&mrcIn, info.In, "main routein", 0);
	lllDataSeparationInfoRead(&leInfo, &mrcIn, info.fptconfigFile);

	if(info.flagdelRInv) {
		lllDataSeparationInfoDelRInvSet(&leInfo, info.delRInv);
	}
	if(info.flagtruePitch) {
		lllDataSeparationInfoTruePitchSet(&leInfo, info.truePitch);
	}
	if(info.flagtruePitch) {
		lllDataSeparationInfoxShiftSet(&leInfo, info.truePitch);
	}
	
	lllExtract (&llMixNea, &llMixFar, &mrcIn, &leInfo); 
	llMixNea.truePitch = llMixFar.truePitch = leInfo.truePitch;
	llMixNea.Weight    = llMixFar.Weight    = 1.0;

	/* RMax Limitation */
	lllDataLowPassFiltering(&llMixNea, info.RMax, 0);
	lllDataLowPassFiltering(&llMixFar, info.RMax, 0);

	/* Layer Line Separation */
	lllExtractWithSeparation(&llSepNea, &llMixNea, &leInfo, 0); 
	lllExtractWithSeparation(&llSepFar, &llMixFar, &leInfo, 0); 
		
	/* rMax Limitation */
	lllDatarMaxLimit(&llSepNea, info.rMax, 0);
	lllDatarMaxLimit(&llSepFar, info.rMax, 0);

	/* Output */
	llDataFileWrite(info.fptSepNea, &llSepNea, &mode);
	llDataFileWrite(info.fptSepFar, &llSepFar, &mode);
	if(info.flagMixNea) {
		llDataFileWrite(info.fptMixNea, &llMixNea, &mode);
	}
	if(info.flagMixFar) {
		llDataFileWrite(info.fptMixFar, &llMixFar, &mode);
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">> llDataSepartionControlFile <<\n");
	lllDataSeparationInfoFileFormat(stderr);
}

