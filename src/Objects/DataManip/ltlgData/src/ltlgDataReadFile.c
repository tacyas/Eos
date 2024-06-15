/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% ltlgDataReadFile ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : ltlgDataReadFile 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%ltlgDataReadFile ver%I%; Date:%D% %Z%";
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEBUG
#include "genUtil.h"
#include "Memory.h"
#include "../inc/ltlgData.h"

void
ltlgDataReadFile(FILE* fpt, ltlgData* ltlg, ltlgDataParaTypeInteger mode, ltlgDataParaTypeInteger* status)
{   
	char  tmp[LTLG_FTN_RECORD];
    char* current;
    char* current1;
    char* current2;

    ltlgDataParaTypeInteger i, j, tmpj, k, tmpk, nllRec, nrRec;
	ltlgDataParaTypeReal data;

    if(fpt==NULL) {
        fprintf(stderr, "File Descripter in NULL\n");
        *status = EXIT_FAILURE;
        return;
    }
    fseek(fpt, 0L, 0);
/* The First Record */
    if(LTLG_FTN_RECORD!=fread(tmp, sizeof(char), LTLG_FTN_RECORD, fpt)) {
		fprintf(stderr, "Cannot read correctly\n");
		exit(EXIT_FAILURE);
	}	
    tmp[LTLG_TITLE_LENGTH-1] = tmp[2*LTLG_TITLE_LENGTH-1] = tmp[2*LTLG_TITLE_LENGTH+LTLG_SIDE_LENGTH-1] = '\0';
	current = tmp;
    strncpy(ltlg->title1, current, LTLG_TITLE_LENGTH);
    current += LTLG_TITLE_LENGTH;
    strncpy(ltlg->title2, current, LTLG_TITLE_LENGTH);
    current += LTLG_TITLE_LENGTH;
    strncpy(ltlg->side,   current, LTLG_SIDE_LENGTH);
    current += LTLG_SIDE_LENGTH;
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeReal), 1);
#else
#endif
    ltlg->R.d    = *((ltlgDataParaTypeReal*)   current);
    current += sizeof(ltlgDataParaTypeReal);
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeInteger), 1);
#else
#endif
    ltlg->ll.Max = *((ltlgDataParaTypeInteger*)current);
	DEBUGPRINT1("llMax: %d\n", ltlg->ll.Max);
    current += sizeof(ltlgDataParaTypeInteger);
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeReal), 1);
	ltlg->r.d    = *((ltlgDataParaTypeReal*)   current); 
#else
	fseek(fpt, current-tmp, SEEK_SET);
	fread(&data, sizeof(float), 1, fpt);
    ltlg->r.d    =  data;
#endif
    current += sizeof(ltlgDataParaTypeReal);
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeReal), 1);
	ltlg->r.Max  = *((ltlgDataParaTypeReal*)   current); 
#else
	fseek(fpt, current-tmp, SEEK_SET);
	fread(&data, sizeof(float), 1, fpt);
    ltlg->r.Max  = data; 
#endif
    current += sizeof(ltlgDataParaTypeReal);
#ifdef II
	memoryByteSwap(current, sizeof(ltlgDataParaTypeInteger), 1);
#else
#endif
    ltlg->r.n    = *((ltlgDataParaTypeInteger*)current);
/* Temporal variables */
    ltlg->r.Min = 0.0;

/* Memory Allocate */
    ltlgDataAllocate(ltlg, status);
    if(*status==EXIT_FAILURE) {
        return;
    }
	fseek(fpt, LTLG_FTN_RECORD, SEEK_SET);
/* The Second Record */
    nllRec = LTLG_FTN_RECORD/sizeof(ltlgDataLLDataInfo);
    current  = tmp;
    current1 = current  + sizeof(ltlgDataParaTypeInteger);
    current2 = current1 + sizeof(ltlgDataParaTypeInteger);
    for(i=0; i<ltlg->ll.Max; i+=nllRec) {
        if(LTLG_FTN_RECORD!=fread(tmp, sizeof(char), LTLG_FTN_RECORD, fpt)) {
			fprintf(stderr, "Cannot read correctly\n");
			exit(EXIT_FAILURE);
		}
        for(j=i; j<i+nllRec && j<ltlg->ll.Max; j++) {
			DEBUGPRINT1("%d\n", j);
            tmpj = j-i;
#ifdef II
			memoryByteSwap(current +tmpj*sizeof(ltlgDataLLDataInfo), sizeof(ltlgDataParaTypeInteger), 1);
			memoryByteSwap(current1+tmpj*sizeof(ltlgDataLLDataInfo), sizeof(ltlgDataParaTypeInteger), 1);
			memoryByteSwap(current2+tmpj*sizeof(ltlgDataLLDataInfo), sizeof(ltlgDataParaTypeReal), 1);
#else
#endif
            ltlg->llInfo[j].NN = *((ltlgDataParaTypeInteger*)(current +tmpj*sizeof(ltlgDataLLDataInfo)));
            ltlg->llInfo[j].NL = *((ltlgDataParaTypeInteger*)(current1+tmpj*sizeof(ltlgDataLLDataInfo)));
            ltlg->llInfo[j].WT = *((ltlgDataParaTypeReal*)   (current2+tmpj*sizeof(ltlgDataLLDataInfo)));
        }
    }

/* ltlgDataLLData Records */
    nrRec = LTLG_FTN_RECORD/(sizeof(ltlgDataParaTypeReal)*2);
    current  = tmp;
    current1 = current+sizeof(ltlgDataParaTypeReal);
    for(i=0; i<ltlg->ll.Max; i++) {
        for(j=0; j<ltlg->r.n; j+=nrRec) {
            fread(tmp, sizeof(char), LTLG_FTN_RECORD, fpt);
            for(k=j; k<j+nrRec && k<ltlg->r.n; k++) {
                tmpk = k-j;
#ifdef II
				memoryByteSwap(current +tmpk*sizeof(ltlgDataParaTypeReal)*2, sizeof(ltlgDataParaTypeReal), 1);
				memoryByteSwap(current1+tmpk*sizeof(ltlgDataParaTypeReal)*2, sizeof(ltlgDataParaTypeReal), 1);
#else
#endif
                ltlg->ltlg[i][k].Re = *((ltlgDataParaTypeReal*)(current +tmpk*sizeof(ltlgDataParaTypeReal)*2));
                ltlg->ltlg[i][k].Im = *((ltlgDataParaTypeReal*)(current1+tmpk*sizeof(ltlgDataParaTypeReal)*2));
            }
        }
    }
    *status = EXIT_SUCCESS;
}
