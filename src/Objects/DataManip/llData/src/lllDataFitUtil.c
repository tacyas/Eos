/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lllDataFitUtil ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lllDataFitUtil 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lllDataFitUtil ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include "../inc/llData.h"
#include "lllDataFit.h"
#include "ctfInfo.h"

void
lllDataFitllCTFSet(llData* dst, ctfInfo ctf, int mode) 
{
	llDataParaTypeInteger l, R;
	
	if(!dst->RValueSet) {
		llDataRValueSet(dst, 0);			
	}
	for(l=0; l<dst->llMax; l++) {
		for(R=0; R<dst->LL[l].nR; R++) {
			dst->LL[l].data[R].Re = ctfFunction(&ctf, dst->LL[l].data[R].R, 0);		
			dst->LL[l].data[R].Im = 0.0;
		}
	}
	llDataFandPHISet(dst);
}

#define STEP      (6.0)
#define STEP2     (STEP/2.0)
#define COUNT_MAX (4)
#define END_VALUE (1e-4)

void
lllDataNewFittedParameterSet(llDataParamToFit* P)
{
	lllDataNewFittedParameterSet0(&(P->Omega));
	lllDataNewFittedParameterSet0(&(P->x));
	lllDataNewFittedParameterSet0(&(P->phi));
	lllDataNewFittedParameterSet0(&(P->z));
	lllDataNewFittedParameterSet0(&(P->r));
}

void
lllDataNewFittedParameterSet0(llDataParaTypeRegion* R)
{
	if(1e-6 < fabs(R->Max - R->Min)) {
		R->Delta = R->Delta/STEP2;
		R->Min   = R->Value - R->Delta;
		R->Max   = R->Value + R->Delta;
	}
}

void
lllDataFittedParameterSet(llDataParamToFit* P, llDataParamToFit* range)
{
	lllDataFittedParameterSet0(&(P->Omega), &(range->Omega));
	lllDataFittedParameterSet0(&(P->x),     &(range->x));
	lllDataFittedParameterSet0(&(P->phi),   &(range->phi));
	lllDataFittedParameterSet0(&(P->z),     &(range->z));
	lllDataFittedParameterSet0(&(P->r),     &(range->r));
}

void
lllDataFittedParameterSet0(llDataParaTypeRegion* R, llDataParaTypeRegion* range)
{
	R->Delta = range->Delta;
	R->Min   = range->Min;
	R->Max   = range->Max;
}

void
lllDataFittedParameterFree(llDataFittedParam* P)
{
	if(P->flagFitFile) {
		free(P->fitFileName);
		free(P->fitFileNameAnti);
	}
	lllDataFittedParameterFree0(&(P->Para));
	lllDataFittedParameterFree0(&(P->PPara));
	lllDataFittedParameterFree0(&(P->QPara));
	lllDataFittedParameterFree0(&(P->Q2Para));
	lllDataFittedParameterFree0(&(P->RPara));
	lllDataFittedParameterFree0(&(P->PParaInv));
	lllDataFittedParameterFree0(&(P->QParaInv));
	lllDataFittedParameterFree0(&(P->Q2ParaInv));
	lllDataFittedParameterFree0(&(P->RParaInv));
}

void
lllDataFittedParameterFree0(llDataParamToFit* P)
{
	if(P->flagLLTable && P->llTable!=NULL) {
		free(P->llTable);
	}
	P->flagLLTable = 0;


	if(P->flagllCTF && P->flagCTF) {
		llDataFree(&(P->llCTF));
	}
	P->flagllCTF = 0;
}

