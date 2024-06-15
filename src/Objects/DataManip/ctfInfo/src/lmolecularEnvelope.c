/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% lmolecularEnvelope ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : lmolecularEnvelope 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%lmolecularEnvelope ver%I%; Date:%D% %Z%";

#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "Array.h"
#include "File.h"
#include "eosString.h"
#include "../inc/ctfInfo.h"

void
lmolecularEnvelopeFileRead(FILE* fpt, molecularEnvelope* mol, int mode)
{
	int i;
	char s[1024];

	mol->nR = fileLineNumberGet2(fpt, "");
	mol->R        = (float*)memoryAllocate(sizeof(float)*mol->nR, "in lmolecularEnvelopeFileRead");
	mol->Envelope = (float*)memoryAllocate(sizeof(float)*mol->nR, "in lmolecularEnvelopeFileRead");
		
	for(i=0; i<mol->nR; i++) {
		stringGetFromFile(s, "", fpt, stdout, 3);
		mol->R[i]        = stringGetNthRealData(s, 1, " \t,");
		mol->Envelope[i] = stringGetNthRealData(s, 2, " \t,");
	}
	mol->mode = 0;
}

void
lmolecularEnvelopeFileWrite(FILE* fpt, molecularEnvelope* mol, int mode)
{
	int i;
	for(i=0; i<mol->nR; i++) {
		fprintf(fpt, "%15g %15g\n", mol->R[i], mol->Envelope[i]);
	}
}


void
lmolecularEnvelopeResampling(molecularEnvelope* dst, molecularEnvelope* src, float dR, float RMax, int mode)
{
	int i, j;
	float R;

	if(0==mode) {
		dst->nR = RMax/dR + 1;
		dst->R        = (float*)memoryAllocate(sizeof(float)*dst->nR, "in lmolecularEnvelopeFileRead"); 		
		dst->Envelope = (float*)memoryAllocate(sizeof(float)*dst->nR, "in lmolecularEnvelopeFileRead");
	}
	j = 0;
	for(i=0; i<dst->nR; i++) {
		R = dR*i;
		/* Linear Interpolation */
		dst->R[i]        = R;
		dst->Envelope[i] = lmolecularEnvelopeDataGet(src, R, 0);
	}
}

float
lmolecularEnvelopeDataGet(molecularEnvelope* src, float R, int mode)
{
	static int j=0;
	float Env;

	while(1) {
		if(src->R[j] <= R
		 	 &&         R <= src->R[j+1]) { 
			break;
		} else if(R<src->R[j]) {
			if(j<=0) {
				j=0;	
				break;
		} else {
				j--;
			}
		} else {
			if(src->nR-2<=j) {
				j=src->nR-2;	
				break;
			} else {
				j++;
			}
		}
	}
	Env = ((src->R[j+1] - R)*src->Envelope[j] + (R - src->R[j])*src->Envelope[j+1]) /(src->R[j+1] - src->R[j]);
	return Env;
}

