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
argCheck(mrcImageGLCMInfo* info, int argc, char* argv[])
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
                SCASE("O") {
                    if(i+1<argc) {
                        info->OutInfo = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("e") {
                    if(i+1<argc) {
                        info->epsilon = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagepsilon++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thresHigh") {
                    if(i+1<argc) {
                        info->thresHigh = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthresHigh++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thresLow") {
                    if(i+1<argc) {
                        info->thresLow = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthresLow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("exceptValue") {
                    if(i+1<argc) {
                        info->exceptValue = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagexceptValue++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("range") {
                    if(i+1<argc) {
                        info->range = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrange++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nHist") {
                    if(i+1<argc) {
                        info->nHist = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnHist++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("offset") {
                    if(i+1<argc) {
                        info->offset = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagoffset++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("angle") {
                    if(i+1<argc) {
                        info->angleMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagangleMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("areaX") {
                    if(i+2<argc) {
                        info->minAreaX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminAreaX++;
                        info->maxAreaX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxAreaX++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("areaY") {
                    if(i+2<argc) {
                        info->minAreaY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminAreaY++;
                        info->maxAreaY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxAreaY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("areaZ") {
                    if(i+2<argc) {
                        info->minAreaZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminAreaZ++;
                        info->maxAreaZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxAreaZ++;
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
