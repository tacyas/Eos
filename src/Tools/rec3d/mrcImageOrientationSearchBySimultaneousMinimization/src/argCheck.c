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
argCheck(mrcImageOrientationSearchBySimultaneousMinimizationInfo* info, int argc, char* argv[])
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
                SCASE("dt") {
                    if(i+1<argc) {
                        info->dtheta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdtheta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dp") {
                    if(i+1<argc) {
                        info->dpsi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdpsi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ms") {
                    if(i+1<argc) {
                        info->ms = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagms++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ird") {
                    if(i+1<argc) {
                        info->ird = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagird++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("MC") {
                    if(i+1<argc) {
                        info->MC = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMC++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("FH") {
                    if(i+1<argc) {
                        info->FileNameHeader = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagFileNameHeader++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mid") {
                    if(i+1<argc) {
                        info->mid = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmid++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("iid") {
                    if(i+1<argc) {
                        info->InInitial = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInInitial++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("msp") {
                    if(i+1<argc) {
                        info->msp = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmsp++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maa") {
                    if(i+1<argc) {
                        info->maa = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaa++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("pdt") {
                    if(i+1<argc) {
                        info->pdtheta = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpdtheta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("pdp") {
                    if(i+1<argc) {
                        info->pdpsi = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpdpsi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mL") {
                    if(i+1<argc) {
                        info->modeL = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmodeL++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mTA") {
                    if(i+1<argc) {
                        info->modeTA = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmodeTA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mca") {
                    if(i+1<argc) {
                        info->modeCA = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmodeCA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("tca") {
                    if(i+1<argc) {
                        info->TCA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagTCA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("mf") {
                    if(i+1<argc) {
                        info->modeF = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmodeF++;
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
