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
argCheck(mrcImageTiltAxisSearchHelpInfo* info, int argc, char* argv[])
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
                SCASE("o1d") {
                    if(i+1<argc) {
                        info->Out1D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut1D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o1de") {
                    if(i+1<argc) {
                        info->Out1DEnlarged = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut1DEnlarged++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("o2d") {
                    if(i+1<argc) {
                        info->Out2D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut2D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("aP") {
                    if(i+3<argc) {
                        info->OriginX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOriginX++;
                        info->OriginY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOriginY++;
                        info->OriginZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagOriginZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("a") {
                    if(i+2<argc) {
                        info->AxisAngleYaw = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAxisAngleYaw++;
                        info->AxisAnglePitch = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagAxisAnglePitch++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("R") {
                    if(i+2<argc) {
                        info->Rmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRmin++;
                        info->Rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Interp") {
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
