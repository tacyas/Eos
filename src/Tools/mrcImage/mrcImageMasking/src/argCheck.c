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
argCheck(mrcImageMaskingInfo* info, int argc, char* argv[])
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
                SCASE("nx") {
                    if(i+1<argc) {
                        info->nx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("ny") {
                    if(i+1<argc) {
                        info->ny = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagny++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("nz") {
                    if(i+1<argc) {
                        info->nz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("cx") {
                    if(i+1<argc) {
                        info->cx = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcx++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("cy") {
                    if(i+1<argc) {
                        info->cy = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcy++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("cz") {
                    if(i+1<argc) {
                        info->cz = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagcz++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Rot") {
                    if(i+4<argc) {
                        info->Euler = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagEuler++;
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
                SCASE("Shape") {
                    if(i+1<argc) {
                        info->Shape = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagShape++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Soft") {
                    if(i+1<argc) {
                        info->Soft = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSoft++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("SoftWidth") {
                    if(i+1<argc) {
                        info->SoftWidth = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSoftWidth++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Normalize") {
                    if(i+1<argc) {
                        info->Normalize = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagNormalize++;
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
