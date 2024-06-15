/*
# mrcImageSpatialFrequencyFilter : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcImageSpatialFrequencyFilter
# Attention
#   $Loccker$
#  	$State$ 
#
*/
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
#include "eosString.h"
#include "lmrcImageSpatialFrequencyFilter.h"

extern void filterFileRead(FILE* fpt, lmrcImageSpatialFrequencyFilterInfo* linfo , int colR, int colW, int mode);
int
main(int argc, char* argv[]) 
{
	mrcImageSpatialFrequencyFilterInfo info;
	lmrcImageSpatialFrequencyFilterInfo linfo;
	mrcImage in;
	mrcImage out;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	mrcFileRead(&in, info.In, "in main", 0);
	filterFileRead(info.fptfilterIn, &linfo, info.colR, info.colW, 0);

	linfo.flagH = info.flagHigh;
	linfo.H = info.High;
	linfo.flagL = info.flagLow;
	linfo.L = info.Low;

	DEBUGPRINT("Call lmrcImageSpatialFrequencyFilter\n");
	lmrcImageSpatialFrequencyFilter(&out, &in, linfo, info.mode);

	DEBUGPRINT("Call mrcFileWrite\n");
	mrcFileWrite(&out, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
filterFileRead(FILE* fpt, lmrcImageSpatialFrequencyFilterInfo* linfo , int colR, int colW, int mode)
{
	char s[1024];
	int count;

	DEBUGPRINT("filterFileRead Start\n");
	count = 0;
	fseek(fpt, 0L, SEEK_SET);
	while(NULL!=stringGetFromFile(s, "in filterFileRead", fpt, stdout, 3)) {
		count++;
	}
	DEBUGPRINT1("Count: %d\n", count);
	linfo->nR = count;
	linfo->R = (double*)memoryAllocate(sizeof(double)*linfo->nR, "in filterFileRead");
	linfo->W = (double*)memoryAllocate(sizeof(double)*linfo->nR, "in filterFileRead");

	fseek(fpt, 0L, SEEK_SET);

	count=0;
	while(NULL!=stringGetFromFile(s, "in filterFileRead", fpt, stdout, 3)) {
		linfo->R[count] = stringGetNthRealData(s, colR, " \t");
		linfo->W[count] = stringGetNthRealData(s, colW, " \t");
		DEBUGPRINT2("%f %g\n", linfo->R[count], linfo->W[count]);
		count++;
	}
	DEBUGPRINT("filterFileRead End\n");
}
