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
argCheck(mrcImageAutoTrimingInfo* info, int argc, char* argv[])
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
                        info->OutParam = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutParam++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EAMode") {
                    if(i+1<argc) {
                        info->EAMode = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagEAMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot1") {
                    if(i+3<argc) {
                        info->Rot1Min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1Min++;
                        info->Rot1Max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1Max++;
                        info->Rot1Delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1Delta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot2") {
                    if(i+3<argc) {
                        info->Rot2Min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2Min++;
                        info->Rot2Max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2Max++;
                        info->Rot2Delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2Delta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot3") {
                    if(i+3<argc) {
                        info->Rot3Min = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3Min++;
                        info->Rot3Max = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3Max++;
                        info->Rot3Delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3Delta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->InterpolationMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagInterpolationMode++;
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
