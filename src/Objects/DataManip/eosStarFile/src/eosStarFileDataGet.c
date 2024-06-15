/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosStarFileDataGet ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosStarFileDataGet 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosStarFileDataGet ver%I%; Date:%D% %Z%";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/eosStarFile.h"

int
eosStarFileDataGetIndex(eosStarFile* star, char* block, char* dataKey, int* blockIndex, int* dataIndex, int mode)  
{
    int i, j;
    for(i=0; i<star->numDataBlock; i++) {
        for(j=0; j<star->block[i].numDataItem; j++) {
            if(NULL==block) {
                if(0==strcmp(star->block[i].data[j].key, dataKey)) {
                    *blockIndex = i;
                    *dataIndex  = j;
                    return *dataIndex;
                }
            } else {
                if((0==strcmp(star->block[i].data[j].key,   dataKey))
                 &&(0==strcmp(star->block[i].dataBlockName, block))) {
                    *blockIndex = i;
                    *dataIndex  = j;
                    return *dataIndex;
                }
            }
        }
    }
    return -1;
}

char** 
eosStarFileDataGetStringP(eosStarFile* star, char* block, char* key, int mode)
{
    int bIndex, dIndex, rval;

    rval = eosStarFileDataGetIndex(star, block, key, &bIndex, &dIndex, mode);  
    if(0<=rval) {
        return star->block[bIndex].data[dIndex].valueS;
    } else {
        return NULL;
    }
}

char*
eosStarFileDataGetString(eosStarFile* star, char* block, char* key, char** value, int mode)
{
    int bIndex, dIndex, rval;

    rval = eosStarFileDataGetIndex(star, block, key, &bIndex, &dIndex, mode);  
    if(0<=rval) {
        value[0] = star->block[bIndex].data[dIndex].valueS[0];
    } else {
        fprintf(stderr, "NO Data: %s %s\n", block, key);
        exit(EXIT_FAILURE);
    }
    return value[0];
}

double* 
eosStarFileDataGetRealP(eosStarFile* star, char* block, char* key, int mode)
{
    int bIndex, dIndex, rval;

    rval = eosStarFileDataGetIndex(star, block, key, &bIndex, &dIndex, mode);  
    if(0<=rval) {
        return star->block[bIndex].data[dIndex].valueR;
    } else {
        return NULL;
    }
}

double
eosStarFileDataGetReal(eosStarFile* star, char* block, char* key, double* value, int mode)
{
    int bIndex, dIndex, rval;

    rval = eosStarFileDataGetIndex(star, block, key, &bIndex, &dIndex, mode);  
    if(0<=rval) {
        *value = star->block[bIndex].data[dIndex].valueR[0];
    } else {
        fprintf(stderr, "NO Data: %s %s\n", block, key);
        exit(EXIT_FAILURE);
    }
    return *value;
}

int*
eosStarFileDataGetIntergerP(eosStarFile* star, char* block, char* key, int mode)
{
    int bIndex, dIndex, rval;

    rval = eosStarFileDataGetIndex(star, block, key, &bIndex, &dIndex, mode);  
    if(0<=rval) {
        return star->block[bIndex].data[dIndex].valueI;
    } else {
        return NULL;
    }
}

int
eosStarFilDataGetInterger(eosStarFile* star, char* block, char* key, int* value, int mode)
{
    int bIndex, dIndex, rval;

    rval = eosStarFileDataGetIndex(star, block, key, &bIndex, &dIndex, mode);  
    if(0<=rval) {
        *value = star->block[bIndex].data[dIndex].valueI[0];
    } else {
        fprintf(stderr, "NO Data: %s %s\n", block, key);
        exit(EXIT_FAILURE);
    }
    return *value;
}
