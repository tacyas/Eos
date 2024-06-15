/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataInterpolate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataInterpolate 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%lllDataInterpolate ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../inc/llData.h"
#include "genUtil.h"
#include "Memory.h"

/*
	lllDataInterpolate
*/

void
lllDataInterpolate(llData* llOut, llData* llIn, llDataParaTypeReal deltaR)
{
    llDataParaTypeInteger l, iR;
    llDataParaTypeReal    R;
	double re, im;

	llDataRRInfoSet(llIn);
    if(llOut->mode!=llDataModeMemoryAllocate) {
        *llOut = *llIn;
        llDataInit(llOut);
    }
    if(llOut->llMax<llIn->llMax) {
        fprintf(stderr, "llOut is smaller than llIn in lllDataInterpolate\n");
        exit(EXIT_FAILURE);
    }

    for(l=0; l<llIn->llMax; l++) {
		/* Set RR */
		free(llOut->LL[l].data);
		llOut->LL[l] = llIn->LL[l];
		llOut->LL[l].delBR = deltaR;
		llOut->LL[l].iRMin = floor(llOut->LL[l].RMin/llOut->LL[l].delBR + 0.5);	
		llOut->LL[l].iRMax = floor(llOut->LL[l].RMax/llOut->LL[l].delBR + 0.5);	
		llOut->LL[l].RMin  = llOut->LL[l].iRMin*deltaR;
		llOut->LL[l].RMax  = llOut->LL[l].iRMax*deltaR;
		llOut->LL[l].nR    = llOut->LL[l].iRMax - llOut->LL[l].iRMin + 1;
		llOut->LL[l].data = (llComplex*)memoryAllocate(sizeof(llComplex)*llOut->LL[l].nR, "in lllDataInterpolate"); 
		/* */
        for(R=llOut->LL[l].RMin, iR=0; iR<llOut->LL[l].nR; R+=deltaR, iR++) {
			llDataValueGet(llIn, l, R, &re, &im);
			llOut->LL[l].data[iR].Re = re;
			llOut->LL[l].data[iR].Im = im;
        }
    }
	llDataFandPHISet(llOut);
}

