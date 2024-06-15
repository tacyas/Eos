/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataSeparationInfoSet ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lllDataSeparationInfoSet 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%llDataSeparationInfoSet ver%I%; Date:%D% %Z%";

#include "lllExtract.h"

void
lllDataSeparationInfoDelRInvSet(lllExtractInfo* leInfo, llDataParaTypeReal delRInv)
{
	if(fabs(delRInv-leInfo->delRInv)>1e-6) {
		fprintf(stderr, "Different Value of delRInv: dst(%e) != src(%e)\n", 
			delRInv, leInfo->delRInv);
		fprintf(stderr, "Use %e\n", delRInv);
	}
	leInfo->delRInv = delRInv;
}

void
lllDataSeparationInfoTruePitchSet(lllExtractInfo* leInfo, llDataParaTypeReal truePitch)
{
	if(fabs(truePitch-leInfo->truePitch)>1e-6) {
		fprintf(stderr, "Different Value of truePitch: dst(%e) != src(%e)\n", 
			truePitch, leInfo->truePitch);
		fprintf(stderr, "Use %e\n", truePitch);
	}
	leInfo->truePitch = truePitch;
}


void
lllDataSeparationInfoxShiftSet(lllExtractInfo* leInfo, llDataParaTypeReal xShift)
{
	if(fabs(xShift-leInfo->xShift)>1e-6) {
		fprintf(stderr, "Different Value of xShift: dst(%e) != src(%e)\n", 
			xShift, leInfo->xShift);
		fprintf(stderr, "Use %e\n", xShift);
	}
	leInfo->xShift = xShift;
}


