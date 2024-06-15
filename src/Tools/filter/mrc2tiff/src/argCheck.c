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
argCheck(mrc2tiffInfo* info, int argc, char* argv[])
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
                SCASE("H") {
                    if(i+1<argc) {
                        info->High = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagHigh++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("L") {
                    if(i+1<argc) {
                        info->Low = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLow++;
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
                SCASE("raw") {
                    if(i+0<argc) {
                        info->raw++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("offset") {
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
                SCASE("Z") {
                    if(i+1<argc) {
                        info->Z = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZ++;
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
                SCASE("e") {
                    if(i+1<argc) {
                        info->format = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagformat++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("color") {
                    if(i+1<argc) {
                        info->colorMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcolorMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("colorRange") {
                    if(i+2<argc) {
                        info->colorRangeMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcolorRangeMin++;
                        info->colorRangeMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcolorRangeMax++;
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
