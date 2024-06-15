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
argCheck(mrcRefHeaderCreateInfo* info, int argc, char* argv[])
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
                SCASE("p") {
                    if(i+3<argc) {
                        info->iP = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagiP++;
                        info->iW = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagiW++;
                        info->iA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagiA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("w") {
                    if(i+3<argc) {
                        info->Wp = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWp++;
                        info->Ww = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWw++;
                        info->Wa = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWa++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+3<argc) {
                        info->Dp = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDp++;
                        info->Dw = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDw++;
                        info->Da = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDa++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sy") {
                    if(i+1<argc) {
                        info->Sy = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ey") {
                    if(i+1<argc) {
                        info->Ey = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagEy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("refsize") {
                    if(i+1<argc) {
                        info->Refsize = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRefsize++;
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
