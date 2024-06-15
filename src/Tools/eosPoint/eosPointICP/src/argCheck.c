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
argCheck(eosPointICPInfo* info, int argc, char* argv[])
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
                SCASE("it") {
                    if(i+1<argc) {
                        info->InType = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagInType++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("iMat") {
                    if(i+1<argc) {
                        info->InMat = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInMat++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->Ref = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rt") {
                    if(i+1<argc) {
                        info->RefType = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRefType++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rMat") {
                    if(i+1<argc) {
                        info->RefMat = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRefMat++;
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
                SCASE("ot") {
                    if(i+1<argc) {
                        info->OutType = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutType++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EAMode") {
                    if(i+1<argc) {
                        info->EAMode = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagEAMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("R") {
                    if(i+1<argc) {
                        info->Ratio = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRatio++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Iter") {
                    if(i+1<argc) {
                        info->IterationLimit = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIterationLimit++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Pattern") {
                    if(i+1<argc) {
                        info->Pattern = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagPattern++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Thres") {
                    if(i+1<argc) {
                        info->ScoreThreshold = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagScoreThreshold++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Omit") {
                    if(i+1<argc) {
                        info->Omit = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOmit++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Pick") {
                    if(i+1<argc) {
                        info->Pickup = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagPickup++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("flag2D") {
                    if(i+1<argc) {
                        info->flag2D = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagflag2D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("debug") {
                    if(i+1<argc) {
                        info->Debug = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDebug++;
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
