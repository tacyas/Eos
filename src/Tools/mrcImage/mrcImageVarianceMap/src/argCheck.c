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
argCheck(mrcImageVarianceMapInfo* info, int argc, char* argv[])
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
                        info->InList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+3<argc) {
                        info->In2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                        info->In2Var = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2Var++;
                        info->In2N = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2N++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Nor") {
                    if(i+2<argc) {
                        info->NorA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNorA++;
                        info->NorB = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNorB++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->RefList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("R") {
                    if(i+3<argc) {
                        info->Ref2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef2++;
                        info->Ref2Var = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef2Var++;
                        info->Ref2N = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef2N++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NorR") {
                    if(i+2<argc) {
                        info->NorARef = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNorARef++;
                        info->NorBRef = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNorBRef++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("IR") {
                    if(i+3<argc) {
                        info->InAndRef2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInAndRef2++;
                        info->InAndRef2Var = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInAndRef2Var++;
                        info->InAndRef2N = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagInAndRef2N++;
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
                SCASE("v") {
                    if(i+1<argc) {
                        info->OutV = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutV++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("c") {
                    if(i+1<argc) {
                        info->configFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagconfigFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("m") {
                    if(i+1<argc) {
                        info->mode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("h") {
                    usage(argv[0]);
                    exit(EXIT_SUCCESS);
                    break;
                }
                SCASE("html") {
                    htmlBeforeUsage(argv[0]);
                    usage(argv[0]);
                    htmlAfterUsage(argv[0]);
                    exit(EXIT_SUCCESS);
                    break;
                }
                SDEFAULT {
                    fprintf(stderr, "Not Supported Options: :%s\n", argv[i]);
                    usage(argv[0]);
                    exit(EXIT_FAILURE);
                    break;
                }
            SSWITCHEND;
        } 
    } 
} 
