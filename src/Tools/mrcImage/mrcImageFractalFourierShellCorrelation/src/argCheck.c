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
argCheck(mrcImageFractalFourierShellCorrelationInfo* info, int argc, char* argv[])
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
                SCASE("r") {
                    if(i+1<argc) {
                        info->Ref = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagRef++;
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
                SCASE("t") {
                    if(i+1<argc) {
                        info->Threshold = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagThreshold++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sx") {
                    if(i+1<argc) {
                        info->stepx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstepx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sy") {
                    if(i+1<argc) {
                        info->stepy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstepy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sz") {
                    if(i+1<argc) {
                        info->stepz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagstepz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxN") {
                    if(i+1<argc) {
                        info->maxN = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxN++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("scaling") {
                    if(i+1<argc) {
                        info->scaling = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagscaling++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("get") {
                    if(i+1<argc) {
                        info->getMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flaggetMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Log") {
                    if(i+1<argc) {
                        info->Log = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagLog++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("xmin") {
                    if(i+1<argc) {
                        info->xmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ymin") {
                    if(i+1<argc) {
                        info->ymin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagymin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zmin") {
                    if(i+1<argc) {
                        info->zmin = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("xmax") {
                    if(i+1<argc) {
                        info->xmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagxmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ymax") {
                    if(i+1<argc) {
                        info->ymax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagymax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("zmax") {
                    if(i+1<argc) {
                        info->zmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagzmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+1<argc) {
                        info->densityThreshold = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdensityThreshold++;
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
