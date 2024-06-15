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
argCheck(mrcImageCrystalCreateInfo* info, int argc, char* argv[])
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
                SCASE("nx") {
                    if(i+1<argc) {
                        info->nx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ny") {
                    if(i+1<argc) {
                        info->ny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagny++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nz") {
                    if(i+1<argc) {
                        info->nz = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("start") {
                    if(i+3<argc) {
                        info->StartX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStartX++;
                        info->StartY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStartY++;
                        info->StartZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagStartZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("A") {
                    if(i+3<argc) {
                        info->AX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAX++;
                        info->AY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAY++;
                        info->AZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("B") {
                    if(i+3<argc) {
                        info->BX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBX++;
                        info->BY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBY++;
                        info->BZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagBZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("C") {
                    if(i+3<argc) {
                        info->CX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCX++;
                        info->CY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCY++;
                        info->CZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCZ++;
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
