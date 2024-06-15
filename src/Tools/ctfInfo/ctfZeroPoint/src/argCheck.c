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
argCheck(ctfZeroPointInfo* info, int argc, char* argv[])
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
                SCASE("dR") {
                    if(i+1<argc) {
                        info->dR = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdR++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kV") {
                    if(i+1<argc) {
                        info->kV = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagkV++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Cs") {
                    if(i+1<argc) {
                        info->Cs = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCs++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("df") {
                    if(i+1<argc) {
                        info->Defocus = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDefocus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dfMin") {
                    if(i+1<argc) {
                        info->MinDefocus = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMinDefocus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dfMax") {
                    if(i+1<argc) {
                        info->MaxDefocus = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMaxDefocus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("deltadf") {
                    if(i+1<argc) {
                        info->DeltaDefocus = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDeltaDefocus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("A") {
                    if(i+1<argc) {
                        info->AoverP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAoverP++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("N") {
                    if(i+1<argc) {
                        info->N = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagN++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ain") {
                    if(i+1<argc) {
                        info->Ain = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ctfMode") {
                    if(i+1<argc) {
                        info->ctfMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagctfMode++;
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
