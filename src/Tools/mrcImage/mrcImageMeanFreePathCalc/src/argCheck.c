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
argCheck(mrcImageMeanFreePathCalcInfo* info, int argc, char* argv[])
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
                SCASE("Owall") {
                    if(i+1<argc) {
                        info->OutWhiteAll = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutWhiteAll++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ow") {
                    if(i+1<argc) {
                        info->OutWhite = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutWhite++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Oball") {
                    if(i+1<argc) {
                        info->OutBlackAll = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutBlackAll++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Ob") {
                    if(i+1<argc) {
                        info->OutBlack = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutBlack++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Owe") {
                    if(i+1<argc) {
                        info->OutWhiteEdge = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutWhiteEdge++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Obe") {
                    if(i+1<argc) {
                        info->OutBlackEdge = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutBlackEdge++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Odir") {
                    if(i+1<argc) {
                        info->Direction = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagDirection++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lt") {
                    if(i+2<argc) {
                        info->LineThicknessX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLineThicknessX++;
                        info->LineThicknessY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLineThicknessY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lm") {
                    if(i+1<argc) {
                        info->LineMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLineMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ls") {
                    if(i+1<argc) {
                        info->LineShape = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLineShape++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("deltaPhi") {
                    if(i+1<argc) {
                        info->deltaPhi = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaPhi++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("deltaTheta") {
                    if(i+1<argc) {
                        info->deltaTheta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaTheta++;
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
