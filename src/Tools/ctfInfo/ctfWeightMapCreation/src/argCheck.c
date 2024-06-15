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
argCheck(ctfWeightMapCreationInfo* info, int argc, char* argv[])
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
                SCASE("kV") {
                    if(i+1<argc) {
                        info->kV = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagkV++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("Cs") {
                    if(i+1<argc) {
                        info->Cs = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagCs++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("df") {
                    if(i+1<argc) {
                        info->Defocus = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagDefocus++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("white") {
                    if(i+1<argc) {
                        info->WhiteNoise = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagWhiteNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("noise") {
                    if(i+1<argc) {
                        info->Noise = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagNoise++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("splusn") {
                    if(i+1<argc) {
                        info->SplusN = stringGetNthWord(argv[i+1], 1, " ,");
                        i++;
                        info->flagSplusN++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dRinv") {
                    if(i+1<argc) {
                        info->dRinv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRinv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("dRmaxInv") {
                    if(i+1<argc) {
                        info->dRmaxInv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagdRmaxInv++;
                    } else {
                        usage(argv[0]);
                        exit(EXIT_FAILURE);
                    }
                    SBREAK;
                }
                SCASE("SinWin") {
                    if(i+2<argc) {
                        info->SinWinRminInv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSinWinRminInv++;
                        info->SinWinRmaxInv = stringGetNthRealData(argv[i+1], 1, " ,");
                        i++;
                        info->flagSinWinRmaxInv++;
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
