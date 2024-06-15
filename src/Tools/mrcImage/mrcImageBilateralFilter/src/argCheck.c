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
argCheck(mrcImageBilateralFilterInfo* info, int argc, char* argv[])
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
                SCASE("sD") {
                    if(i+1<argc) {
                        info->SigmaDensity = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaDensity++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kTD") {
                    if(i+1<argc) {
                        info->KernelTypeDensity = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelTypeDensity++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sS") {
                    if(i+1<argc) {
                        info->SigmaSpace = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaSpace++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sS3") {
                    if(i+3<argc) {
                        info->SigmaSpaceX = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaSpaceX++;
                        info->SigmaSpaceY = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaSpaceY++;
                        info->SigmaSpaceZ = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigmaSpaceZ++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kTS") {
                    if(i+1<argc) {
                        info->KernelTypeSpace = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelTypeSpace++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kS") {
                    if(i+1<argc) {
                        info->KernelSize = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelSize++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kS3") {
                    if(i+3<argc) {
                        info->KernelSizeX = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelSizeX++;
                        info->KernelSizeY = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelSizeY++;
                        info->KernelSizeZ = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelSizeZ++;
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
