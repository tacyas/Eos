/*
# mrcFFTSpectrum : $Revision$  
# $Date$ 
# Created by $Author$
# Usage : mrcFFTSpectrum
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

#define DEBUG
#include "genUtil.h"
#include "Vector.h"
#include "mrcImage.h"
#include "lmrcFFTInfo.h"

typedef struct lmrcFFTSpectrumInfo {
	floatVector** spectrum;
	floatVector*  R;
	int 		N;
	mrcImageParaTypeReal Axis; 
} lmrcFFTSpectrumInfo;
/*
typedef enum lmrcFFTSpectrumMode {
	a=0,
	b=1
} lmrcFFTSpectrumMode;
*/


extern int	spectrumPrint(lmrcFFTSpectrumInfo* linfo, FILE* fpt, int mode);

int
main(int argc, char* argv[]) 
{
	mrcFFTSpectrumInfo  info;
	lmrcFFTSpectrumInfo linfo;
	mrcImage mrc;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	linfo.N = info.N;
	linfo.Axis = info.Axis*RADIAN;
	DEBUGPRINT("Program Start\n");
	mrcFileRead(&mrc, info.In, "in main", 0);

	linfo.spectrum = lmrcFSInfoScatteringAngularDistributionDivisionAverage(
			&mrc, 
			linfo.Axis, linfo.N, info.mode);

	linfo.R       = lmrcFSInfoSpacing(&mrc);

	spectrumPrint(&linfo, info.fptOut, info.mode);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}


int	
spectrumPrint(lmrcFFTSpectrumInfo* linfo, FILE* fpt, int mode)
{
	int i, j;
	for(j=0; j<linfo->spectrum[0]->size; j++) {
		fprintf(fpt, "%15.6g ", linfo->R->data[j]);
		for(i=0; i<linfo->N; i++) {
			fprintf(fpt, "%15.6g ", linfo->spectrum[i]->data[j]);
		}	
		fprintf(fpt, "\n");
	}
}

