/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataSet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataSet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataSet ver%I%; Date:%D% %Z%";

#undef DEBUG
#include "genUtil.h"
#include "../inc/llData.h"

void
llDataFandPHISet(llData* dst)
{
	long l;
	long R;
	double F;

	/* Set F, PHI */
	for(l=0; l<dst->llMax; l++) {
		for(R=0; R<dst->LL[l].nR; R++) {
			F   = SQR(dst->LL[l].data[R].Re)+SQR(dst->LL[l].data[R].Im);
			if(F==0) {
				dst->LL[l].data[R].F   = 0.0;
				dst->LL[l].data[R].PHI = 0.0;
			} else {
				dst->LL[l].data[R].F = sqrt(F);
				dst->LL[l].data[R].PHI = atan2(dst->LL[l].data[R].Im, dst->LL[l].data[R].Re);
			}
		}
	}
}

void
llDataReAndImSet(llData* dst)
{
	long l;
	long R;

	/* Set F, PHI */
	for(l=0; l<dst->llMax; l++) {
		for(R=0; R<dst->LL[l].nR; R++) {
			dst->LL[l].data[R].Re = dst->LL[l].data[R].F*cos(dst->LL[l].data[R].PHI);
			dst->LL[l].data[R].Im = dst->LL[l].data[R].F*sin(dst->LL[l].data[R].PHI);
		}
	}
}

void
llDataRRSet(llData* dst)
{
	long l;
	long R;

	DEBUGPRINT2("delBR %f, RMin %f in llDataRRSet\n", dst->LL[l].RMin, dst->LL[l].delBR);
	for(l=0; l<dst->llMax; l++) {
		for(R=0; R<dst->LL[l].nR; R++) {
			dst->LL[l].data[R].RR = dst->LL[l].RMin + R*dst->LL[l].delBR;
		}
	}
}

void
llDataRRInfoSet(llData* dst)
{
	long l;
	long nRMax;
	/* Set RMin, RMax, iRMin, iRMax, delBR */

	nRMax = 0;
	for(l=0; l<dst->llMax; l++) {
		if(0 == dst->LL[l].nR) {
			dst->LL[l].RMin  = 0.0; 
			dst->LL[l].RMax  = 0.0; 
			dst->LL[l].delBR = 0.0;
			dst->LL[l].iRMin = 0;
			dst->LL[l].iRMax = 0;
		} else if (1==dst->LL[l].nR){
			dst->LL[l].RMin  = dst->LL[l].data[0].RR; 
			dst->LL[l].RMax  = dst->LL[l].data[0].RR; 
			dst->LL[l].delBR = 0.0;
			dst->LL[l].iRMin = 0;
			dst->LL[l].iRMax = 0;
		} else {
			dst->LL[l].RMin  = dst->LL[l].data[0].RR; 
			dst->LL[l].RMax  = dst->LL[l].data[dst->LL[l].nR-1].RR; 
			dst->LL[l].delBR = (dst->LL[l].RMax - dst->LL[l].RMin)/(dst->LL[l].nR - 1);
			dst->LL[l].iRMin = floor(dst->LL[l].RMin/dst->LL[l].delBR + 0.5);
			dst->LL[l].iRMax = floor(dst->LL[l].RMax/dst->LL[l].delBR + 0.5);
			if(dst->LL[l].iRMax - dst->LL[l].iRMin + 1 != dst->LL[l].nR) {
				fprintf(stderr, "Something wrong in llDataRRInfoSet: nR(%d) %d != %d (Max-Min+1)\n", 
					dst->LL[l].nl,
					dst->LL[l].nR,
					dst->LL[l].iRMax - dst->LL[l].iRMin + 1);
			}
		}
		if(nRMax < dst->LL[l].nR) {
			nRMax = dst->LL[l].nR;
		}
	}
	dst->nRMax = nRMax;

	dst->RRInfoSet = 1;
}

/*
@(#) llDataAttributesSet2
@(#)    AttributesSet for MergeDifferentN  
*/
void
llDataAttributesSet2(llData* dst, llData* src)
{
	long l, l1;
	long count;


	llDataRRInfoSet(src);
	/* Set Attributes */
	l=0;
	dst->LL[0] = src->LL[0];
	for(l1=0; l1<src->llMax-1; l1++) {
		if(src->LL[l1].nl != src->LL[l1+1].nl) {
			dst->LL[l+1] = src->LL[l1+1];
			l++;
		}
	}

	for(l=0; l<dst->llMax; l++) {
		count = 0;
		for(l1=0; l1<src->llMax; l1++) {
			if(dst->LL[l].nl==src->LL[l1].nl) {
				if(0==count) {
					dst->LL[l] = src->LL[l1];	
				} else {
					dst->LL[l].delBR = MIN(src->LL[l1].delBR, dst->LL[l].delBR);
					dst->LL[l].RMin  = MIN(src->LL[l1].RMin,  dst->LL[l].RMin);
					dst->LL[l].RMax  = MAX(src->LL[l1].RMax,  dst->LL[l].RMax);
				}
				count++;
			}
		}
		if(0==count) {
			fprintf(stderr, "No Layer Line: dst(%ld, %ld) in llDataAttributesSet2\n",
				dst->LL[l].nn,
				dst->LL[l].nl);
		} else {
			dst->LL[l].iRMin = floor(dst->LL[l].RMin/dst->LL[l].delBR + 0.5);
			dst->LL[l].iRMax = floor(dst->LL[l].RMax/dst->LL[l].delBR + 0.5);
			dst->LL[l].nR    = dst->LL[l].iRMax - dst->LL[l].iRMin + 1;
			dst->LL[l].RMin  = dst->LL[l].iRMin*dst->LL[l].delBR;
			dst->LL[l].RMax  = dst->LL[l].iRMax*dst->LL[l].delBR;
		}
	}
}
