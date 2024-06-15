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
argCheck(mrcImagePrintInfo* info, int argc, char* argv[])
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
                SCASE("H") {
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
                SCASE("L") {
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
                SCASE("Section") {
                    if(i+1<argc) {
                        info->section = argv[i+1][0];
                        i++;
                        info->flagsection++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("x") {
                    if(i+2<argc) {
                        info->xMin = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxMin++;
                        info->xMax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("y") {
                    if(i+2<argc) {
                        info->yMin = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagyMin++;
                        info->yMax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagyMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("z") {
                    if(i+2<argc) {
                        info->zMin = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzMin++;
                        info->zMax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+1<argc) {
                        info->Scale = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagScale++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("AS") {
                    if(i+1<argc) {
                        info->AbScale = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAbScale++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("E") {
                    if(i+1<argc) {
                        info->Enlarge = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagEnlarge++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("center") {
                    if(i+2<argc) {
                        info->cx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcx++;
                        info->cy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("C") {
                    if(i+1<argc) {
                        {
                        int j, nv, check, count, nitem;
                        nv    = argc - i - 1;
                        nitem = 1 ;
