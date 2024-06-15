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
argCheck(mrcImageAutoRotationAverageInfo* info, int argc, char* argv[])
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
                        info->InList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn++;
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
                SCASE("range") {
                    if(i+4<argc) {
                        info->Min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMin++;
                        info->Max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMax++;
                        info->Delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDelta++;
                        info->Iter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("iter") {
                    if(i+1<argc) {
                        info->iter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagiter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->CorMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCorMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Method") {
                    if(i+1<argc) {
                        info->Method = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMethod++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Periodic") {
                    if(i+0<argc) {
                        info->Periodic++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxIter") {
                    if(i+1<argc) {
                        info->maxIter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rmsd") {
                    if(i+1<argc) {
                        info->rmsd = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrmsd++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("log") {
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
                SCASE("thres") {
                    if(i+1<argc) {
                        info->Thres = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagThres++;
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
