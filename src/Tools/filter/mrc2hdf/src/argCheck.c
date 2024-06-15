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
argCheck(mrc2hdfInfo* info, int argc, char* argv[])
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
                        info->InListList = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInList++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I2") {
                    if(i+1<argc) {
                        info->InList2List = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagInList2++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Icolor") {
                    if(i+4<argc) {
                        info->IR = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIR++;
                        info->IG = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIG++;
                        info->IB = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIB++;
                        info->IA = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagIA++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("I2color") {
                    if(i+4<argc) {
                        info->I2R = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagI2R++;
                        info->I2G = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagI2G++;
                        info->I2B = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagI2B++;
                        info->I2A = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagI2A++;
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
                SCASE("nres") {
                    if(i+1<argc) {
                        info->nResolution = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flagnResolution++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("M") {
                    if(i+1<argc) {
                        info->hdf5mode = stringGetNthIntegerData(argv[i+1], 1, " ,");
                        i++;
                        info->flaghdf5mode++;
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
