/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosStarFileWrite ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosStarFileWrite 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosStarFileWrite ver%I%; Date:%D% %Z%";


#include <stdio.h>

#define DEBUG
#include "genUtil.h"
#include "../inc/eosStarFile.h"

void 
eosStarFileWrite(FILE* fpt, eosStarFile* star, int mode)
{
    int dataBlockIndex; 
    int dataItemIndex;
    int loopKeyIndex;
    int loopDataIndex;

    DEBUGPRINT1("numDataBlock; %d\n", star->numDataBlock);
    for(dataBlockIndex=0; dataBlockIndex<star->numDataBlock; dataBlockIndex++) {
        DEBUGPRINT1("dataBlockIndex; %d\n", dataBlockIndex);
        fprintf(fpt, "%s\n", star->block[dataBlockIndex].dataBlockName);
        DEBUGPRINT1("numDataItem; %d\n", star->block[dataBlockIndex].numDataItem);
        for(dataItemIndex=0; dataItemIndex<star->block[dataBlockIndex].numDataItem; dataItemIndex++) {
            fprintf(fpt, "%s %s\n", star->block[dataBlockIndex].data[dataItemIndex].key, 
                                    star->block[dataBlockIndex].data[dataItemIndex].valueS[0]);
        }

        DEBUGPRINT1("numLoopKey; %d\n", star->block[dataBlockIndex].numLoopKey);
        DEBUGPRINT1("numLoopData; %d\n", star->block[dataBlockIndex].numLoopData);
        fprintf(fpt, "loop_\n");
        for(loopKeyIndex=0; loopKeyIndex<star->block[dataBlockIndex].numLoopKey; loopKeyIndex++) {
            fprintf(fpt, "%s\n", star->block[dataBlockIndex].loop[loopKeyIndex].key);
        }
        for(loopDataIndex=0; loopDataIndex<star->block[dataBlockIndex].numLoopData; loopDataIndex++) {
            for(loopKeyIndex=0; loopKeyIndex<star->block[dataBlockIndex].numLoopKey; loopKeyIndex++) {
                fprintf(fpt, "%s ", star->block[dataBlockIndex].loop[loopKeyIndex].valueS[loopDataIndex]);
            }
            fprintf(fpt, "\n");
        }
    }
}
