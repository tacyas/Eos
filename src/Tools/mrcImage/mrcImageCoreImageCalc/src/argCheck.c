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
argCheck(mrcImageCoreImageCalcInfo* info, int argc, char* argv[])
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
                SCASE("el") {
                    if(i+1<argc) {
                        info->EL = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagEL++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("bg") {
                    if(i+1<argc) {
                        info->BGList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagBG++;
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
                SCASE("O") {
                    if(i+1<argc) {
                        info->OutBG = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutBG++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Chi") {
                    if(i+1<argc) {
                        info->OutChi = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutChi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("initial") {
                    if(i+3<argc) {
                        info->A1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagA1++;
                        info->A2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagA2++;
                        info->A3 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagA3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("limitA3") {
                    if(i+2<argc) {
                        info->LimitA3Min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLimitA3Min++;
                        info->LimitA3Max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLimitA3Max++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("baseEELS") {
                    if(i+1<argc) {
                        info->BaseEELS = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBaseEELS++;
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
