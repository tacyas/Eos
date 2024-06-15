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
argCheck(mrcImageDeconvolutionInfo* info, int argc, char* argv[])
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
                SCASE("k") {
                    if(i+1<argc) {
                        info->Kernel = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernel++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("kcentre") {
                    if(i+1<argc) {
                        info->KernelCentre = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagKernelCentre++;
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
                SCASE("oconv") {
                    if(i+1<argc) {
                        info->OutConv = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutConv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("O") {
                    if(i+1<argc) {
                        info->OutASCII = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutASCII++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ORMSD") {
                    if(i+1<argc) {
                        info->OutRMSD = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOutRMSD++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("thresCTF") {
                    if(i+1<argc) {
                        info->thresCTF = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagthresCTF++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NSRatio") {
                    if(i+1<argc) {
                        info->NSRatio = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNSRatio++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("NSCoeff") {
                    if(i+1<argc) {
                        info->NSCoeff = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNSCoeff++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Pad3DMode") {
                    if(i+1<argc) {
                        info->Pad3DMode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagPad3DMode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("r") {
                    if(i+1<argc) {
                        info->r = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagr++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("w") {
                    if(i+1<argc) {
                        info->w = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagw++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("v") {
                    if(i+1<argc) {
                        info->v = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Floating") {
                    if(i+0<argc) {
                        info->Floating++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("maxIter") {
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
                SCASE("minRMSD") {
                    if(i+1<argc) {
                        info->minRMSD = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminRMSD++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("lambda") {
                    if(i+1<argc) {
                        info->lambda = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglambda++;
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
