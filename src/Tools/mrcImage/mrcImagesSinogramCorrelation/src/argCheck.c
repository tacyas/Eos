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
argCheck(mrcImagesSinogramCorrelationInfo* info, int argc, char* argv[])
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
                SCASE("I") {
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
                SCASE("oH") {
                    if(i+1<argc) {
                        info->OutHeader = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutHeader++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rd") {
                    if(i+1<argc) {
                        info->Rd = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRd++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Nd") {
                    if(i+1<argc) {
                        info->Nd = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagNd++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("D1d") {
                    if(i+1<argc) {
                        info->D1d = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagD1d++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("D2d") {
                    if(i+1<argc) {
                        info->D2d = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagD2d++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ld") {
                    if(i+1<argc) {
                        info->Ld = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagLd++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CE") {
                    if(i+1<argc) {
                        info->CorrelationExtension = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagCorrelationExtension++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("LE") {
                    if(i+1<argc) {
                        info->ListExtension = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagListExtension++;
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
                SCASE("Nm") {
                    if(i+1<argc) {
                        info->Nmode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("D1m") {
                    if(i+1<argc) {
                        info->D1mode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagD1mode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("D2m") {
                    if(i+1<argc) {
                        info->D2mode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagD2mode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Lm") {
                    if(i+1<argc) {
                        info->Lmode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("LTM") {
                    if(i+1<argc) {
                        info->LengthThresholdMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLengthThresholdMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("LTR") {
                    if(i+1<argc) {
                        info->LengthThresholdRatio = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLengthThresholdRatio++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CM") {
                    if(i+1<argc) {
                        info->CM = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCM++;
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
