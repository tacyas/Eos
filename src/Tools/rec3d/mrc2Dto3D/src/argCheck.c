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
argCheck(mrc2Dto3DInfo* info, int argc, char* argv[])
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
                SCASE("I") {
                    if(i+1<argc) {
                        info->In2List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagIn2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("each") {
                    if(i+0<argc) {
                        info->each++;
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
                SCASE("Rmax") {
                    if(i+1<argc) {
                        info->Rmax = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagRmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("single") {
                    if(i+1<argc) {
                        info->single = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsingle++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("singleFilter") {
                    if(i+1<argc) {
                        info->singleFilter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsingleFilter++;
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
                SCASE("Double") {
                    if(i+0<argc) {
                        info->Double++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("DoubleCounter") {
                    if(i+1<argc) {
                        info->DoubleCounter = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagDoubleCounter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CounterThreshold") {
                    if(i+1<argc) {
                        info->CounterThreshold = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCounterThreshold++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CounterThresholdMode") {
                    if(i+1<argc) {
                        info->CounterThresholdMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCounterThresholdMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("WeightMode") {
                    if(i+1<argc) {
                        info->WeightMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWeightMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thicknessWeight") {
                    if(i+0<argc) {
                        info->thicknessWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Sub") {
                    if(i+1<argc) {
                        info->SubSampling = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSubSampling++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("PlusXrot") {
                    if(i+0<argc) {
                        info->PlusXrot++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("N") {
                    if(i+3<argc) {
                        info->Nx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNx++;
                        info->Ny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNy++;
                        info->Nz = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("SIRT") {
                    if(i+0<argc) {
                        info->SIRT++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("max") {
                    if(i+1<argc) {
                        info->maxIter = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxIter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("rms") {
                    if(i+1<argc) {
                        info->rms = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrms++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("CTF") {
                    if(i+1<argc) {
                        info->CTFInfoList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagCTFInfo++;
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
