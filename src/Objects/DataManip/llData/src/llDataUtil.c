/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataUtil ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>
#include "Memory.h"
#include "../inc/llData.h"

#undef DEBUG
#include "genUtil.h"

void
llDataRValueSet(llData* ll, int mode)
{
	llDataParaTypeInteger l;
	llDataParaTypeInteger iRR;
	double Z;

	if(ll->RValueSet) {
		fprintf(stderr, "You already set RValue \n");
		return;
	} 
	if(!ll->ZValueSet) {
		llDataZValueSet(ll, 0);
	}
	for(l=0; l<ll->llMax; l++) {
		Z = ll->LL[l].Z;
		for(iRR=0; iRR<ll->LL[l].nR; iRR++) {
			ll->LL[l].data[iRR].R = sqrt(SQR(ll->LL[l].data[iRR].RR) + SQR(Z)); 
		}
	}
	ll->RValueSet = 1;
}

void
llDataFmaxSet(llData* ll, int mode)
{
	llDataParaTypeInteger l;
	llDataParaTypeInteger iRR;
	double Fmax;
	for(l=0; l<ll->llMax; l++) {
		Fmax = 0.0;
		for(iRR=0; iRR<ll->LL[l].nR; iRR++) {
			if(Fmax < ll->LL[l].data[iRR].F) {
				Fmax = ll->LL[l].data[iRR].F;
			}
		}
		ll->LL[l].Fmax = Fmax;
	}
	ll->FmaxSet = 1;
}

void
llDataZValueSet(llData* ll, int mode)
{
	llDataParaTypeInteger l;
	double Z;

	if(ll->ZValueSet) {
		fprintf(stderr, "You already set ZValue \n");
		return;
	} 
	for(l=0; l<ll->llMax; l++) {
		ll->LL[l].Z = ll->LL[l].nl/ll->truePitch; 
	}
	ll->ZValueSet = 1;
}

llDataParaTypeInteger*
llDataTableBetweenTwollDataCreate(llData* ll1, llData* ll2, int mode)
{
	llDataParaTypeInteger* table;
	llDataParaTypeInteger l1, l2;

	table = (llDataParaTypeInteger*)memoryAllocate(sizeof(llDataParaTypeInteger)*ll1->llMax, 
							"in llDataTableBetweenTwollDataCreate"); 
	switch(mode) {
		case 0: {
			for(l1=0; l1 < ll1->llMax; l1++) {
				for(l2=0; l2 < ll2->llMax; l2++) {
					if(ll1->LL[l1].nl == ll2->LL[l2].nl
					&& ll1->LL[l1].nn == ll2->LL[l2].nn) {
						table[l1] = l2;
						break;	
					} else {
						table[l1] = ll2->llMax;
					}
				}
			}
			break;
		}
		case 1: {
			for(l1=0; l1 < ll1->llMax; l1++) {
				table[l1] = l1;
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported mode in llDataTableBetweenTwollDataCreate: %d\n", mode);
			exit(EXIT_FAILURE);
		}
	}
	return table;
}

inline
llDataParaTypeReal 
nearSidePhaseGet(llDataParaTypeReal phase, llDataParaTypeInteger nn, llDataParaTypeInteger side, llDataParaTypeInteger pole)
{
    llDataParaTypeReal fpole;
    llDataParaTypeReal p;
 	
	switch(pole) {
    	case llDataPoleNormal: {
       		fpole = 1.0;
			break;
		}
		case llDataPoleAnti: {
        	fpole = -1.0;
			break;
		}
		default: {
        	ERRORPRINT1("The pole value (%d) is wrong in nearSidePhaseGet\n", pole);
			break;
		}
    }
	switch(side) {
		case FarSide: {
			p = fpole*(phase+nn*PI);
			DEBUGPRINT4("FarSide: side:%d pole:%d --- %f -> %f\n", side, pole, phase, p);
			break;
		}
		case AverageSide:
		case NearSide: {
			p = fpole*phase;
			DEBUGPRINT4("NeaSide: side:%d pole:%d --- %f -> %f\n", side, pole, phase, p);
			break;
		}
		default: {
        	ERRORPRINT1("The side value (%d) is wrong in nearSidePhaseGet\n", side);
			break;
		}
	}
    return NORMAL_PHASE(p);
}

llDataParaTypeReal 
farSidePhaseGet(llDataParaTypeReal phase, llDataParaTypeInteger nn, llDataParaTypeInteger side, llDataParaTypeInteger pole)
{
 	llDataParaTypeReal p;

	p = nearSidePhaseGet(phase, nn, side, pole);
    return NORMAL_PHASE(p - nn*M_PI);
}

void
lllDataAttributeCopy(llData* ll1, llData* ll2)
{
	int l, r;
	oneLLData* lltmp;
	llComplex* tmp;

	lltmp = ll1->LL;
	*ll1 = *ll2;
	ll1->LL = lltmp;
	for(l=0; l<ll2->llMax; l++) {
		tmp = ll1->LL[l].data;
		ll1->LL[l] = ll2->LL[l];
		ll1->LL[l].data = tmp;
		for(r=0; r<ll2->LL[l].nR; r++) {
			ll1->LL[l].data[r].R  = ll2->LL[l].data[r].R;
			ll1->LL[l].data[r].RR = ll2->LL[l].data[r].RR;
		}
	}
}

void
lllDataHeaderCopy(llData* ll1, llData* ll2)
{
	int l;
	oneLLData* lltmp;
	llComplex* tmp;

	lltmp = ll1->LL;
	*ll1 = *ll2;
	ll1->LL = lltmp;
	for(l=0; l<ll2->llMax; l++) {
		tmp = ll1->LL[l].data;
		ll1->LL[l] = ll2->LL[l];
		ll1->LL[l].data = tmp;
	}
}

void
lllDataCopy(llData* ll1, llData* ll2)
{
	int l, r;
	oneLLData* lltmp;
	llComplex* tmp;

	lltmp = ll1->LL;
	*ll1 = *ll2;
	ll1->LL = lltmp;
	for(l=0; l<ll2->llMax; l++) {
		tmp = ll1->LL[l].data;
		ll1->LL[l] = ll2->LL[l];
		ll1->LL[l].data = tmp;
		for(r=0; r<ll2->LL[l].nR; r++) {
			ll1->LL[l].data[r] = ll2->LL[l].data[r];
		}
	}
}

void
lllDataClear(llData* ll1)
{
    int l, r;

    for(l=0; l<ll1->llMax; l++) {
    	for(r=0; r<ll1->LL[l].nR; r++) {
            ll1->LL[l].data[r].Re  = 0;
            ll1->LL[l].data[r].Im  = 0;
            ll1->LL[l].data[r].F   = 0;
            ll1->LL[l].data[r].PHI = 0; 
    	}
    }
}

void
lllDataMul(llData* ll1, llData* ll2)
{
    int l, r;
    double PHI, F;

	switch(ll1->LL[0].Side) {
		case NearSide:
		case AverageSide: {
			switch(ll2->LL[0].Side) {
				case NearSide:
				case AverageSide: {
	    			for(l=0; l<ll2->llMax; l++) {
   		 				for(r=0; r<ll2->LL[l].nR; r++) {
            				ll1->LL[l].data[r].F   *= ll2->LL[l].data[r].F;
            				ll1->LL[l].data[r].PHI += ll2->LL[l].data[r].PHI;
            				ll1->LL[l].data[r].Re   = ll1->LL[l].data[r].F*cos(ll1->LL[l].data[r].PHI);
            				ll1->LL[l].data[r].Im   = ll1->LL[l].data[r].F*sin(ll1->LL[l].data[r].PHI);
						}
					}
					break;
				}
				case FarSide: {
	    			for(l=0; l<ll2->llMax; l++) {
   		 				for(r=0; r<ll2->LL[l].nR; r++) {
							PHI = nearSidePhaseGet(ll2->LL[l].data[r].PHI, ll2->LL[l].nn, ll2->Side, ll2->Pole);
							F = ll2->LL[l].data[r].F;
            				ll1->LL[l].data[r].F   *= F;
            				ll1->LL[l].data[r].PHI += PHI;
            				ll1->LL[l].data[r].Re   = ll1->LL[l].data[r].F*cos(ll1->LL[l].data[r].PHI);
            				ll1->LL[l].data[r].Im   = ll1->LL[l].data[r].F*sin(ll1->LL[l].data[r].PHI);
						}
					}
					break;
				}
				default: {
					fprintf(stderr, "Not Supported Side in lllDataAdd\n");
					exit(EXIT_FAILURE);
					break;
				}
    		}
			break;
		}
		case FarSide: {
			switch(ll2->LL[0].Side) {
				case FarSide: {
	    			for(l=0; l<ll2->llMax; l++) {
   		 				for(r=0; r<ll2->LL[l].nR; r++) {
            				ll1->LL[l].data[r].F   *= ll2->LL[l].data[r].F;
            				ll1->LL[l].data[r].PHI += ll2->LL[l].data[r].PHI;
            				ll1->LL[l].data[r].Re   = ll1->LL[l].data[r].F*cos(ll1->LL[l].data[r].PHI);
            				ll1->LL[l].data[r].Im   = ll1->LL[l].data[r].F*sin(ll1->LL[l].data[r].PHI);
						}
					}
					break;
				}
				case NearSide:
				case AverageSide: {
	    			for(l=0; l<ll2->llMax; l++) {
   		 				for(r=0; r<ll2->LL[l].nR; r++) {
							PHI = farSidePhaseGet(ll2->LL[l].data[r].PHI, ll2->LL[l].nn, ll2->LL[l].Side, ll2->Pole);
							F = ll2->LL[l].data[r].F;
            				ll1->LL[l].data[r].F   *= F;
            				ll1->LL[l].data[r].PHI += PHI;
            				ll1->LL[l].data[r].Re   = ll1->LL[l].data[r].F*cos(ll1->LL[l].data[r].PHI);
            				ll1->LL[l].data[r].Im   = ll1->LL[l].data[r].F*sin(ll1->LL[l].data[r].PHI);
						}
					}
					break;
				}
				default: {
					fprintf(stderr, "Not Supported Side in lllDataAdd\n");
					exit(EXIT_FAILURE);
					break;
				}
    		}
			break;
		}
		default: {
			fprintf(stderr, "Not Supported Side in lllDataAdd\n");
			exit(EXIT_FAILURE);
			break;
		}
	}		
}

void
lllDataPoleSet(llData* ll1, llDataPole pole) 
{
    ll1->Pole = pole;
}
void
lllDataSideSet(llData* ll1, llDataParaTypeInteger Side)
{
	int l;

    for(l=0; l<ll1->llMax; l++) {
        ll1->LL[l].Side = Side;
    }
}

void
lllDataDevidedByReal(llData* ll1, llDataParaTypeReal f)
{
    int l, r;

    for(l=0; l<ll1->llMax; l++) {
    	for(r=0; r<ll1->LL[l].nR; r++) {
            ll1->LL[l].data[r].Re  /= f;
            ll1->LL[l].data[r].Im  /= f;
            ll1->LL[l].data[r].F   /= f;
    	}
    }
}


void
lllDataMultiplyReal(llData* ll1, llDataParaTypeReal f)
{
    int l, r;

    for(l=0; l<ll1->llMax; l++) {
    	for(r=0; r<ll1->LL[l].nR; r++) {
            ll1->LL[l].data[r].Re  *= f;
            ll1->LL[l].data[r].Im  *= f;
            ll1->LL[l].data[r].F   *= f;
    	}
    }
}

