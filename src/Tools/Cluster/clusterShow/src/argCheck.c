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
argCheck(clusterShowInfo* info, int argc, char* argv[])
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
                SCASE("i2") {
                    if(i+1<argc) {
                        info->In2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ib") {
                    if(i+1<argc) {
                        info->InB = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInB++;
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
                        info->Out2 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("PS") {
                    if(i+1<argc) {
                        info->OutPS = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutPS++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("OL") {
                    if(i+1<argc) {
                        info->OutOL = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutOL++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("OT") {
                    if(i+1<argc) {
                        info->TreeInfo = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagTreeInfo++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("AL") {
                    if(i+3<argc) {
                        info->OutAL = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutAL++;
                        info->OutALRange = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutALRange++;
                        info->OutALSuffix = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutALSuffix++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Last") {
                    if(i+1<argc) {
                        info->LastNum = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLastNum++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+2<argc) {
                        info->ShoulderScale = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShoulderScale++;
                        info->ArmScale = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagArmScale++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("P") {
                    if(i+2<argc) {
                        info->PosX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagPosX++;
                        info->PosY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagPosY++;
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
                SCASE("I") {
                    if(i+1<argc) {
                        info->InListList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInList++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Log") {
                    if(i+0<argc) {
                        info->Log++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Scaling") {
                    if(i+0<argc) {
                        info->Scaling++;
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
