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
argCheck(mrcImageSuperResolutionInfo* info, int argc, char* argv[])
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
                        info->InOriginal = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInOriginal++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("i") {
                    if(i+1<argc) {
                        info->InPrevious = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInPrevious++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ic") {
                    if(i+1<argc) {
                        info->FFTInCount = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagFFTInCount++;
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
                        info->t = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagt++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("fromp1") {
                    if(i+3<argc) {
                        info->x00 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagx00++;
                        info->y00 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagy00++;
                        info->z00 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagz00++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("top1") {
                    if(i+3<argc) {
                        info->x01 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagx01++;
                        info->y01 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagy01++;
                        info->z01 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagz01++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("fromp2") {
                    if(i+3<argc) {
                        info->x10 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagx10++;
                        info->y10 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagy10++;
                        info->z10 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagz10++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("top2") {
                    if(i+3<argc) {
                        info->x11 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagx11++;
                        info->y11 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagy11++;
                        info->z11 = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagz11++;
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
                SCASE("LabelingMode") {
                    if(i+1<argc) {
                        info->labelingmode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flaglabelingmode++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("max") {
                    if(i+1<argc) {
                        info->max = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("min") {
                    if(i+1<argc) {
                        info->min = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagmin++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sh") {
                    if(i+1<argc) {
                        info->shape = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagshape++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("hvp") {
                    if(i+1<argc) {
                        info->hvp = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flaghvp++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Inverse") {
                    if(i+0<argc) {
                        info->Inverse++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nM") {
                    if(i+1<argc) {
                        info->nMolecule = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnMolecule++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->MolecularWeight = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagMolecularWeight++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("D") {
                    if(i+1<argc) {
                        info->Density = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDensity++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("counter") {
                    if(i+1<argc) {
                        info->incounter = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagincounter++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dDensity") {
                    if(i+1<argc) {
                        info->deltaDens = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaDens++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dArea") {
                    if(i+1<argc) {
                        info->deltaArea = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdeltaArea++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("sub") {
                    if(i+1<argc) {
                        info->sub = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagsub++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ratio") {
                    if(i+1<argc) {
                        info->ratio = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagratio++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("tmax") {
                    if(i+1<argc) {
                        info->tmax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagtmax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("wd") {
                    if(i+1<argc) {
                        info->WeightDelta = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWeightDelta++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("wm") {
                    if(i+1<argc) {
                        info->WeightMax = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWeightMax++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Subtraction") {
                    if(i+0<argc) {
                        info->Subtraction++;
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
