/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ctfDeterminationFromThonRing ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ctfDeterminationFromThonRing
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ctfDeterminationFromThonRing ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>                  
#define GLOBAL_DECLARATION
#include "../inc/config.h"

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "mrcImage.h"
#include "ctfInfo.h"

typedef struct lctfDeterminationFromThonRingInfo {
	ctfInfo val;
	ctfInfo min;
	ctfInfo max;
	ctfInfo del;
	float*  thonRing; 	
	int     nThonRing;

	double minE;
	double minDef;
	double minAmp;

	mrcImage par;
} lctfDeterminationFromThonRingInfo;

extern void lctfDeterminationFromThonRing(lctfDeterminationFromThonRingInfo* linfo);

void
main(int argc, char* argv[]) 
{
	ctfDeterminationFromThonRingInfo   info;
	lctfDeterminationFromThonRingInfo linfo;
	int i;

	init0(&info);
    argCheck(&info, argc, argv);
    init1(&info);

	DEBUGPRINT("Program Start\n");
	linfo.val.kV = info.kV;
	linfo.val.Cs = info.Cs;
	linfo.val.Ain = 0.02;
	linfo.val.mode = ctfInfoModePhaseAndAmpCTF;
	linfo.min.defocus = info.minDef;
	linfo.max.defocus = info.maxDef;
	linfo.del.defocus = info.delDef;
	linfo.min.ratioOfAmpToPhase = info.minAmp;
	linfo.max.ratioOfAmpToPhase = info.maxAmp;
	linfo.del.ratioOfAmpToPhase = info.delAmp;

	linfo.nThonRing = info.flagR;
	linfo.thonRing = (float*)memoryAllocate(sizeof(float)*linfo.nThonRing, "in main");
	for(i=0; i<linfo.nThonRing; i++) {
		linfo.thonRing[i] = info.R[i];
	}

	lctfDeterminationFromThonRing(&linfo);

	fprintf(info.fptOut, "minE : %f  (%f, %f)\n", linfo.minE, linfo.minDef, linfo.minAmp);

	if(info.flagOut2) {
		mrcFileWrite(&(linfo.par), info.Out2, "in main", 0);
	}
	exit(EXIT_SUCCESS);
}

void
additionalUsage()
{
	fprintf(stderr, "----- Additional Usage -----\n");
}

void
lctfDeterminationFromThonRing(lctfDeterminationFromThonRingInfo* linfo)
{
	ctfInfo   tmp;
	int iDef, nDef;
	int iAmp, nAmp;
	int i;
	double ctf, tmpE;

	nDef = (linfo->max.defocus - linfo->min.defocus)/linfo->del.defocus + 1;
	nAmp = (linfo->max.ratioOfAmpToPhase - linfo->min.ratioOfAmpToPhase)/linfo->del.ratioOfAmpToPhase + 1;

	memoryClear(&(linfo->par.Header.Cont), 1024, 0);
	linfo->par.HeaderN.x = nDef;
	linfo->par.HeaderN.y = nAmp;
	linfo->par.HeaderN.z = 1;
	linfo->par.HeaderMode = mrcFloatImage;
	linfo->par.HeaderLength.x = linfo->del.defocus/1e4; 
	linfo->par.HeaderLength.y = linfo->del.ratioOfAmpToPhase*100;
	DEBUGPRINT2("Length: %f %f\n", linfo->par.HeaderLength.x, linfo->par.HeaderLength.y);
	mrcInit(&(linfo->par), NULL);

	tmp = linfo->val;	
	linfo->minE = 1.0;

	for(iDef=0; iDef<nDef; iDef++) {	
		for(iAmp=0; iAmp<nAmp; iAmp++) {	
			tmp.defocus = iDef*linfo->del.defocus + linfo->min.defocus;	
			tmp.ratioOfAmpToPhase = iAmp*linfo->del.ratioOfAmpToPhase + linfo->min.ratioOfAmpToPhase;	
		
			tmpE = 0.0;
			for(i=0; i<linfo->nThonRing; i++) {
				ctf = ctfFunction(&tmp, linfo->thonRing[i], 0);
				tmpE += fabs(ctf);
			}
			tmpE /= linfo->nThonRing;
			if(tmpE<linfo->minE) {
				linfo->minE   = tmpE;
				linfo->minDef = tmp.defocus;
				linfo->minAmp = tmp.ratioOfAmpToPhase;
				DEBUGPRINT3("%f: (%f, %f)\n", linfo->minE, linfo->minDef, linfo->minAmp);
			}
			mrcPixelDataSet(&(linfo->par), iDef, iAmp, 0.0, tmpE, mrcPixelRePart);
		}
	}
}

