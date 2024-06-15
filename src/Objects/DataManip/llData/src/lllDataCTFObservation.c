/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataCTFObservation ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataCTFObservation 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataCTFObservation ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include "../inc/llData.h"
#include "ctfInfo.h"

void
lllDataCTFObservation(llData* ll, ctfInfo ctf, int mode)
{
	llDataParaTypeInteger l, R;
	double weight;

	if(!ll->RValueSet) {
		llDataRValueSet(ll, 0);
	}
	for(l=0; l<ll->llMax; l++) {
		for(R=0; R< ll->LL[l].nR; R++) {
			switch(mode) {
				case 0: {
					weight = fabs(ctfFunction(&ctf, ll->LL[l].data[R].R, 0));
					break;
				}
				case 1: {
					weight = ctfFunction(&ctf, ll->LL[l].data[R].R, 0);
					break;
				}
				default: {
					fprintf(stderr, "Not supported in lllDataCTFCompensation\n");
					exit(EXIT_FAILURE);
					break;
				}
			}
			ll->LL[l].data[R].Re *= weight;
			ll->LL[l].data[R].Im *= weight;
		}
	}

	llDataFandPHISet(ll);
}
