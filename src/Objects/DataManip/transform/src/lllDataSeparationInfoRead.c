/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% llDataSeparate ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : llDataSeparate
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%llDataSeparate ver%I%; Date:%D% %Z%";

#define indexNL 1
#define indexZ  2 
#define indexNN 3
#define indexN0 4 

#include "lllExtract.h"
#include "eosString.h"
#include "Memory.h"

void
lllDataSeparationInfoFileFormat(FILE* fpt)
{
     fprintf(stderr, "llMax(different) truePitch[A] rMax[A] RMax[/A]\n");
	 fprintf(stderr, "nl Z numberOfN n0 n1 n2...\n");
}

void
lllDataSeparationInfoRead(lllExtractInfo* linfo, mrcImage* mrc, FILE* fpt)
{
	char s[STRING_MAX_LENGTH];
	llDataParaTypeInteger l, nl;
	llDataParaTypeInteger nn;
	llDataParaTypeInteger i;
	llDataParaTypeReal    truePitch;

	linfo->Title = "lllDataSeparateExtract";
	linfo->xStep = mrc->HeaderLength.x;
	linfo->yStep = mrc->HeaderLength.y;
	linfo->MaxX = mrc->HeaderN.x/2;
	linfo->MaxY = mrc->HeaderN.y/2;
	linfo->RotationAngle = 0.0;
	linfo->Omega = 0.0;
	linfo->Shear = 0.0;
	linfo->ievery = 0;
	linfo->axl = 0;
	linfo->ayl = 0;
	linfo->xShift  = mrc->HeaderN.x/2;
	linfo->delRInv = (linfo->xStep*mrc->HeaderN.x);
	linfo->flagOutputInfo = 0;

	fseek(fpt, 0L, SEEK_SET);
	stringGetFromFile(s, "", fpt, stdout, 3);
	nl = stringGetNthIntegerData(s, 1, " ,\t");
	linfo->truePitch = stringGetNthIntegerData(s, 2, " ,\t");
	linfo->rMax.rMax = stringGetNthIntegerData(s, 3, " ,\t");
	linfo->RMax      = stringGetNthIntegerData(s, 4, " ,\t");
	linfo->llMax = nl;
	linfo->n     = (long*)memoryAllocate(sizeof(long)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->nn    = (long*)memoryAllocate(sizeof(long)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->ns    = (long**)memoryAllocate(sizeof(long*)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->l     = (long*)memoryAllocate(sizeof(long)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->Y     = (float*)memoryAllocate(sizeof(float)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->leftMin = (float*)memoryAllocate(sizeof(float)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->leftMax = (float*)memoryAllocate(sizeof(float)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->rightMin = (float*)memoryAllocate(sizeof(float)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->rightMax = (float*)memoryAllocate(sizeof(float)*nl, "in lllDataSeparateExtractInfoRead");
	linfo->weight = (float*)memoryAllocate(sizeof(float)*nl, "in lllDataSeparateExtractInfoRead");

	for(l=0; l<linfo->llMax; l++) {
		stringGetFromFile(s, "", fpt, stdout, 3);
		nn = stringGetNthIntegerData(s, indexNN, ", \t"); 
		if(nn!=0) {
			linfo->n[l] = stringGetNthIntegerData(s, indexN0, " ,\t");
			linfo->l[l] = stringGetNthIntegerData(s, indexNL, " ,\t");
			linfo->Y[l] = stringGetNthIntegerData(s, indexZ,  " ,\t");
			linfo->leftMin[l]  = 0;
			linfo->leftMax[l]  = mrc->HeaderN.x/2 - 1;
			linfo->rightMin[l] = 0;
			linfo->rightMax[l] = mrc->HeaderN.x/2 - 1;
			linfo->nn[l] = nn;
			linfo->ns[l] = (long*)memoryAllocate(sizeof(long)*nn, "in lllDataSeparateExtractInfoRead");
			for(i=0; i<nn; i++) {
				linfo->ns[l][i] = stringGetNthIntegerData(s, indexN0+i, " ,\t");
			}
		} else {
			l--;
		}
		linfo->weight[l] = 1.0;
	}
	for(l=linfo->llMax-1; l>=0; l--) {
		if(0!=linfo->l[l]) {
			truePitch = (mrc->HeaderN.y*mrc->HeaderLength.y)
						/(((double)linfo->Y[l])/((double)linfo->l[l]));
			break;
		}
	}
	linfo->truePitch = truePitch;
}

