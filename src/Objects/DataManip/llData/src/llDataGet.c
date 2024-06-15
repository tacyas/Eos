/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataGet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataGet ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include "../inc/llData.h"

inline long
llDataValueGet(llData* ll, long l, double R, double* re, double* im)
{
	static long iR = 0;
	double t;

	if(ll->LL[l].nR<=0) {
		*re = 0.0;
		*im = 0.0;
		return 0;
	}
	if(iR<0) {
		iR = 0;
	} else if(ll->LL[l].nR-1 <= iR) {
		iR = ll->LL[l].nR - 2;
	}
	if(R < ll->LL[l].data[0].RR || ll->LL[l].data[ll->LL[l].nR-1].RR < R) {
		*re = 0;
		*im = 0;
		return 0;
	} else if(ll->LL[l].data[iR].RR <= R){
		while(iR<ll->LL[l].nR-1) {
			if(ll->LL[l].data[iR].RR <= R && R <= ll->LL[l].data[iR+1].RR) {
				break;
			}
			iR++;	
		}
	} else if(R <= ll->LL[l].data[iR].RR) {
		while(0<=iR) {
			if(ll->LL[l].data[iR].RR <= R && R <= ll->LL[l].data[iR+1].RR) {
				break;
			}
			iR--;
		}
	} else {
		fprintf(stderr, "Something wrong in llDataValueGet\n");
		exit(EXIT_FAILURE);
	}

	if(iR < 0) {
		*re = 0.0;
		*im = 0.0;
		iR = 0; 
		return 0;
	} else if(ll->LL[l].nR - 1  <= iR) {
		*re = 0.0;
		*im = 0.0;
		iR = ll->LL[l].nR - 2; 
		return 0;
	}

	t = (R - ll->LL[l].data[iR].RR)/(ll->LL[l].data[iR+1].RR - ll->LL[l].data[iR].RR); 
	*re = (1-t)*ll->LL[l].data[iR].Re + t*ll->LL[l].data[iR+1].Re;
	*im = (1-t)*ll->LL[l].data[iR].Im + t*ll->LL[l].data[iR+1].Im;

	return 0;
}

long
inline llDataValueGet2(llData* ll, long nn, long nl, double R, double* re, double* im)
{
	long l;

	l = llDataLayerNumberGet(ll, nn, nl);

	return llDataValueGet(ll, l, R, re, im);
}

/*
	Retern Layer Number
*/

long
llDataLayerNumberGet(llData* ll, long nn, long nl)
{
	long l;

	for(l=0; l<ll->llMax; l++) {
		if(  ll->LL[l].nl == nl 
		  && ll->LL[l].nn == nn) {
			return l; 
		}
	}
	return -1;
}

long 
llDataNLNumberGet(llData* ll)
{
	long l;
	long llMax;

	if(ll->llMax<=0) {
		return 0;
	}
	llMax=1;
	for(l=1; l<ll->llMax; l++) {
		if(ll->LL[l-1].nl != ll->LL[l].nl) {
			llMax++;
		}
	}
	return llMax;
}
