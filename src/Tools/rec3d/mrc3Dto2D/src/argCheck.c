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
argCheck(mrc3Dto2DInfo* info, int argc, char* argv[])
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
                SCASE("fileList") {
                    if(i+3<argc) {
                        info->filenamePrefix = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagfilenamePrefix++;
                        info->filenameSuffix = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagfilenameSuffix++;
                        info->filenameFormat = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagfilenameFormat++;
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
                SCASE("AreaMode") {
                    if(i+1<argc) {
                        info->AreaMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAreaMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("pthread") {
                    if(i+1<argc) {
                        info->pthreadMax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagpthreadMax++;
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
