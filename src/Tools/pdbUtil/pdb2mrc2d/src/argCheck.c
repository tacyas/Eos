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
argCheck(pdb2mrc2dInfo* info, int argc, char* argv[])
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
                        info->Out3D = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagOut3D++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("d") {
                    if(i+2<argc) {
                        info->dx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdx++;
                        info->dy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("s") {
                    if(i+2<argc) {
                        info->sx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsx++;
                        info->sy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("n") {
                    if(i+2<argc) {
                        info->nx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnx++;
                        info->ny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagny++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot") {
                    if(i+2<argc) {
                        info->rotnx = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrotnx++;
                        info->rotny = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagrotny++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("S") {
                    if(i+3<argc) {
                        info->srotx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsrotx++;
                        info->sroty = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsroty++;
                        info->srotz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsrotz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("startEA") {
                    if(i+4<argc) {
                        info->sRotMode = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagsRotMode++;
                        info->sRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsRot1++;
                        info->sRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsRot2++;
                        info->sRot3 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsRot3++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EAMode") {
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
                SCASE("EARot1") {
                    if(i+3<argc) {
                        info->dRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot1++;
                        info->minRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminRot1++;
                        info->maxRot1 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxRot1++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("EARot2") {
                    if(i+3<argc) {
                        info->dRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRot2++;
                        info->minRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagminRot2++;
                        info->maxRot2 = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmaxRot2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("w") {
                    if(i+1<argc) {
                        info->Weight = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sig") {
                    if(i+1<argc) {
                        info->Sigma = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSigma++;
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
