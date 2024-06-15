/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% mrcImageColorlizing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : mrcImageColorlizing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%mrcImageColorlizing ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"
#include "mrcImage.h"
#include "gifFile.h"
#define DEBUG

#include "genUtil.h"

int
main(int argc, char* argv[]) 
{
	long status;
	mrcImageColoringInfo info;
	mrcImage or;
	mrcImage r;
	mrcImage og;
	mrcImage g;
	mrcImage ob;
	mrcImage b;
	int n;
	int nr, ng, nb;
	ColorMapObject* ColorMap;

	fprintf(stdout, "init"); fflush(stdout); 
	DEBUGPRINT("Init--");
	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	fprintf(stdout, "start"); fflush(stdout); 
	DEBUGPRINT("Start--");
	if(info.flagrIn) {
		mrcFileRead(&or, info.rIn, "in main", 0);
		mrcImageSectionGet(&r, &or, 0, 0);
		mrcStatDataSet(&r, 0);
		nr=0;
	} else {
		r.HeaderN.x = r.HeaderN.y = r.HeaderN.z = 0;
		nr = 1;
	}
	if(info.flaggIn) {
		mrcFileRead(&og, info.gIn, "in main", 0);
		mrcImageSectionGet(&g, &og, 0, 0);
		mrcStatDataSet(&g, 0);
		ng=0;
	} else {
		g.HeaderN.x = g.HeaderN.y = g.HeaderN.z = 0;
		ng = 1;
	}
	if(info.flagbIn) {
		mrcFileRead(&ob, info.bIn, "in main", 0);
		mrcImageSectionGet(&b, &ob, 0, 0);
		mrcStatDataSet(&b, 0);
		nb=0;
	} else {
		b.HeaderN.x = b.HeaderN.y = b.HeaderN.z = 0;
		nb = 1;
	}
	if(nr==1) {
		if(ng==1) {
			if(nb==1) {
				;
			} else {
				nb = 256;
			}
		} else {
			if(nb==1) {
				ng = 256;
			} else {
				ng = 16;
				nb = 16;
			}
		}
	} else {
		if(ng==1) {
			if(nb==1) {
				nr = 256;
			} else {
				nr = 16; 
				nb = 16;
			}
		} else {
			if(nb==1) {
				nr = 16;
				ng = 16;
			} else {
				nr = 6;
				ng = 6;
				nb = 6;
			}
		}
	}
	n = nr*ng*nb;

	fprintf(stdout, "colormpa"); fflush(stdout); 
	DEBUGPRINT("ColorMap--");
	ColorMap = gifColorMapInit(n, (long)NULL);
	gifColorMapColor(ColorMap, n, nr, ng, nb); 
	
	fprintf(stdout, "gifColor"); fflush(stdout); 
	if(info.flagrHigh) {
		r.HeaderAMax = info.rHigh;
	}
	if(info.flaggHigh) {
		g.HeaderAMax = info.gHigh;
	}
	if(info.flagbHigh) {
		b.HeaderAMax = info.bHigh;
	}
	if(info.flagrLow) {
		r.HeaderAMin = info.rLow;
	}
	if(info.flaggLow) {
		g.HeaderAMin = info.gLow;
	}
	if(info.flagbLow) {
		b.HeaderAMin = info.bLow;
	}

	DEBUGPRINT("lmrc2gifColor--");
	lmrc2gifColor(info.Out, &r, &g, &b, ColorMap, n, nr, ng, nb, 0);

	fprintf(stdout, "end"); fflush(stdout); 
	return 0;
}

void
additionalUsage()
{
}
