/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataInit ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataInit 
#%Z% Attention
#%Z%
*/

static char __sccs_id[] = "%Z%llDataInit ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#undef DEBUG
#include "genUtil.h"
#define __LLDATAINIT__
#include "../inc/llData.h"
#include "Memory.h"

void
llDataInitWithReference(llData* dst, llData* org)
{
	*dst = *org;	
	llDataHeaderInit(dst);
	lllDataHeaderCopy(dst, org);
	llDataDataInit(dst);
	lllDataAttributeCopy(dst, org);
}

void
llDataInitWithReference2(llData* dst, llData* org, int side)
{
	int l;

	llDataInitWithReference(dst, org);
	dst->Side = side;
	for(l=0; l<dst->llMax; l++) {
		dst->LL[l].Side = side;
	}
}

void
llDataInit(llData* ll)
{
	int i;
	
	llDataHeaderInit(ll);
	for(i=0; i<ll->llMax; i++) {
		ll->LL[i].nR = ll->nRMax;
	}
	llDataDataInit(ll);
}

void
llDataHeaderInit(llData* ll)
{
	ll->Pole      = llDataPoleNormal;
	ll->RRInfoSet = 0;
	ll->FmaxSet = 0;
	ll->RValueSet = 0;
	ll->ZValueSet = 0;
	ll->LL = (oneLLData*)memoryAllocate(sizeof(oneLLData)*ll->llMax, "ll->LL in llDataInit");
}

void
llDataDataInit(llData* ll)
{
	int l;
	DEBUGPRINT("Start llDataDataInit\n");
	for(l=0; l<ll->llMax; l++) {
		DEBUGPRINT2("%d: %d\n", l, ll->LL[l].nR);
		ll->LL[l].data = (llComplex*)memoryAllocate(sizeof(llComplex)*ll->LL[l].nR, "ll->LL[l].data in llDataInit");
	}
    ll->mode = llDataModeMemoryAllocate;
}

void
llDataFree(llData* ll)
{
	llDataDataFree(ll);
	llDataHeaderFree(ll);
}

void
llDataHeaderFree(llData* ll)
{
	free(ll->LL);
}

void
llDataDataFree(llData* ll)
{
	int i;

	for(i=0; i<ll->llMax; i++) {
		free(ll->LL[i].data);
	}
    ll->mode = llDataModeMemoryAllocate;
}

