/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataContributionCalcDifferentN ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDatarMaxLimit
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataContributionCalcDifferentN ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#include "llData.h"
#undef DEBUG
#include "genUtil.h"
#include "lllDataContributionCalcDifferentN.h"

void
lllDataContributionCalcDifferentN(llData* dst, llData* src, int mode)
{
	int l;
	int R;
	int currentl;

	switch(mode) {
		case 0: {
			dst->llMax = src->llMax;
			llDataHeaderInit(dst);
			for(l=0; l<dst->llMax; l++) {
				dst->LL[l] = src->LL[l];
			}
			llDataDataInit(dst);
			lllDataAttributeCopy(dst, src);
			break;
		}
		case 1: {
			break;
		}
		default: {
			fprintf(stderr, "NotSuppoted Mode %d in lllDataMergeDifferentN\n", mode);
			exit(EXIT_FAILURE);
			break;
		}
	}
	if(dst->llMax != src->llMax
	 ||dst->nRMax != src->nRMax) {
		fprintf(stderr, "Diffrent Size: dst(%ld, %ld) src(%ld, %ld) in lllDataMergeDifferentN\n", 
			src->llMax, src->nRMax,
			dst->llMax, dst->nRMax);
	}
	for(l=0; l<dst->llMax; l++) {
		for(R=0; R<dst->LL[l].nR; R++) {
			dst->LL[l].data[R].Re = 0.0;
			dst->LL[l].data[R].Im = 0.0;
			dst->LL[l].data[R].F  = 0.0;
			dst->LL[l].data[R].PHI = 0.0;
		}
	}

	currentl = 0;
	for(l=0; l<dst->llMax; l++) {
		if(src->LL[l].nl != src->LL[currentl].nl) {
			currentl = l;
		}
		for(R=0; R<dst->LL[l].nR; R++) {
			dst->LL[currentl].data[R].F += src->LL[l].data[R].F;
		}
	}

	currentl = 0;
	for(l=0; l<dst->llMax; l++) {
		if(src->LL[l].nl != src->LL[currentl].nl) {
			currentl = l;
		} else {
			for(R=0; R<dst->LL[l].nR; R++) {
				dst->LL[l].data[R].F = dst->LL[currentl].data[R].F;
			}
		}
	}

	currentl = 0;
	for(l=0; l<dst->llMax; l++) {
		for(R=0; R<dst->LL[l].nR; R++) {
			dst->LL[l].data[R].RR  = src->LL[l].data[R].RR; 
			if(dst->LL[l].data[R].F != 0) {
				dst->LL[l].data[R].F   = src->LL[l].data[R].F/dst->LL[l].data[R].F;
			} else {
				dst->LL[l].data[R].F   = 0.0;
			}
		}
	}
}

