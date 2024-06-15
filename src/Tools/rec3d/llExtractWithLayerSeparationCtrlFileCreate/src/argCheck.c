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
argCheck(llExtractWithLayerSeparationCtrlFileCreateInfo* info, int argc, char* argv[])
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
                SCASE("t") {
                    if(i+1<argc) {
                        info->Turn = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagTurn++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("u") {
                    if(i+1<argc) {
                        info->Unit = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagUnit++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("N") {
                    if(i+1<argc) {
                        info->nHelix = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnHelix++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dY") {
                    if(i+1<argc) {
                        info->dY = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("truePitch") {
                    if(i+1<argc) {
                        info->truePitch = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtruePitch++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rMax") {
                    if(i+1<argc) {
                        info->rMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RMax") {
                    if(i+1<argc) {
                        info->RMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RZMax") {
                    if(i+1<argc) {
                        info->RZMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRZMax++;
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
