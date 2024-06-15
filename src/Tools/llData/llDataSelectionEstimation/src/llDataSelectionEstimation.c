/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataSelectionEstimation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataSelectionEstimation
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataSelectionEstimation ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "llData.h"
#include "Memory.h"

typedef struct lllDataSelectionEstimationInfo {
	int t;
	int u;
	float m1;	
	float m2;	
	float r;	
} lllDataSelectionEstimationInfo;

int
main(int argc, char* argv[]) 
{
	llDataSelectionEstimationInfo info;
	int t, u, nmax, i;
	lllDataSelectionEstimationInfo* linfo;
	int im1, im2;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	nmax = (2*info.tmax+1)*(info.umax-1);
	linfo=(lllDataSelectionEstimationInfo*)memoryAllocate(sizeof(lllDataSelectionEstimationInfo)*nmax, "in main"); 
	i = 0;
	for(t=-info.tmax; t<=info.tmax; t++) {
	for(u=2; u<=info.umax; u++) {
		linfo[i].t = t;
		linfo[i].u = u;
		linfo[i].m1 = (info.L1 - t*info.N1)/u;
		if(0<=linfo[i].m1) {
			im1 = (int)(linfo[i].m1+0.5);
		} else {
			im1 = (int)(linfo[i].m1-0.5);
		}
		linfo[i].m2 = (info.L2 - t*info.N2)/u;
		if(0<=linfo[i].m2) {
			im2 = (int)(linfo[i].m2+0.5);
		} else {
			im2 = (int)(linfo[i].m2-0.5);
		}
		linfo[i].r  = sqrt((SQR(linfo[i].m1-im1)+SQR(linfo[i].m2-im2))/2.0);	
		if(linfo[i].r<info.r) {
			fprintf(info.fptOut, "t: %d u: %d m1: %15.6g m2: %15.6g r: %15.6g\n", 
				linfo[i].t, linfo[i].u, linfo[i].m1, linfo[i].m2, linfo[i].r);
		}
		i++;
	}
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}
