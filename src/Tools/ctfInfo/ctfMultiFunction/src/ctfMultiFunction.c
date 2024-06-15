/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfMultiFunction ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfMultiFunction
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfMultiFunction ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "eosString.h"
#include "genUtil.h"
#define SECTION_MARK " \t,"
#include "Memory.h"
#include "ctfInfo.h"

int
main(int argc, char* argv[]) 
{
	ctfMultiFunctionInfo info;
	float R;
	ctfInfo* CTFInfo;
	long i;
	char s[GEN_UTIL_MAX_STRING_LENGTH];
	FILE* fpt;
	float data=0;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	memoryClear(&(CTFInfo), sizeof(CTFInfo), 0);
	fpt = info.fptInList;
	fseek(fpt, 0L, SEEK_SET);

	DEBUGPRINT1("info.flagIn [%ld]\n",info.flagIn);

	CTFInfo =(ctfInfo*)memoryAllocate(info.flagIn*sizeof(ctfInfo), "in main");

	for(i=0; i<info.flagIn; i++) {
		stringGetFromFile(s, "", fpt, stdout, 1);
		CTFInfo[i].defocus           = stringGetNthRealData(s, 1, SECTION_MARK);
		CTFInfo[i].Cs                = stringGetNthRealData(s, 2, SECTION_MARK);
		CTFInfo[i].kV                = stringGetNthRealData(s, 3, SECTION_MARK);
		CTFInfo[i].ratioOfAmpToPhase = stringGetNthRealData(s, 4, SECTION_MARK);
		DEBUGPRINT4("defocus [%15.6f] Cs [%15.6f] kV[%15.6f] AmplitudeContrast[%15.6f]\n",
															CTFInfo[i].defocus,
															CTFInfo[i].Cs,
															CTFInfo[i].kV,
															CTFInfo[i].ratioOfAmpToPhase);
		CTFInfo[i].mode = info.ctfMode;
		CTFInfo[i].Ain = info.Ain;
		/*
		CTFInfo[i].WhiteNoise = info.WhiteNoise;
		*/
	}

	for(R=0; R<info.Rmax; R+=info.dR) {
		for(i=0; i<info.flagIn; i++) {
			data = data + fabs(ctfFunction(&CTFInfo[i], R, 0));
		}
		data = data/info.flagIn;

		fprintf(info.fptOut, "%e %e\n", R, data);
		DEBUGPRINT2("R [%15.6f] data [%15.6f] \n", R, data);

		data = 0;
	}

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
	fprintf(stderr, ">>>> ctfMode <<<< \n");
	fprintf(stderr, " 0: Phase CTF \n");
	fprintf(stderr, " 1: PhaseCTF + ratio*AmpCTF \n");
	fprintf(stderr, " 32: EnvFromAillumination*()\n");
	fprintf(stderr, ">>>> File Format <<<< \n");
	fprintf(stderr, "Defocus[A] Cs[mm] AccV[kV] AmplitudeContrast \n");
	fprintf(stderr, "Info file was made by llExtractWithLayerSeparationFilamentInfo -oI \n");
}
