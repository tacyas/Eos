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
argCheck(llDataSeparateInfo* info, int argc, char* argv[])
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
                SCASE("o1") {
                    if(i+1<argc) {
                        info->SepNea = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagSepNea++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o2") {
                    if(i+1<argc) {
                        info->SepFar = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagSepFar++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("O1") {
                    if(i+1<argc) {
                        info->MixNea = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagMixNea++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("O2") {
                    if(i+1<argc) {
                        info->MixFar = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagMixFar++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("delRInv") {
                    if(i+1<argc) {
                        info->delRInv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdelRInv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("truePitch") {
                    if(i+1<argc) {
                        info->truePitch = stringGetNthRealData(argv[i+1], 1, " ,");
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
                SCASE("xShift") {
                    if(i+1<argc) {
                        info->xShift = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxShift++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("L") {
                    if(i+1<argc) {
                        info->Log = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagLog++;
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
