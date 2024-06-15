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
argCheck(mrcImageFourierNeighborCorrelationInfo* info, int argc, char* argv[])
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
                SCASE("d") {
                    if(i+1<argc) {
                        info->delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("C") {
                    if(i+1<argc) {
                        info->Centre = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCentre++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->GetMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagGetMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("FSC") {
                    if(i+0<argc) {
                        info->FSC++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Cref") {
                    if(i+0<argc) {
                        info->Cref++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("FSCfull") {
                    if(i+0<argc) {
                        info->FSCfull++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NoiseWeighted") {
                    if(i+1<argc) {
                        info->Brestore = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBrestore++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mask") {
                    if(i+1<argc) {
                        info->InMask = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInMask++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maskBack") {
                    if(i+1<argc) {
                        info->InBackMask = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInBackMask++;
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