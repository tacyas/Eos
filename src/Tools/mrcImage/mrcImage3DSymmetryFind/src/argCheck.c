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
argCheck(mrcImage3DSymmetryFindInfo* info, int argc, char* argv[])
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
                SCASE("a") {
                    if(i+1<argc) {
                        info->Avg = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagAvg++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+1<argc) {
                        info->ISGN = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagISGN++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("RotMode") {
                    if(i+1<argc) {
                        info->RotMode = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRotMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot1") {
                    if(i+3<argc) {
                        info->minRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminRot1++;
                        info->maxRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxRot1++;
                        info->dRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot2") {
                    if(i+3<argc) {
                        info->minRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminRot2++;
                        info->maxRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxRot2++;
                        info->dRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dCos") {
                    if(i+1<argc) {
                        info->dCos = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdCos++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CorMode") {
                    if(i+1<argc) {
                        info->corMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcorMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("OffsetMode") {
                    if(i+1<argc) {
                        info->OffsetMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOffsetMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("InterpolationMode") {
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
