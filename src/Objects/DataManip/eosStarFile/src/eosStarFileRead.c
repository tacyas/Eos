/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosStarFileRead ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosStarFileRead 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosStarFileRead ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <string.h>

#define DEBUG
#include "genUtil.h"
#include "eosString.h"
#include "Memory.h"
#include "../inc/eosStarFile.h"

void 
eosStarFileRead (FILE* fpt, eosStarFile* star, int mode)
{
    eosStarFileDataSizeGet(fpt, star, mode);    
    eosStarFileRead0(fpt, star, mode);    
}

void
eosStarFileDataSizeGet(FILE* fpt, eosStarFile* star, int mode)
{
    int flagData=0;
    int flagLoop=0;
    int dataBlockIndex = 0;
    int dataKeyIndex = 0;
    int loopDataKeyIndex = 0;
    int i, j;
    char stmp[STRING_MAX_LENGTH];
    char* stmp2;
    char* firstWord;
    
    // DataBlockCount
    fseek(fpt, 0L, SEEK_SET);
    star->numDataBlock = 0;
    while(NULL != (stmp2 = stringGetFromFile(stmp, "in", fpt, stderr, 3))) {
        if(stmp[0] != '\n') { // Not Comment
        firstWord = stringGetNthWord0(stmp, 1, " \t");
        if(firstWord!=NULL) {
        if(firstWord[0] != '#' && firstWord[0] != ';') { // Not Comment
            if(0==strncmp(firstWord, "data_", 5)) { // in loop 
                flagData = 1;
                flagLoop = 0;
                star->numDataBlock++;
            }
            if(0==strncmp(firstWord, "loop_", 6)) { // in loop 
                flagData = 0;
                flagLoop = 1;
            }
        }
        if(firstWord!=NULL) free(firstWord);
        }
        }
    }
    DEBUGPRINT1("numDataBlock: %d\n", star->numDataBlock);
    star->block = (eosStgrFileDataBlock*)memoryAllocate(sizeof(eosStgrFileDataBlock)*star->numDataBlock, "in  eosStarFileDataSizeGet");

    fseek(fpt, 0L, SEEK_SET);
    dataBlockIndex = 0;
    while(NULL != (stmp2 = stringGetFromFile(stmp, "in", fpt, stderr, 3))) {
        if(stmp[0] != '\n') { // Not Comment
        firstWord = stringGetNthWord0(stmp, 1, " \t");
        if(firstWord!=NULL) {
        if(firstWord[0] != '#' && firstWord[0] != ';' && stmp[0] != '\n') { // Not Comment
            if(flagLoop==1) {
                if(firstWord[0] == '_') { // LoopKey
                    star->block[dataBlockIndex-1].numLoopKey++;
                } else { // LoopData
                    star->block[dataBlockIndex-1].numLoopData++;
                }
            }
            if(flagData==1) {
                if(firstWord[0] == '_') { // dataItem
                    star->block[dataBlockIndex-1].numDataItem++;
                }
            }
            
            // Mode Check
            if(0==strncmp(firstWord, "data_", 5)) { // in loop 
                flagData = 1;
                flagLoop = 0;
                dataBlockIndex++;
                star->block[dataBlockIndex-1].numDataItem=0;
                DEBUGPRINT1("dataDataBlock: %d\n", dataBlockIndex-1);
            }
            if(0==strncmp(firstWord, "loop_", 6)) { // in loop 
                flagData = 0;
                flagLoop = 1;
                star->block[dataBlockIndex-1].numLoopKey=0;
            }
        }
        if(firstWord!=NULL) free(firstWord);
        }
        }
    }


    for(i=0; i<star->numDataBlock; i++) {
        DEBUGPRINT1("dataBlock: %d\n", i);
        DEBUGPRINT1("numDataItem: %d\n", star->block[i].numDataItem);
        star->block[i].data = (eosStarFileData*)memoryAllocate(sizeof(eosStarFileData)* star->block[i].numDataItem, "in  eosStarFileDataSizeGet");
        for(j=0; j<star->block[i].numDataItem; j++) { 
            star->block[i].data[j].valueS = (char**)  malloc(sizeof(char*));
            star->block[i].data[j].valueI = (int*)    malloc(sizeof(int));
            star->block[i].data[j].valueR = (double*) malloc(sizeof(double));
        }

        DEBUGPRINT1("numDataItem: %d\n", star->block[i].numLoopKey);
        star->block[i].loop = (eosStarFileData*)memoryAllocate(sizeof(eosStarFileData)* star->block[i].numLoopKey, "in  eosStarFileDataSizeGet");
        for(j=0; j<star->block[i].numLoopKey; j++) {
            star->block[i].loop[j].valueS = (char**)  malloc(sizeof(char*) *star->block[i].numLoopData);
            star->block[i].loop[j].valueI = (int*)    malloc(sizeof(int)   *star->block[i].numLoopData);
            star->block[i].loop[j].valueR = (double*) malloc(sizeof(double)*star->block[i].numLoopData);
        }
    }
}


void 
eosStarFileRead0 (FILE* fpt, eosStarFile* star, int mode)
{
    int flagData=0;
    int flagLoop=0;
    int flagMultiLine=0;
    int dataBlockIndex = 0;
    int dataKeyIndex = 0;
    int loopDataKeyIndex = 0;
    int loopDataIndex = 0;
    int i, j;
    char stmp[STRING_MAX_LENGTH];
    char* stmp2;
    char* firstWord;

    DEBUGPRINT("eosStartFileRead0\n");
    fseek(fpt, 0L, SEEK_SET);
    dataBlockIndex = 0;
    while(NULL != (stmp2 = stringGetFromFile(stmp, "in", fpt, stderr, 3))) {
        if(stmp[0] != '\n') { // Not Comment
        firstWord = stringGetNthWord0(stmp, 1, " \t");
        if(firstWord!=NULL) {
        if(firstWord[0] != '#' && firstWord[0] != ';') { // Not Comment
            if(flagLoop==1) {
                if(firstWord[0] == '_') { // LoopKey
                    star->block[dataBlockIndex-1].loop[loopDataKeyIndex].key = stringGetNthWord(stmp, 1, " \t");
                    DEBUGPRINT2("LoopKey: %d %s\n", loopDataKeyIndex, star->block[dataBlockIndex-1].loop[loopDataKeyIndex].key);
                    loopDataKeyIndex++;
                } else { // LoopData
                    if(loopDataKeyIndex != star->block[dataBlockIndex-1].numLoopKey) {
                        fprintf(stderr, "Not equal numLoopKey: %d %d\n", loopDataKeyIndex, star->block[dataBlockIndex-1].numLoopKey); 
                        exit(EXIT_FAILURE);
                    }
                    for(i=0; i<star->block[dataBlockIndex-1].numLoopKey; i++) {
                        star->block[dataBlockIndex-1].loop[i].valueS[loopDataIndex] = stringGetNthWord(stmp, i+1, " \t");
                        star->block[dataBlockIndex-1].loop[i].valueI[loopDataIndex] = stringGetNthIntegerData(stmp, i+1, " \t");
                        star->block[dataBlockIndex-1].loop[i].valueR[loopDataIndex] = stringGetNthRealData(stmp, i+1, " \t");
                        DEBUGPRINT4("value: %d %d %s %s\n", loopDataKeyIndex, i+1, 
                            star->block[dataBlockIndex-1].loop[i].key,
                            star->block[dataBlockIndex-1].loop[i].valueS[loopDataIndex]);
                    }
                    loopDataIndex++;
                }
            }
            if(flagData==1) {
                if(firstWord[0] == '_') { // dataItem
                    star->block[dataBlockIndex-1].data[dataKeyIndex].key = stringGetNthWord(stmp, 1, " \t");
                    star->block[dataBlockIndex-1].data[dataKeyIndex].valueS[0] = stringGetNthWord(stmp, 2, " \t");
                    star->block[dataBlockIndex-1].data[dataKeyIndex].valueI[0] = stringGetNthIntegerData(stmp, 2, " \t");
                    star->block[dataBlockIndex-1].data[dataKeyIndex].valueR[0] = stringGetNthRealData(stmp, 2, " \t");
                    DEBUGPRINT3("data: %d %s %s\n", dataKeyIndex, star->block[dataBlockIndex-1].data[dataKeyIndex].key, star->block[dataBlockIndex-1].data[dataKeyIndex].valueS[0]);
                    dataKeyIndex++;
                }
            }
            
            // Mode Check
            if(0==strncmp(firstWord, "data_", 5)) { // in loop 
                flagData = 1;
                flagLoop = 0;
                dataBlockIndex++;
                dataKeyIndex = 0;
                star->block[dataBlockIndex-1].dataBlockName = stringGetNthWord(stmp, 1, " \t");
                DEBUGPRINT2("DataBlock: %d %s\n", dataBlockIndex, star->block[dataBlockIndex-1].dataBlockName);
            }
            if(0==strncmp(firstWord, "loop_", 6)) { // in loop 
                flagData = 0;
                flagLoop = 1;
                loopDataKeyIndex = 0;
                loopDataIndex = 0;
                DEBUGPRINT("_loop: in\n");
            }
        }
        if(firstWord!=NULL) free(firstWord);
        }
        }
    }
}
