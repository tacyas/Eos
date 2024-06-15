/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataRescaling ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataRescaling 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%lllDataRescaling ver%I%; Date:%D% %Z%";
#include "genUtil.h"
#include "../inc/llData.h"
#include "lllDataRescaling.h"

void
lllDataRescaling(llData* llOut, llData* llIn, lllDataRescalingInfo linfo, long  mode) 
{
	llDataParaTypeInteger l;
	llDataParaTypeInteger iR;
	llDataParaTypeReal    R;
	double re, im;

	*llOut = *llIn;

	llDataHeaderInit(llOut);
	llDataRRInfoSet(llIn);
	
	for(l=0; l<llOut->llMax; l++) {
		if(0==linfo.delBR) {
			linfo.delBR = llIn->LL[l].delBR;
		}
		llOut->LL[l]  = llIn->LL[l];
		llOut->LL[l].delBR = linfo.delBR;
		llOut->LL[l].iRMin  = floor((llIn->LL[l].RMin*linfo.rScale)/linfo.delBR + 0.5);
		llOut->LL[l].RMin   = llOut->LL[l].iRMin*llOut->LL[l].delBR;
		llOut->LL[l].iRMax  = floor((llIn->LL[l].RMax*linfo.rScale)/linfo.delBR + 0.5);
		llOut->LL[l].RMax   = llOut->LL[l].iRMax*llOut->LL[l].delBR;
		llOut->LL[l].nR = llOut->LL[l].iRMax - llOut->LL[l].iRMin + 1;
	}

	llDataDataInit(llOut);

	for(l=0; l<llOut->llMax; l++) {
		for(iR=0; iR<llOut->LL[l].nR; iR++) {
			R = llOut->LL[l].RMin + iR*llOut->LL[l].delBR;
			llDataValueGet(llIn, l, R, &re, &im);  
			llOut->LL[l].data[iR].RR  = R; 	
			llOut->LL[l].data[iR].Re  = re;
			llOut->LL[l].data[iR].Im  = im;
		}
	}
	llDataFandPHISet(llOut);
}
