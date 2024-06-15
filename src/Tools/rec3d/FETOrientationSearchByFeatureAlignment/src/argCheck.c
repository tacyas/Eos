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
argCheck(FETOrientationSearchByFeatureAlignmentInfo* info, int argc, char* argv[])
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
                        info->InS = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInS++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i2") {
                    if(i+1<argc) {
                        info->InS2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInS2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+1<argc) {
                        info->InF = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInF++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ia") {
                    if(i+1<argc) {
                        info->InA = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInA++;
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
                SCASE("oclog") {
                    if(i+1<argc) {
                        info->OutLOG = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutLOG++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oa") {
                    if(i+1<argc) {
                        info->OutA = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o2d") {
                    if(i+1<argc) {
                        info->Out2D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut2D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("itm") {
                    if(i+1<argc) {
                        info->ITMAX = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagITMAX++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dvm") {
                    if(i+1<argc) {
                        info->DEVMAX = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDEVMAX++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mitm") {
                    if(i+1<argc) {
                        info->MITMAX = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMITMAX++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mdvm") {
                    if(i+1<argc) {
                        info->MDEVMAX = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMDEVMAX++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ldn") {
                    if(i+1<argc) {
                        info->LDN = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLDN++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("srl") {
                    if(i+1<argc) {
                        info->SRL = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSRL++;
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
