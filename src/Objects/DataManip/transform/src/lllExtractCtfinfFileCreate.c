/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllExtractCtfinfFileCreate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllExtractCtfinfFileCreate 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllExtractCtfinfFileCreate ver%I%; Date:%D% %Z%";

#include "lllExtractCtfinfFileCreate.h"

void
llExtractCtfinfFileCreateI(infoDataList* linfo,
						   ctfInfo* CTFInfo,
						   ctfInfoZeroPoint* CTFInfoZeroPoint)
{
	float FirstZero;

		if (linfo->flagFirstZero){
			FirstZero = linfo->FirstZero;
			DEBUGPRINT1("FirstZero %15.6f in direct\n",FirstZero);
		} else {
			FirstZero = ctfZeroPoint(CTFInfo, CTFInfoZeroPoint, 0)
			DEBUGPRINT1("FirstZero %15.6f in ctfZeroPoint\n",FirstZero);
		}
		
	fprintf(linfo->fptOut, "%15.6f   -1 0\n",0.0);
	fprintf(linfo->fptOut, "%15.6f   -1 0\n",FirstZero);
	fprintf(linfo->fptOut, "%15.6f    0 0\n",FirstZero);
}

void
llExtractCtfinfFileCreateII(infoDataList* linfo,
							ctfInfo* CTFInfo)
{
	fprintf(linfo->fptOut, "%15.6f %15.6f %15.6f %15.6f\n",
							CTFInfo->defocus, CTFInfo->Cs, CTFInfo->kV, CTFInfo->ratioOfAmpToPhase);
}

