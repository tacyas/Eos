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
argCheck(mrcMultiFFTCentralSectionsCompareInfo* info, int argc, char* argv[])
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
                        info->In2D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i3d") {
                    if(i+2<argc) {
                        info->In3D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn3D++;
                        info->volPath = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagvolPath++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Prior") {
                    if(i+2<argc) {
                        info->Prior = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagPrior++;
                        info->PriPath = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagPriPath++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EulerMode") {
                    if(i+1<argc) {
                        info->EulerMode = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagEulerMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot1") {
                    if(i+3<argc) {
                        info->Rot1Start = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1Start++;
                        info->Rot1End = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1End++;
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
                        info->Rot2Start = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2Start++;
                        info->Rot2End = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2End++;
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
                        info->Rot3Start = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3Start++;
                        info->Rot3End = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3End++;
                        info->Rot3Delta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3Delta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("trans") {
                    if(i+2<argc) {
                        info->TransX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagTransX++;
                        info->TransY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagTransY++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("InterpMode") {
                    if(i+1<argc) {
                        info->InterpMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagInterpMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o") {
                    if(i+1<argc) {
                        info->Out1 = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("oL") {
                    if(i+1<argc) {
                        info->OutLikelihood = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutLikelihood++;
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
                SCASE("Lmode") {
                    if(i+3<argc) {
                        info->Lcalcmode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLcalcmode++;
                        info->Lmode1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLmode1++;
                        info->Lmode2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagLmode2++;
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
