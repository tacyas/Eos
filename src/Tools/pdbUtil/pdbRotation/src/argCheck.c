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
argCheck(pdbRotationInfo* info, int argc, char* argv[])
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
                SCASE("ZXY") {
                    if(i+3<argc) {
                        info->ZXYrotx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZXYrotx++;
                        info->ZXYroty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZXYroty++;
                        info->ZXYrotz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZXYrotz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ZYX") {
                    if(i+3<argc) {
                        info->ZYXrotx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZYXrotx++;
                        info->ZYXroty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZYXroty++;
                        info->ZYXrotz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagZYXrotz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("YXZ") {
                    if(i+3<argc) {
                        info->YXZrotx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagYXZrotx++;
                        info->YXZroty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagYXZroty++;
                        info->YXZrotz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagYXZrotz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("XYZ") {
                    if(i+3<argc) {
                        info->XYZrotx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagXYZrotx++;
                        info->XYZroty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagXYZroty++;
                        info->XYZrotz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagXYZrotz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EA") {
                    if(i+4<argc) {
                        info->RotMode = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRotMode++;
                        info->Rot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot1++;
                        info->Rot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot2++;
                        info->Rot3 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRot3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("cuda") {
                    if(i+1<argc) {
                        info->cudaDeviceID = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcudaDeviceID++;
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
