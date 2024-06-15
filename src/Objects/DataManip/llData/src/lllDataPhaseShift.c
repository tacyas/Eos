/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataPhaseShift ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataPhaseShift
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataPhaseShift ver%I%; Date:%D% %Z%";

#define UNDEBUG
#include "genUtil.h"
#include <stdlib.h>
#include <math.h>
#include "../inc/llData.h"
#include "lllDataFit.h"
#include "lllDataFitParamInverse.h"

/*
	llDataPhaseShift(
		llData* ll1,     LayerLineData Pointer to be treated
		llData* ll2,     LayerLineData Pointer to be treated
        llDataFittedParam* p
		);  

*/

void
lllDataPhaseShiftInverse(llData* ll1, llData* ll2, llDataFittedParam* p)
{
	llData lltmp;
	llDataFittedParam pInv;	
	
	lllDataFitParamInverse(&pInv, p); 

	llDataInitWithReference(&lltmp, ll2);
  	lllDataPhaseShiftInter(&lltmp, ll2, &pInv);
	lllDataPhaseShiftIntra(ll1, &lltmp, &pInv);
	llDataFree(&lltmp);
}

void
lllDataPhaseShift(llData* ll1, llData* ll2, llDataFittedParam* p)
{
	llData lltmp;

	llDataInitWithReference(&lltmp, ll2);
	lllDataPhaseShiftIntra(&lltmp, ll2, p);
  	lllDataPhaseShiftInter(ll1, &lltmp, p);
	llDataFree(&lltmp);
}

void
lllDataPhaseShiftIntra(llData* ll1, llData* ll2, llDataFittedParam* p)
{
    int l, r;
	long sig;
	
	DEBUGPRINT("---- lllDataPhaseShiftIntra Start\n");
	DEBUGPRINT2("shift: %f, Omega: %f\n", p->Para.x.Value, p->Para.Omega.Value);
	lllDataAttributeCopy(ll1, ll2);
    for(l=0; l<ll2->llMax; l++) {
        ll1->LL[l].Z = ll2->LL[l].nl/ll2->truePitch;
        if(   (ll2->LL[l].Side==NearSide&&ll2->LL[l].nn>=0)
            ||(ll2->LL[l].Side==FarSide &&ll2->LL[l].nn< 0)) {
            sig = -1.0;
        } else {
            sig =  1.0;
        }
    	for(r=0; r<ll2->LL[l].nR; r++) {
            ll1->LL[l].data[r]     = ll2->LL[l].data[r];
            ll1->LL[l].data[r].PHI = ll2->LL[l].data[r].PHI - sig*(2*M_PI*ll2->LL[l].data[r].RR*p->Para.x.Value + p->Para.Omega.Value*ll2->LL[l].nn);
    	}
    }
	llDataReAndImSet(ll1);
}

void
lllDataPhaseShiftInter(llData* ll1, llData* ll2, llDataFittedParam* p)
{
    int l, r;
    double sig;

	lllDataAttributeCopy(ll1, ll2);
    if(llDataPoleNormal == p->Para.Pole) {
        sig =  1.0;
    } else if(llDataPoleAnti == p->Para.Pole) {
        sig = -1.0;
    }
    for(l=0; l<ll2->llMax; l++) {
        ll1->LL[l].Z = ll2->LL[l].nl/ll2->truePitch;
    	for(r=0; r<ll2->LL[l].nR; r++) {
            ll1->LL[l].data[r] = ll2->LL[l].data[r];
            ll1->LL[l].data[r].PHI = sig*ll2->LL[l].data[r].PHI - ll2->LL[l].nn*p->Para.phi.Value + 2*M_PI*ll2->LL[l].Z*p->Para.z.Value;
            ll1->LL[l].data[r].Re  = ll1->LL[l].data[r].F*cos(ll1->LL[l].data[r].PHI);
            ll1->LL[l].data[r].Im  = ll1->LL[l].data[r].F*sin(ll1->LL[l].data[r].PHI);
    	}
    }
}

