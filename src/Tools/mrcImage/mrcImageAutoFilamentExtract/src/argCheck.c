#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/config.h"
#include "genUtil.h"
#include "eosString.h"
#include "File.h"
#include "Memory.h"


void
argCheck(mrcImageAutoFilamentExtractInfo* info, int argc, char* argv[])
{
    long i;
    char s[1024];
    FILE* fpt;
    
    if(NULL==(fpt=fopen(".EosLog", "a+"))) { 
        
    } else {
        for(i=0; i<argc; i++) {
            fprintf(fpt, "%s ", argv[i]);
        }
        fprintf(fpt, "\n");
        fclose(fpt);
    }
    for(i=1; i<argc; i++) {
        if(OPTION_FLAG==argv[i][OPTION_FLAG_POS]) {
            SSWITCH(argv[i]+OPTION_POS)
                SCASE("i") {
                    if(i+1<argc) {
                        info->In = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("iS") {
                    if(i+1<argc) {
                        info->InS = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInS++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oE") {
                    if(i+1<argc) {
                        info->OutE = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutE++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+1<argc) {
                        info->Out = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oF") {
                    if(i+1<argc) {
                        info->OutF = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutF++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rROI") {
                    if(i+8<argc) {
                        info->blx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagblx++;
                        info->bly = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbly++;
                        info->brx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbrx++;
                        info->bry = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagbry++;
                        info->trx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtrx++;
                        info->try = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtry++;
                        info->tlx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtlx++;
                        info->tly = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtly++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rUnbent") {
                    if(i+1<argc) {
                        {
                        int j, nv, check, count, nitem;
                        nv    = argc - i - 1;
                        nitem = 1 ;
