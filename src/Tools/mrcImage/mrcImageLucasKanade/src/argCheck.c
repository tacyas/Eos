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
argCheck(mrcImageLucasKanadeInfo* info, int argc, char* argv[])
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
                    if(i+3<argc) {
                        info->InVx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInVx++;
                        info->InVy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInVy++;
                        info->InVz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInVz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I") {
                    if(i+3<argc) {
                        info->InVxListList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInVxList++;
                        info->InVyListList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInVyList++;
                        info->InVzListList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInVzList++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i1") {
                    if(i+3<argc) {
                        info->In1Vx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn1Vx++;
                        info->In1Vy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn1Vy++;
                        info->In1Vz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn1Vz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i2") {
                    if(i+3<argc) {
                        info->In2Vx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2Vx++;
                        info->In2Vy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2Vy++;
                        info->In2Vz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2Vz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i3") {
                    if(i+3<argc) {
                        info->In3Vx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn3Vx++;
                        info->In3Vy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn3Vy++;
                        info->In3Vz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn3Vz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i4") {
                    if(i+3<argc) {
                        info->In4Vx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn4Vx++;
                        info->In4Vy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn4Vy++;
                        info->In4Vz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn4Vz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+3<argc) {
                        info->outVx = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagoutVx++;
                        info->outVy = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagoutVy++;
                        info->outVz = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagoutVz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nos") {
                    if(i+1<argc) {
                        info->NOS = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNOS++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oSize") {
                    if(i+1<argc) {
                        info->Size = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagSize++;
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
