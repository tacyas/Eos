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
argCheck(mrc2bildInfo* info, int argc, char* argv[])
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
                SCASE("i3") {
                    if(i+3<argc) {
                        info->In0 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn0++;
                        info->In1 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn1++;
                        info->In2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i4") {
                    if(i+4<argc) {
                        info->InX = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInX++;
                        info->InY = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInY++;
                        info->InZ = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInZ++;
                        info->InWeight = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInWeight++;
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
                SCASE("color") {
                    if(i+3<argc) {
                        info->Red = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRed++;
                        info->Green = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagGreen++;
                        info->Blue = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBlue++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zoom") {
                    if(i+1<argc) {
                        info->Zoom = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZoom++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("arrow") {
                    if(i+3<argc) {
                        info->R1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagR1++;
                        info->R2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagR2++;
                        info->Rho = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRho++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("skip") {
                    if(i+3<argc) {
                        info->skipX = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagskipX++;
                        info->skipY = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagskipY++;
                        info->skipZ = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagskipZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rainbow") {
                    if(i+1<argc) {
                        info->RainbowMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRainbowMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rainbowThresLow") {
                    if(i+1<argc) {
                        info->RainbowThresLow = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRainbowThresLow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rainbowThresHigh") {
                    if(i+1<argc) {
                        info->RainbowThresHigh = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRainbowThresHigh++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rainbowRangeLow") {
                    if(i+1<argc) {
                        info->RainbowRangeLow = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRainbowRangeLow++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rainbowRangeHigh") {
                    if(i+1<argc) {
                        info->RainbowRangeHigh = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRainbowRangeHigh++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangeX") {
                    if(i+2<argc) {
                        info->RangeXMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeXMin++;
                        info->RangeXMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeXMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangeY") {
                    if(i+2<argc) {
                        info->RangeYMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeYMin++;
                        info->RangeYMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeYMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangeZ") {
                    if(i+2<argc) {
                        info->RangeZMin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeZMin++;
                        info->RangeZMax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeZMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rangeR") {
                    if(i+4<argc) {
                        info->RangeRCX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeRCX++;
                        info->RangeRCY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeRCY++;
                        info->RangeRCZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeRCZ++;
                        info->RangeRR = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRangeRR++;
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
