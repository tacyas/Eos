/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataLowPassFiltering ver %I%
#%Z% Created by tacyas@tkyemghp.phys.s.u-tokyo.ac.jp
#%Z%
#%Z% Usage : lllDataLowPassFiltering 
#%Z% Attention 
#%Z%	Mode 0: Memory-unsaved data 
#%Z%	Mode 1: Memory-saved data
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataLowPassFiltering ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "lllDataLowPassFiltering.h"

/*
	Mode 0: Allocation of minimum layer line data
		 1: Assigned zero-values as the maginitude
*/

void
lllDataLowPassFiltering(llData* ll, double RMax, int mode)
{
	int l, R;
	int newnR;
	llComplex* data;

	if(!ll->RValueSet) {
		llDataRValueSet(ll, 0);
	}
	switch(mode) {
		case lllDataLowPassFilteringModeSavedMemorySize: {
			for(l=0; l<ll->llMax; l++) {
				newnR = 0;
				for(R=0; R<ll->LL[l].nR; R++) {
					if(ll->LL[l].data[R].R < RMax) {
						newnR++;
					} else {
						break;
					}
				}
				ll->LL[l].nR = newnR;

				if(0==ll->LL[l].nR) {
					free(ll->LL[l].data);
					ll->LL[l].data = (llComplex*)memoryAllocate(sizeof(llComplex), "in lllDataLowPass");
					ll->LL[l].iRMax = ll->LL[l].iRMin; 
					ll->LL[l].RMax  = ll->LL[l].RMin; 
				} else {
					/* Data Setting */
					data = (llComplex*)memoryAllocate(sizeof(llComplex)*ll->LL[l].nR, 
						"in lllDataLowPassFiltering");
					for(R=0; R<ll->LL[l].nR; R++) {
						data[R] = ll->LL[l].data[R];
					}
					free(ll->LL[l].data);
					ll->LL[l].data = data;

					/* RR Setting */
					ll->LL[l].iRMax = ll->LL[l].iRMin + ll->LL[l].nR - 1; 
					ll->LL[l].RMax  = ll->LL[l].data[ll->LL[l].nR - 1].RR;
				}
			}
			break;
		}
		case lllDataLowPassFilteringModeSameMemorySize: {
			for(l=0; l<ll->llMax; l++) {
				for(R=ll->LL[l].nR-1 ; 0<=R; R--) {
					if(RMax < ll->LL[l].data[R].R) {
						ll->LL[l].data[R].Re  = 0;
						ll->LL[l].data[R].Im  = 0;
						ll->LL[l].data[R].F   = 0;
						ll->LL[l].data[R].PHI = 0;
						DEBUGPRINT4("l: %d R: %d/%d : %g\n", l, R, ll->LL[l].nR, ll->LL[l].data[R].F);
					} else {
						break;
					}
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported in lllDataLowPassFiltering\n");
			exit(EXIT_FAILURE);
			break;
		}
	}
}


void
lllDataRadialLowPassFiltering(llData* ll, double RRMax, int mode)
{
	int l, R;
	int newnR;
	llComplex* data;

	switch(mode) {
		case lllDataLowPassFilteringModeSavedMemorySize: {
			for(l=0; l<ll->llMax; l++) {
				newnR = 0;
				for(R=0; R<ll->LL[l].nR; R++) {
					if(ll->LL[l].data[R].RR < RRMax) {
						newnR++;
					} else {
						break;
					}
				}
				ll->LL[l].nR = newnR;

				if(0==ll->LL[l].nR) {
					free(ll->LL[l].data);
					ll->LL[l].data = (llComplex*)memoryAllocate(sizeof(llComplex), "in lllDtaRadialLowPass");
					ll->LL[l].iRMax = ll->LL[l].iRMin; 
					ll->LL[l].RMax  = ll->LL[l].RMin; 
				} else {
					/* Data Setting */
					data = (llComplex*)memoryAllocate(sizeof(llComplex)*ll->LL[l].nR, 
						"in lllDataLowPassFiltering");
					for(R=0; R<ll->LL[l].nR; R++) {
						data[R] = ll->LL[l].data[R];
					}
					free(ll->LL[l].data);
					ll->LL[l].data = data;

					/* RR Setting */
					ll->LL[l].iRMax = ll->LL[l].iRMin + ll->LL[l].nR - 1; 
					ll->LL[l].RMax  = ll->LL[l].data[ll->LL[l].nR - 1].RR;
				}
			}
			break;
		}
		case lllDataLowPassFilteringModeSameMemorySize: {
			for(l=0; l<ll->llMax; l++) {
				for(R=ll->LL[l].nR-1; 0<=R; R--) {
					if(RRMax < ll->LL[l].data[R].RR) {
						ll->LL[l].data[R].Re  = 0;
						ll->LL[l].data[R].Im  = 0;
						ll->LL[l].data[R].F   = 0;
						ll->LL[l].data[R].PHI = 0;
						DEBUGPRINT4("l: %d R: %d/%d : %g\n", l, R, ll->LL[l].nR, ll->LL[l].data[R].F);
					} else {
						break;
					}
				}
			}
			break;
		}
		default: {
			fprintf(stderr, "Not supported in lllDataLowPassFiltering\n");
			exit(EXIT_FAILURE);
			break;
		}
	}
}


