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
argCheck(tiff2mrcInfo* info, int argc, char* argv[])
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
                        info->inFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flaginFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+1<argc) {
                        info->outFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagoutFile++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->Resolution = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagResolution++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r3") {
                    if(i+3<argc) {
                        info->ResolutionX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagResolutionX++;
                        info->ResolutionY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagResolutionY++;
                        info->ResolutionZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagResolutionZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("t") {
                    if(i+1<argc) {
                        info->time = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtime++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+1<argc) {
                        info->dirnum = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdirnum++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+0<argc) {
                        info->Inverse++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Signed") {
                    if(i+0<argc) {
                        info->Signed++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Offset") {
                    if(i+1<argc) {
                        info->Offset = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOffset++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Max") {
                    if(i+1<argc) {
                        info->Max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Min") {
                    if(i+1<argc) {
                        info->Min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("realMin") {
                    if(i+1<argc) {
                        info->realMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrealMin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("realMax") {
                    if(i+1<argc) {
                        info->realMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrealMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("realMaxBit") {
                    if(i+1<argc) {
                        info->realMaxBit = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrealMaxBit++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sin") {
                    if(i+1<argc) {
                        info->sinFile = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagsinFile++;
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
                SCASE("S") {
                    if(i+1<argc) {
                        info->Shrink = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShrink++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->Mode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMode++;
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
