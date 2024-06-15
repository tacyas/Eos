/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataMergeDifferentN ver %I%
#%Z% Created by tacyas
#%Z%
#%Z% Usage : lllDataMergeDifferentN(llData* dst, llData* src, int mode)
#%Z%             mode: 0 := initialize dst and allocate memory
#%Z%                   1 := not initialize
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataMergeDifferentN ver%I%; Date:%D% %Z%";

#include <stdlib.h>
#include "llData.h"
#undef DEBUG
#include "genUtil.h"
#include "lllDataMergeDifferentN.h"

static void __lllDataMergeDifferentNInit(llData* dst, llData* src);

/*
	Separated layer lines -> one merged layer line
*/
void
lllDataMergeDifferentN(llDataBoth* dst, llDataBoth* src, int mode)
{
	int l, l1;
	int R;
	double Re, Im;

	switch(mode) {
		case 0: {
			__lllDataMergeDifferentNInit(&(dst->Nea), &(src->Nea));
			__lllDataMergeDifferentNInit(&(dst->Far), &(src->Far));
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

	lllDataClear(&(dst->Nea));
	lllDataClear(&(dst->Far));

	/* Merge */
	for(l=0; l<dst->Nea.llMax; l++) {
		for(l1=0; l1<src->Nea.llMax; l1++) {
			if(src->Nea.LL[l1].nl==dst->Nea.LL[l].nl) {
				if(dst->Nea.LL[l].nR != src->Far.LL[l1].nR) {
					fprintf(stderr, "Nea and Far are different in size in lllDataMerge\n");
				}
				if((0<=src->Nea.LL[l1].nn   && 0<=dst->Nea.LL[l].nn) 
				 ||(   src->Nea.LL[l1].nn<0 &&    dst->Nea.LL[l].nn<0)) { /* Same */ 
				 	DEBUGPRINT2("Same:src:%d -> dst:%d\n", src->Nea.LL[l1].nn, dst->Nea.LL[l].nn)
					for(R=0; R<dst->Nea.LL[l].nR; R++) {
						/* Near Side */
						llDataValueGet(&(src->Nea), l1, dst->Nea.LL[l].data[R].RR, &Re, &Im);
						dst->Nea.LL[l].data[R].Re += Re;
						dst->Nea.LL[l].data[R].Im += Im;

						/* Far Side */
						llDataValueGet(&(src->Far), l1, dst->Nea.LL[l].data[R].RR, &Re, &Im);
						dst->Far.LL[l].data[R].Re += Re;
						dst->Far.LL[l].data[R].Im += Im;
					}
				} else {
				 	DEBUGPRINT2("Diff:src:%d -> dst:%d\n", src->Nea.LL[l1].nn, dst->Nea.LL[l].nn)
					for(R=0; R<dst->Nea.LL[l].nR; R++) {
						/* Near Side */
						llDataValueGet(&(src->Far), l1, dst->Nea.LL[l].data[R].RR, &Re, &Im);
						dst->Nea.LL[l].data[R].Re += Re;
						dst->Nea.LL[l].data[R].Im += Im;

						/* Far Side */
						llDataValueGet(&(src->Nea), l1, dst->Nea.LL[l].data[R].RR, &Re, &Im);
						dst->Far.LL[l].data[R].Re += Re;
						dst->Far.LL[l].data[R].Im += Im;
					}
				}
				DEBUGPRINT2("Merge: %f += %f)\n", dst->Nea.LL[l ].data[1].Re, 
									   		      src->Nea.LL[l1].data[1].Re);
			}

		}
	}
	llDataFandPHISet(&(dst->Nea));
	llDataFandPHISet(&(dst->Far));

	DEBUGPRINT2("%d -> %d in lllDataMergeDifferentN\n", src->Nea.llMax, dst->Nea.llMax);
}


void 
__lllDataMergeDifferentNInit(llData* dst, llData* src)
{
	*dst = *src;

	/* Set llMax and initialize header area */
	dst->llMax = llDataNLNumberGet(src);
	llDataHeaderInit(dst);
	/* Set nR of each filament and initialize data area */
	llDataAttributesSet2(dst, src);
	llDataDataInit(dst);
	llDataRRSet(dst);
}
