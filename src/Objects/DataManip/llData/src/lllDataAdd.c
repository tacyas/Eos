/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataAdd ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataAdd
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataAdd ver%I%; Date:%D% %Z%";
#include <math.h>
#include <stdlib.h>
#include "../inc/llData.h"
#undef DEBUG
#include "genUtil.h"

void
lllDataAdd(llData* ll1, llData* ll2)
{
	lllDataAdd2(ll1, ll1, ll2);
}

void
lllDataAdd2(llData* ll, llData* ll1, llData* ll2)
{
    int l, R;
    double PHI1, F1;
    double PHI2, F2;

	DEBUGPRINT("----- lllDataAdd2 -----\n");
	DEBUGPRINT3("Side: %d = %d + %d\n", ll->LL[0].Side, ll1->LL[0].Side, ll2->LL[0].Side);
	
	if( 0==llDataSizeCheck(ll, ll1, "dst and src1: in lllDataAdd2")
	  ||0==llDataSizeCheck(ll, ll2, "dst and src2: in lllDataAdd2")) {
	  	fprintf(stderr, "Different size in lllDataAdd2\n");
	}

	switch(ll->LL[0].Side) {
		case NearSide:
		case AverageSide: {
	    	for(l=0; l<ll->llMax; l++) {
   		 		for(R=0; R<ll1->LL[l].nR; R++) {
					F1   = ll1->LL[l].data[R].F;
					PHI1 = nearSidePhaseGet(ll1->LL[l].data[R].PHI, ll1->LL[l].nn, ll1->LL[l].Side, ll1->Pole);
					F2   = ll2->LL[l].data[R].F;
					PHI2 = nearSidePhaseGet(ll2->LL[l].data[R].PHI, ll2->LL[l].nn, ll2->LL[l].Side, ll2->Pole);
					ll->LL[l].data[R].Re = F1*cos(PHI1) + F2*cos(PHI2);
					ll->LL[l].data[R].Im = F1*sin(PHI1) + F2*sin(PHI2);
#define DEBUG0000
#ifdef  DEBUG0000
					if(ll1->LL[l].nn%2==1) {	
						DEBUGPRINT2("NN: %d + %d --", 
							ll1->LL[l].nn,
							ll2->LL[l].nn);	
						DEBUGPRINT4("PHI: (%f->%f) + (%f->%f)\n", 
							ll1->LL[l].data[R].PHI*DEGREE, 
							PHI1*DEGREE,
							ll2->LL[l].data[R].PHI*DEGREE, 
							PHI2*DEGREE);
					}
#endif
#undef DEBUG0000
				}
			}
			break;
		}

		case FarSide: {
	    	for(l=0; l<ll->llMax; l++) {
   		 		for(R=0; R<ll2->LL[l].nR; R++) {
					F1   = ll1->LL[l].data[R].F;
					PHI1 = farSidePhaseGet(ll1->LL[l].data[R].PHI, ll1->LL[l].nn, ll1->LL[l].Side, ll1->Pole);

					F2   = ll2->LL[l].data[R].F;
					PHI2 = farSidePhaseGet(ll2->LL[l].data[R].PHI, ll2->LL[l].nn, ll2->LL[l].Side, ll2->Pole);

					ll->LL[l].data[R].Re = F1*cos(PHI1) + F2*cos(PHI2);
					ll->LL[l].data[R].Im = F1*sin(PHI1) + F2*sin(PHI2);
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

	llDataFandPHISet(ll);
}

