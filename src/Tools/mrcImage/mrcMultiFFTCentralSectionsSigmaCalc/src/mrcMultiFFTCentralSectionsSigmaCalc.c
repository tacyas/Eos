/*
# mrcMultiFFTCentralSectionsSigmaCalc : $Revision$
# $Date$
# Created by $Author$
# Usage : mrcMultiFFTCentralSectionsSigmaCalc
# Attention
#   $Loccker$
#  	$State$
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lmrcFFTCentralSection.h"

int
main(int argc, char* argv[])
{
	mrcMultiFFTCentralSectionsSigmaCalcInfo info;
	lmrcMultiFFTCentralSectionsCompareInfo linfo;
	lmrcMultiFFTCentralSectionsCompareInfoOut* likelihood;
	mrcImage in;
	mrcImage sigma;
	mrcImage volume;
	char filename[1024];
	char filename0[1024];
	char buf[1024];
	char s[2048];
	int i;

	init0(&info);
	argCheck(&info, argc, argv);
	init1(&info);

	DEBUGPRINT("Program Start\n");

	sprintf(filename, "%s%s", info.PathIn, info.In);
	DEBUGPRINT1("In: %s\n", filename);
	mrcFileRead(&in, filename, "in main", 0);

// Euler angle setting
	DEBUGPRINT("EulerSetting\n");
	strncpy(linfo.EulerMode, info.EulerMode, 4);
	strncpy(linfo.llinfo.llinfo.EulerMode, info.EulerMode, 4);
	linfo.llinfo.llinfo.TransX = info.TransX;
	linfo.llinfo.llinfo.TransY = info.TransY;
	linfo.llinfo.llinfo.InterpMode = info.InterpMode;

//Rot1
	linfo.llinfo.Rot1Start = info.Rot1Start*RADIAN;
	linfo.llinfo.Rot1End = info.Rot1End*RADIAN;
	linfo.llinfo.Rot1Delta = info.Rot1Delta*RADIAN;
	linfo.llinfo.nRot1 = MAX(1,(int)(fabs((linfo.llinfo.Rot1End - linfo.llinfo.Rot1Start)/linfo.llinfo.Rot1Delta)+0.5));

//Rot2
	linfo.llinfo.Rot2Start = info.Rot2Start*RADIAN;
	linfo.llinfo.Rot2End = info.Rot2End*RADIAN;
	linfo.llinfo.Rot2Delta = info.Rot2Delta*RADIAN;
	linfo.llinfo.nRot2 = MAX(1,(int)(fabs((linfo.llinfo.Rot2End - linfo.llinfo.Rot2Start)/linfo.llinfo.Rot2Delta)+0.5));

//Rot3
	linfo.llinfo.Rot3Start = info.Rot3Start*RADIAN;
	linfo.llinfo.Rot3End = info.Rot3End*RADIAN;
	linfo.llinfo.Rot3Delta = info.Rot3Delta*RADIAN;
	linfo.llinfo.nRot3 = MAX(1,(int)(fabs((linfo.llinfo.Rot3End - linfo.llinfo.Rot3Start)/linfo.llinfo.Rot3Delta)+0.5));

	linfo.llinfo.RotSize = ((linfo.llinfo.nRot1))*((linfo.llinfo.nRot2))*((linfo.llinfo.nRot3));

// Size
	linfo.OutSize = info.flagIn3D;
	linfo.PriorSize = info.flagIn3D;

	// Likelihood 
	likelihood = memoryAllocate(sizeof(lmrcMultiFFTCentralSectionsCompareInfoOut)*info.flagInLikelihood, "in main");
	rewind(info.fptInLikelihoodList);
	for(i=0; i<info.flagInLikelihood; i++) {
		fgets(s, 1024, info.fptInLikelihoodList); 
		sscanf(s, "%s %s %lf %lf %lf %s %d %lf", filename, 
			likelihood[i].EulerMode, &likelihood[i].Rot[0], &likelihood[i].Rot[1], &likelihood[i].Rot[2], 
			likelihood[i].volume, &likelihood[i].OriginNum, &likelihood[i].Likelihood);
		sprintf(filename0, "%s%s", info.PathL, filename);
		//DEBUGPRINT2("Likelihood %d: %s\n", i, filename0);
		//mrcFileRead(&likelihood[i].out, filename0, "in main", 0);	
		likelihood[i].Rot[0] = likelihood[i].Rot[0]/DEGREE;
		likelihood[i].Rot[1] = likelihood[i].Rot[1]/DEGREE;
		likelihood[i].Rot[2] = likelihood[i].Rot[2]/DEGREE;
		i++;
	}

	// Out
	linfo.Out = memoryAllocate(sizeof(lmrcMultiFFTCentralSectionsCompareInfoOut)*info.flagIn3D, "in main");
	rewind(info.fptIn3DList);
	DEBUGPRINT1("flagIn3D: %d\n", info.flagIn3D);
	for(i=0; i<info.flagIn3D; i++) {
		fgets(s, 1024, info.fptIn3DList);
		sscanf(s, "%s %s %lf %lf %lf %s %d", filename, 
			linfo.Out[i].EulerMode, &linfo.Out[i].Rot[0], &linfo.Out[i].Rot[1], &linfo.Out[i].Rot[2], 
			linfo.Out[i].volume, &linfo.Out[i].OriginNum);
		DEBUGPRINT2("Ref: %d: %s\n", i, filename);
		sprintf(filename0, "%s%s", info.Path3D, filename);
		mrcFileRead(&(linfo.Out[i].out), filename0, "in main", 0);
		linfo.Out[i].Rot[0] = linfo.Out[i].Rot[0]/DEGREE;
		linfo.Out[i].Rot[1] = linfo.Out[i].Rot[1]/DEGREE;
		linfo.Out[i].Rot[2] = linfo.Out[i].Rot[2]/DEGREE;
	}

	DEBUGPRINT("Start Calc\n");
	lmrcMultiFFTCentralSectionsSigma(&sigma, linfo.Out, &in, &linfo, info.mode);
	DEBUGPRINT("End Calc\n");

	mrcFileWrite(&sigma, info.Out, "in main", 0);
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
