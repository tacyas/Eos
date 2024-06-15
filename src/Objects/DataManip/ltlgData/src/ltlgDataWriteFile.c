/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ltlgDataWriteFile ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ltlgDataWriteFile 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ltlgDataWriteFile ver%I%; Date:%D% %Z%";
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#undef DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/ltlgData.h"

void
ltlgDataWriteFile(FILE* fpt, ltlgData* ltlg, ltlgDataParaTypeInteger mode, ltlgDataParaTypeInteger* status)
{   
    char  tmp[LTLG_FTN_RECORD];
    char* current;
    char* current1;
    char* current2;
	char* prd;
	char* prMax;
    ltlgDataParaTypeInteger i, j, tmpj, k, tmpk, nllRec, nrRec;

    if(fpt==NULL) {
        fprintf(stderr, "File Descripter in NULL\n");
        *status = EXIT_FAILURE;
        return;
    }
    fseek(fpt, 0L, 0);
/* The First Record */
    current = tmp;
    strncpy(current, ltlg->title1, LTLG_TITLE_LENGTH);
    current += LTLG_TITLE_LENGTH;
    strncpy(current, ltlg->title2, LTLG_TITLE_LENGTH);
    current += LTLG_TITLE_LENGTH;
    strncpy(current, ltlg->side, LTLG_SIDE_LENGTH);
    current += LTLG_SIDE_LENGTH;
    *((ltlgDataParaTypeReal*)   current) = ltlg->R.d;
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeReal), 1);
#endif
    current += sizeof(ltlgDataParaTypeReal);
    *((ltlgDataParaTypeInteger*)current) = ltlg->ll.Max;
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeInteger), 1);
#endif
	DEBUGPRINT1("llMax: %f\n", ltlg->ll.Max);
    current += sizeof(ltlgDataParaTypeInteger);
#ifdef II
    *((ltlgDataParaTypeReal*)   current) = ltlg->r.d;
	memoryByteSwap(current, sizeof(ltlgDataParaTypeReal), 1);
#else
	prd = (char*)(current - tmp);
#endif
    current += sizeof(ltlgDataParaTypeReal);
#ifdef II
    *((ltlgDataParaTypeReal*)   current) = ltlg->r.Max;
	memoryByteSwap(current, sizeof(ltlgDataParaTypeReal), 1);
#else
	prMax = (char*)(current - tmp);
#endif
    current += sizeof(ltlgDataParaTypeReal);
    *((ltlgDataParaTypeInteger*)current) = ltlg->r.n;

#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeInteger), 1);
#endif
    tmp[LTLG_TITLE_LENGTH-1] = tmp[2*LTLG_TITLE_LENGTH-1] = tmp[2*LTLG_TITLE_LENGTH+LTLG_SIDE_LENGTH-1] = ' ';

    fwrite(tmp, sizeof(char), LTLG_FTN_RECORD, fpt);
#ifdef II
#else
	fseek(fpt, (size_t)prd, SEEK_SET);
	fwrite(&(ltlg->r.d), sizeof(ltlgDataParaTypeReal), 1, fpt);
	fseek(fpt, (size_t)prMax, SEEK_SET);
	fwrite(&(ltlg->r.Max), sizeof(ltlgDataParaTypeReal), 1, fpt);
#endif
	fseek(fpt, LTLG_FTN_RECORD, SEEK_SET);
/* The Second Record */
    nllRec = LTLG_FTN_RECORD/sizeof(ltlgDataLLDataInfo);
	DEBUGPRINT2("llMax: %f , nRec: %d\n", ltlg->ll.Max, nllRec);
    current  = tmp;
    current1 = current  + sizeof(ltlgDataParaTypeInteger);
    current2 = current1 + sizeof(ltlgDataParaTypeInteger);
    for(i=0; i<ltlg->ll.Max; i+=nllRec) {
        for(j=i; j<i+nllRec && j<ltlg->ll.Max; j++) {
			DEBUGPRINT1("%d\n", j);
            tmpj = j-i;
            *((ltlgDataParaTypeInteger*)(current +tmpj*sizeof(ltlgDataLLDataInfo))) = ltlg->llInfo[j].NN;
            *((ltlgDataParaTypeInteger*)(current1+tmpj*sizeof(ltlgDataLLDataInfo))) = ltlg->llInfo[j].NL;
            *((ltlgDataParaTypeReal*)   (current2+tmpj*sizeof(ltlgDataLLDataInfo))) = ltlg->llInfo[j].WT;
#ifdef II
			memoryByteSwap(current +tmpj*sizeof(ltlgDataLLDataInfo), sizeof(ltlgDataParaTypeInteger), 1);
			memoryByteSwap(current1+tmpj*sizeof(ltlgDataLLDataInfo), sizeof(ltlgDataParaTypeInteger), 1);
			memoryByteSwap(current2+tmpj*sizeof(ltlgDataLLDataInfo), sizeof(ltlgDataParaTypeReal), 1);
#endif
        }
        fwrite(tmp, sizeof(char), LTLG_FTN_RECORD, fpt);
    }
/* ltlgDataLLData Records */
    nrRec = LTLG_FTN_RECORD/(sizeof(ltlgDataParaTypeReal)*2);
    current  = tmp;
    current1 = current+sizeof(ltlgDataParaTypeReal);
    for(i=0; i<ltlg->ll.Max; i++) {
        for(j=0; j<ltlg->r.n; j+=nrRec) {
            for(k=j; k<j+nrRec && k<ltlg->r.n; k++) {
                tmpk = k-j;
                *((ltlgDataParaTypeReal*)(current +tmpk*sizeof(ltlgDataParaTypeReal)*2)) = ltlg->ltlg[i][k].Re;
                *((ltlgDataParaTypeReal*)(current1+tmpk*sizeof(ltlgDataParaTypeReal)*2)) = ltlg->ltlg[i][k].Im;
#ifdef II
				memoryByteSwap(current +tmpk*sizeof(ltlgDataParaTypeReal)*2, sizeof(ltlgDataParaTypeReal), 1);
				memoryByteSwap(current1+tmpk*sizeof(ltlgDataParaTypeReal)*2, sizeof(ltlgDataParaTypeReal), 1);
#endif
            }
        	fwrite(tmp, sizeof(char), LTLG_FTN_RECORD, fpt);
        }
    }
    *status = EXIT_SUCCESS;
}
