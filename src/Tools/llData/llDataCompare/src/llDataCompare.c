/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataCompare ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataCompare
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataCompare ver%I%; Date:%D% %Z%";
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
#include "lllDataCompare.h"

int
main(int argc, char* argv[]) 
{
	llData* in;
	llData ref;
	llDataCompareInfo info;
	lllDataCompareInfo* Ininfo;
	lllDataCompareInfo* Refinfo;
	llDataParaTypeInteger status;
	int i;
	lllDataIntensityInformation* dataIn;
	lllDataIntensityInformation* dataRef;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	DEBUGPRINT("----- Input Data Files -----\n");
	in = (llData*)memoryAllocate(sizeof(llData)*info.flagIn, "in main");

	dataIn = (lllDataIntensityInformation* )memoryAllocate(sizeof(lllDataIntensityInformation)*info.flagIn, "in main");

	for(i=0; i<info.flagIn; i++) {
		llDataFileRead(info.fptIn[i],  &in[i],  &status);
		dataIn[i].onedata = (onelllDataIntensityInformation* )memoryAllocate(sizeof(onelllDataIntensityInformation)*in[i].llMax, "in main");
		dataIn[i].llMax   = in[i].llMax;
		lllDataIntensityInformationGet(&in[i], &(dataIn[i]), info.mode);
	}

	DEBUGPRINT("----- Input Reference File -----\n");
	dataRef = (lllDataIntensityInformation* )memoryAllocate(sizeof(lllDataIntensityInformation)*1, "in main");
	llDataFileRead(info.fptRef,  &ref,  &status);
	dataRef[0].onedata = (onelllDataIntensityInformation* )memoryAllocate(sizeof(onelllDataIntensityInformation)*ref.llMax, "in main");
	dataRef[0].llMax   = ref.llMax;
	lllDataIntensityInformationGet(&ref, &(dataRef[0]), info.mode);

	
	DEBUGPRINT("----- Data Compare -----\n");
	Ininfo  = (lllDataCompareInfo* )memoryAllocate(sizeof(lllDataCompareInfo)*1, "in main");
	Refinfo = (lllDataCompareInfo* )memoryAllocate(sizeof(lllDataCompareInfo)*1, "in main");
	Ininfo[0].FilamentNumber  = info.flagIn;
	Refinfo[0].FilamentNumber = 1;
	lllDataCompare(dataIn,  Ininfo,  info.mode);
	lllDataCompare(dataRef, Refinfo, info.mode);

	DEBUGPRINT("----- Result -----\n");
	fprintf(stderr,"In  %15.6f\n",  Ininfo[0].ratio);
	fprintf(stderr,"Ref %15.6f\n", Refinfo[0].ratio);
	fprintf(info.fptOut,"In  %15.6f\n",  Ininfo[0].ratio);
	fprintf(info.fptOut,"Ref %15.6f\n", Refinfo[0].ratio);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, "Mode\n");
	fprintf(stderr, "0: Integral\n");
	fprintf(stderr, "1: Peak\n");
}
