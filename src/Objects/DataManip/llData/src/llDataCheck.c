/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataCheck ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataCheck 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%llDataCheck ver%I%; Date:%D% %Z%";

#include "../inc/llData.h"

long
llDataSizeCheck(llData* ll1, llData* ll2, char* message)
{
	long l;
	long returnValue;

	returnValue = 1;
	if(ll1->llMax != ll2->llMax) {
		fprintf(stderr, "Different llMax: %d != %d\n", ll1->llMax, ll2->llMax);
		returnValue *= 0;
	}
	for(l=0; l<ll1->llMax; l++) {
		if(ll1->LL[l].nR!=ll2->LL[l].nR) {
			fprintf(stderr, "Different nR(%ld): %d != %d\n", l, ll1->LL[l].nR, ll2->LL[l].nR);
			returnValue *= 0;
		}
		if(ll1->LL[l].nR!=0) {
			if(fabs(1.0/ll1->LL[l].delBR-1.0/ll2->LL[l].delBR)>1e-2) {
				fprintf(stderr, "Different delBR(%ld): %g != %g\n", l, ll1->LL[l].delBR, ll2->LL[l].delBR);
				returnValue *= 0;
			}
			if(fabs(ll1->LL[l].RMin -ll2->LL[l].RMin )>1e-6) {
				fprintf(stderr, "Different RMin(%ld): %g != %g\n", l, ll1->LL[l].RMin, ll2->LL[l].RMin);
				returnValue *= 0;
			}
		}
	}
	return returnValue;
}
