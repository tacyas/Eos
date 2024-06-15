/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llExtractWithLayerSeparationCtrlFileCreateMyosin ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llExtractWithLayerSeparationCtrlFileCreateMyosin
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llExtractWithLayerSeparationCtrlFileCreateMyosin ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"

typedef struct infoDataList{
	int Y;
} infoDataList;

int
main(int argc, char* argv[]) 
{
	llExtractWithLayerSeparationCtrlFileCreateMyosinInfo info;
	infoDataList linfo;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");

	linfo.Y = info.Y;

		fprintf(info.fptOut, "13\n");
		fprintf(info.fptOut, " 0  %4d   5   0   9  -9  18  -18\n",linfo.Y*0);
		fprintf(info.fptOut, " 1  %4d   4   3  -6  12 -15     \n",linfo.Y*1);
		fprintf(info.fptOut, " 2  %4d   4  -3   6 -12  15     \n",linfo.Y*2);
		fprintf(info.fptOut, " 3  %4d   5   0   9  -9  18  -18\n",linfo.Y*3);
		fprintf(info.fptOut, " 4  %4d   4   3  -6  12 -15     \n",linfo.Y*4);
		fprintf(info.fptOut, " 5  %4d   4  -3   6 -12  15     \n",linfo.Y*5);
		fprintf(info.fptOut, " 6  %4d   5   0   9  -9  18  -18\n",linfo.Y*6);
		fprintf(info.fptOut, " 7  %4d   4   3  -6  12 -15     \n",linfo.Y*7);
		fprintf(info.fptOut, " 8  %4d   4  -3   6 -12  15     \n",linfo.Y*8);
		fprintf(info.fptOut, " 9  %4d   5   0   9  -9  18  -18\n",linfo.Y*9);
		fprintf(info.fptOut, "10  %4d   4   3  -6  12 -15     \n",linfo.Y*10);
		fprintf(info.fptOut, "11  %4d   4  -3   6 -12  15     \n",linfo.Y*11);
		fprintf(info.fptOut, "12  %4d   5   0   9  -9  18  -18\n",linfo.Y*12);

	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
