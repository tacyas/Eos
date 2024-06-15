#include <stdio.h>
#include <stdlib.h>
#include "Memory.h"
#include "../inc/ltlgData.h"

void
ltlgDataAllocate(ltlgData* ltlg, ltlgDataParaTypeInteger* status)
{
    ltlgDataParaTypeInteger i;

    ltlg->llInfo = (ltlgDataLLDataInfo*)memoryAllocate(sizeof(ltlgDataLLDataInfo)*((size_t)ltlg->ll.Max), "in ltlgDataAllocate");
    ltlg->ltlg = (ltlgDataLLData**)memoryAllocate(sizeof(ltlgDataLLData*)*((size_t)ltlg->ll.Max), "in ltlgDataAllocate");
    for(i=0; i<ltlg->ll.Max; i++) {
        ltlg->ltlg[i] = (ltlgDataLLData*)memoryAllocate(sizeof(ltlgDataLLData)*((size_t)ltlg->r.n), "in ltlgDataAllocate");
	}
    *status = EXIT_SUCCESS;
}

void
ltlgDataFree(ltlgData* ltlg)
{
    ltlgDataParaTypeInteger i;

    free(ltlg->llInfo);
    for(i=0; i<ltlg->ll.Max; i++) {                               
        free(ltlg->ltlg[i]);
    }
    free(ltlg->ltlg);
}


